#include <string.h>
#include <stdlib.h>

#include "string.h"

string8_t string8_new(char* bytes) {

    return string8_lnew(strlen(bytes), bytes);
}

string8_t string8_lnew(uint8_t length, char* bytes) {

    string8_t string;

    string.length = length;
    string.bytes  = calloc(length + 1, 1);

    if (bytes && string.bytes)
        strncpy(string.bytes, bytes, length);

    return string;
}

char* string8_at(string8_t string, long pos) {

    pos = (pos >= 0) ? pos : string.length + pos;

    if (pos >= string.length)
        return '\0';

    return string.bytes + pos;
}

bool string8_empty(string8_t string) {

    return ! string.length;
}


int string8_cmp(string8_t string1, string8_t string2) {

    return strcmp(string1.bytes, string2.bytes);
}

bool string8_eq(string8_t string1, string8_t string2) {

    if (string1.length < string2.length)
        return false;

    return strcmp(string1.bytes, string2.bytes) == 0;
}

string8_t string8_cat(string8_t string1, string8_t string2) {

    string8_t result = string8_lnew(string1.length + string2.length, NULL);

    strncpy(result.bytes, string1.bytes, string1.length);
    strncpy(result.bytes + string1.length, string2.bytes, string2.length);

    return result;
}

//  a  b  c  d  e
//  0  1  2  3  4
// -5 -4 -3 -2 -1
// 5

void string8_free(string8_t string) {
    free(string.bytes);
}