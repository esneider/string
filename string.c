#include <string.h>
#include <stdlib.h>

#include "string.h"

string8_t string8_new(char* bytes) {

    return (string8_t) {
        .bytes  = bytes,
        .length = strlen(bytes)
    };
}

string8_t string8_lnew(uint8_t length, char* bytes) {

    return (string8_t) {
        .bytes  = bytes,
        .length = length
    };
}

char string8_at(string8_t string, long pos) {

    pos = (pos >= 0) ? pos : string.length - pos;

    if (pos >= string.length)
        return '\0';

    return string.bytes[pos];
}

//  a  b  c  d  e
//  0  1  2  3  4
// -5 -4 -3 -2 -1
// 5

void string8_free(string8_t string) {
    free(string.bytes);
}