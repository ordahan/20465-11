#include "par.h"

/* Global Const */
static const unsigned int MAX_LINE_LENGTH = 100;

/* Function prototypes */

/**
 * Gets the matching opening parenthesis for the given closing
 * parenthesis
 *
 * @param cPar Closing parenthesis to match
 *
 * @return Matching opening parenthesis or 0 if the given char is invalid
 */
char get_opening_parenthesis(char cPar);

/**
 * Adds the given parenthesis to the array of last seen parenthesis
 *
 * @param cPar Par to add
 * @param arrPars Array of last seen parenthesis
 * @param nParDepth Current location in the array
 *
 * @return The new location in the array
 */
int opening_parenthesis(char cPar, char arrPars[MAX_LINE_LENGTH], int nParDepth);

/**
 * Checks if the last par added to the array of last seen matches
 * the given closing par, and removes it from the array if it is.
 *
 * @param cPar Par to check for a match with
 * @param arrPars Array of last seen parenthesis
 * @param nParDepth Current location in the array
 *
 * @return The new location in the array
 */
int closing_parenthesis(char cPar, char arrPars[MAX_LINE_LENGTH], int nParDepth);

/**
 * Checks if the current char is entering or exiting ignore mode
 *
 * @param szString String in which we check the curr char
 * @param nCurrLinePos Current position in the string where the char is
 * @param fIgnore Whether we are already in ignore mode or not
 */
int toggle_ignore(char* szString, int nCurrLinePos, int fIgnore);

/* Internal Functions */
char get_opening_parenthesis(char cPar)
{
	char cMatchingPar = 0;
	switch (cPar)
	{
	case ')':
		cMatchingPar = '(';
		break;
	case ']':
		cMatchingPar = '[';
		break;
	case '}':
		cMatchingPar = '{';
		break;
	default:
		break;
	}

	return cMatchingPar;
}

int opening_parenthesis(char cPar, char arrPars[MAX_LINE_LENGTH], int nParDepth)
{
	/* Save the par so we can tell if its closed later */
	nParDepth++;
	arrPars[nParDepth] = cPar;
	return nParDepth;
}

int closing_parenthesis(char cPar, char arrPars[MAX_LINE_LENGTH], int nParDepth)
{
	/* Is this an extra closing ? */
	if (nParDepth < 0)
	{
		return --nParDepth;
	}

	/* Check if the last opening par presented was legal */
	if ((arrPars[nParDepth] == get_opening_parenthesis(cPar)))
	{
		/* 'remove' it from the list */
		nParDepth--;
	}

	return nParDepth;
}

int toggle_ignore(char* szString, int nCurrLinePos, int fIgnore)
{
	/* Start or end of a string */
	if ((szString[nCurrLinePos] == '"') &&
	/* Not escaped by a backslash */
		(szString[nCurrLinePos-1] != '\\'))
	{
		/* Toggle ignore mode */
		if (fIgnore == 1)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}

	return fIgnore;
}

/* Entry Point */
int main()
{
	return 0;
}

/* API Functions */
eParBalanceLine get_par_balance_in_line(char* szLine,
										unsigned int nLineLength,
										unsigned int nStartBlock)
{
	eParBalanceLine eBalanced = E_PAR_LINE_BALANCED;
	char arrPars[MAX_LINE_LENGTH];
	int nParDepth = -1;
	int i = 0;
	int nCurrCharIndex = 0;
	int fIgnore = 0; /* When we are in the middle of a string, ignore chars */

	/* Make sure the line's length is ok */
	if (nLineLength > MAX_LINE_LENGTH)
	{
		return E_PAR_LINE_ERROR;
	}
	else if (nLineLength == 0)
	{
		return E_PAR_LINE_BALANCED;
	}

	/* Check the special case in which the line is
	 * the start of a new block and unbalanced by it
	 * line is known to be at least 1 char in length
	 */
	if (szLine[0] == '{')
	{
		eBalanced = E_PAR_LINE_START_BLOCK;
		nCurrCharIndex = 1;
	}

	/* Go over the entire line and check for balancing */
	for (i = nCurrCharIndex; (i < MAX_LINE_LENGTH) && (i < nLineLength); ++i)
	{
		/* Set the ignore flag as needed */
		fIgnore = toggle_ignore(szLine, i, fIgnore);

		/* Not in ignore mode */
		if (!(fIgnore == 1))
		{
			/* Check for parenthesis */
			switch (szLine[i])
			{
			/* An opening parenthesis */
			case '(':
			case '[':
			case '{':
			{
				/* Don't count these as valid if we already short of parenthesis */
				if (nParDepth >= -1)
				{
					nParDepth = opening_parenthesis(szLine[i], arrPars, nParDepth);
				}
				break;
			}
			/* A closing parenthesis */
			case ')':
			case ']':
			case '}':
			{
				nParDepth = closing_parenthesis(szLine[i], arrPars, nParDepth);
				break;
			}
			default:
				break;
			}
		}
	}

	/* Line is unbalanced */
	if (nParDepth != -1)
	{
		eBalanced = E_PAR_LINE_NOT_BALANCED;
	}

	return eBalanced;
}
