#ifndef _INCLUDE_KIO_H
#define _INCLUDE_KIO_H

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define GET_MACRO(_1,_2,NAME,...) NAME
#define AT __FILE__ ":" TOSTRING(__LINE__)

#define ESC "\x1b"
#define CSI ESC "["
#define RIS ESC "c"

#define CUP(row,col) CSI TOSTRING(row) ";" TOSTRING(col) "H" 
#define SGR(...) GET_MACRO(__VA_ARGS__, SGR2, SGR1)(__VA_ARGS__)
#define SGR1(a) CSI TOSTRING(a) "m"
#define SGR2(a,b) CSI TOSTRING(a) ";" TOSTRING(b) "m"

#define COLOUR_RESET CSI "39;49m"
#define COLOURF_BLK CSI "30m"
#define COLOURF_RED CSI "31m"
#define COLOURF_GRN CSI "32m"
#define COLOURF_YEL CSI "33m"
#define COLOURF_BLU CSI "34m"
#define COLOURF_MAG CSI "35m"
#define COLOURF_CYN CSI "36m"
#define COLOURF_WIT CSI "37m"
#define COLOURB_BLK CSI "40m"
#define COLOURB_RED CSI "41m"
#define COLOURB_GRN CSI "42m"
#define COLOURB_YEL CSI "43m"
#define COLOURB_BLU CSI "44m"
#define COLOURB_MAG CSI "45m"
#define COLOURB_CYN CSI "46m"
#define COLOURB_WIT CSI "47m"

#define INFO COLOUR_RESET "[" COLOURF_GRN "INFO" COLOUR_RESET "]"
#define WARN COLOUR_RESET "[" COLOURF_YEL "WARN" COLOUR_RESET "]"
#define ERROR COLOUR_RESET "[" COLOURF_RED "ERROR" COLOUR_RESET "]"
#define KLOG(level, message) kprint(level " " message "\n");

void kput(char c);
void kprint(char *s);

#endif
