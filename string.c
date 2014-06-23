#include <string.h>
#include <stdlib.h>

#include "string.h"


string8_t string8_new(const char* bytes) {

    if (! bytes)
        return (string8_t) {0, NULL};

    return string8_lnew(strlen(bytes), bytes);
}


string8_t string8_lnew(uint8_t length, const char* bytes) {

    string8_t string = {
        .length = length,
        .bytes  = calloc(length + 1, 1),
    };

    if (bytes && string.bytes)
        strncpy(string.bytes, bytes, length);

    return string;
}


char* string8_at(string8_t string, long pos) {

    if (pos < -string.length)
        return NULL;

    if (pos >= string.length)
        return NULL;

    if (pos < 0)
        pos = string.length + pos;

    return string.bytes + pos;
}


bool string8_empty(string8_t string) {

    return ! string.length;
}


int string8_cmp(string8_t s1, string8_t s2) {

    return strcmp(s1.bytes, s2.bytes);
}


bool string8_eq(string8_t s1, string8_t s2) {

    if (s1.length < s2.length)
        return false;

    return strcmp(s1.bytes, s2.bytes) == 0;
}


string8_t string8_cat(string8_t s1, string8_t s2) {

    uintmax_t length = (uintmax_t) s1.length + (uintmax_t) s2.length;

    if (length > UINT8_MAX)
        length = UINT8_MAX;

    string8_t result = string8_lnew(length, NULL);

    strncpy(result.bytes, s1.bytes, s1.length);
    strncpy(result.bytes + s1.length, s2.bytes, length - s1.length);

    return result;
}


static long string8_slice_index(string8_t string, long pos) {

    if (pos < -string.length)
        return 0;

    if (pos >= string.length)
        return string.length;

    if (pos < 0)
        return string.length + pos;

    return pos;
}


string8_t string8_slice(string8_t string, long from, long to) {
    
    from = string8_slice_index(string, from);
    to   = string8_slice_index(string, to);
    
    if (from >= to)
        return string8_new("");

    return string8_lnew(to - from, string.bytes + from);
}


string8_split_t string8_split(string8_t string, char c) {

    return (string8_split_t) {
        .delimiter = c,
        .last = string.bytes,
    };
}


string8_t string8_split_next(string8_split_t* split) {

    char* start = split->last;
    char* end   = start;

    if (*start == '\0')
        return (string8_t) {0, NULL};

    while(*end && *end != split->delimiter)
        end++;

    split->last = *end ? end + 1 : end;

    return string8_lnew(end - start, start);
}

string8_t string8_join(const string8_t* const parts, size_t n, char c) {

    uintmax_t length = n - 1;
    uintmax_t pos;
    
    for (size_t i = 0; i < n; i++) {
        length += parts[i].length;

        if (length > UINT8_MAX) {
            length = UINT8_MAX;
            break;
        }
    }

    string8_t string = string8_lnew(length, NULL);

    pos = 0;

    for (size_t i = 0; i < n; i++) {
        if (pos >= length)
            break;

        strncpy(string.bytes + pos, parts[i].bytes, length - pos);

        pos += parts[i].length;

        if (i + 1 < n)
            string.bytes[pos++] = c;
    }

    return string;
}

// string_split_t iter = string_split(string);

// while (true) {
//     string_t part = string_iter_next(&iter);

//     if (!part)
//         break;

//     string_free(part);
// }


//  a  b  c  d  e
//  0  1  2  3  4
// -5 -4 -3 -2 -1
// 5

void string8_free(string8_t string) {

    free(string.bytes);
}
