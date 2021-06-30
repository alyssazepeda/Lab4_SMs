/*	Author: Alyssa Zepeda
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: PB0 and PB1 each connect to an LED, and 
 *	PB0's LED is initially on. Pressing a button connected to PA0 
 *	turns off PB0's LED and turns on PB1's LED, staying that way 
 *	after button release. Pressing the button again turns off PB1's 
 *	LED and turns on PB0's LED.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
//start, off, off release, on press, on release, off press
enum states {start, off_r, on_p, on_r, off_p} state;

int TickFct() {
	switch(state) { //transitions
		case start:
			state = off_r;
			break;
		case off_r:
			state = (PINA == 0x01) ? on_p : off_r;
			break;
		case on_p:
			state = (PINA == 0x01) ? on_p : on_r;
			break;
		case on_r:
			state = (PINA == 0x01) ? off_p : on_r;
			break;
		case off_p:
			state = (PINA == 0x01) ? off_p : off_r;
			break;
		default:
			state = start;
			break;
	}
	switch(state) { //actions
		case off_r:
			PORTB = 0x01;
			break;
		case on_p:
			PORTB = 0x02;
			break;
		case on_r:
			break;
		case off_p:
			PORTB = 0x01;
			break;
		default: break;
	}
}


int main(void) {
 	DDRA = 0X00; PINA = 0XFF; //A IS INPUT
	DDRB = 0XFF; PINB = 0X00; //B IS OUTPUT
  	state = start;
    	while (1) {
		TickFct();
    	}
    return 1;
}
