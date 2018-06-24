#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


typedef unsigned char   uint8_t;


volatile int pisca =0;
volatile int count =0;
volatile char buffer[30];
volatile int nova_menssagem = 0;

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





  
int main(void)
{   

     DDRB = (1 << 5);

    //lcd_init();
    //deshabilitar interrupções globais
    cli();
    


    init_uart(115200);
    
    //habilitar interrupções globais
    sei();

   

    
    
    int i =0;
    while (1) {
        // _delay_ms(1000);
        // uart_puts("merda");
        
        if(nova_menssagem ==1){
        	
            
            testMessage(buffer);
             
            

            nova_menssagem =0;
        }       
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
    void testMessage( char b[]){

        uint8_t check;
    
        // uart_puts(buffer);
        
            
        check = checksum(b);

        //Try if message is valid
        if((uint8_t) check == (uint8_t) b[b[1]+2]){
            


            if(b[2] == 0x30){
                b[2] = 0x31;
                b[4] = checksum(b);
                
                write_msg(b);
               
            }

            if(b[2] == 0x20){
                b[1] = 2;
                b[2] = 0x21;
                b[3] = 0x10;
                b[4] = checksum(b);
                
                write_msg(b);
               
            }

        }


    }


    void write_msg( char b[]){
        int i =0;
        
            for( i =0; i < b[1]+3; i++ ){
                uart_putc(b[i]);
            }
    
        uart_putc(0xe7);

    }


