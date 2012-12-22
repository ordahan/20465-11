/*
 * my_string.c
 *
 *  Created on: Oct 6, 2012
 *      Author: Or Dahan 201644929
 *
 */

#include "my_string.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void read_user_input();

int main()
{
	read_user_input();
	return 0;
}

void read_user_input()
{
	/* Assume the function name is limited */
	char szFunction[128];

	/* Read user input untill he exits */
	for(;;)
	{
		printf("Enter a function name to run (case sensitive):\n");
		scanf("%s", szFunction);

		/* Check which function is needed to run */
		if (strcmp("my_strchr", szFunction) == 0)
		{
			char cToSearchFor;
			char szToSearchIn[128];
			int nCharIndex = -1;
			printf("Enter char to search for:\n");
			scanf("%s", &cToSearchFor);
			printf("Enter the string to search in:\n");
			scanf("%s", szToSearchIn);
			nCharIndex = my_strchr(szToSearchIn, cToSearchFor);
			if (nCharIndex == -1)
			{
				printf("Char %c was not found in string %s\n", cToSearchFor, szToSearchIn);
			}
			else
			{
				printf("First occurrence is: %d\n", nCharIndex);
			}
		}
		else if (strcmp("my_strcmp", szFunction) == 0)
		{
			char szFirstString[128];
			char szSecondString[128];
			printf("Enter the first string to compare:\n");
			scanf("%s", szFirstString);
			printf("Enter the second string to compare:\n");
			scanf("%s", szSecondString);
			if (my_strcmp(szFirstString, szSecondString) == 0)
			{
				printf("Strings match\n");
			}
			else
			{
				printf("Strings don't match\n");
			}
		}
		else if (strcmp("my_strncmp", szFunction) == 0)
		{
			char szFirstString[128];
			char szSecondString[128];
			int nNumOfChars;
			printf("Enter the first string to compare:\n");
			scanf("%s", szFirstString);
			printf("Enter the second string to compare:\n");
			scanf("%s", szSecondString);
			printf("Enter the number of chars to compare\n");
			scanf("%d", &nNumOfChars);
			if (my_strncmp(szFirstString, szSecondString, nNumOfChars) == 0)
			{
				printf("Strings match for at least %d first character(s)\n", nNumOfChars);
			}
			else
			{
				printf("Strings don't match\n");
			}
		}
		else
		{
			printf("Error! No method called %s\n", szFunction);
		}
	}
}

int my_strcmp(const char* s, const char* t)
{
	unsigned int nStringsLength = 0;
	unsigned int nSLength = strlen(s);
	unsigned int nTLength = strlen(t);

	/* Assume both have the same length */
	nStringsLength = nSLength;

	/* In case both strings aren't the same,
	 * return the difference in length as
	 * there is no specific behavior defined
	 * in the study book for this case
	 */
	if (nSLength != nTLength)
	{
		return (nSLength - nTLength);
	}
	else
	{
		/* Compare both strings */
		return my_strncmp(s, t, nStringsLength);
	}
}

int my_strncmp(const char* s, const char* t, unsigned int n)
{
	int i = 0;

	/* Go over both strings and compare them char by char */
	for (i = 0; i < n; i++)
	{
		/* Compare the current location */
		if (s[i] < t[i])
		{
			return -1;
		}
		else if (s[i] > t[i])
		{
			return 1;
		}
	}

	/* both strings match */
	return 0;
}

int my_strchr(const char* s, char c)
{
	int nFirstOccurrence = -1;
	int i = 0;

	/* Go over the string char by char until we reach the end
	 * of the string (marked by \0) or we find an occurrence
	 * of char c.
	 */
	while ((s[i] != '\0') && (nFirstOccurrence == -1))
	{
		/* Check if the current char is the requested one */
		if (s[i] == c)
		{
			/* Found it */
			nFirstOccurrence = i;
		}

		/* Move on to the next char */
		i++;
	}

	/* Check the special case in which we are actively looking
	 * for the null terminating char (the first scan would
	 * halt when reaching the null-terminator)
	 */
	if ((nFirstOccurrence == -1) && (s[i] == c))
	{
		nFirstOccurrence = i;
	}

	return nFirstOccurrence;
}
