#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>



volatile int count =0;
volatile char buffer[30];
volatile int nova_menssagem = 0;

/*Função que sera executada toda vez q um byte for recebido na serial*/
ISR( USART0_RX_vect)
{
	char c;

	c= UDR0;
	if(c != '\n'){
		buffer[count] =  c;
		count++;
	}else{
		buffer[count] = 'X';
		nova_menssagem = 1;
		count =0;
	}
}

int main(void)
{	

	 
	//deshabilitar interrupções globais
	cli();

	init_uart(9600);
	
	//habilitar interrupções globais
	sei();

	

	
	
	

	// lcd_write_char('A');
	
	

	// lcd_write_str("Testeaaaaaaaaaaaaaa");

	
	
	while (1) {

		if(nova_menssagem ==1){
			uart_puts(buffer);
			nova_menssagem =0;
		}
		// // lcd_clear();
		// _delay_ms(1000);
		
		// lcd_write_char('a');
		// // lcd_set_pos(1,0);
		 
		// _delay_ms(1000);

		
	}
}