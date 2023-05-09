#pragma once

#ifndef FUN_BAD__H
#define FUN_BAD__H

/* Shamelessly borrowed from git */

#define NOPE(func) nope_##func##_is_banned

#undef strcpy
#define strcpy(x,y) NOPE(strcpy)
#undef strcat
#define strcat(x,y) NOPE(strcat)
#undef strncpy
#define strncpy(x,y,n) NOPE(strncpy)
#undef strncat
#define strncat(x,y,n) NOPE(strncat)

#undef sprintf
#undef vsprintf
#ifdef HAVE_VARIADIC_MACROS
#define sprintf(...) NOPE(sprintf)
#define vsprintf(...) NOPE(vsprintf)
#else
#define sprintf(buf,fmt,arg) NOPE(sprintf)
#define vsprintf(buf,fmt,arg) NOPE(vsprintf)
#endif

#undef gmtime
#define gmtime(t) NOPE(gmtime)
#undef localtime
#define localtime(t) NOPE(localtime)
#undef ctime
#define ctime(t) NOPE(ctime)
#undef ctime_r
#define ctime_r(t, buf) NOPE(ctime_r)
#undef asctime
#define asctime(t) NOPE(asctime)
#undef asctime_r
#define asctime_r(t, buf) NOPE(asctime_r)

#endif /* FUN_BAD__H */

