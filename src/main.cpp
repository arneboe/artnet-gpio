#include <Arduino.h>
#include "WiFi.h"
#include "Config.hpp"
#include "Network.hpp"
#include "IOHandler.hpp"
#include "Ui.hpp"
#include <ESPmDNS.h>

#define SSID "Unten"
#define PASS "XBueLkpWnLUdeffx"

// put function declarations here:

Preferences preferences;
Config *config;
Network *network;
IOHandler *ioHandler;
Ui *ui;

void setupNetwork(Config *cfg)
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

  // Initialize mDNS with MAC address
  String macAddress = WiFi.macAddress();
  macAddress.replace(":", ""); // Remove colons from MAC
  String hostname = "artnet-gpio-" + macAddress;

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
  Serial.println(hostname);
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting gpio artnet sender");

  preferences.begin("cfg", false);
  config = new Config(preferences);
  config->print();

  setupNetwork(config);

  const auto targetIp = WiFi.broadcastIP();
  network = new Network(config->getUniverse(), targetIp.toString());

  ioHandler = new IOHandler([](uint8_t pin, bool value)
                            { network->setChannel(pin, value ? 255 : 0); });

  ui = new Ui({13}, config);
}

void loop()
{
  ioHandler->update();
  network->update();
}
