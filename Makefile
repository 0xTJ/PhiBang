.PHONY: clean kernel libc user

all: libc kernel user

libc:
	$(MAKE) -C libc

sosh: libc
	$(MAKE) -C user/sosh

kernel: libc
	$(MAKE) -C kernel

clean:
	$(MAKE) -C libc clean
	$(MAKE) -C user/sosh clean
	$(MAKE) -C kernel clean
