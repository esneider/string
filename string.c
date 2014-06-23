#include "string.h"


#if !defined(__STRING_BITS)


#include <stdlib.h>
#include <string.h>


#define __STRING_BITS 8
#include "string.c"

#define __STRING_BITS 16
#include "string.c"

#define __STRING_BITS 32
#include "string.c"


#elif defined(__STRING_BITS) /* else */


#define __CONCAT_3__(a,b,c) a ## b ## c
#define __CONCAT_3(a,b,c) __CONCAT_3__(a,b,c)

#define __uint     __CONCAT_3(  uint, __STRING_BITS, _t)
#define __UINT_MAX __CONCAT_3(  UINT, __STRING_BITS, _MAX)
#define __fn(name) __CONCAT_3(string, __STRING_BITS, _ ## name)
#define __string   __CONCAT_3(string, __STRING_BITS, _t)
#define __split    __CONCAT_3(string, __STRING_BITS, _split_t)


__string __fn(new)(const char *bytes) {

    if (! bytes)
        return (__string) {0, NULL};

    return __fn(lnew)(strlen(bytes), bytes);
}


__string __fn(lnew)(__uint length, const char *bytes) {

    __string string = {
        .length = length,
        .bytes  = calloc(length + 1, 1),
    };

    if (bytes && string.bytes)
        strncpy(string.bytes, bytes, length);

    return string;
}


char *__fn(at)(__string string, long pos) {

    if (-pos > string.length)
        return NULL;

    if (pos >= string.length)
        return NULL;

    if (pos < 0)
        pos = string.length + pos;

    return string.bytes + pos;
}


bool __fn(empty)(__string string) {

    return ! string.length;
}


int __fn(cmp)(__string s1, __string s2) {

    return strcmp(s1.bytes, s2.bytes);
}


bool __fn(eq)(__string s1, __string s2) {

    if (s1.length < s2.length)
        return false;

    return strcmp(s1.bytes, s2.bytes) == 0;
}


__string __fn(cat)(__string s1, __string s2) {

    uintmax_t length = (uintmax_t) s1.length + (uintmax_t) s2.length;

    if (length > __UINT_MAX)
        length = __UINT_MAX;

    __string result = __fn(lnew)(length, NULL);

    strncpy(result.bytes, s1.bytes, s1.length);
    strncpy(result.bytes + s1.length, s2.bytes, length - s1.length);

    return result;
}


static long __fn(slice_index)(__string string, long pos) {

    if (-pos > string.length)
        return 0;

    if (pos >= string.length)
        return string.length;

    if (pos < 0)
        return string.length + pos;

    return pos;
}


__string __fn(slice)(__string string, long from, long to) {

    from = __fn(slice_index)(string, from);
    to   = __fn(slice_index)(string, to);

    if (from >= to)
        return __fn(new)("");

    return __fn(lnew)(to - from, string.bytes + from);
}


__split __fn(split_init)(__string string, char c) {

    return (__split) {
        .delimiter = c,
        .next = string.bytes,
    };
}


__string __fn(split_next)(__split *split) {

    const char *start = split->next;
    const char *end   = start;

    if (*start == '\0')
        return (__string) {0, NULL};

    while(*end && *end != split->delimiter)
        end++;

    split->next = *end ? end + 1 : end;

    return __fn(lnew)(end - start, start);
}

__string __fn(join)(const __string *parts, size_t n, char c) {

    uintmax_t length = n ? n - 1 : 0;
    uintmax_t pos;

    for (size_t i = 0; i < n; i++) {
        length += parts[i].length;

        if (length > __UINT_MAX) {
            length = __UINT_MAX;
            break;
        }
    }

    __string string = __fn(lnew)(length, NULL);

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


void __fn(free)(__string string) {

    free(string.bytes);
}


#undef __STRING_BITS
#undef __CONCAT_3__
#undef __CONCAT_3
#undef __uint
#undef __UINT_MAX
#undef __fn
#undef __string
#undef __split


#endif /* defined(__STRING_BITS) */

