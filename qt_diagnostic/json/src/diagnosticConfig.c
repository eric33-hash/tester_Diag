#include "json/include/diagnosticConfig.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

long _toenum(char *enum_s, const char *x) {
    long i = 0;
    size_t len = strlen(enum_s);

    char *copy = (char*) malloc(sizeof(char) * (len + 1));
    strncpy(copy, enum_s, len);
    copy[len] = '\0';

    char *saveptr = NULL;
    char *s = strtok_r(copy, ", ", &saveptr);
    do {
        if (strcmp(s, x) == 0) {
            free(copy);
            return i;
        }
        i++;
    } while((s = strtok_r(NULL, ", ", &saveptr)) != NULL);

    free(copy);
    return -1;
}
