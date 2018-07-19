.PHONY: clean kernel libc initrd

all: libc kernel

libc:
	$(MAKE) -C libc

initrd:
	$(MAKE) -C initrd

sosh: libc
	$(MAKE) -C user/sosh

webby: libc
	$(MAKE) -C user/webby

kernel: libc initrd
	$(MAKE) -C kernel

clean:
	$(MAKE) -C libc clean
	$(MAKE) -C user/sosh clean
	$(MAKE) -C user/webby clean
	$(MAKE) -C kernel clean
	$(MAKE) -C initrd clean
