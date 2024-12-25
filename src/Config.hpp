#include <Preferences.h>
#include <Arduino.h>
#pragma once

class Config
{
public:
    void begin();

    const IPAddress &getStaticIp() const;
    void setStaticIp(const IPAddress &ip);

    const IPAddress &getStaticSubnet() const;
    void setStaticSubnet(const IPAddress &subnet);

    const IPAddress &getStaticGateway() const;
    void setStaticGateway(const IPAddress &gateway);

    bool getUseDHCP() const;
    void setUseDHCP(bool useDHCP);

    uint16_t getUniverse() const;
    void setUniverse(uint16_t universe);

    void print();

private:
    Preferences preferences;

    IPAddress staticIp;
    IPAddress staticSubnet;
    IPAddress staticGateway;
    bool useDHCP;
    uint16_t universe;
};