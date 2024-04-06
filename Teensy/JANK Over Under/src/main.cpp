#include <Arduino.h>
#include <main.hpp>
#include <iostream>
// put function declarations here:
int myFunction(int, int);

SerialHandler serialHandler(115200);
TeensyData randomData;
Adafruit_BNO08x bno = Adafruit_BNO08x(2, 3);

void receiveData() {
    while (true) {
        serialHandler.receive();
        v5Data = serialHandler.getV5Data();
        threads.delay(1);
    }
}

void sendData() {
    while (true) {
        serialHandler.send(&randomData);
        threads.delay(2);
    }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  serialHandler.flush();
  randomData.x = 582;
  randomData.y = 178;
  randomData.heading = 17.0;
  randomData.gyroHeading = 63.0;
  randomData.headingMerged = 12.0;
  pinMode(1, OUTPUT);
  pinMode(33, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //serialHandler.send(&randomData);
  std::cout << "Sent Data" << std::endl;
  printf("Sent Data\n");
  digitalWrite(1, HIGH);
  digitalWrite(33, HIGH);
  delay(1000);
  digitalWrite(1, LOW);
  digitalWrite(33, LOW);
  delay(1000);

}

// put function definitions here: