#pragma once
#include <array>
#include "Config.hpp"

class Ui
{
public:
    Ui(const std::array<uint8_t, 8> &availablePins, Config *cfg);

private:
    Config *cfg;
};