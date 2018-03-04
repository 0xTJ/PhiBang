CC = sdcc
CFLAGS = -mz80

INCDIR = include
SRCDIR = src

CFLAGS := $(CFLAGS) -I$(INCDIR)

C_SOURCES = $(wildcard $(SRCDIR)*.c)
ASM_SOURCES = $(wildcard $(SRCDIR)*.asm)
SOURCES = $(C_SOURCES) $(ASM_SOURCES)

C_REL = $(C_SOURCES:c=rel)
ASM_REL = $(ASM_SOURCES:asm=rel)
REL = $(C_REL) $(ASM_REL)

.PHONY: all clean

all: kernel.ihx

kernel.ihx: $(REL)
	$(CC) $(CFLAGS) $^

%.rel: %.c
	$(CC) $(CFLAGS) -c $<

clean:
