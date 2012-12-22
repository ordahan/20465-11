#include "../my_string.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

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

	assert(my_strchr(empty_no_match, c) == -1);
	assert(my_strchr(len_1_no_match, c) == -1);
	assert(my_strchr(len_1_match, c) == 0);
	assert(my_strchr(len_n_no_match, c) == -1);
	assert(my_strchr(len_n_match_first, c) == 0);
	assert(my_strchr(len_n_match_mid, c) == 4);
	assert(my_strchr(len_n_match_last, c) == (strlen(len_n_match_last) - 1));

	c = '\0';
	assert(my_strchr(len_1_no_match, c) == 1);
	assert(my_strchr(len_1_match_null, c) == 0);
	assert(my_strchr(len_n_no_match, c) == strlen(len_n_no_match));
	assert(my_strchr(len_n_match_null_first, c) == 0);
	assert(my_strchr(len_n_match_null_mid, c) == strlen(len_n_match_null_mid));
	assert(my_strchr(len_n_match_null_last, c) == strlen(len_n_match_null_last));

	/* test my_strncmp */
	assert(my_strncmp("", "", 0) == 0);
	assert(my_strncmp("a", "", 0) == 0);
	assert(my_strncmp("", "b", 0) == 0);
	assert(my_strncmp("a", "b", 1) == -1);
	assert(my_strncmp("b", "a", 1) == 1);
	assert(my_strncmp("ab", "bb", 1) == -1);
	assert(my_strncmp("ab", "a", 1) == 0);
	assert(my_strncmp("aA", "aB", 2) == -1);
	assert(my_strncmp("ac", "ab", 2) == 1);

	/* test my_strcmp */
	assert(my_strcmp("", "") == 0);
	assert(my_strcmp("a", "") != 0);
	assert(my_strcmp("", "b") != 0);
	assert(my_strcmp("a", "b") == -1);
	assert(my_strcmp("b", "a") == 1);
	assert(my_strcmp("ab", "bb") == -1);
	assert(my_strcmp("ab", "a") != 0);
	assert(my_strcmp("aA", "aB") == -1);
	assert(my_strcmp("ac", "ab") == 1);

	return 0;
}
