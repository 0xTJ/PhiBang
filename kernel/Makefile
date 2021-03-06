CC = sdcc
AS = sdasz80

ASFLAGS = -plosgffw
CFLAGS = -mz80 --xram-loc 0x8000 --nostdinc --nostdlib --no-std-crt0 --std-sdcc11

INC_DIR = include
SRC_DIR = src
OUT_DIR = bin

CFLAGS := $(CFLAGS) -I$(INC_DIR) -I../libc/include

C_SOURCES = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c) $(wildcard $(SRC_DIR)/*/*/*.c)
ASM_SOURCES = $(wildcard $(SRC_DIR)/*.s) $(wildcard $(SRC_DIR)/*/*.s) $(wildcard $(SRC_DIR)/*/*/*.s)
SOURCES = $(ASM_SOURCES) $(C_SOURCES)

C_REL = $(C_SOURCES:c=rel)
ASM_REL = $(ASM_SOURCES:s=rel)
REL = src/crt0.rel $(filter-out src/crt0.rel, $(ASM_REL) $(C_REL))

.PHONY: all clean

all: $(OUT_DIR)/kernel.bin

$(OUT_DIR)/kernel.ihx: $(REL)
	$(CC) $(CFLAGS) $^ -o $@

%.bin: %.ihx
	makebin $< $@

%.rel: %.s
	$(AS) $(ASFLAGS) $@ $<

src/kernel.rel: src/kernel.c ../initrd/initrd.img.h
	$(CC) $(CFLAGS) -c $< -o $@

%.rel: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f bin/*
	rm -f src/*.asm src/*.lst src/*.rel src/*.sym
	rm -f src/*/*.asm src/*/*.lst src/*/*.rel src/*/*.sym
	rm -f src/*/*/*.asm src/*/*/*.lst src/*/*/*.rel src/*/*/*.sym
