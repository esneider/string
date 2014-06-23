#include <stdio.h>

#include "string.h"

int main(void) {
    string8_t string1 = string8_new("hello world");
    string8_t string2 = string8_new("another");

    printf("%s\n", string1.bytes);
    printf(" 2: %c\n" , *string8_at(string1, 2));
    printf("-1: %c\n", *string8_at(string1, -1));

    printf("Compared to itself: %d %d\n",
        string8_cmp(string1, string1),
        string8_eq(string1, string1)
    );

    printf("Compared to 'another': %d %d\n",
        string8_cmp(string1, string2),
        string8_eq(string1, string2)
    );

    string8_free(string2);
    string8_free(string1);

    return 0;
}