#include <Arduino.h>
#include "main.h"

void setup() {
  Serial.begin(115200);
  pins_init();
  adxl_init();
  hmc_init();
  app_init();
  rs485_init();
}

void loop() {
  app_poll();
}
