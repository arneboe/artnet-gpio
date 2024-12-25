#include <Arduino.h>
#include "Config.hpp"
#include "DMX.hpp"
#include "IOHandler.hpp"
#include "Ui.hpp"
#include "Network.hpp"

// put function declarations here:
void setupNormalMode(Config *cfg);
void setupHotspotMode();

Config config;
Network network;
DMX dmx;
IOHandler ioHandler;
Ui ui;

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting gpio artnet sender");

  config.begin();
  config.print();

  // TODO check button for hotspot mode
  network.begin(config, false);
  dmx.begin(config, &network);
  ioHandler.begin();

  // ioHandler->addChangedCb([](uint8_t pin, uint8_t index, bool value)
  //                         { network->setChannel(index, value ? 255 : 0); });

  ui.begin(ioHandler, &config);
}

void loop()
{
  ioHandler.update();
  dmx.update();
  network.update();
}
