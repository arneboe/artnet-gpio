#include "IOHandler.hpp"
#include <Arduino.h>

void IOHandler::begin()
{

    ioConfig[0] = {39, false}; // no internal pulldown, need to add one
    ioConfig[1] = {36, false}; // no internal pulldown, need to add one
    ioConfig[2] = {35, false}; // no internal pulldown, need to add one
    ioConfig[3] = {4, false};  // normal io
    // ioConfig[4] = {17, false}; // normal io but green eld
    // ioConfig[5] = {5, false};  // normal io but green eld
    // ioConfig[4] = {33, false}; // normal io
    // ioConfig[5] = {32, false}; // normal io

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
            Serial.printf("Pin %d changed to %d\n", pin.pin, newValue);
            pin.currentValue = newValue;
            for (const auto &cb : cbs)
            {
                cb(i, pin.currentValue);
            }
        }
    }
}