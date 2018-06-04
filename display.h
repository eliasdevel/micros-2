/*MEGA
PINOUT:
RS = PH5
EN = PH6
D4 = PG5
D5 = PE3
D6 = PH3
D7 = PH4
*/

extern void lcd_init(void);
extern void lcd_home(void);
extern void lcd_clear(void);
extern void lcd_write_nibble(unsigned char data);
extern void lcd_set_mode(unsigned char m);
extern void lcd_pulse_en(void);
extern void lcd_cmd(unsigned char cmd);
extern void lcd_write_char( char c);
extern void lcd_write_str(unsigned char data);
extern void lcd_write_nibble(unsigned char data);   
extern void lcd_line(int line);
extern void lcd_set_pos(int l, int c);




