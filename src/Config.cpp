#include "Config.hpp"
#include <Preferences.h>

void Config::begin()
{
    preferences.begin("cfg", false);
    useDHCP = preferences.getBool("useDHCP", true);
    useUnicast = preferences.getBool("useUnicast", false);
    staticIp = preferences.getUInt("staticIp", 0);
    staticSubnet = preferences.getUInt("staticSubnet", 0);
    staticGateway = preferences.getUInt("staticGateway", 0);
    universe = preferences.getUShort("universe", 0);
    unicastIp = preferences.getUInt("unicastIp", 0);
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
}
