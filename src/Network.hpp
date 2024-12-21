#pragma once
#include <ArtnetWiFi.h>
#include <array>

class Network
{
public:
    Network(uint16_t universe, const String &destination);

    void setChannel(uint16_t channel, uint8_t value);
    void update();

private:
    uint16_t universe;
    String destination;
    std::array<uint8_t, 512> dmxData{};
    ArtnetWiFiSender sender;
};
