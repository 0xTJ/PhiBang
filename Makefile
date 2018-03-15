.PHONY: kernel libc user

all: libc kernel user

libc:
	$(MAKE) -C libc

kernel: libc
	$(MAKE) -C kernel
