/*
 * MorseCode.c
 *
 * Created: 7/13/2014 PM 10:19:02
 *  Author: Koji
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL  // 8 MHz
#include <util/delay.h>

#define MORSE_UNIT 250L // 250ms

#define MORSE_DDR DDRB
#define MORSE_PORT PORTB
#define MORSE_OUTPINBIT PINB4
#define SELECT_PIN PINB
#define SELECT_INPINBIT PB3

void inCodeBreak()
{
	_delay_ms(MORSE_UNIT);
}
void plusCharBreak()
{
	_delay_ms(MORSE_UNIT * 2L);
}
void plusWordBreak()
{
	_delay_ms(MORSE_UNIT * 6L);
}

#define tone(count) \
{ \
	MORSE_PORT |= _BV(MORSE_OUTPINBIT); \
	_delay_ms(MORSE_UNIT * count); \
	MORSE_PORT &= ~_BV( MORSE_OUTPINBIT); \
	inCodeBreak(); \
}
void shortTone()
{
	tone(1L);
}
void longTone()
{
	tone(3L);
}

//void shortTone()
//{
	//MORSE_PORT |= (1 << MORSE_OUTPINBIT);
	//_delay_ms(MORSE_UNIT);
	//MORSE_PORT &= !(1 << MORSE_OUTPINBIT);
	//inCodeBreak();
//}
//void longTone()
//{
	//MORSE_PORT |= (1 << MORSE_OUTPINBIT);
	//_delay_ms(MORSE_UNIT * 3L);
	//MORSE_PORT &= !(1 << MORSE_OUTPINBIT);
	//inCodeBreak();
//}

void charK()
{
	longTone();
	shortTone();
	longTone();
}

void charY()
{
	longTone();
	shortTone();
	longTone();
	longTone();
}

void litName()
{
	charY();
	plusCharBreak();
	charK();
	plusWordBreak();
	charY();
	plusCharBreak();
	charK();	
}

void blink()
{
	int times = 10;
	//while(1)
	while (times > 0)
	{
		MORSE_PORT ^= (1 << MORSE_OUTPINBIT);
		_delay_ms(1000);
		times--;
	}
}

int main(void)
{
	MORSE_DDR = 0xff ^ _BV(SELECT_INPINBIT); // set for output other than SELECT_INPINBIT
	MORSE_PORT = _BV(SELECT_INPINBIT); // configure pull-up for SELECT_INPINBIT
	_delay_ms(2000);
	if (bit_is_clear(SELECT_PIN, SELECT_INPINBIT)) {
		blink();
	} else {
		litName();
	}
	//blink();
	//_delay_ms(2000);
	//litName();

	MORSE_PORT &= ~_BV(MORSE_OUTPINBIT);
}