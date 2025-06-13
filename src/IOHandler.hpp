#pragma once
#include <array>
#include <functional>
#include <vector>

class IOHandler
{
public:
    struct IOConfig
    {
        uint8_t pin;
        bool currentValue;
    };
    /** @param index The index in the ioConfig array that has changed */
    using ChangedCb = std::function<void(uint8_t index, bool value)>;

    /// @brief  @note this will call the cb for each pin during construction
    void begin();

    void addChangedCb(ChangedCb cb);

    void update();

    const std::array<IOConfig, 4> &getIOConfig() const
    {
        return ioConfig;
    }

private:
    std::vector<ChangedCb> cbs;

    std::array<IOConfig, 4> ioConfig;
};