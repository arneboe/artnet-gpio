#include "DMX.hpp"

void DMX::begin(const Config &cfg, const Network *_network)
{
    universe = cfg.getUniverse();
    network = _network;
    sender.begin();
    sender.setArtDmxData(dmxData.data(), dmxData.size());
}

void DMX::setChannel(uint16_t channel, uint8_t value)
{
    dmxData[channel] = value;
}

void DMX::update()
{
    if (network->isConnected())
    {
        const String destination = network->getBroadcastAddress().toString();
        sender.setArtDmxData(dmxData.data(), dmxData.size());
        sender.streamArtDmxTo(destination, universe);
    }
}