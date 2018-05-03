CC = sdcc
AS = sdasz80

ASFLAGS = -plosgffw
CFLAGS = -mz80 --code-loc 0xA000 --data-loc 0xA800 --nostdinc --nostdlib --no-std-crt0 --std-c99 --Werror

CFLAGS := $(CFLAGS) -I../../libc/include -L../../libc -llibc

C_SOURCES = $(wildcard *.c)
ASM_SOURCES = $(wildcard *.s)
SOURCES = $(ASM_SOURCES) $(C_SOURCES)

C_REL = $(C_SOURCES:c=rel)
ASM_REL = $(ASM_SOURCES:s=rel)
REL = $(ASM_REL) $(C_REL)

.PHONY: all clean

all: sosh.bin

sosh.bin: sosh.ihx
	makebin -s 65536 $< $@
	mv $@ full_$@
	dd if=full_$@ of=$@ bs=1 skip=40960 count=2048

sosh.ihx: $(REL)
	$(CC) $(CFLAGS) $^ -o $@

%.rel: %.s
	$(AS) $(ASFLAGS) $@ $<

%.rel: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.asm *.lst *.rel *.sym *.noi *.map *.lk *.bin *.ihx *.bin.bak
