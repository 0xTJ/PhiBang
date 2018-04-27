CC = sdcc
AS = sdasz80

ASFLAGS = -plosgffw
CFLAGS = -mz80 --xram-loc 0x8000 --nostdinc --nostdlib --no-std-crt0 --std-c99 --Werror

CFLAGS := $(CFLAGS) -I../../libc/include -L../../libc -llibc

C_SOURCES = $(wildcard *.c)
ASM_SOURCES = $(wildcard *.s)
SOURCES = $(ASM_SOURCES) $(C_SOURCES)

C_REL = $(C_SOURCES:c=rel)
ASM_REL = $(ASM_SOURCES:s=rel)
REL = $(ASM_REL) $(C_REL)

.PHONY: all clean

all: sosh.bin

sosh.bin: $(REL)
	$(CC) $(CFLAGS) $< -o $@

%.rel: %.s
	$(AS) $(ASFLAGS) $@ $<

%.rel: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.asm *.lst *.rel *.sym
