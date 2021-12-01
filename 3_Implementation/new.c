#include<avr/io.h>
#include "lcd.h"
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned int d=0,c=0,angle=0;
unsigned char tmp,tmp1,tmp2,tmp3;
unsigned int t,buzzer_on=0;
ISR(USART0_RX_vect)
  {
	unsigned char angle_led_on_pattern[8] = {0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F};	// led pattern for angle
	unsigned int angle_led;
	PORTF= PORTF | 0b00000010;		// sound buzzer
	buzzer_on=1;
	d++;						// byte counter
	tmp=UDR0;					// save received byte
	tmp=tmp-0x30;				// convert it into decimal
	if(d==1) tmp1=tmp;			// get first 3 bytes
	else if(d==2) tmp2=tmp;
	else if(d==3) tmp3=tmp;  
	else if(d==9)				// when all 9 byte received
	{
		d=0;					// reset byte counter
		t=tmp1*100+tmp2*10+tmp3;	// calculate distance
		lcd_cmd(0x94);
		lcd_str("object detected");		// display message
		lcd_cmd(0xD4);			
		lcd_str("dist=");			// and distance
		lcd_num(t);
		lcd_str("cm");
		angle_led=angle;		// indicate angle on LED dial
		if(angle_led <=8)
		  {
		  	PORTG = 0x0F;
			angle_led-=1;
			PORTC = angle_led_on_pattern[angle_led];
		  }	
		else
		  {
		  	PORTC = 0xFF;
			angle_led-=9;
			PORTG = angle_led_on_pattern[angle_led];
		  }				
	}
  }
angle_disp()
  {
  	lcd_cmd(0xC0);
	switch(angle)			// for different angle values
	  {
		case 1:			// display angle on LCD
			if((c%2)==0) lcd_str("angle:30");
			else lcd_str("angle:330");
			break;
		case 2:
			if((c%2)==0) lcd_str("angle:60");
			else lcd_str("angle:300");
			break;
		case 3:
			if((c%2)==0) lcd_str("angle:90");
			else lcd_str("angle:270");
			break;
		case 4:
			if((c%2)==0) lcd_str("angle:120");
			else lcd_str("angle:240");
			break;
		case 5:
			if((c%2)==0) lcd_str("angle:150");
			else lcd_str("angle:210");
			break;
		case 6:
			lcd_str("angle:180");
			break;
		case 7:
			if((c%2)==0) lcd_str("angle:210");
			else lcd_str("angle:150");
			break;
		case 8:
			if((c%2)==0) lcd_str("angle:240");
			else lcd_str("angle=120");
			break;
		case 9:
			if((c%2)==0) lcd_str("angle:270");
			else lcd_str("angle:90");
			break;
		case 10:
			if((c%2)==0) lcd_str("angle=300");
			else lcd_str("angle:60");
			break;
		case 11:
			if((c%2)==0) lcd_str("angle:330");
			else lcd_str("angle:30"); 
			break;
		case 12:
			lcd_str("angle:0 deg  ");
			break;
	  }
  }
void UARTInit(void)
{
	UBRR0H = 0x00;
	UBRR0L = 0x33;					// for 9600 baud rate
	UCSR0B = (1<<RXEN0) | (1<<RXCIE0);	//enable reception
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
}
ISR(INT4_vect)
  {
  	PORTB=PORTB & 0b10011111;			// motor stop
	_delay_ms(200);					// wait for 200 ms
	c++;	
	angle=0;			// reset angle to reference position
  }
void main()
  {  	
	DDRB=0x70;						// initialize ports
	DDRF=0x03;
	PORTB=0x10;
	PORTF=0x00;
	DDRC = 0xFF;
	PORTC = 0xFF;
	DDRG = 0x0F;
	PORTG = 0x0F;
	UARTInit();				// initialize UART and LCD
	lcd_init();	
	lcd_cmd(0x01);
	lcd_str(" scanning........");	// start scanning process	
	MCUCR = (1<<ISC01) | (0<<ISC00); 	// enable interrupts
	EIMSK=(1<<INT4);
	sei();
	while(1)
	  {
	  	PORTF= PORTF | 0b00000001;			// operation LED ON
		angle++;						// increment angle
		angle_disp();					// display it
		if((c%2)==0) PORTB= PORTB | 0b00100000;// rotate motor
		else PORTB= PORTB | 0b01000000; 		// CLK or ACLK
		_delay_ms(1000);					// for 1 sec 
		PORTB=PORTB & 0b10011111;			// stop motor
		PORTF=PORTF & 0b11111110;		// operation LED off
		_delay_ms(1500);				// wait for 1.5 sec
		if(buzzer_on) 
  {
PORTF= PORTF & 0b11111101; // if buzzer is ON
buzzer_on=0;			// turn it off
  }	
	  }
  }
