#ifndef __STRING_H__

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>


struct string {
    const uint_fast32_t length;
    char * const bytes;
};


struct string_split {
    const char delimiter;
    const char *next;
};


typedef struct string string_t;
typedef struct string_split string_split_t;


/**
 * Create a new fixed length string.
 *
 * Create a string with the contents initialized with a copy of a
 * null-terminated character string. The length is determined by the first null
 * character.
 *
 * If the initialization string is NULL, a NULL string is returned.
 * If there was an out-of-memory error, a NULL string is returned.
 *
 * This function runs in O(length of bytes) time.
 *
 * @param bytes pointer to a character string used for initialization.
 *
 * @return new string.
 */
string_t string_new(const char *bytes);

/**
 * Create a new fixed length string.
 *
 * Create a string of a given length, with the contents initialized with a copy
 * of the first characters of a null-terminated character string. If the
 * initialization string is shorter than the given length (or NULL), the
 * remaining characters (all characters) are set to the null character.
 *
 * If there was an out-of-memory error, a NULL string is returned.
 *
 * This function runs in O(length) time.
 *
 * @param length size of the resulting string.
 * @param bytes  pointer to a character string used for initialization.
 *
 * @return new string.
 */
string_t string_lnew(size_t length, const char *bytes);

/**
 * Check if a string is the NULL string.
 *
 * This function runs in O(1) time.
 *
 * @param string string to test.
 *
 * @return true if the string is the NULL string, false otherwise.
 */
bool string_null(string_t string);

/**
 * Check if a string is empty.
 *
 * This function runs in O(1) time.
 *
 * @param string string to test.
 *
 * @return true if the string is empty and not NULL, false otherwise.
 */
bool string_empty(string_t string);

/**
 * Access a character at a specified position.
 *
 * TODO
 *
 * @param string string to access.
 * @param pos    position to access.
 *
 * @return pointer to the accessed character, or NULL if pos is invalid.
 */
char *string_at(string_t string, int32_t pos);

int string_cmp(string_t s1, string_t s2);
bool string_eq(string_t s1, string_t s2);

string_t string_cat(string_t s1, string_t s2);
string_t string_slice(string_t s, int32_t from, int32_t to);

string_split_t string_split_init(string_t s, char c);
string_t string_split_next(string_split_t *split);
string_t string_join(const string_t *parts, size_t n, char c);

void string_free(string_t s);


#endif /* __STRING_H__ */

