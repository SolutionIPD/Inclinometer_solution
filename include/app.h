#ifndef APP_H_
#define APP_H_

#include <stdint.h>
#include <HardwareSerial.h>
#include <Wire.h>

typedef enum {
    WAIT_TILL_START,
    GET_MEASURE,
    SEND_MEASURE
} app_state;

typedef struct {
    float adxl_angl_x;
    float adxl_angl_y;
    float adxl_angl_z;
    float hmc_heading;
} SENSOR_CONTROL_T, *SENSOR_CONTROL_PTR;

extern SENSOR_CONTROL_T sensorControl;

typedef struct {
    uint8_t rs485_message[100];
    char rs485_command;
    uint8_t rs485_size;
    uint8_t indexrs485;

} RS485_CONTROL_T, *RS485_CONTROL_PTR;

void app_init(void);
void app_poll(void);

#endif