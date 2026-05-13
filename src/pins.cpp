#include "pins.h"

void pins_init(void) {
    Wire.begin(SDA, SCL); 
    Wire.begin(21, 20);
    Wire.setClock(100000);
}