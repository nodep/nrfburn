# Name: Makefile
# Project: bootloadHID
# Author: Christian Starkjohann
# Creation Date: 2007-03-19
# Tabsize: 4
# Copyright: (c) 2007 by OBJECTIVE DEVELOPMENT Software GmbH
# License: GNU GPL v2 (see License.txt)
# This Revision: $Id$

DEVICE = atmega88p
BOOTLOADER_ADDRESS = 1800
F_CPU  = 12000000
TARGET = bootloader

VPATH = ../usbdrv:../../mcu-lib

FUSEX = 0xf8
FUSEH = 0xdd
FUSEL = 0xff

OBJECTS = main.o usbdrvasm.o usbdrv.o

#AVRDUDE = avrdude -c dragon_isp -P usb -p $(DEVICE)
AVRDUDE = avrdude -c stk500v2 -P avrdoper -p $(DEVICE)
LDFLAGS = -Wl,--relax,--gc-sections -Wl,--section-start=.text=$(BOOTLOADER_ADDRESS)
COMPILE = avr-gcc -Wall -Os -flto -fno-move-loop-invariants -fno-tree-scev-cprop -fno-inline-small-functions -I../usbdrv -I../../mcu-lib -I. -mmcu=$(DEVICE) -DF_CPU=$(F_CPU) -DDEBUG_LEVEL=0

hex: $(TARGET).hex

$(TARGET).hex: $(OBJECTS)
	$(COMPILE) -o $(TARGET).elf $(OBJECTS) $(LDFLAGS)
	rm -f $(TARGET).hex $(TARGET).eep.hex
	avr-objcopy -j .text -j .data -O ihex $(TARGET).elf $(TARGET).hex
	avr-size $(TARGET).hex

.c.o:
	$(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@

flash: all
	$(AVRDUDE) -U flash:w:$(TARGET).hex:i

fuse:
	$(AVRDUDE) -U hfuse:w:$(FUSEH):m -U lfuse:w:$(FUSEL):m -U efuse:w:$(FUSEX):m
	
read_flash:
	$(AVRDUDE) -U flash:r:read.hex:i

read_fuse:
	$(AVRDUDE) -U hfuse:r:-:h -U lfuse:r:-:h -U efuse:r:-:h
	
lock:
	$(AVRDUDE) -U lock:w:0x2f:m

clean:
	rm -f $(TARGET).hex $(TARGET).elf $(OBJECTS)

all: clean $(TARGET).hex
	
disasm:	$(TARGET).elf
	avr-objdump -d $(TARGET).elf
