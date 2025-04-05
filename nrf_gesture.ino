#include <Wire.h>
#include <MPU6050.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 9
#define CSN_PIN 10

MPU6050 mpu;
RF24 radio(CE_PIN, CSN_PIN);
const byte address[6] = "00001"; // Communication address

int16_t ax, ay, az;
float angleX, angleY;
char command;

void setup() {
    Serial.begin(9600);  
    Wire.begin();
    mpu.initialize();
    
    radio.begin();
    radio.openWritingPipe(address);
    radio.setPALevel(RF24_PA_LOW);
    radio.stopListening(); // Set as transmitter
}

void loop() {
    mpu.getAcceleration(&ax, &ay, &az);
    
    angleY = atan2(ay, az) * 180 / PI;
    angleX = atan2(ax, az) * 180 / PI;

    if (abs(angleX) > abs(angleY)) {
        if (angleX > 10) {
            command = 'B'; // Forward
        } else if (angleX < -10) {
            command = 'F'; // Backward
        } else {
            command = 'S'; // Stop
        }
    } else {
        if (angleY > 10) {
            command = 'R'; // Right
        } else if (angleY < -10) {
            command = 'L'; // Left
        } else {
            command = 'S'; // Stop
        }
    }

    radio.write(&command, sizeof(command)); // Send command
    Serial.print("Sent: ");
    Serial.println(command);

    delay(100);
}
