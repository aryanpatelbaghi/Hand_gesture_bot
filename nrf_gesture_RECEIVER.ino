#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define ENA 5  // PWM for Motor A
#define IN1 2  // Motor A Direction
#define IN2 3  // Motor A Direction
#define ENB 6 // PWM for Motor B
#define IN3 4  // Motor B Direction
#define IN4 7  // Motor B Direction

#define CE_PIN 9
#define CSN_PIN 10

RF24 radio(CE_PIN, CSN_PIN);
const byte address[6] = "00001";
char command = 'S';  // Default state is stop

void setup() {
    Serial.begin(9600);
    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    radio.begin();
    radio.openReadingPipe(0, address);
    radio.setPALevel(RF24_PA_LOW);
    radio.startListening();  // Set as receiver
}

void loop() {
    if (radio.available()) {
        radio.read(&command, sizeof(command));
        Serial.print("Received: ");
        Serial.println(command);

        switch (command) {
            case 'F': // Forward
                digitalWrite(IN1, HIGH);
                digitalWrite(IN2, LOW);
                digitalWrite(IN3, HIGH);
                digitalWrite(IN4, LOW);
                analogWrite(ENA, 200);
                analogWrite(ENB, 200);
                break;

            case 'B': // Backward
                digitalWrite(IN1, LOW);
                digitalWrite(IN2, HIGH);
                digitalWrite(IN3, LOW);
                digitalWrite(IN4, HIGH);
                analogWrite(ENA, 200);
                analogWrite(ENB, 200);
                break;

            case 'L': // Right
                digitalWrite(IN1, HIGH);
                digitalWrite(IN2, LOW);
                digitalWrite(IN3, LOW);
                digitalWrite(IN4, HIGH);
                analogWrite(ENA, 200);
                analogWrite(ENB, 200);
                break;

            case 'R': // Left
                digitalWrite(IN1, LOW);
                digitalWrite(IN2, HIGH);
                digitalWrite(IN3, HIGH);
                digitalWrite(IN4, LOW);
                analogWrite(ENA, 200);
                analogWrite(ENB, 200);
                break;

            case 'S': // Stop
                digitalWrite(IN1, LOW);
                digitalWrite(IN2, LOW);
                digitalWrite(IN3, LOW);
                digitalWrite(IN4, LOW);
                analogWrite(ENA, 0);
                analogWrite(ENB, 0);
                break;
        }
    }
}
