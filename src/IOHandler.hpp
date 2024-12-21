#pragma once
#include <array>
#include <functional>

class IOHandler
{
public:
    using ChangedCb = std::function<void(uint8_t pin, bool value)>;

    /// @brief  @note this will call the cb for each pin durinc construction
    /// @param cb
    IOHandler(ChangedCb cb);

    void update();

private:
    struct IOConfig
    {
        uint8_t pin;
        bool currentValue;
    };

    ChangedCb cb;

    std::array<IOConfig, 8> ioConfig;
};