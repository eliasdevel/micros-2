#include <avr/io.h>
#include <avr/interrupt.h>

void init_uart(unsigned int baud_rate){
	unsigned int baud = ((16000000/16)/(baud_rate)-1);
	/* Configura a taxa de comunicação nos registradores. */
	//UBRR0H =(unsigned char) baud >> 8;
	//UBRR0L =(unsigned char) baud;
	UBRR0H =0x00;
	UBRR0L = 0x07;
	/*HABILITA O MÓDULO DE RECEPÇÃO E ENVIO DE DADOS e hahilita interrupçao do modulo*/
	UCSR0B  = (1<< RXEN0) | (1 << TXEN0) | (1 << RXCIE0);

	/*MODO ASSÍNCRONO, SEM PARIDADE 1 STOP BIT E 8 BITS DE DADOS */
	UCSR0C = (1<< UCSZ01) | (1 << UCSZ00);
}



void uart_putc(char c){
/*testar para ver se registrador de saida esta livre*/	
		while(! (UCSR0A & (1<<UDRE0)));

		/*escrever no registrador*/
		UDR0 = c;

		/*Testa se o dado foi enviado corretamente*/
		while(! (UCSR0A & (1 << TXC0)));

}

void uart_puts(char *str)
{
	while(*str){
		uart_putc(*str++);
	}
}

char uart_getc (void){
		/*Testa se tem dados válidos*/
		if( UCSR0A &(1<<RXC0)){
			/*Remove o dado do buffer. */
			return UDR0;
		}
		return -1;
}


