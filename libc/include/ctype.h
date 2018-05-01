#ifndef _INCLUDE_CTYPE_H
#define _INCLUDE_CTYPE_H

#ifndef EOF
#define EOF (-1)
#endif

int   isalnum(int);
int   isalpha(int);
int   isascii(int);
int   isblank(int);
int   iscntrl(int);
int   isdigit(int);
int   isgraph(int);
int   islower(int);
int   isprint(int);
int   ispunct(int);
int   isspace(int);
int   isupper(int);
int   isxdigit(int);
int   toascii(int);
int   tolower(int);
int   toupper(int);

#endif
