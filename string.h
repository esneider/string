#ifndef _STRING_H_
#define _STRING_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

struct string8 {
    const uint8_t length;
    char* const bytes;
};

typedef struct string8 string8_t;


struct string8_split {
    char  delimiter;
    char* last;
};

typedef struct string8_split string8_split_t;


string8_t string8_new(const char* bytes);
string8_t string8_lnew(uint8_t length, const char* bytes);


bool string8_empty(string8_t string);
char* string8_at(string8_t string, long pos);


int string8_cmp(string8_t string1, string8_t string2);
bool string8_eq(string8_t string1, string8_t string2);


string8_t string8_cat(string8_t string1, string8_t string2);
string8_t string8_slice(string8_t string, long from, long to);

string8_split_t string8_split(string8_t string, char c);
string8_t string8_split_next(string8_split_t* split);
string8_t string8_join(const string8_t* const parts, size_t n, char c);



void string8_free(string8_t string);


#endif /* include guard */
