CC = sdcc
AS = sdasz80

ASFLAGS = -plosgffw
CFLAGS = -mz80 --xram-loc 0x8000 --nostdinc --nostdlib --no-std-crt0 --std-c89

CFLAGS := $(CFLAGS) -I../../libc/include -L../../libc -llibc

C_SOURCES = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c) $(wildcard $(SRC_DIR)/*/*/*.c)
ASM_SOURCES = $(wildcard $(SRC_DIR)/*.s) $(wildcard $(SRC_DIR)/*/*.s) $(wildcard $(SRC_DIR)/*/*/*.s)
SOURCES = $(ASM_SOURCES) $(C_SOURCES)

C_REL = $(C_SOURCES:c=rel)
ASM_REL = $(ASM_SOURCES:s=rel)
REL = $(ASM_REL) $(C_REL)

.PHONY: all clean

all: sosh.rel	

%.rel: %.s
	$(AS) $(ASFLAGS) $@ $<

%.rel: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f bin/*
	rm -f *.asm *.lst *.rel *.sym
