#include "DMX.hpp"

void DMX::begin(const Config &cfg, const Network *_network)
{
    universe = cfg.getUniverse();
    network = _network;
    useUnicast = cfg.getUseUnicast();
    unicastDestination = cfg.getUnicastIp().toString();
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
        sender.setArtDmxData(dmxData.data(), dmxData.size());
        if (useUnicast)
        {
            sender.streamArtDmxTo(unicastDestination, universe);
        }
        else
        {
            sender.streamArtDmxTo(network->getBroadcastAddress().toString(), universe);
        }
    }
}