#ifndef ADXL_H_
#define ADXL_H_

#include "calib.h"
#include "app.h"
#include "Adafruit_Sensor.h"
#include "Adafruit_ADXL345_U.h"

void adxl_init(void);
void adxl_measurements(SENSOR_CONTROL_PTR sensorControl);

#endif