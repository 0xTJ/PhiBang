#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define FILE_COUNT 2

struct initrd_header {
   uint32_t nfiles;
   uint8_t loaded;
} __attribute__((packed));

struct initrd_file_header {
   uint8_t magic;       // Magic number, for error checking.
   uint8_t name[65];       // Filename.
   uint16_t offset;       // Offset in the initrd that the file starts.
   uint16_t length;       // Length of the file.
} __attribute__((packed));

int main(char argc, char **argv) {
   int nheaders = (argc-1)/2;
   struct initrd_file_header headers[FILE_COUNT] = {0};
   printf("size of header: %d\n", sizeof(struct initrd_file_header));
   unsigned int off = sizeof(struct initrd_file_header) * FILE_COUNT + sizeof(struct initrd_header);
   int i;
   for(i = 0; i < nheaders; i++) {
       printf("writing file %s->%s at 0x%x\n", argv[i*2+1], argv[i*2+2], off);
       strcpy(headers[i].name, argv[i*2+2]);
       headers[i].offset = off;
       FILE *stream = fopen(argv[i*2+1], "rb");
       if(stream == 0) {
         printf("Error: file not found: %s\n", argv[i*2+1]);
         return 1;
       }
       fseek(stream, 0, SEEK_END);
       headers[i].length = ftell(stream);
       off += headers[i].length;
       fclose(stream);
       headers[i].magic = 0xBF;
   }

   FILE *wstream = fopen("./initrd.img", "wb");
   unsigned char *data = (unsigned char *)malloc(off);
   fwrite(&nheaders, sizeof(int), 1, wstream);
   fwrite("", sizeof(uint8_t), 1, wstream);
   fwrite(headers, sizeof(struct initrd_file_header), FILE_COUNT, wstream);

   for(i = 0; i < nheaders; i++) {
     FILE *stream = fopen(argv[i*2+1], "rb");
     unsigned char *buf = (unsigned char *)malloc(headers[i].length);
     fread(buf, 1, headers[i].length, stream);
     fwrite(buf, 1, headers[i].length, wstream);
     fclose(stream);
     free(buf);
   }

   fclose(wstream);
   free(data);

   return 0;
}
