#include "Network.hpp"
#include <ESPmDNS.h>
// Important to be defined BEFORE including ETH.h for ETH.begin() to work.
/*
 * ETH_CLOCK_GPIO0_IN   - default: external clock from crystal oscillator
 * ETH_CLOCK_GPIO0_OUT  - 50MHz clock from internal APLL output on GPIO0 - possibly an inverter is needed for LAN8720
 * ETH_CLOCK_GPIO16_OUT - 50MHz clock from internal APLL output on GPIO16 - possibly an inverter is needed for LAN8720
 * ETH_CLOCK_GPIO17_OUT - 50MHz clock from internal APLL inverted output on GPIO17 - tested with LAN8720
 */
#define ETH_CLK_MODE ETH_CLOCK_GPIO0_IN //  ETH_CLOCK_GPIO17_OUT

// Pin# of the enable signal for the external crystal oscillator (-1 to disable for internal APLL source)
#define ETH_PHY_POWER 16

// Type of the Ethernet PHY (LAN8720 or TLK110)
#define ETH_PHY_TYPE ETH_PHY_LAN8720

// I²C-address of Ethernet PHY (0 or 1 for LAN8720, 31 for TLK110)
#define ETH_PHY_ADDR 1

// Pin# of the I²C clock signal for the Ethernet PHY
#define ETH_PHY_MDC 23

// Pin# of the I²C IO signal for the Ethernet PHY
#define ETH_PHY_MDIO 18

#include <ETH.h>
#include <WiFi.h>
#include <Arduino.h>
#include <ESPmDNS.h>

#define AP_SSID "ArtNet-GPIO"

void Network::handleNetworkEvent(WiFiEvent_t event)
{
    Serial.println("WiFi event: " + String(event));
    switch (event)
    {

    case ARDUINO_EVENT_ETH_START:
        Serial.println("ETH Started");
        ETH.setHostname(hostname.c_str());
        break;

    case ARDUINO_EVENT_ETH_CONNECTED:
        Serial.println("ETH Connected");
        break;

    case ARDUINO_EVENT_ETH_GOT_IP:
        if (!connected)
        {
            Serial.print("ETH MAC: ");
            Serial.print(ETH.macAddress());
            Serial.print(", IPv4: ");
            Serial.println(ETH.localIP());

            if (ETH.fullDuplex())
            {
                Serial.print("FULL_DUPLEX, ");
            }
            else
            {
                Serial.print("HALF_DUPLEX, ");
            }
            Serial.print(ETH.linkSpeed());
            connected = true;
        }

        break;

    case ARDUINO_EVENT_ETH_DISCONNECTED:
        Serial.println("ETH Disconnected");
        connected = false;
        break;

    case ARDUINO_EVENT_ETH_STOP:
        Serial.println("ETH Stopped");
        connected = false;
        break;
    default:
        // lots of other events that we do not care about
        break;
    }
}

void Network::begin(const Config &cfg, bool isHotspot)
{

    hostname = "artnet-gpio-" + String(ESP.getEfuseMac(), HEX);

    if (isHotspot)
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
    else
    {
        WiFi.onEvent([this](WiFiEvent_t event, WiFiEventInfo_t /*info*/)
                     { this->handleNetworkEvent(event); });
        ETH.begin(ETH_PHY_ADDR, ETH_PHY_POWER, ETH_PHY_MDC, ETH_PHY_MDIO, ETH_PHY_TYPE, ETH_CLK_MODE);
    }
    MDNS.begin(hostname.c_str());
    MDNS.addService("artnet", "udp", 6454);

    Serial.println("mDNS hostname: " + hostname + ".local");
}

IPAddress Network::getBroadcastAddress() const
{
    // TODO this does not work in hotspot mode. but does it have to? hotspot is only for config
    return ETH.broadcastIP();
}

void Network::update()
{
    if (dnsServer)
    {
        dnsServer->processNextRequest();
    }
}