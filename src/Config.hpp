#include <Preferences.h>
#include <Arduino.h>
#include <vector>
#pragma once

class Config
{
public:
    void begin(uint8_t numPins);

    const IPAddress &getStaticIp() const;
    void setStaticIp(const IPAddress &ip);

    const IPAddress &getStaticSubnet() const;
    void setStaticSubnet(const IPAddress &subnet);

    const IPAddress &getStaticGateway() const;
    void setStaticGateway(const IPAddress &gateway);

    const IPAddress &getUnicastIp() const;
    void setUnicastIp(const IPAddress &ip);

    bool getUseDHCP() const;
    void setUseDHCP(bool useDHCP);

    bool getUseUnicast() const;
    void setUseUnicast(bool useUnicast);

    uint16_t getUniverse() const;
    void setUniverse(uint16_t universe);

    uint8_t getPinLowValue(uint8_t pin) const;
    void setPinLowValue(uint8_t pin, uint8_t value);

    uint8_t getPinHighValue(uint8_t pin) const;
    void setPinHighValue(uint8_t pin, uint8_t value);

    uint16_t getPinAddress(uint8_t pin) const;
    void setPinAddress(uint8_t pin, uint16_t address);

    void print();

private:
    uint8_t numPins;
    Preferences preferences;

    IPAddress staticIp;
    IPAddress staticSubnet;
    IPAddress staticGateway;
    IPAddress unicastIp;
    bool useDHCP;
    bool useUnicast;
    uint16_t universe;
    std::vector<uint8_t> pinLowValues;
    std::vector<uint8_t> pinHighValues;
    std::vector<uint8_t> pinAddresses;
};