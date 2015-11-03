ifeq ($(OS),Windows_NT)
	USBFLAGS  =
	USBLIBS   = -lhid -lsetupapi
	TARGET    = nrfburn.exe
	LINKFLAGS = -static-libgcc -static-libstdc++
else
	USBFLAGS  = `libusb-config --cflags`
	USBLIBS   = `libusb-config --libs`
	TARGET    = nrfburn
	LINKFLAGS =
endif
	
OBJS = hiddev.o main.o programmer.o flashmem.o bootloader.o progress.o

$(TARGET): $(OBJS)
	g++ $(LINKFLAGS) $(USBFLAGS) $(OBJS) -o $(TARGET) $(USBLIBS)

%.o: %.cpp
	g++ $(USBFLAGS) -Wall -O2 -c $(<) -o $*.o

clean:
	rm -f $(OBJS) $(TARGET)

all: clean $(TARGET)

strip:
	strip $(TARGET)
