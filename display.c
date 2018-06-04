#include <avr/io.h>
#include <util/delay.h>

void init(){
    
}

void lcd_write_nibble(unsigned char data)
{
	if (data & (1 << 0)) {
		PORTG |= (1 << 5);
	} else {
		PORTG &= ~(1 << 5);
	}

	if (data & (1 << 1)) {
		PORTE |= (1 << 3);
	} else {
		PORTE &= ~(1 << 3);
	}

	if (data & (1 << 2)) {
		PORTH |= (1 << 3);
	} else {
		PORTH &= ~(1 << 3);
	}

	if (data & (1 << 3)) {
		PORTH |= (1 << 4);
	} else {
		PORTH &= ~(1 << 4);
	}
}


void lcd_set_mode(unsigned char m)
{
	if (m == 0) {
		PORTH &= ~(1 << 5);
	} else {
        PORTH |= (1 << 5);
	}
}

void lcd_pulse_en()
{
	PORTH &= ~(1 << 6);
	PORTH |= (1 << 6);
	PORTH &= ~(1 << 6);
	_delay_us(40);
}

void lcd_cmd(unsigned char cmd)
{
	lcd_set_mode(0);

	lcd_write_nibble(cmd >> 4);
	lcd_pulse_en();

	lcd_write_nibble(cmd);
	lcd_pulse_en();
}

void lcd_write_char(char c)
{
	lcd_set_mode(1);

	lcd_write_nibble(c >> 4);
	lcd_pulse_en();

	lcd_write_nibble(c);
	lcd_pulse_en();
}

void lcd_write_str(char *str)
{
	while (*str != '\0') {
		lcd_write_char(*str);
		str++;
	}

}


void lcd_clear()
{
	lcd_cmd(0x01);
	_delay_ms(2);
}
void lcd_init(){
	/* Configura como saída. */

	DDRB = 1 << 4;

	/* Acende a luz de fundo do LCD. */
	PORTB |= 1 << 4;

	/* Configura os pinos de saída conectados
	   ao LCD. */
	DDRH |= (1 << 3) | (1 << 4) |
			(1 << 5) | (1 << 6);
	DDRE |= (1 << 3);
	DDRG |= (1 << 5);

	lcd_set_mode(0);
	lcd_write_nibble(0x03);
	lcd_pulse_en();
	_delay_us(4100);

	lcd_set_mode(0);
	lcd_write_nibble(0x03);
	lcd_pulse_en();
	_delay_us(100);

	lcd_set_mode(0);
	lcd_write_nibble(0x03);
	lcd_pulse_en();

	lcd_set_mode(0);
	lcd_write_nibble(0x02);
	lcd_pulse_en();
	/***********/

	/* Configurações do LCD. */
	lcd_cmd(0x2C);
	lcd_cmd(0x0F);
	lcd_cmd(0x06);

	lcd_clear();
}

void lcd_home(){
    lcd_cmd(0x02);
}
void lcd_line(int line){
    if(line ==1){
        lcd_home();
    }else if(line ==2){
        // lcd_home();s
        lcd_cmd( 0xC0);
    }
}
void lcd_set_pos(int l, int c){
    int addr = 0x80;
    if(l !=0)
        addr += 0x40;
    addr += c;
    lcd_cmd(addr);
}

