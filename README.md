# HacktoberFest e-Yantra

---
![e-Yantra](logo.png "e-Yantra")
---

# Bluetooth Interfacing with Firebird Robot

This repository is for interfacing the HC-05 Bluetooth module with the Firebird Robot. You will need both the HC-05 sensor and the Firebird robot in order to work on this repository. This repository is open to all members of the e-Yantra community. Any member may contribute to this project without being a collaborator.

## How to contribute to this project
Fork this repository and get started. You are supposed to interface the sensor with the Firebird robot. You can use any of the Firebirds GPIO pins. A basic code template is given to help you get started. You are free to edit the code however you like. You must add comments wherever necessary.

## Rules
1. Use only the HC-05 sensor for this project.
2. You must only use the Firebird robot.
3. Display the output of the bluetooth module on the LCD of the Firebird robot
4. Using any readily available bluetooth app, the interfacing will be tested.
5. You must add comments in your code. File level, function level and line level comments are expected wherever necessary

## Winner
First PR that follows the given rules and completes the given task, is declared the winner at e-Yantra's discretion

Author Notes :

 BluetoothInterfacing.c

 Author: Shivam Mahesh Potdar (github/shivampotdar) (shivampotdar99@gmail.com)
 This code forms an interface for HC05 bluetooth module with Firebird

 HC05 module is connected to UART3 interface of the ATMEGA2560 on Firebird
 It continuously monitors the HC05 module for serial input from bluetooth device such
 as a phone and prints the same on LCD screen on Firebird.
 For this setup Serial Bluetooth Terminal (from Play Store, publisher Kai Morich) was used.
 The settings done in the app are : Character delay: 5ms, Newline: None
 The program continuosly takes input from the app and prints on LCD, there is no clear condition,
 the input just rolls over to next line on crossing first row and then restarts for 1,1 if entire LCD is filled
 
		Connections
 HC-05 <---------> Firebird Expansion Header
  Vcc           			Pin21/22 (5V)
  GND				Pin23/24 (Ground)
  RX				Pin46 (TXD3) 				
  TX				Pin45 (RXD3)
