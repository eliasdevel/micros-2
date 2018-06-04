#include <avr/io.h>
#include "leds.h"

void leds_config(void)
{
    /* Arduino Uno. */
	//DDRB = (1 << 5);

    /* Arduino Mega. */
    DDRB = (1 << 7);
    DDRE = (1 << 3);
    DDRH = (1 << 3) | (1 << 6);
    
   
 }

void leds_on(void)
{
    /* Arduino Uno. */
	//PORTB |= (1 << 5);

    /* Arduino Mega. */
	PORTB |= (1 << 7);
}


void led_red_on(void)
{
    PORTE |= (1<< 3);
}

void led_red_off(void)
{
    PORTE &= ~(1 << 3);
}

void led_blue_on(void)
{
    PORTH |= (1 << 3);
}

void led_blue_off(void)
{
    PORTH &= ~(1 << 3);
}

void led_green_on(void)
{
    PORTH |= (1 << 6);
}

void led_green_off(void)
{
    PORTH &= ~(1 << 6);
}

void rgb(int c){
       if(c & 0x01){
            led_red_on();            
        }else{
            led_red_off();            
        }
         if(c & 0x02){
            led_green_on();            
        }else{ 
            led_blue_off(); 
        }
        if(c & 0x04){
            led_blue_on();            
        }else{
            led_blue_off(); 
        }
    
}





void leds_off(void)
{
    /* Arduino Uno. */
	//PORTB &= ~(1 << 5);

    /* Arduino Mega. */
	PORTB &= ~(1 << 7);
}

