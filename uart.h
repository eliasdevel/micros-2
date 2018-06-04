#ifndef UART_H
#define UART_H
	extern void init_uart(unsigned int baud_rate);
	extern void uart_putc(char c);
	extern void uart_getc(char c);
	extern void uart_puts(char *str);




#endif /* UART_H */
