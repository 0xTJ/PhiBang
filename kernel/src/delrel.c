#include "delrel.h"
#include <stddef.h>
#include "kio.h"

void processDrl(struct drlHeader *header, struct drlEntry entries[], unsigned char *code_loc, unsigned char *data_loc) {
    size_t i;
    // if (strncmp(header->drlSig, "D31431", 6))
        // return;
    code_loc;
    data_loc;
    for (i = 0; i < header->offLen; ++i) {
        // kprint("Updating entry at address ");
        // kput_uint16((unsigned short)(code_loc + entries[i].position));
        // kprint(".\n");
        switch (entries[i].area) {
            case 1:
                *(unsigned short *)(code_loc + entries[i].position) += (size_t)code_loc;
                break;
            case 2:
                *(unsigned short *)(code_loc + entries[i].position) += (size_t)data_loc - 0x8000;
                break;
            default:
                // Handle bad file
        }
    }
}
