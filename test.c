#include <stdio.h>

#include "string.h"

int main(void) {
    
    string8_t string = string8_new("hello world");
    printf("'%s' at 3: %c\n", string.bytes, string8_at(string, 3));

    // This would result in a fault:
    // string8_free(string);
    // The string is literal, and was not allocated.

    return 0;
}