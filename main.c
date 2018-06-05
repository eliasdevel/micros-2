#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "display.h"


volatile int pisca =0;
volatile int count =0;
volatile char buffer[30];
volatile int nova_menssagem = 0;


/*Captura a interrupção do Timer 1 gerada no overflow: 0xFFFF -> 0x0000*/
ISR(TIMER1_OVF_vect)
{
	if (pisca){
         PORTB ^= 1 << 7;
	}
         /*Valor inicial para o contador*/
        //  TCNT1 = 3035; // para 0,5 sec
         TCNT1 = 34285; // para 1seg
	
}


/*Função que sera executada toda vez q um byte for recebido na serial*/
ISR( USART0_RX_vect)
{
	char c;

	c= UDR0;


	if(c != '\n'){
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
	//Timer 1 modo de operação normal.
    TCCR1A = 0x00;



    /*Configura Timer 1 com preescala 8= 1mhz*/
    // TCCR1B = (1 << CS11) | (1 << CS10) ; // para 0.5 segundos
    TCCR1B = (1 << CS12)  ; //para 1 segundo

    /*Habilita Interrupção do Timer 1 quando ocorrer o estouro 0xFFFF -> 0x0000. */
    TIMSK1 = 1 << TOIE1;




	init_uart(9600);
	
	//habilitar interrupções globais
	sei();

	lcd_init();

	 
	

	
	
	// lcd_write_char('A');
	
	

	//  lcd_write_str("Testeaaaaaaaaaaaaaa");

	
	int i =0;
	while (1) {

		if(nova_menssagem ==1){
			
			// lcd_write_char(buffer[2]);
			
			testMessage(buffer);
			uart_puts(buffer);

			nova_menssagem =0;
		}		
	}
}
	void testMessage( char b[]){
		if(b[0] == 'S'){
			if (b[1] == 'T'){
				testLedMessage(b);
			}
			if (b[1] == 'M'){
				testLcdMessage(b);
			}
		}
	}

	void testLedMessage(char b[]){	
				if (b[2] == 'L'){
					pisca =0;
					PORTB |= (1 << 7);
				}else if(b[2] == 'D'){
					pisca =0;
					PORTB &= ~(1<<7);	
				}else if(b[2] == 'X'){
					pisca = ~(pisca);
				
				}
		
	}

	void testLcdMessage(char b[]){
				if (b[2] == 'X'){
					
					lcd_clear();
					lcd_set_pos(0,0);
				}else if(b[2] == 'B'){
					lcd_write_message(b);
				}
	}

	void lcd_write_message(char b[]){
		int i =3;
		lcd_set_pos(0,0);
		while(b[i] != '\0'){
			
			lcd_write_char(b[i]);
			i++;
		}
	}