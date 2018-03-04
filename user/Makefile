C_SOURCES = $(wildcard *.c)
ASM_SOURCES = $(wildcard *.asm)
SOURCES = $(C_SOURCES) $(ASM_SOURCES)

.PHONY: all clean none

all: none

none: $(SOURCES)
	zcc +$@ -Iinclude --reloc-info -create-app $(SOURCES) -o user

clean:
	rm -f *.bin *.def *.ihx *.sym *.reloc *.map *.rom
