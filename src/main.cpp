#include <Arduino.h>
#include "Config.hpp"
#include "DMX.hpp"
#include "IOHandler.hpp"
#include "Ui.hpp"
#include "Network.hpp"

#define HOTSPOT_PIN 32 // GPIO 32 is used to detect if we are in hotspot mode, this is the "cfg" pin

Config config;
Network network;
DMX dmx;
IOHandler ioHandler;
Ui ui;

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting gpio artnet sender");

  config.begin(ioHandler.getIOConfig().size());
  config.print();

  pinMode(HOTSPOT_PIN, INPUT_PULLUP); // this is the green led, but we use it as jumper to detect hotspot mode
  if (digitalRead(HOTSPOT_PIN) == LOW)
  {
    network.begin(config, true);
    Serial.println("Starting in hotspot mode");
  }
  else
  {
    network.begin(config, false);
    Serial.println("Starting in normal mode");
  }

  dmx.begin(config, &network);
  ioHandler.begin();

  ioHandler.addChangedCb([](uint8_t index, bool isPressed)
                         {
                            const uint8_t pinValue = isPressed ? config.getPinHighValue(index) : config.getPinLowValue(index);
                            const uint16_t pinAddress = config.getPinAddress(index);


                           dmx.setChannel(pinAddress, pinValue); });

  ui.begin(ioHandler, &config);
}

void loop()
{
  ioHandler.update();
  dmx.update();
  network.update();
}
