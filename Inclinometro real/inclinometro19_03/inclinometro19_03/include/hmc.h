#ifndef HMC_H_
#define HMC_H_

#include "calib.h"
#include "app.h"
#include <Adafruit_HMC5883_U.h>
#include <Wire.h>

void hmc_init(void);
void hmc_measurements(SENSOR_CONTROL_PTR sensorControl);

#endif