#include <stdlib.h>
#include <string.h>
#include "string.h"


string_t string_new(const char *bytes) {

    if (! bytes)
        return (string_t) {0, NULL};

    return string_lnew(strlen(bytes), bytes);
}


string_t string_lnew(size_t length, const char *bytes) {

    string_t string = {
        .length = length,
        .bytes  = calloc(length + 1, 1),
    };

    if (bytes && string.bytes)
        strncpy(string.bytes, bytes, length);

    return string;
}


bool string_null(string_t string) {

    return !! string.bytes;
}

bool string_empty(string_t string) {

    return ! string.length && string.bytes;
}

char *string_at(string_t string, int32_t pos) {

    if (-pos > (int_fast32_t)string.length)
        return NULL;

    if (pos >= (int_fast32_t)string.length)
        return NULL;

    if (pos < 0)
        pos = string.length + pos;

    return string.bytes + pos;
}


int string_cmp(string_t s1, string_t s2) {

    return strcmp(s1.bytes, s2.bytes);
}


bool string_eq(string_t s1, string_t s2) {

    if (s1.length < s2.length)
        return false;

    return strcmp(s1.bytes, s2.bytes) == 0;
}


string_t string_cat(string_t s1, string_t s2) {

    uintmax_t length = (uintmax_t) s1.length + (uintmax_t) s2.length;

    if (length > UINT32_MAX)
        length = UINT32_MAX;

    string_t result = string_lnew(length, NULL);

    strncpy(result.bytes, s1.bytes, s1.length);
    strncpy(result.bytes + s1.length, s2.bytes, length - s1.length);

    return result;
}


static size_t string_slice_index(string_t string, int32_t pos) {

    if (-pos > (int_fast32_t)string.length)
        return 0;

    if (pos >= (int_fast32_t)string.length)
        return string.length;

    if (pos < 0)
        return string.length + pos;

    return pos;
}


string_t string_slice(string_t string, int32_t from, int32_t to) {

    from = string_slice_index(string, from);
    to   = string_slice_index(string, to);

    if (from >= to)
        return string_new("");

    return string_lnew(to - from, string.bytes + from);
}


string_split_t string_split_init(string_t string, char c) {

    return (string_split_t) {
        .delimiter = c,
        .next = string.bytes,
    };
}


string_t string_split_next(string_split_t *split) {

    const char *start = split->next;
    const char *end   = start;

    if (*start == '\0')
        return (string_t) {0, NULL};

    while(*end && *end != split->delimiter)
        end++;

    split->next = *end ? end + 1 : end;

    return string_lnew(end - start, start);
}

string_t string_join(const string_t *parts, size_t n, char c) {

    uintmax_t length = n ? n - 1 : 0;
    uintmax_t pos;

    for (size_t i = 0; i < n; i++) {
        length += parts[i].length;

        if (length > UINT32_MAX) {
            length = UINT32_MAX;
            break;
        }
    }

    string_t string = string_lnew(length, NULL);

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


void string_free(string_t string) {

    free(string.bytes);
}

