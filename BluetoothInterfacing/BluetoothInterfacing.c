/*
* BluetoothInterfacing.c
*
* Author: Shivam Mahesh Potdar (github/shivampotdar) (shivampotdar99@gmail.com)
* This code forms an interface for HC05 bluetooth module with Firebird
*
* HC05 module is connected to UART3 interface of the ATMEGA2560 on Firebird
* It continuously monitors the HC05 module for serial input from bluetooth device such
* as a phone and prints the same on LCD screen on Firebird.
* For this setup Serial Bluetooth Terminal (from Play Store, publisher Kai Morich) was used.
* The settings done in the app are : Character delay: 5ms, Newline: None
* The program continuosly takes input from the app and prints on LCD, there is no clear condition,
* the input just rolls over to next line on crossing first row and then restarts for 1,1 if entire LCD is filled
* 
*		Connections
* HC-05 <---------> Firebird Expansion Header
*  Vcc              Pin21/22 (5V)
*  GND				Pin23/24 (Ground)
*  RX				Pin46 (TXD3) 				
*  TX				Pin45 (RXD3)
*/

#define F_CPU 14745600
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include "lcd.h"

volatile unsigned char data;				// to store the data from ISR
int i=0;									// for LCD character printing
int bufctr = 0;								// buffer counter
int bufsize = 32;							// buffer size (maxm characters 16x2 LCD can show)

char input_buf[32];							// input buffer to store input


/****************** uart3_init ****************************************
Input:   None
Output:  None
Remarks: Enable UART3 pins with required settings
************************************************************************************/ 
void uart3_init()
{
	UCSR3B = 0x00;							//disable while setting baud rate
	UCSR3A = 0x00;
	UCSR3C = 0x06;							// Async UART, Parity disabled, 1 stop bit, 8 bit size
	UBRR3L = 0x5F; 							// 9600BPS at 14745600Hz
	UBRR3H = 0x00;							
	UCSR3B = 0x98;							// RX interrupt, Receiver, Transmitter enable
}

/****************** USART3_RX_VECT ****************************************
Remarks: ISR triggered on receiving data through HC05, stores it in buffer, restarts if buffer filled
************************************************************************************/
ISR(USART3_RX_vect)
{
	data = UDR3;
	if(bufctr==bufsize)
	bufctr=0;
	input_buf[bufctr]=data;
	bufctr++;
}

/****************** init_devices() ****************************************
Input:   None
Output:  None
Remarks: Initialise ports and devices
************************************************************************************/
void init_devices()
{
	cli();									// clear global interrupt flag
	lcd_port_config();						// config PORTC for LCD
	lcd_init();								// LCD mode and other settings
	uart3_init();							// init UART3
	sei();									// set global interrupt flag
}

int main(void)
{
	init_devices();
	char l1[16],l2[16];						// to separate input buffer into two lines for LCD
	while(1)
	{
		for(int i=0;i<=15;i++)				
			l1[i] = input_buf[i];
		for(int i=16;i<=bufsize;i++)
			l2[i-16] = input_buf[i];
		lcd_string(1,1,l1);					// print input lines on LCD
		lcd_string(2,1,l2);
	}
}