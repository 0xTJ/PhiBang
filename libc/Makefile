CC = sdcc
AS = sdasz80
AR = sdar

ASFLAGS = -plosgffw
CFLAGS = -mz80 -c --nostdinc --nostdlib --no-std-crt0 --std-sdcc99 --Werror
ARFLAGS = -r

INC_DIR = include
SRC_DIR = src
OUT_DIR = build

CFLAGS := $(CFLAGS) -I$(INC_DIR)

C_SOURCES = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c)
ASM_SOURCES = $(wildcard $(SRC_DIR)/*.s) $(wildcard $(SRC_DIR)/*/*.s)
SOURCES = $(ASM_SOURCES) $(C_SOURCES)

C_REL = $(C_SOURCES:c=rel)
ASM_REL = $(ASM_SOURCES:s=rel)
REL = $(ASM_REL) $(C_REL)

.PHONY: all clean

all: libc.lib

libc.lib: $(REL)
	$(AR) $(ARFLAGS) $@ $^

%.rel: %.s
	$(AS) $(ASFLAGS) $@ $<

%.rel: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f build/*
	rm -f libc.lib
	rm -f src/*.asm src/*.lst src/*.rel src/*.sym
	rm -f src/*/*.asm src/*/*.lst src/*/*.rel src/*/*.sym
