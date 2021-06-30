/*	Author: Alyssa Zepeda
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #2
 *	Exercise Description: Buttons are connected to PA0 and PA1. 
 *	Output for PORTC is initially 7. Pressing PA0 increments PORTC 
 *	once (stopping at 9). Pressing PA1 decrements PORTC once (stopping 
 *	at 0). If both buttons are depressed (even if not initially 
 *	simultaneously), PORTC resets to 0.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
//start, off, off release, on press, on release, off press
enum states {start,check, inc, dec, wait1, wait2} state;

int TickFct() {
	switch(state) { //transitions
		case start:
			PORTC = 0X07;
			state = check;
		       	break;
		case check:
			if((PINA & 0x03) == 0x01) {
				state = inc;
			}
			else if((PINA & 0x03) == 0x02) {
				state = dec;
			}
			break;
		case inc:
			state = wait1;
			break;
		case dec:
			state = wait2;
			break;
		case wait1:
			state = ((PINA & 0x03) == 0x01) ? wait1 : check;
			break;
		case wait2:
			state = ((PINA & 0x03) == 0x02) ? wait2 : check;
			break;
		default:
			state = start;
			break;	
	}
	switch(state) { //actions
		case start:
			break;
		case check:
			if((PINA & 0x03) == 0x03) {
				PORTC = 0;
			}
			break;
		case inc:
			if(PORTC < 0x09) {
				PORTC += 1;
			}
			break;
		case dec:
			if(PORTC > 0x00) {
				PORTC -=1;
			}
			break;
		case wait1:
		case wait2:
			if((PINA & 0x03) == 0x03) {
				PORTC = 0;
			}
			break;
		default: break;
	}
}


int main(void) {
 	DDRA = 0X00; PINA = 0XFF; //A IS INPUT
	DDRC = 0XFF; PINC = 0X00; //B IS OUTPUT
  	state = start;
    	while (1) {
		TickFct();
    	}
    return 1;
}
