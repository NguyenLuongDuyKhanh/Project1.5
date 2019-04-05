/*
 * test.cpp
 *
 * Created: 8/29/2017 2:20:20 PM
 * Author : Khanh
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#define SPIDDR DDRB
#define SPIPORT PORTB
#define TESTDDR DDRD
#define TESTPORT PORTD
#define MOSI 3
#define MISO 4
#define SCK 5
#define SS 0

void Rung();
void buzz();
void led();
void interruptinit();

int main(void)
{
    /* Replace with your application code */
	interruptinit();
	
    while (1) 
    {
	//led();
    }
}

void interruptinit()
{
	DDRD &= ~(1<<INT0);		//Chan INT0 = input
	MCUCR |= (1<<ISC01);	//Kich canh xuong
	GICR |= (1<<INT0);		//Cho phep INT0 hoat dong
	sei();
}

void onRung()
{
	DDRC |= (1<<0)|(1<<1);	//2 chan Rung la output
	PORTC |= (1<<0);		//1 chan duong, chan con lai am
}

void offRung()
{
	PORTC &= ~(1<<0);		//Tat chan duong di, 2 chan am se khong rung
}
void onBuzz()
{
	DDRC |= (1<<2)|(1<<3);
	PORTC |= (1<<3);
}

void offBuzz()
{
	PORTC &= ~(1<<3);
}

void onLed()
{
	DDRC |= (1<<4)|(1<<5);
	DDRC |= (1<<0)|(1<<1)|(1<<4)|(1<<5)|(1<<6)|(1<<7);
	
	PORTC |= (1<<4)|(1<<5);
	PORTD |= (1<<0)|(1<<1)|(1<<4)|(1<<5)|(1<<6)|(1<<7);
}

void offLed()
{
	PORTC &= ~(1<<4)&~(1<<5);
	PORTD &= ~(1<<0)&~(1<<1)&~(1<<4)&~(1<<5)&~(1<<6)&~(1<<7);
}
ISR(INT0_vect)
{
	onRung();
	onBuzz();
	onLed();
	_delay_ms(3000);
	offLed();
	offRung();
	offBuzz();
}