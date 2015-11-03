# select target board
#TARGET_BOARD = USBASP
TARGET_BOARD = NRFBURN


TARGET  = nrfavr
ifeq ($(TARGET_BOARD),NRFBURN)
	DEVICE  = atmega88a
else ifeq ($(TARGET_BOARD),USBASP)
	DEVICE  = atmega8a
else
    $(error Please set TARGET_BOARD to either NRFBURN or USBASP)
endif

F_CPU   = 12000000

AVRDUDE = avrdude -c dragon_isp -P usb -p $(DEVICE)
#AVRDUDE = avrdude -c stk500v2 -P avrdoper -p $(DEVICE)

VPATH = usbdrv:../mcu-lib

CFLAGS  = -I. -Wall -Os -Iusbdrv -I../mcu-lib -flto
ifeq ($(TARGET_BOARD),USBASP)
	CFLAGS += -DON_USBASP
endif
LFLAGS  = -Wl,--relax -flto
#LFLAGS += -u vfprintf -lprintf_min

COMPILE = avr-gcc -mmcu=$(DEVICE) -DF_CPU=$(F_CPU) $(CFLAGS)

OBJECTS = main.o prg_spi.o prg_parse.o usb.o usbdrv.o usbdrvasm.o
ifeq ($(TARGET_BOARD),NRFBURN)
	OBJECTS += avrdbg.o 
endif

hex: $(TARGET).hex

$(TARGET).hex: $(OBJECTS)
	$(COMPILE) -o $(TARGET).elf $(OBJECTS) $(LFLAGS)
	rm -f $(TARGET).hex $(TARGET).eep.hex
	avr-objcopy -j .text -j .data -O ihex $(TARGET).elf $(TARGET).hex
	avr-size -C --mcu=$(DEVICE) $(TARGET).elf

flash: all $(TARGET).hex
	$(AVRDUDE) -U flash:w:$(TARGET).hex:i

clean:
	rm -f $(TARGET).hex $(TARGET).elf $(OBJECTS)

read_fuse:
	$(AVRDUDE) -U hfuse:r:-:h -U lfuse:r:-:h -U efuse:r:-:h

# $(COMPILE) -S -fverbose-asm $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@

.c.o:
	$(COMPILE) -c $< -o $@

all: clean $(TARGET).hex
