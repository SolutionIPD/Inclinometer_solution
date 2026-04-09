#include "adxl.h"

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(10);

void adxl_init(void){
  if(!accel.begin()) { // assume range 2g
    Serial.println("ADXL345 não detectado!");
    while(1);
  }

  Serial.println("ADXL iniciado com sucesso!");  
}

void adxl_measurements(SENSOR_CONTROL_PTR sensorControl){ //Medições
  sensors_event_t AccelEvent;
  accel.getEvent(&AccelEvent);
  
  float h[3] = {AccelEvent.acceleration.x, AccelEvent.acceleration.y, AccelEvent.acceleration.z}; //organização das acelerações em forma de vetor
  float Ainv [3] [3] = {{0.983286,0.003250,0.000004},{0.003250,0.976451,0.002108},{0.000004,0.002108,0.958748}}; //coeficientes da matriz A inversa, retiradas da calibração com o magneto
  float b [3] = {-0.009334, 0.007129 , -0.041051}; //coeficientes de BIAS retirados da calibração com o magneto

  /*int accelx=AccelEvent.acceleration.x
  int accely=AccelEvent.acceleration.y;
  int accelz=AccelEvent.acceleration.z;*/ // testes sem a calibração

  calib_accel_init(&sensorCalib, h, Ainv, b); //utilização do algorítmo de calibração
  sensorControl->adxl_angl_x = atan2f(sensorCalib.acc_x_calib,(sqrt((sensorCalib.acc_y_calib*sensorCalib.acc_y_calib)+(sensorCalib.acc_z_calib*sensorCalib.acc_z_calib))))*(RAD_TO_DEG);
  sensorControl->adxl_angl_y = atan2f(sensorCalib.acc_y_calib,(sqrt((sensorCalib.acc_x_calib*sensorCalib.acc_x_calib)+(sensorCalib.acc_z_calib*sensorCalib.acc_z_calib))))*(RAD_TO_DEG);
  sensorControl->adxl_angl_z = atan2f(sensorCalib.acc_z_calib, (sqrt((sensorCalib.acc_x_calib*sensorCalib.acc_x_calib)+(sensorCalib.acc_y_calib*sensorCalib.acc_y_calib))))*(RAD_TO_DEG);;
  //cálculo dos ângulos, a partir das acelerações, e sua alocação no vetor sensorControl

  //Serial.println(sensorCalib.acc_x_calib);
  //Serial.println(sensorCalib.acc_y_calib);
  //Serial.println(sensorCalib.acc_z_calib);
  //Serial.println(sensorControl->adxl_angl_x);
  //Serial.println(sensorControl->adxl_angl_y);
  //Serial.println(sensorControl->adxl_angl_z);
  //Prints para testes 
}
