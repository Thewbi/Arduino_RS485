# Arduino_RS485
Using the SNx5176B (specifically the SN75176BP) transceivers from an Arduino

## Credits
I learned how to use the transceiver here: https://microcontrollerelectronics.com/sn75176-rs485-communications-between-two-arduinos/

The code is a modified version. Modifications are mainly renaming of variables and added comments.

## Basic Idea
The SNx5176B transceivers allow access to a RS485 bus. The device can be thought of as a gateway to RS485. As a gateway it can be logically split into two interfaces. There is a client facing interface and a RS485 facing interface.

The client is connected to 1, 2, 3 and 4. Pins 1 and 4 are connected to a UART implementation on the Client. Pin 2 (Receiver Enable) is pulled LOW, when the client wants to receive data from the bus. Pin 3 (Driver Enable) is pulled HIGH, when the client wants to send data onto the bus.

From the clients side, the chip is interfaced via a UART. The bytes that are sent into the UART are then converted into RS485 signals and sent onto the bus for all bus participants to pick up. The bytes that are read from the UART are broadcast on the bus by some other communication partner.

As baudrate for the UART, use the baudrate that the entire RS485 bus uses. I tested it using 115200 baud, 8N1 data format.

The RS485 facing interface consist of the pins 5, 6, 7 and 8. 5 being GND and 8 being VCC. The chip works perfectly using 5V for VCC. Pin 6 (dataline A) and Pin 7 (dataline B) are connected to the lines A and B of the RS485 bus. The client does not control chips 5, 6, 7 and 8. The transceiver chip is in control over those chips.

On the receiver side, the receiving system will also connect a UART to pins 1 and 4. The receiver is a perfect copy of the client as far as connections to the transceiver chip goes.

## SourceCode
The source code uses a UART for the transceiver chip and a second UART for debugging purposes. The second UART is your tool to connect a terminal emulator to the Arduino and to send messages to the Arduino which are then transmitted over RS485 to the bus.

## Testing the RS485 bus
You can use any RS485 to USB converter and plug that converted into your laptop or PC. Under Windows, the adapter will show up as a COM port. This COM Port can be used by any terminal emulator (YAT, microterm, picoterm, hyperterm, putty, ...).

Given the fact that you are using a known good RS485 to USB adapter, you can exclude one source of error and concentrate on the Arduino code for the RS485 transceiver.
