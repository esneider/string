#ifndef _STRING_H_
#define _STRING_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

struct string8 {
    uint8_t length;
    char* bytes;
};

typedef struct string8 string8_t;

string8_t string8_new(char* bytes);
string8_t string8_lnew(uint8_t length, char* bytes);

bool string8_empty(string8_t string);
char* string8_at(string8_t string, long pos);

int string8_cmp(string8_t string1, string8_t string2);
bool string8_eq(string8_t string1, string8_t string2);

string8_t string8_cat(string8_t string1, string8_t string2);

void string8_free(string8_t string);

#endif /* include guard */