#include "../my_string.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int test_main()
{
	/* Test my_strchr */
	char c = '5';
	char* empty_no_match = "";
	char* len_1_no_match = "4";
	char* len_1_match = "5";
	char* len_1_match_null = "\0";
	char* len_n_no_match = "abde3dg";
	char* len_n_match_first = "5abcdefgh";
	char* len_n_match_mid = "abcd5efgh";
	char* len_n_match_last = "abcdefgh5";
	char* len_n_match_null_first = "\0abcdefgh";
	char* len_n_match_null_mid = "abcd\05efgh";
	char* len_n_match_null_last = "abcdefgh5\0";

	printf("my_strchr\n");
	assert(my_strchr(empty_no_match, c) != NULL);
	printf("%d\n", (int)my_strchr(len_1_no_match, c));
	printf("%s\n", my_strchr(len_1_no_match, '\0'));
	printf("%s\n", my_strchr(len_1_match, c));
	printf("%s\n", my_strchr(len_1_match_null, '\0'));
	printf("%d\n", (int)my_strchr(len_n_no_match, c));
	printf("%s\n", my_strchr(len_n_no_match, '\0'));
	printf("%s\n", my_strchr(len_n_match_first, c));
	printf("%s\n", my_strchr(len_n_match_mid, c));
	printf("%s\n", my_strchr(len_n_match_last, c));
	printf("%s\n", my_strchr(len_n_match_null_first, '\0'));
	printf("%s\n", my_strchr(len_n_match_null_mid, '\0'));
	printf("%s\n", my_strchr(len_n_match_null_last, '\0'));

	/* test my_strncmp */
	printf("%d", my_strncmp("", "", 0) == 0);
	printf("%d", my_strncmp("a", "", 0) == 0);
	printf("%d", my_strncmp("", "b", 0) == 0);
	printf("%d", my_strncmp("a", "b", 1) == -1);
	printf("%d", my_strncmp("b", "a", 1) == 1);
	printf("%d", my_strncmp("ab", "bb", 1) == -1);
	printf("%d", my_strncmp("ab", "a", 1) == 0);
	printf("%d", my_strncmp("aA", "aB", 2) == -1);
	printf("%d", my_strncmp("ac", "ab", 2) == 1);

	/* test my_strcmp */
	printf("%d", my_strcmp("", "") == 0);
	printf("%d", my_strcmp("a", "") == 0);
	printf("%d", my_strcmp("", "b") == 0);
	printf("%d", my_strcmp("a", "b") == -1);
	printf("%d", my_strcmp("b", "a") == 1);
	printf("%d", my_strcmp("ab", "bb") == -1);
	printf("%d", my_strcmp("ab", "a") == 0);
	printf("%d", my_strcmp("aA", "aB") == -1);
	printf("%d", my_strcmp("ac", "ab") == 1);

	return 0;
}
