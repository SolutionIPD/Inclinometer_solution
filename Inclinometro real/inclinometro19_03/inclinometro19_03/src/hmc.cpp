#include "hmc.h"
#include "math.h"

Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12); // qqr valor

void hmc_init(void) {
    if (!mag.begin()) {
        Serial.println("HMC5883L não detectado!");
        while (1);
    }
    mag.setMagGain(HMC5883_MAGGAIN_4_0); // +- 4G, 440 LSB/Gauss, meio termo de sensibilidade
    Serial.println("HMC iniciado com sucesso!");
}

void hmc_measurements(SENSOR_CONTROL_PTR sensorControl) {
    float h_offsetX = -72.045; // pegos do calib_HMC e calculados para chegar nisso
    float h_offsetY = -8.545;
    float h_offsetZ = -21.125;

    float h_scaleX = 0.939;
    float h_scaleY = 1.005;
    float h_scaleZ = 1.069;

    sensors_event_t event;
    mag.getEvent(&event);

    float mx = (event.magnetic.x - h_offsetX) * h_scaleX;
    float my = (event.magnetic.y - h_offsetY) * h_scaleY;
    float mz = (event.magnetic.z - h_offsetZ) * h_scaleZ;

    sensorControl->hmc_heading = atan2(my * cos(roll) - mz * sin(roll), mx * cos(pitch) + my * sin(roll) * sin(pitch) + mz * cos(roll) * sin(pitch));
    if (sensorControl->hmc_heading < 0) sensorControl->hmc_heading += 360.0;

    //Serial.print("[DEBUG] Heading: ");
    //Serial.println(sensorControl->hmc_heading, 2);

}