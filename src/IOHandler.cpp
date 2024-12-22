#include "IOHandler.hpp"
#include <Arduino.h>

IOHandler::IOHandler()
{
    ioConfig[0] = {13, false};
    ioConfig[1] = {4, false};
    ioConfig[2] = {5, false};
    ioConfig[3] = {18, false};
    ioConfig[4] = {19, false};
    ioConfig[5] = {21, false};
    ioConfig[6] = {22, false};
    ioConfig[7] = {23, false};

    for (int i = 0; i < ioConfig.size(); i++)
    {
        auto &config = ioConfig[i];
        pinMode(config.pin, INPUT_PULLUP);
        config.currentValue = digitalRead(config.pin);
    }
}

void IOHandler::addChangedCb(ChangedCb cb)
{
    cbs.push_back(cb);
}

void IOHandler::update()
{
    // TODO maybe debounce, but maybe this is also fine because we only send at 44hz
    for (int i = 0; i < ioConfig.size(); i++)
    {
        auto &pin = ioConfig[i];
        bool newValue = digitalRead(pin.pin);
        if (newValue != pin.currentValue)
        {
            pin.currentValue = newValue;
            for (const auto &cb : cbs)
            {
                cb(pin.pin, i, pin.currentValue);
            }
        }
    }
}