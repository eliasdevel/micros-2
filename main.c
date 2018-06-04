#include <avr/io.h>
#include <util/delay.h>
#include "display.h"





int main(void)
{
	lcd_init();

	// lcd_write_char('A');
	
	lcd_write_str("Testeaaaaaaaaaaaaaa");

	lcd_set_pos(1,2);
	lcd_write_str("1234");
	
	
	
	
	while (1) {
		
	}
}