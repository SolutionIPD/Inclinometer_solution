# Conventional Inclinometer - Solution IPD

Codes for prototyping the conventional inclinometer 
using RS-485 for comunication. 

The team designed the PCB and the codes for the prototype.

## Technologies
This project uses ADXL355 to get the measurements and it was designed to work with the MPU6050. But, the sensor is not working since the last update.  
Both sensors are connected to a ESP32-S2-MINI-2U

## Board conections
To upload the firmware to the ESP32, we tryed with the BTE13-009 and the FTDI32. Both worked as planned. RX* and TX must be placed crossed (RX-TX, TX-RX).

For the RS-485, we used the USB-485 with A and B connected to 485A and 485B respectfully (A-485A, B-485B).  

The board needs a 12V input to work properly.

ALL GROUNDS MUST BE CONNECTED TOGETHER.

*For the FTDI32, the right connectors are RXD and TXD

## How to upload the firmware
1 - Clone the repository;  
2 - Conect a jumper on both pins for the BOOT;  
3 - Conect the Vcc and GND, and power the board;  
4 - Upload the code;  
4.1 - While the upload is on going, hold the button until the "Connecting..." shows;  
*Note:* If the "Connecting" part takes to too long after the button release, it did not work  

## How to run and see results
1 - After uploading the firmware, unplug the boot jumper;  
2 - Press the button;  
3 - Run the "interface_medicao.py", chaging the COM port to the one used by the USB-485;  
4 - Right after adding the max depth and a name, the "run and get results" screen will show up;  
5 - You can run the measurements for each step or re-run if necessary;

## Updates
### [15/03/2025]
Currently we are at the end (hopefully) of the prototyping stage: the main code works for the most part, but the data is not being imprinted, or sent, to the python plots.  
this can either be a problem related to the rs485, or to the python GUI.
### [27/05/2025]
The code now works well. All parts of it are working as expected, meaning that the data aquisition from the sensors, data calibration, data filtering using a complementary filter, a second-order low-pass butterworth filter, and a moving average filter that goes through 100 iterations before showing the final values, which are then sent through a buffer by the rs485 user-built library. As of today, all of this, including the python GUI is working.  
 However. there is still one problem that we ought to get through: the mpu6050 has shown I2c communication erros throughout the project, and right now, this has no solution. This problem is most likely due to one of three possibilities: a project error, a building error, or a component error.  
Through software, there is no way to currently get through this MPU error, and even though the code itself works, there is no way to actually use the gyroscope measurements reliably. 
