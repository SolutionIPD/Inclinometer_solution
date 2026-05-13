#ifndef HMC_H_
#define HMC_H_

#include "calib.h"
#include "app.h"
#include <Wire.h>

#define HMC5883_ADDR 0x1E

void hmc_init(void);
void hmc_write(uint8_t reg, uint8_t value);
int16_t hmc_read_axis(uint8_t reg);
void hmc_measurements(SENSOR_CONTROL_PTR sensorControl);

#endif