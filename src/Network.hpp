#pragma once
#include <WiFiGeneric.h>
#include <DNSServer.h>
#include "Config.hpp"

class Network
{
public:
    void begin(const Config &cfg, bool isHotspot);
    void update();

    bool isConnected() const { return connected; }

    IPAddress getBroadcastAddress() const;

private:
    void handleNetworkEvent(WiFiEvent_t event);
    bool connected = false;
    DNSServer *dnsServer; // this is only used in hotspot mode
    String hostname;
};