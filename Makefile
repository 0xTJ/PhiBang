.PHONY: clean kernel libc initrd

all: libc kernel

libc:
	$(MAKE) -C libc

initrd:
	$(MAKE) -C initrd

sosh: libc
	$(MAKE) -C user/sosh

kernel: libc initrd
	$(MAKE) -C kernel

clean:
	$(MAKE) -C libc clean
	$(MAKE) -C user/sosh clean
	$(MAKE) -C kernel clean
	$(MAKE) -C initrd clean
