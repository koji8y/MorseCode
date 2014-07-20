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

# define MORSE_DDR DDRB
# define MORSE_PORT PORTB
# define MORSE_PIN PINB4

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
	MORSE_PORT |= _BV(MORSE_PIN); \
	_delay_ms(MORSE_UNIT * count); \
	MORSE_PORT &= ~_BV( MORSE_PIN); \
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
	//MORSE_PORT |= (1 << MORSE_PIN);
	//_delay_ms(MORSE_UNIT);
	//MORSE_PORT &= !(1 << MORSE_PIN);
	//inCodeBreak();
//}
//void longTone()
//{
	//MORSE_PORT |= (1 << MORSE_PIN);
	//_delay_ms(MORSE_UNIT * 3L);
	//MORSE_PORT &= !(1 << MORSE_PIN);
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

int main(void)
{
	MORSE_DDR = 0xff;
	MORSE_PORT = 0x00;
	_delay_ms(2000);
	/*
	int times = 10;
	//while(1)
	while (times > 0)
	{
		MORSE_PORT ^= (1 << MORSE_PIN);
		_delay_ms(1000);
		times--;
	}
	*/
	charY();
	plusCharBreak();
	charK();
	plusWordBreak();
	charY();
	plusCharBreak();
	charK();

	MORSE_PORT &= ~_BV(MORSE_PIN);
}