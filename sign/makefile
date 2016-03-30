#make all

.PHONY: all 
all: main 

CC = sdcc -I inc 

BUILD_DIR = build

SRC = $(wildcard *.c)
REL = $(subst .c,.rel,$(SRC))
BUILD_REL = $(addprefix $(BUILD_DIR)/,$(REL))

main: $(BUILD_REL)
	$(CC) $(BUILD_REL) -o build/main.ihx
	packihx build/main.ihx > build/main.hex
	objcopy -I ihex -O binary build/main.hex build/main.bin

build/%.rel: %.c
	$(CC) -c $< -o $@

flash:
	sudo python ../stcflash.py --port /dev/ttyUSB1 -l 2400 build/main.bin

clean:
	rm -rf build/*
