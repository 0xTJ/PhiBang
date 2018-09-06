CC = sdcc
AS = sdasz80

ASFLAGS = -plosgffw
CFLAGS = -mz80 --nostdinc --nostdlib --no-std-crt0 --std-sdcc11 --Werror

CFLAGS := $(CFLAGS) -I../../libc/include -L../../libc -llibc

C_SOURCES = $(wildcard *.c)
ASM_SOURCES = $(wildcard *.s)
SOURCES = $(ASM_SOURCES) $(C_SOURCES)

C_REL = $(C_SOURCES:c=rel)
ASM_REL = $(ASM_SOURCES:s=rel)
REL = $(ASM_REL) $(C_REL)

.PHONY: all clean

all: ../../initrd/initrd/sosh.bin

../../initrd/initrd/%.bin: %.bin
	cp $< $@

sosh.bin: sosh_0000.bin sosh_8000.bin
	python deltrelator.py $^ $@

sosh_0000.bin: sosh_0000.ihx
	makebin -s 65536 $< $@
	mv $@ full_$@
	dd if=full_$@ of=$@ bs=1 skip=0 count=2048

sosh_8000.bin: sosh_8000.ihx
	makebin -s 65536 $< $@
	mv $@ full_$@
	dd if=full_$@ of=$@ bs=1 skip=513 count=2048

sosh_0000.ihx: $(REL)
	$(CC) $(CFLAGS) --code-loc 0x0000 --data-loc 0x8000 $^ -o $@

sosh_8000.ihx: $(REL)
	$(CC) $(CFLAGS) --code-loc 0x0201 --data-loc 0x8504 $^ -o $@

%.rel: %.s
	$(AS) $(ASFLAGS) $@ $<

%.rel: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.asm *.lst *.rel *.sym *.noi *.map *.lk *.bin *.ihx *.bin.bak *.rst
