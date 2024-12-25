#pragma once
#include <array>
#include "Config.hpp"
#include "IOHandler.hpp"
#include <vector>

class Ui
{
public:
    void begin(IOHandler &ioHandler, Config *cfg);

private:
    void enableNetworkConfig(bool enable);
    void enableUnicastConfig(bool enable);

    Config *cfg;
    std::array<uint16_t, 8> pinStatusLabels;
    std::vector<uint16_t> networkControls;
    std::vector<uint16_t> unicastControls;
};