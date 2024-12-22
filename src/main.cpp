#include <Arduino.h>
#include "WiFi.h"
#include "Config.hpp"
#include "Network.hpp"
#include "IOHandler.hpp"
#include "Ui.hpp"
#include <ESPmDNS.h>
#include <DNSServer.h>

#define SSID "Unten"
#define PASS "XBueLkpWnLUdeffx"
#define AP_SSID "ArtNet-GPIO"

#define HOTSPOT_MODE_PIN 25

// put function declarations here:
void setupNormalMode(Config *cfg);
void setupHotspotMode();

Preferences preferences;
Config *config;
Network *network;
IOHandler *ioHandler;
Ui *ui;

DNSServer *dnsServer; // this is only used in hotspot mode

void setupNormalMode(Config *cfg)
{
  if (!cfg->getUseDHCP())
  {
    WiFi.config(cfg->getStaticIp(), cfg->getStaticGateway(), cfg->getStaticSubnet());
  }

  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Subnet Mask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
  Serial.print("Broadcast IP: ");
  Serial.println(WiFi.broadcastIP());

  String hostname = "artnet-gpio-" + String(ESP.getEfuseMac(), HEX);

  if (!MDNS.begin(hostname.c_str()))
  {
    Serial.println("Error setting up MDNS responder!");
    while (1)
    {
      delay(1000);
    }
  }

  MDNS.addService("artnet", "udp", 6454);

  Serial.print("mDNS name: ");
  Serial.println(hostname + ".local");
}

// hotspot mode is used as fallback for configuration.
// It is not intended to be used as a permanent mode.
void setupHotspotMode()
{

  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_SSID); // Remove password parameter to create an open network

  Serial.println("Access Point Mode");
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  dnsServer = new DNSServer();
  dnsServer->setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer->setTTL(300);
  // DNSServer is started serving any "*" domain name. It will reply
  // AccessPoint's IP to all DNS request and the ESPUI will catch all requests and redirect them to the root page
  dnsServer->start(53, "*", WiFi.softAPIP());
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting gpio artnet sender");

  pinMode(HOTSPOT_MODE_PIN, INPUT_PULLUP);

  preferences.begin("cfg", false);
  config = new Config(preferences);
  config->print();

  const bool enableHotspot = digitalRead(HOTSPOT_MODE_PIN) == LOW;
  if (enableHotspot)
  {
    setupHotspotMode();
  }
  else
  {
    // Normal mode
    setupNormalMode(config);
  }
  const auto targetIp = WiFi.broadcastIP();
  network = new Network(config->getUniverse(), targetIp.toString());

  ioHandler = new IOHandler();
  ioHandler->addChangedCb([](uint8_t pin, uint8_t index, bool value)
                          { network->setChannel(index, value ? 255 : 0); });

  ui = new Ui(ioHandler, config);
}

void loop()
{
  // dnsServer only exists when in hotspot config mode
  if (dnsServer)
  {
    dnsServer->processNextRequest();
  }

  ioHandler->update();
  network->update();
}
