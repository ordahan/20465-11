#include "my_string.h"
#include <stdlib.h>
#include <stdio.h>

#if 0
int main()
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
	printf("%d\n", (int)my_strchr(empty_no_match, c));
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
	return 0;
}
#endif
