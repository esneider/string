#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "string.h"

#define verify(condition) 

int main(void) {
    
    string8_t temp;

    string8_t string1 = string8_new("hello world");
    string8_t string2 = string8_new("another");

    printf("Testing new()...\n");
    assert(strcmp("hello world", string1.bytes) == 0);

    
    printf("Testing at()...\n");
    
    assert(*string8_at(string1, 4) == 'o');
    assert(*string8_at(string1, -1) == 'd');

    assert(string8_at(string1, 100) == NULL);
    assert(string8_at(string1, -100) == NULL);


    printf("Testing cmp()...\n");

    assert(string8_cmp(string1, string1) == 0);
    assert(string8_cmp(string1, string2) > 0);
    assert(string8_cmp(string2, string1) < 0);


    printf("Testing eq()...\n");

    assert(string8_eq(string1, string1));
    assert(! string8_eq(string1, string2));


    printf("Testing cat()...\n");

    temp = string8_cat(string1, string2);
    assert(temp.length == string1.length + string2.length);
    assert(strncmp(string1.bytes, temp.bytes, string1.length) == 0);
    assert(strcmp(string2.bytes, temp.bytes + string1.length) == 0);
    string8_free(temp);


    printf("Testing slice()...\n");

    temp = string8_slice(string1, 1, 6);
    assert(strcmp(temp.bytes, "ello"));
    string8_free(temp);

    temp = string8_slice(string1, 1, -1);
    assert(strcmp(temp.bytes, "ello worl") == 0);
    string8_free(temp);

    temp = string8_slice(string1, -5, -2);
    assert(strcmp(temp.bytes, "wor") == 0);
    string8_free(temp);

    temp = string8_slice(string1, -100, 100);
    assert(strcmp(temp.bytes, "hello world") == 0);
    string8_free(temp);


    printf("Testing split()...\n");

    string8_split_t split = string8_split(string1, 'o');

    temp = string8_split_next(&split);
    assert(strcmp(temp.bytes, "hell") == 0);
    string8_free(temp);

    temp = string8_split_next(&split);
    assert(strcmp(temp.bytes, " w") == 0);
    string8_free(temp);

    temp = string8_split_next(&split);
    assert(strcmp(temp.bytes, "rld") == 0);
    string8_free(temp);

    temp = string8_split_next(&split);
    assert(! temp.bytes);
    string8_free(temp);

    string8_free(string1);
    string8_free(string2);


    printf("All tests passed.\n");
    return 0;
}
