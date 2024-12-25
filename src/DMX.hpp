#pragma once
#include <ArtnetETH.h>
#include <array>
#include "Config.hpp"
#include "Network.hpp"

class DMX
{
public:
    void begin(const Config &cfg, const Network *network);

    void setChannel(uint16_t channel, uint8_t value);
    void update();

private:
    uint16_t universe;
    String destination;
    std::array<uint8_t, 512> dmxData{};
    ArtnetSender sender;
    const Network *network;
};
