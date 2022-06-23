# AVRDUDE ARGUMENTS
MCU = atmega328p
ISP = arduino
PORT = /dev/ttyUSB0
BAUD = 9600UL
F_CPU = 16000000UL

# avr-gcc
CC = avr-gcc
CC_OBJCOPY = avr-objcopy
CFLAGS = -std=gnu99 -DF_CPU=$(F_CPU) -DBAUD=$(BAUD) -mmcu=$(MCU)
BUILD_DIR = Build
PROGRAM = usart_led
OBJECT_FILES = $(BUILD_DIR)/main.o $(BUILD_DIR)/USART.o

all: create_build_dir $(OBJECT_FILES)
	$(CC) $(CFLAGS)  $(OBJECT_FILES) -o $(BUILD_DIR)/$(PROGRAM).elf
	$(CC_OBJCOPY) -O ihex $(BUILD_DIR)/$(PROGRAM).elf $(BUILD_DIR)/$(PROGRAM).hex

create_build_dir:
	@if [ ! -e ${BUILD_DIR} ]; then mkdir ${BUILD_DIR}; fi

$(BUILD_DIR)/main.o: main.c
	$(CC) $(CFLAGS) -Os -c main.c -o $@

$(BUILD_DIR)/USART.o: USART.h USART.c
	$(CC) $(CFLAGS) -Os -DF_CPU=$(F_CPU) -DBAUD=$(BAUD) -mmcu=$(MCU) -c USART.c -o $@

flash_check:
	sudo avrdude -c $(ISP) -p $(MCU) -P $(PORT)

flash:
	sudo avrdude -c $(ISP) -p $(MCU) -P $(PORT) -U flash:w:$(BUILD_DIR)/$(PROGRAM).hex

clean:
	@if [ -e ${BUILD_DIR} ]; then rm -rf ${BUILD_DIR}; fi
