/**
 * Compares two strings in lexical order
 *
 * @param s: First string to compare
 * @param t: Second string to compare
 *
 * @return: <0 if s<t, 0 if s==t, or >0 if s>t
 */
int my_strcmp(const char* s, const char* t);

/**
 * Compares a limited number of characters
 * in two strings, in lexical order.
 *
 * @param s: First string to compare
 * @param t: Second string to compare
 * @param n: Number of chars to compare
 *
 * @return: <0 if s<t, 0 if s==t, or >0 if s>t
 */
int my_strncmp(const char* s, const char* t);

/**
 * Finds the first occurrence of a character in a string
 *
 * @param s: String to search inside
 * @param c: Character to search for
 *
 * @return: Pointer to the first occurrence of c in s, or
 * NULL if it doesn't exist
 */
char* strchr(const char* s, char c);
