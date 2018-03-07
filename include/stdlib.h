#ifndef _INCLUDE_STDLIB_H
#define _INCLUDE_STDLIB_H

#define double float
/* TYPES */

#ifndef _TYPEDEF_SIZE_T
typedef unsigned short int size_t;
#define _TYPEDEF_SIZE_T
#endif

#ifndef _TYPEDEF_WCHAR_T
typedef unsigned short int wchar_t;
#define _TYPEDEF_WCHAR_T
#endif

#ifndef _TYPEDEF_DIV_T
typedef struct {
  int quot;
  int rem;
} div_t;
#define _TYPEDEF_DIV_T
#endif

#ifndef _TYPEDEF_LDIV_T
typedef struct {
  long int quot;
  long int rem;
} ldiv_t;
#define _TYPEDEF_LDIV_T
#endif


/* MACROS */

#ifndef NULL
#define NULL (0)
#endif

#ifndef EXIT_FAILURE
#define EXIT_FAILURE (1)
#endif

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS (0)
#endif

#ifndef RAND_MAX
#define RAND_MAX (0)
#endif

#ifndef MB_CUR_MAX
#define MB_CUR_MAX (2)
#endif


/* FUNCTIONS */

/* String Conversion */
double atof(const char *nptr);
int atoi(const char *nptr);
long int atol(const char *nptr);
double strtod(const char *nptr, char **endptr);
long int strtol(const char *nptr, char **endptr, int base);
unsigned long int strtoul(const char *nptr, char **endptr,
        int base);
/* Pseudo-random Sequence Generation */
int rand(void);
void srand(unsigned int seed);
/* Memory Management */
void *calloc(size_t nmemb, size_t size);
void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
/* Communication with Environment */
void abort(void);
int atexit(void (*func)(void));
void exit(int status);
char *getenv(const char *name);
int system(const char *string);
/* Searching and Sorting */
void *bsearch(const void *key, const void *base,
        size_t nmemb, size_t size,
        int (*compar)(const void *, const void *));
void qsort(void *base, size_t nmemb, size_t size,
        int (*compar)(const void *, const void *));
/* Integer Arithmetic */
int abs(int j);
div_t div(int numer, int denom);
long int labs(long int j);
ldiv_t ldiv(long int numer, long int denom);
/* Multibyte Character */
int mblen(const char *s, size_t n);
int mbtowc(wchar_t *pwc, const char *s, size_t n);
int wctomb(char *s, wchar_t wchar);
size_t mbstowcs(wchar_t *pwcs, const char *s, size_t n);
size_t wcstombs(char *s, const wchar_t *pwcs, size_t n);


#endif
