CC = avr-gcc
CC_OBJCOPY = avr-objcopy
CFLAGS = -std=gnu99
BUILD_DIR = Build
PROGRAM = cylon_led

# AVRDUDE ARGUMENTS
MICROCONTROLLER = atmega328p
ISP = arduino
PORT = /dev/ttyUSB0
BAUD = 115200
CLK_FREQUENCY = 1000000

all: create_build_dir
	cd $(BUILD_DIR) && $(CC) $(CFLAGS) -Os -DF_CPU=$(CLK_FREQUENCY) -mmcu=$(MICROCONTROLLER) -c ../$(PROGRAM).c
	cd $(BUILD_DIR) && $(CC) $(CFLAGS) -DF_CPU=$(CLK_FREQUENCY) -mmcu=$(MICROCONTROLLER) -o $(PROGRAM).elf $(PROGRAM).o
	cd $(BUILD_DIR) && $(CC_OBJCOPY) -O ihex $(PROGRAM).elf $(PROGRAM).hex
	cd $(BUILD_DIR) && rm $(PROGRAM).o
	cd $(BUILD_DIR) && rm $(PROGRAM).elf

create_build_dir:
	@if [ ! -e ${BUILD_DIR} ]; then mkdir ${BUILD_DIR}; fi

flash_check:
	sudo avrdude -c $(ISP) -p $(MICROCONTROLLER) -P $(PORT)

flash:
	sudo avrdude -c $(ISP) -p $(MICROCONTROLLER) -P $(PORT) -U flash:w:$(BUILD_DIR)/$(PROGRAM).hex
