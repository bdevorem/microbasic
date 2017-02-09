#ifndef DUMB_HEAD
#define DUMB_HEAD
#include "token.h"


#define ESC "\033"
#define ERR ESC"\e[0;31mERROR"ESC"\e[0;37m"
#define NVARS (10)
#define MAX_LEN (40)
#define MAX_TOKEN (20)
#define MAX_LINE (5)
#define MAX_LOOP_TOKENS (20)
#define STR_TABL_W (10)
#define STR_TABL_H (5)

extern int str_ptr;
extern char STR_TABL[STR_TABL_H][STR_TABL_W];
extern int vars[NVARS];
extern char line[MAX_LEN+1];
extern breezy_t BREEZYXR[MAX_LOOP_TOKENS];
extern int pc;
extern int _loop;

#endif
