#include "IOHandler.hpp"
#include <Arduino.h>

IOHandler::IOHandler(ChangedCb cb) : cb{cb}
{
    ioConfig[0] = {13, false};
    ioConfig[1] = {4, false};
    ioConfig[2] = {5, false};
    ioConfig[3] = {18, false};
    ioConfig[4] = {19, false};
    ioConfig[5] = {21, false};
    ioConfig[6] = {22, false};
    ioConfig[7] = {23, false};

    for (auto &config : ioConfig)
    {
        pinMode(config.pin, INPUT_PULLUP);
        config.currentValue = digitalRead(config.pin);
        cb(config.pin, config.currentValue);
    }
}

void IOHandler::update()
{
    // TODO maybe debounce, but maybe this is also fine because we only send at 44hz
    for (auto &config : ioConfig)
    {
        bool newValue = digitalRead(config.pin);
        if (newValue != config.currentValue)
        {
            config.currentValue = newValue;
            cb(config.pin, config.currentValue);
        }
    }
}