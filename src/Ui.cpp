#include "Ui.hpp"
#include <ESPUI.h>

Ui::Ui(IOHandler *ioHandler, Config *cfg) : cfg{cfg}
{
    const auto networkGroupId = ESPUI.addControl(ControlType::Tab, "Network Configuration", "Network Configuration");

    ESPUI.addControl(ControlType::Label, "Info", "Changes to the configuration will take effect after restart.", ControlColor::None);
    ESPUI.addControl(ControlType::Button, "Restart", "Restart", ControlColor::Carrot, Control::noParent, [](Control *sender, int type)
                     { ESP.restart(); });

    ESPUI.addControl(ControlType::Switcher, "use DHCP", cfg->getUseDHCP() ? "1" : "0", ControlColor::None, networkGroupId, [this](Control *sender, int type)
                     { this->cfg->setUseDHCP(sender->value.toInt() == 1); });

    // Static IP controls
    const IPAddress &ip = cfg->getStaticIp();
    const auto staticIpGrp = ESPUI.addControl(ControlType::Number, "Static IP", String(ip[0]), ControlColor::None, networkGroupId, [this](Control *sender, int type)
                                              {
        auto ip = this->cfg->getStaticIp();
        ip[0] = sender->value.toInt();
        this->cfg->setStaticIp(ip); });
    ESPUI.addControl(ControlType::Min, "", String(0), ControlColor::None, staticIpGrp);
    ESPUI.addControl(ControlType::Max, "", String(255), ControlColor::None, staticIpGrp);
    const auto static1 = ESPUI.addControl(ControlType::Number, "", String(ip[1]), ControlColor::None, staticIpGrp, [this](Control *sender, int type)
                                          {
        auto ip = this->cfg->getStaticIp();
        ip[1] = sender->value.toInt();
        this->cfg->setStaticIp(ip); });
    ESPUI.addControl(ControlType::Min, "", String(0), ControlColor::None, static1);
    ESPUI.addControl(ControlType::Max, "", String(255), ControlColor::None, static1);
    const auto static2 = ESPUI.addControl(ControlType::Number, "", String(ip[2]), ControlColor::None, staticIpGrp, [this](Control *sender, int type)
                                          {
        auto ip = this->cfg->getStaticIp();
        ip[2] = sender->value.toInt();
        this->cfg->setStaticIp(ip); });
    ESPUI.addControl(ControlType::Min, "", String(0), ControlColor::None, static2);
    ESPUI.addControl(ControlType::Max, "", String(255), ControlColor::None, static2);

    const auto static3 = ESPUI.addControl(ControlType::Number, "", String(ip[3]), ControlColor::None, staticIpGrp, [this](Control *sender, int type)
                                          {
        auto ip = this->cfg->getStaticIp();
        ip[3] = sender->value.toInt();
        this->cfg->setStaticIp(ip); });
    ESPUI.addControl(ControlType::Min, "", String(0), ControlColor::None, static3);
    ESPUI.addControl(ControlType::Max, "", String(255), ControlColor::None, static3);

    const IPAddress &subnet = cfg->getStaticSubnet();
    const auto subnetGrp = ESPUI.addControl(ControlType::Number, "Static Subnet Mask", String(subnet[0]), ControlColor::None, networkGroupId, [this](Control *sender, int type)
                                            {
        auto subnet = this->cfg->getStaticSubnet();
        subnet[0] = sender->value.toInt();
        this->cfg->setStaticSubnet(subnet); });
    ESPUI.addControl(ControlType::Min, "", String(0), ControlColor::None, subnetGrp);
    ESPUI.addControl(ControlType::Max, "", String(255), ControlColor::None, subnetGrp);
    const auto subnet1 = ESPUI.addControl(ControlType::Number, "", String(subnet[1]), ControlColor::None, subnetGrp, [this](Control *sender, int type)
                                          {
        auto subnet = this->cfg->getStaticSubnet();
        subnet[1] = sender->value.toInt();
        this->cfg->setStaticSubnet(subnet); });
    ESPUI.addControl(ControlType::Min, "", String(0), ControlColor::None, subnet1);
    ESPUI.addControl(ControlType::Max, "", String(255), ControlColor::None, subnet1);
    const auto subnet2 = ESPUI.addControl(ControlType::Number, "", String(subnet[2]), ControlColor::None, subnetGrp, [this](Control *sender, int type)
                                          {
        auto subnet = this->cfg->getStaticSubnet();
        subnet[2] = sender->value.toInt();
        this->cfg->setStaticSubnet(subnet); });
    ESPUI.addControl(ControlType::Min, "", String(0), ControlColor::None, subnet2);
    ESPUI.addControl(ControlType::Max, "", String(255), ControlColor::None, subnet2);
    const auto subnet3 = ESPUI.addControl(ControlType::Number, "", String(subnet[3]), ControlColor::None, subnetGrp, [this](Control *sender, int type)
                                          {
        auto subnet = this->cfg->getStaticSubnet();
        subnet[3] = sender->value.toInt();
        this->cfg->setStaticSubnet(subnet); });
    ESPUI.addControl(ControlType::Min, "", String(0), ControlColor::None, subnet3);
    ESPUI.addControl(ControlType::Max, "", String(255), ControlColor::None, subnet3);

    const IPAddress &gateway = cfg->getStaticGateway();
    const auto gatewayGrp = ESPUI.addControl(ControlType::Number, "Static Gateway", String(gateway[0]), ControlColor::None, networkGroupId, [this](Control *sender, int type)
                                             {
        auto gateway = this->cfg->getStaticGateway();
        gateway[0] = sender->value.toInt();
        this->cfg->setStaticGateway(gateway); });
    ESPUI.addControl(ControlType::Min, "", String(0), ControlColor::None, gatewayGrp);
    ESPUI.addControl(ControlType::Max, "", String(255), ControlColor::None, gatewayGrp);
    const auto gateway1 = ESPUI.addControl(ControlType::Number, "", String(gateway[1]), ControlColor::None, gatewayGrp, [this](Control *sender, int type)
                                           {
        auto gateway = this->cfg->getStaticGateway();
        gateway[1] = sender->value.toInt();
        this->cfg->setStaticGateway(gateway); });
    ESPUI.addControl(ControlType::Min, "", String(0), ControlColor::None, gateway1);
    ESPUI.addControl(ControlType::Max, "", String(255), ControlColor::None, gateway1);
    const auto gateway2 = ESPUI.addControl(ControlType::Number, "", String(gateway[2]), ControlColor::None, gatewayGrp, [this](Control *sender, int type)
                                           {
        auto gateway = this->cfg->getStaticGateway();
        gateway[2] = sender->value.toInt();
        this->cfg->setStaticGateway(gateway); });
    ESPUI.addControl(ControlType::Min, "", String(0), ControlColor::None, gateway2);
    ESPUI.addControl(ControlType::Max, "", String(255), ControlColor::None, gateway2);
    const auto gateway3 = ESPUI.addControl(ControlType::Number, "", String(gateway[3]), ControlColor::None, gatewayGrp, [this](Control *sender, int type)
                                           {
        auto gateway = this->cfg->getStaticGateway();
        gateway[3] = sender->value.toInt();
        this->cfg->setStaticGateway(gateway); });
    ESPUI.addControl(ControlType::Min, "", String(0), ControlColor::None, gateway3);
    ESPUI.addControl(ControlType::Max, "", String(255), ControlColor::None, gateway3);

    // Universe control
    const auto universeCtrl = ESPUI.addControl(ControlType::Number, "Universe", String(cfg->getUniverse()), ControlColor::None, networkGroupId, [this](Control *sender, int type)
                                               { this->cfg->setUniverse(sender->value.toInt()); });
    ESPUI.addControl(ControlType::Min, "", String(0), ControlColor::None, universeCtrl);
    ESPUI.addControl(ControlType::Max, "", String(32767), ControlColor::None, universeCtrl);

    const auto pingGroupId = ESPUI.addControl(ControlType::Tab, "Pin Configuration", "Pin Configuration");

    // Add entries for each configured pin
    const auto &pins = ioHandler->getIOConfig();
    for (size_t i = 0; i < pins.size(); i++)
    {
        const auto labelGrp = ESPUI.addControl(ControlType::Label, "", "Pin " + String(pins[i].pin) + " (DMX Address " + String(i) + ")", ControlColor::None, pingGroupId);

        pinStatusLabels[i] = ESPUI.addControl(ControlType::Label, "Status",
                                              pins[i].currentValue ? "<div style='background-color: #4CAF50; padding: 5px; color: white;'>HIGH</div>" : "<div style='background-color: #f44336; padding: 5px; color: white;'>LOW</div>",
                                              ControlColor::None, labelGrp);
    }

    // Register callback to update labels when pins change
    ioHandler->addChangedCb([this](uint8_t pin, uint8_t index, bool newValue)
                            { ESPUI.updateLabel(this->pinStatusLabels[index],
                                                newValue ? "<div style='background-color: #4CAF50; padding: 5px; color: white;'>HIGH</div>"
                                                         : "<div style='background-color: #f44336; padding: 5px; color: white;'>LOW</div>"); });

    ESPUI.begin("ArtNet GPIO");
}