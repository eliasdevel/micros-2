#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "display.h"


volatile int pisca =0;
volatile int count =0;
volatile char buffer[30];
volatile int nova_menssagem = 0;





/*Função que sera executada toda vez q um byte for recebido na serial*/
ISR( USART0_RX_vect)
{
	char c;

	c= UDR0;


	if(c != 0xE7){
		buffer[count] =  c;
		count++;
	}else{
		buffer[count] = '\0';
		nova_menssagem = 1;
		count =0;
	}
}





  
int main(void)
{	

	 DDRB = (1 << 7);

	//lcd_init();
	//deshabilitar interrupções globais
	cli();
	


	init_uart(9600);
	
	//habilitar interrupções globais
	sei();

	lcd_init();

	
	
	int i =0;
	while (1) {

		if(nova_menssagem ==1){
			
			// lcd_write_char(buffer[2]);
			
			testMessage(buffer);

			

			nova_menssagem =0;
		}		
	}
}
	void testMessage( char b[]){
		int i =0;
		// uart_puts(buffer);
		if(b[0] == 0x7E){
			while (i <= b[1] ){
				uart_putc(b[i+2]);
				
			}
		}
	}
