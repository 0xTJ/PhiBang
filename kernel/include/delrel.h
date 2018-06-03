#ifndef _INCLUDE_DELREL_H
#define _INCLUDE_DELREL_H

#include <stddef.h>

struct drlHeader {
    char drlSig[6];
    size_t offLen;
};

struct drlEntry {
    unsigned char area;
    size_t position;
};

void processDrl(struct drlHeader *header, struct drlEntry entries[], unsigned char *code, unsigned char *data);

#endif
