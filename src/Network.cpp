#include "Network.hpp"

Network::Network(uint16_t universe, const String &destination) : universe{universe}, destination{destination}
{
    sender.begin();
    sender.setArtDmxData(dmxData.data(), dmxData.size());
}

void Network::setChannel(uint16_t channel, uint8_t value)
{
    dmxData[channel] = value;
}

void Network::update()
{
    sender.setArtDmxData(dmxData.data(), dmxData.size());
    sender.streamArtDmxTo(destination, universe);
}