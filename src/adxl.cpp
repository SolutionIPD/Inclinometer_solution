#include "adxl.h"

#define RAD_TO_DEG 57.29577951308232f

void adxl_write(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(ADXL355_ADDR);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

uint8_t adxl_read(uint8_t reg) {
  Wire.beginTransmission(ADXL355_ADDR);
  Wire.write(reg);
  Wire.endTransmission(false);

  Wire.requestFrom(ADXL355_ADDR, 1);
  return Wire.read();
}

void adxl_init(void) {
  // Verifica ID (DEVID_AD = 0x00 deve ser 0xAD)
  uint8_t id = adxl_read(0x00);
  if (id != 0xAD) {
    Serial.println("ADXL355 não detectado!");
    while (1);
  }

  adxl_write(0x2C, 0x01); // confirma que é 2g

  // Coloca em modo de medição (POWER_CTL = 0x2D)
  adxl_write(0x2D, 0x00); // bit 0 = 0 → measurement mode

  Serial.println("ADXL355 iniciado!");
}

int32_t adxl_read_axis(uint8_t reg) {
  Wire.beginTransmission(ADXL355_ADDR);
  Wire.write(reg);
  Wire.endTransmission(false);

  Wire.requestFrom(ADXL355_ADDR, 3);

  int32_t value = 0;
  value |= ((int32_t)Wire.read() << 12);
  value |= ((int32_t)Wire.read() << 4);
  value |= ((Wire.read() >> 4) & 0x0F);

  // Sign extend (20 bits)
  if (value & 0x80000) {
    value |= 0xFFF00000;
  }

  return value;
}

void adxl_measurements(SENSOR_CONTROL_PTR sensorControl){
  int32_t raw_x = adxl_read_axis(0x08);
  int32_t raw_y = adxl_read_axis(0x0B);
  int32_t raw_z = adxl_read_axis(0x0E);

  // Converte pra g (±2g → 256000 LSB/g)
  float h[3];
  h[0] = (float)raw_x / 256000.0;
  h[1] = (float)raw_y / 256000.0;
  h[2] = (float)raw_z / 256000.0;

  float Ainv[3][3] = {{0.983286, 0.003250, 0.000004}, {0.003250, 0.976451, 0.002108}, {0.000004, 0.002108, 0.958748}};

  float b[3] = {-0.009334, 0.007129, -0.041051};

  // calibração
  calib_accel_init(&sensorCalib, h, Ainv, b);

  sensorControl->adxl_angl_x = atan2f(sensorCalib.acc_x_calib, sqrtf(sensorCalib.acc_y_calib * sensorCalib.acc_y_calib +
                sensorCalib.acc_z_calib * sensorCalib.acc_z_calib)) * RAD_TO_DEG;

  sensorControl->adxl_angl_y = atan2f(sensorCalib.acc_y_calib, sqrtf(sensorCalib.acc_x_calib * sensorCalib.acc_x_calib +
                sensorCalib.acc_z_calib * sensorCalib.acc_z_calib)) * RAD_TO_DEG;

  sensorControl->adxl_angl_z = atan2f(sensorCalib.acc_z_calib, sqrtf(sensorCalib.acc_x_calib * sensorCalib.acc_x_calib +
                sensorCalib.acc_y_calib * sensorCalib.acc_y_calib)) * RAD_TO_DEG;
}
