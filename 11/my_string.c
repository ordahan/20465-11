/*
 * my_string.c
 *
 *  Created on: Oct 6, 2012
 *      Author: Or Dahan
 */

#include "my_string.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
	return 0;
}

int my_strcmp(const char* s, const char* t)
{
	unsigned int nMinLength = 0;
	unsigned int nSLength = strlen(s);
	unsigned int nTLength = strlen(t);

	/* Assume s is shorter */
	nMinLength = nSLength;

	/* Check if t is shorter */
	if (nTLength < nMinLength)
	{
		nMinLength = nTLength;
	}

	/* Compare both strings according to the shorter of the two */
	return my_strncmp(s, t, nMinLength);
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

char* my_strchr(const char* s, char c)
{
	char* pFirstOccurrence = NULL;
	int i = 0;

	/* Go over the string char by char until we reach the end
	 * of the string (marked by \0) or we find an occurrence
	 * of char c.
	 */
	while ((s[i] != '\0') && (pFirstOccurrence == NULL))
	{
		/* Check if the current char is the requested one */
		if (s[i] == c)
		{
			/* Found it */
			pFirstOccurrence = (char*)&(s[i]);
		}

		/* Move on to the next char */
		i++;
	}

	/* Check the special case in which we are actively looking
	 * for the null terminating char (the first scan would
	 * halt when reaching the null-terminator)
	 */
	if ((pFirstOccurrence == NULL) && (s[i] == c))
	{
		pFirstOccurrence = (char*)&(s[i]);
	}

	return pFirstOccurrence;
}
