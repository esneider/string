#if !defined(__STRING_H)
#   if !defined(__STRING_BITS)


#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>


typedef struct {
    const char delimiter;
    const char *next;
} string_split_t;


#define __STRING_BITS 8
#include "string.h"

#define __STRING_BITS 16
#include "string.h"

#define __STRING_BITS 32
#include "string.h"

#define __STRING_H


#   elif defined(__STRING_BITS) /* else */


#define __CONCAT_3__(a,b,c) a ## b ## c
#define __CONCAT_3(a,b,c) __CONCAT_3__(a,b,c)

#define __uint     __CONCAT_3(  uint, __STRING_BITS, _t)
#define __fn(name) __CONCAT_3(string, __STRING_BITS, _ ## name)
#define __string   __CONCAT_3(string, __STRING_BITS, _t)
#define __split    __CONCAT_3(string, __STRING_BITS, _split_t)


typedef string_split_t __split;

typedef struct {
    const __uint length;
    char *const bytes;
} __string;


__string __fn(new)(const char *bytes);
__string __fn(lnew)(__uint length, const char *bytes);

bool __fn(empty)(__string s);
char *__fn(at)(__string s, long pos);

int __fn(cmp)(__string s1, __string s2);
bool __fn(eq)(__string s1, __string s2);

__string __fn(cat)(__string s1, __string s2);
__string __fn(slice)(__string s, long from, long to);

__split __fn(split_init)(__string s, char c);
__string __fn(split_next)(__split *split);
__string __fn(join)(const __string *parts, size_t n, char c);

void __fn(free)(__string s);


#undef __STRING_BITS
#undef __CONCAT_3__
#undef __CONCAT_3
#undef __uint
#undef __fn
#undef __string
#undef __split


#   endif /* defined(__STRING_BITS) */
#endif /* !defined(__STRING_H) */

