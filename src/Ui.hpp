#pragma once
#include <array>
#include "Config.hpp"
#include "IOHandler.hpp"

class Ui
{
public:
    Ui(IOHandler *ioHandler, Config *cfg);

private:
    Config *cfg;
    std::array<uint16_t, 8> pinStatusLabels;
};