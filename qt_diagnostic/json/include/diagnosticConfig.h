#ifndef _DIAGNOSTICCONFIG_H_
#define _DIAGNOSTICCONFIG_H_


#include <stdio.h>

#define CREATEENUM(name, first, ...) \
    typedef enum { first = 0, __VA_ARGS__ } name; \
    char name##_s[] = #first ", " #__VA_ARGS__;
#define TOSTR(x) #x
#define TOENUM(name, x) ((name) _toenum(name##_s, x))


#define BOOL_TRUE 1
#define BOOL_FALSE 0




#endif
