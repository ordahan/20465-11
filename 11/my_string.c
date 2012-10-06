/*
 * my_string.c
 *
 *  Created on: Oct 6, 2012
 *      Author: Or Dahan
 */

#include "my_string.h"
#include <stdlib.h>

int main()
{
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
	do
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
	while ((s[i] != '\0') && (pFirstOccurrence == NULL));

	return pFirstOccurrence;
}
