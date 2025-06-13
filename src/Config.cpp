#include "Config.hpp"
#include <Preferences.h>

void Config::begin(uint8_t numPins)
{
    this->numPins = numPins;
    preferences.begin("cfg", false);
    useDHCP = preferences.getBool("useDHCP", true);
    useUnicast = preferences.getBool("useUnicast", false);
    staticIp = preferences.getUInt("staticIp", 0);
    staticSubnet = preferences.getUInt("staticSubnet", 0);
    staticGateway = preferences.getUInt("staticGateway", 0);
    universe = preferences.getUShort("universe", 0);
    unicastIp = preferences.getUInt("unicastIp", 0);

    for (int i = 0; i < numPins; i++)
    {
        String key = "plv_" + String(i);
        const uint8_t lowValue = preferences.getUChar(key.c_str(), 0);
        pinLowValues.push_back(lowValue);

        key = "phv_" + String(i);
        const uint8_t highValue = preferences.getUChar(key.c_str(), 255);
        pinHighValues.push_back(highValue);

        key = "pa_" + String(i);
        const uint16_t address = preferences.getUShort(key.c_str(), i);
        pinAddresses.push_back(address);
    }
}

bool Config::getUseDHCP() const
{
    return useDHCP;
}

void Config::setUseDHCP(bool value)
{
    useDHCP = value;
    preferences.putBool("useDHCP", value);
    Serial.print("new useDHCP: ");
    Serial.println(value);
}

const IPAddress &Config::getStaticIp() const
{
    return staticIp;
}

void Config::setStaticIp(const IPAddress &value)
{
    staticIp = value;
    preferences.putUInt("staticIp", value);
    Serial.print("new static ip: ");
    Serial.println(value.toString());
}

const IPAddress &Config::getStaticSubnet() const
{
    return staticSubnet;
}

void Config::setStaticSubnet(const IPAddress &value)
{
    staticSubnet = value;
    preferences.putUInt("staticSubnet", value);
    Serial.print("new static subnet: ");
    Serial.println(value.toString());
}

const IPAddress &Config::getStaticGateway() const
{
    return staticGateway;
}

void Config::setStaticGateway(const IPAddress &value)
{
    staticGateway = value;
    preferences.putUInt("staticGateway", value);
    Serial.print("new static gateway: ");
    Serial.println(value.toString());
}

uint16_t Config::getUniverse() const
{
    return universe;
}

void Config::setUniverse(uint16_t value)
{
    universe = value;
    preferences.putUShort("universe", value);
    Serial.print("new universe: ");
    Serial.println(value);
}

bool Config::getUseUnicast() const
{
    return useUnicast;
}

void Config::setUseUnicast(bool value)
{
    useUnicast = value;
    preferences.putBool("useUnicast", value);
    Serial.print("new useUnicast: ");
    Serial.println(value);
}

const IPAddress &Config::getUnicastIp() const
{
    return unicastIp;
}

void Config::setUnicastIp(const IPAddress &value)
{
    unicastIp = value;
    preferences.putUInt("unicastIp", value);
    Serial.print("new unicast ip: ");
    Serial.println(value.toString());
}

uint8_t Config::getPinLowValue(uint8_t pin) const
{
    if (pin < pinLowValues.size())
    {
        return pinLowValues[pin];
    }
    return 0;
}

void Config::setPinLowValue(uint8_t pin, uint8_t value)
{
    if (pin < pinLowValues.size())
    {
        pinLowValues[pin] = value;
        String key = "plv_" + String(pin);
        preferences.putUChar(key.c_str(), value);
        Serial.printf("new low value for pin %d: %d\n", pin, value);
    }
}

uint8_t Config::getPinHighValue(uint8_t pin) const
{
    if (pin < pinHighValues.size())
    {
        return pinHighValues[pin];
    }
    return 255;
}

void Config::setPinHighValue(uint8_t pin, uint8_t value)
{
    if (pin < pinHighValues.size())
    {
        pinHighValues[pin] = value;
        String key = "phv_" + String(pin);
        preferences.putUChar(key.c_str(), value);
        Serial.printf("new high value for pin %d: %d\n", pin, value);
    }
}

uint16_t Config::getPinAddress(uint8_t pin) const
{
    if (pin < pinAddresses.size())
    {
        return pinAddresses[pin];
    }
    return pin; // default to pin number if not set
}

void Config::setPinAddress(uint8_t pin, uint16_t address)
{
    if (pin < pinAddresses.size())
    {
        pinAddresses[pin] = address;
        String key = "pa_" + String(pin);
        preferences.putUShort(key.c_str(), address);
        Serial.printf("new address for pin %d: %d\n", pin, address);
    }
}

void Config::print()
{
    Serial.println("Config:");
    Serial.print("useDHCP: ");
    Serial.println(useDHCP);
    Serial.print("staticIp: ");
    Serial.println(staticIp.toString());
    Serial.print("staticSubnet: ");
    Serial.println(staticSubnet.toString());
    Serial.print("staticGateway: ");
    Serial.println(staticGateway.toString());
    Serial.print("universe: ");
    Serial.println(universe);
    Serial.print("useUnicast: ");
    Serial.println(useUnicast);
    Serial.print("unicastIp: ");
    Serial.println(unicastIp.toString());
    Serial.println("Pin configurations:");
    for (uint8_t i = 0; i < numPins; i++)
    {
        Serial.printf("Pin %d: Low Value: %d, High Value: %d, Address: %d\n",
                      i,
                      getPinLowValue(i),
                      getPinHighValue(i),
                      getPinAddress(i));
    }
}
