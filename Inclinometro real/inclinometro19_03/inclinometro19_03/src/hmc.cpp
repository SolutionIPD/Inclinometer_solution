#include "hmc.h"
#include "math.h"

#define RAD_TO_DEG 57.29577951308232f
#define DEG_TO_RAD 0.017453292519943295f

void hmc_write(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(HMC5883_ADDR);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

void hmc_init(void) {
  hmc_write(0x00, 0x70); //8 amostras médias, 15 Hz, normal mode
  hmc_write(0x01, 0xA0); // Gain = ±4.0 Gauss, 440 LSB/Gauss → valor = 0xA0
  hmc_write(0x02, 0x00); // modo: medicao continua

  Serial.println("HMC iniciado com sucesso!");
}

int16_t hmc_read_axis(uint8_t reg) {
  Wire.beginTransmission(HMC5883_ADDR);
  Wire.write(reg);
  Wire.endTransmission(false);

  Wire.requestFrom(HMC5883_ADDR, 2);

  return (Wire.read() << 8) | Wire.read();
}

void hmc_measurements(SENSOR_CONTROL_PTR sensorControl) {
  float h_offsetX = -72.045;
  float h_offsetY = -8.545;
  float h_offsetZ = -21.125;

  float h_scaleX = 0.939;
  float h_scaleY = 1.005;
  float h_scaleZ = 1.069;

  int16_t raw_x = hmc_read_axis(0x03);
  int16_t raw_z = hmc_read_axis(0x05);
  int16_t raw_y = hmc_read_axis(0x07);

  // Converter pra Gauss (±4G → 440 LSB/Gauss)
  float mx = ((float)raw_x / 440.0 - h_offsetX) * h_scaleX;
  float my = ((float)raw_y / 440.0 - h_offsetY) * h_scaleY;
  float mz = ((float)raw_z / 440.0 - h_offsetZ) * h_scaleZ;

  float roll_rad  = sensorControl->adxl_angl_x * DEG_TO_RAD;
  float pitch_rad = sensorControl->adxl_angl_y * DEG_TO_RAD;

  sensorControl->hmc_heading = atan2f(my * cosf(roll_rad) - mz * sinf(roll_rad), mx * cosf(pitch_rad) + 
        my * sinf(roll_rad) * sinf(pitch_rad) + mz * cosf(roll_rad) * sinf(pitch_rad)) * RAD_TO_DEG;

  if (sensorControl->hmc_heading < 0)
    sensorControl->hmc_heading += 360.0;
}