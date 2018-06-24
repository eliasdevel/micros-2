# Define o nome do projeto.
TARGET = blink

# Define os fontes do projeto.
SOURCES += \
	main.c \
	leds.c \
	uart.c \
	display.c

# Modelo do microcontrolador.
#   Arduino Uno  = atmega328p
#   Arduino Mega = atmega2560
MCU = atmega328p

# Frequência do cristal.
F_CPU = 16000000UL

# Opções do programador.
#  PG 	   = arduino (Arduino Uno) | wiring (Arduino Mega/ADK)
#  PG_PORT = porta de comunicação
#  PG_BAUD = velocidade de gravação
PG	= arduino
PG_PORT	= /dev/ttyUSB0
PG_BAUD	= 57600 

# Outras configurações.
CC 	= avr-gcc
OBJCOPY = avr-objcopy
CP 	= cp
DEL 	= rm

CFLAGS  = -Os -Wall -Wextra -g -std=gnu99 -DF_CPU=$(F_CPU) 
ARCH	= -mmcu=$(MCU)

OBJECTS  = $(SOURCES:.c=.o)

all: $(TARGET).hex

%.hex: %.elf
	$(OBJCOPY) -R .eeprom -j .text -j .data -O ihex $< $@

$(TARGET).elf: $(OBJECTS)
	$(CC) $(CFLAGS) $(ARCH) $^ -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $(ARCH) -o $@ $(CCFLAGS) $<

clean:
	$(DEL) -f *.o *.elf *.hex

prog: $(TARGET).hex
	sudo avrdude  -c $(PG) -p $(MCU) -P $(PG_PORT) -b $(PG_BAUD) -U flash:w:$<:i
