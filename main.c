#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


typedef unsigned char   uint8_t;


volatile int pisca =0;
volatile int count =0;
volatile char buffer[30];
volatile int nova_menssagem = 0;
short temp =0;

char tosend[30];



/*Função que sera executada toda vez q um byte for recebido na serial*/
ISR(USART_RX_vect)
{
    uint8_t c;
    
    c= UDR0;

    PORTB |= (1<<5);
    // uart_putc(c); 
	
    if(  c != 0xE7 ){
            
        buffer[count] =  c;
        count++;
    }else{
        buffer[count] = 0x00;
        nova_menssagem = 1;
        count =0;
    }
}

uint8_t checksum(char b[]){
            int i =0;
    uint8_t sm = 0;
    if(b[0] ==0x7E){
            for( i =0; i < b[1]; i++ ){
                sm = sm + b[i+2];
            }
    }
            
    return (uint8_t) 0xFF - sm;         
}

void check_leds(char b[]){
		if(b[3] & 0x01){
			PORTD |= (1<< 2);
		}else{
			PORTD &= ~(1 << 2);
		}
		if(b[3] & 0x02){
			PORTD |= (1<< 3);
		}else{
			PORTD &= ~(1 << 3);
		}
		if(b[3] & 0x04){
			PORTD |= (1<< 4);
		}else{
			PORTD &= ~(1 << 4);
		}
}

 void write_msg( char b[]){
        int i =0;
        
            for( i =0; i < b[1]+3; i++ ){
                uart_putc(b[i]);
            }
    
        uart_putc(0xe7);

}



void testMessage( char b[]){

        uint8_t check;
    
        // uart_puts(buffer);
        
            
        check = checksum(b);

        //Try if message is valid
        if((uint8_t) check == (uint8_t) b[b[1]+2]){
            


            if(b[2] == 0x30){
                b[2] = 0x31;

		check_leds(b);

                b[4] = checksum(b);
                
                write_msg(b);
               
            }

            if(b[2] == 0x20){
                b[1] = 3;
                b[2] = 0x21;
		
                b[4] =  8 << temp;
                b[3] =   temp;

                b[4] = checksum(b);
                
                write_msg(b);
               
            }

        }


}


void adc_init(void)
{
	/* Configura referência de tensão para 5 V e configura
	   o pino AD0 como analógico. */
	ADMUX = 1 << 6;

	/* Liga o conversor analógico e configura o prescaler de aquisição
	   para 128. */
	ADCSRA = (1 << 7) | (1 << 2) | (1 << 1) | (1 << 0);

	/* Desabilita o circuito digital do pino analógico AD0. */
	DIDR0 = (1 << 0);
}

int adc_read(int ch)
{
	int resultado = 0;
	 ADMUX |= 1 << ch+6;
	/* Inicia uma nova conversão. */
	ADCSRA |= (1 << 6);

	/* Aguarda enquanto está convertendo. */
	while (!(ADCSRA & (1 << 4)));

	/* Obtém o resultado da conversão. */
	resultado = ADCL;
	resultado |= ADCH << 8;

	return resultado;
}

int read_ADC10(){
	// return the sum of ten reads
	int i=0;
	int val=0;
	for (i=0;i<10;i++){
		val+=adc_read(0);
	}
	return val/10;
}

  
int main(void)
{   

     DDRB = (1 << 5);
     DDRD = (1 << 2) | (1 << 3) | (1 << 4) ;
	
    adc_init();
    //lcd_init();
    //deshabilitar interrupções globais
    cli();
    
	

    init_uart(115200);
    
    //habilitar interrupções globais
    sei();

   

    
    
    int i =0;
    while (1) {
	temp = (short) read_ADC10();
	temp = (3.3*temp*100)/1023.0;

        
        
        if(nova_menssagem ==1){
        	
            
            testMessage(buffer);
             
            

            nova_menssagem =0;
        }       
    }
}



  


   

	


