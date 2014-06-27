#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "string.h"

#define verify(condition)

int main(void) {

    string_t temp;

    string_t string1 = string_new("hello world");
    string_t string2 = string_new("another");
    string_t string3 = string_new("a third");

    printf("Testing new()...\n");
    assert(strcmp("hello world", string1.bytes) == 0);


    printf("Testing at()...\n");

    assert(*string_at(string1, 4) == 'o');
    assert(*string_at(string1, -1) == 'd');

    assert(string_at(string1, 100) == NULL);
    assert(string_at(string1, -100) == NULL);


    printf("Testing cmp()...\n");

    assert(string_cmp(string1, string1) == 0);
    assert(string_cmp(string1, string2) > 0);
    assert(string_cmp(string2, string1) < 0);


    printf("Testing eq()...\n");

    assert(string_eq(string1, string1));
    assert(! string_eq(string1, string2));


    printf("Testing cat()...\n");

    temp = string_cat(string1, string2);
    assert(temp.length == string1.length + string2.length);
    assert(strncmp(string1.bytes, temp.bytes, string1.length) == 0);
    assert(strcmp(string2.bytes, temp.bytes + string1.length) == 0);
    string_free(temp);


    printf("Testing slice()...\n");

    temp = string_slice(string1, 1, 6);
    assert(strcmp(temp.bytes, "ello"));
    string_free(temp);

    temp = string_slice(string1, 1, -1);
    assert(strcmp(temp.bytes, "ello worl") == 0);
    string_free(temp);

    temp = string_slice(string1, -5, -2);
    assert(strcmp(temp.bytes, "wor") == 0);
    string_free(temp);

    temp = string_slice(string1, -100, 100);
    assert(strcmp(temp.bytes, "hello world") == 0);
    string_free(temp);


    printf("Testing split()...\n");

    string_split_t split = string_split_init(string1, 'o');

    temp = string_split_next(&split);
    assert(strcmp(temp.bytes, "hell") == 0);
    string_free(temp);

    temp = string_split_next(&split);
    assert(strcmp(temp.bytes, " w") == 0);
    string_free(temp);

    temp = string_split_next(&split);
    assert(strcmp(temp.bytes, "rld") == 0);
    string_free(temp);

    temp = string_split_next(&split);
    assert(! temp.bytes);
    string_free(temp);


    printf("Testing join()...\n");

    string_t parts[] = {string1, string2, string3};
    temp = string_join(parts, 3, ' ');
    assert(strcmp(temp.bytes, "hello world another a third") == 0);
    string_free(temp);

    // string_t[] parts = {s1, s2, s3};
    // int joined = join(parts, sizeof(parts) / sizeof(*parts));

    string_free(string1);
    string_free(string2);
    string_free(string3);


    printf("All tests passed.\n");
    return 0;
}
