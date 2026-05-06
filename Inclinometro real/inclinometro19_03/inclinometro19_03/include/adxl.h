#ifndef ADXL_H_
#define ADXL_H_

#include "calib.h"
#include "app.h"
#include <Wire.h>

#define ADXL355_ADDR 0x1D

void adxl_init(void);
void adxl_write(uint8_t reg, uint8_t value);
uint8_t adxl_read(uint8_t reg);
void adxl_measurements(SENSOR_CONTROL_PTR sensorControl);
int32_t adxl_read_axis(uint8_t reg);

#endif