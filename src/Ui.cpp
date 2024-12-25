#include "Ui.hpp"
#include <ESPUI.h>
void Ui::begin(IOHandler &ioHandler, Config *_cfg)
{
    cfg = _cfg;

    const auto networkGroupId = ESPUI.addControl(ControlType::Tab, "Network", "Network");

    ESPUI.addControl(ControlType::Label, "Info", "Changes will take effect after restart.", ControlColor::None);
    ESPUI.addControl(ControlType::Button, "Restart", "Restart", ControlColor::Carrot, Control::noParent, [](Control *sender, int type)
                     { ESP.restart(); });

    ESPUI.addControl(ControlType::Switcher, "use DHCP", cfg->getUseDHCP() ? "1" : "0", ControlColor::None, networkGroupId, [this](Control *sender, int type)
                     {
                        const bool use = sender->value.toInt() == 1;
                         cfg->setUseDHCP(use);
                         enableNetworkConfig(!use); });

    // Static IP controls
    const IPAddress &ip = cfg->getStaticIp();
    const auto staticIpGrp = ESPUI.addControl(ControlType::Text, "Static IP", ip.toString(), ControlColor::None, networkGroupId, [this](Control *sender, int type)
                                              {
                                                 String newValue = sender->value;
                                                 IPAddress newIp;
                                                 if (newIp.fromString(newValue))
                                                 {
                                                     cfg->setStaticIp(newIp);
                                                 } });
    networkControls.push_back(staticIpGrp);

    const IPAddress &subnet = cfg->getStaticSubnet();
    const auto subnetGrp = ESPUI.addControl(ControlType::Text, "Static Subnet Mask", subnet.toString(), ControlColor::None, networkGroupId, [this](Control *sender, int type)
                                            {
                                               String newValue = sender->value;
                                               IPAddress newSubnet;
                                               if (newSubnet.fromString(newValue))
                                               {
                                                   cfg->setStaticSubnet(newSubnet);
                                               } });
    networkControls.push_back(subnetGrp);

    const IPAddress &gateway = cfg->getStaticGateway();
    const auto gatewayGrp = ESPUI.addControl(ControlType::Text, "Static Gateway", gateway.toString(), ControlColor::None, networkGroupId, [this](Control *sender, int type)
                                             {
                                                String newValue = sender->value;
                                                IPAddress newGateway;
                                                if (newGateway.fromString(newValue))
                                                {
                                                    cfg->setStaticGateway(newGateway);
                                                } });
    networkControls.push_back(gatewayGrp);

    const auto artnetTabId = ESPUI.addControl(ControlType::Tab, "Artnet", "Artnet");
    const auto universeCtrl = ESPUI.addControl(ControlType::Number, "Universe", String(cfg->getUniverse()), ControlColor::None, artnetTabId, [this](Control *sender, int type)
                                               { cfg->setUniverse(sender->value.toInt()); });
    ESPUI.addControl(ControlType::Min, "", String(0), ControlColor::None, universeCtrl);
    ESPUI.addControl(ControlType::Max, "", String(32767), ControlColor::None, universeCtrl);

    ESPUI.addControl(ControlType::Switcher, "use unicast", cfg->getUseUnicast() ? "1" : "0", ControlColor::None, artnetTabId, [this](Control *sender, int type)
                     {
                        const bool use = sender->value.toInt() == 1;
                        cfg->setUseUnicast(use);
                        enableUnicastConfig(use); });

    const IPAddress &unicastIp = cfg->getUnicastIp();

    const auto unicastGrp = ESPUI.addControl(ControlType::Text, "Unicast IP", unicastIp.toString(), ControlColor::None, artnetTabId, [this](Control *sender, int type)
                                             {
                                                 String newValue = sender->value;
                                                 IPAddress newIp;
                                                 if (newIp.fromString(newValue))
                                                 {
                                                     cfg->setUnicastIp(newIp);
                                                 } });

    unicastControls.push_back(unicastGrp);

    const auto pingGroupId = ESPUI.addControl(ControlType::Tab, "Pins", "Pins");

    // Add entries for each configured pin
    const auto &pins = ioHandler.getIOConfig();
    for (size_t i = 0; i < pins.size(); i++)
    {
        const auto labelGrp = ESPUI.addControl(ControlType::Label, "", "Pin " + String(pins[i].pin) + " (DMX Address " + String(i) + ")", ControlColor::None, pingGroupId);

        pinStatusLabels[i] = ESPUI.addControl(ControlType::Label, "Status",
                                              pins[i].currentValue ? "<div style='background-color: #4CAF50; padding: 5px; color: white;'>HIGH</div>" : "<div style='background-color: #f44336; padding: 5px; color: white;'>LOW</div>",
                                              ControlColor::None, labelGrp);
    }

    // Register callback to update labels when pins change
    ioHandler.addChangedCb([this](uint8_t pin, uint8_t index, bool newValue)
                           { ESPUI.updateLabel(this->pinStatusLabels[index],
                                               newValue ? "<div style='background-color: #4CAF50; padding: 5px; color: white;'>HIGH</div>"
                                                        : "<div style='background-color: #f44336; padding: 5px; color: white;'>LOW</div>"); });

    enableNetworkConfig(!cfg->getUseDHCP());
    enableUnicastConfig(cfg->getUseUnicast());

    ESPUI.begin("ArtNet GPIO");
}

void Ui::enableNetworkConfig(bool enable)
{
    for (const auto &ctrl : networkControls)
    {
        ESPUI.setEnabled(ctrl, enable);
    }
}

void Ui::enableUnicastConfig(bool enable)
{
    for (const auto &ctrl : unicastControls)
    {
        ESPUI.setEnabled(ctrl, enable);
    }
}