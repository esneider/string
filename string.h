#ifndef _STRING_H_
#define _STRING_H_

#include <stdint.h>
#include <stddef.h>

struct string8 {
    uint8_t length;
    char* bytes;
};

typedef struct string8 string8_t;

string8_t string8_new(char* bytes);
string8_t string8_lnew(uint8_t length, char* bytes);

char string8_at(string8_t string, long pos);

void string8_free(string8_t string);

#endif /* include guard */