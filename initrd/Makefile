CC = gcc

FILES = $(wildcard initrd/*)
FILES_PLUS_DEST = $(foreach F, $(patsubst initrd/%, %, $(FILES)),initrd/$(F) $(F))

.PHONY: all clean 

all: initrd.img.h

initrd.img: initrd.exe $(FILES)
	./initrd.exe $(FILES_PLUS_DEST)

initrd.img.h: initrd.img
	bin2h initrd_img < initrd.img > initrd.img.h

initrd.exe: initrd.c
	$(CC) initrd.c -o initrd
	
clean:
	rm -f initrd.img initrd.img.h initrd.exe
	