/*
Arduino Sketch to allow RS232/RS485 communications
via two Arduinos with attached SN75176 ICs.

From: earl@microcontrollerelectronics.com
*/

#include <SoftwareSerial.h>

SoftwareSerial rs485Serial(8, 9); // RX, TX
#define DE 7 // DE = DriverEnable. HIGH means chip enables the driver and can write to the bus

void setup() {

  // UART connection to talk to the client/Arduino (over Serial terminal such as 
  // YAT, microterm, picoterm, hyperterm, putty, ...)
  Serial.begin(115200);

  // UART connected to the pins that are connected to the SN75176 RS484 transceiver chip 
  rs485Serial.begin(115200);

  // configure the pin that is connected to the driver on the chip as an output
  pinMode(DE, OUTPUT);

  // disable the driver to go into listen mode
  digitalWrite(DE, LOW);
}

void loop() {

  // if there is data received from the RS485 bus
  if (rs485Serial.available()) {
    
    // forward the RS485 data to the client UART
    Serial.write(rs485Serial.read());
  }

  // if the bus client send data over UART to the Arduino, forward this data to the RS485 bus
  if (Serial.available()) {

    // enable the RS485 bus driver
    digitalWrite(DE, HIGH);

    // write the client data to the RS485 bus
    rs485Serial.write(Serial.read());

    // disable the bus driver so that the chip can then receive data that is placed onto the RS485 bus by a communication partner
    digitalWrite(DE, LOW);
  }
}