#include "par.h"
#include <string.h>
#include <stdio.h>

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
 * @param currChar Current char in the program
 */
int toggle_ignore(char currChar);

/**
 * Reads a C program from a stream and prints the same program
 * without the comments to another stream

 * @param inStream Given stream that has the original program
 * @param outStream Stream to print the formatted program out to
 */
void ClearComments(FILE* inStream, FILE* outStream);

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

enum status {OUT, LEFT_SLASH, RIGHT_STAR, IN_STRING, IN_COMMENT};
int toggle_ignore(char currChar)
{
	static int state = OUT;

	switch (state)
	{
	case OUT:
		if (currChar == '\"' || currChar == '\'')
		{
			state = IN_STRING;
		}
		else if (currChar == '/')
		{
			state = LEFT_SLASH;
		}
		break;
	case LEFT_SLASH:
		if (currChar == '*')
		{
			state = IN_COMMENT;
		}
		else
		{
			state = OUT;
		}
		break;
	case IN_COMMENT:
		if (currChar == '*')
		{
			state = RIGHT_STAR;
		}
		break;
	case RIGHT_STAR:
		if (currChar == '/')
		{
			state = OUT;
		}
		else if (currChar != '*')
		{
			state = IN_COMMENT;
		}
		break;
	case IN_STRING:
		if (currChar == '\"' || currChar == '\'')
		{
			state = OUT;
		}
		break;

	default:
		break;
	}

	/* Certains states cause us to be in "ignore mode" */
	if (state == IN_COMMENT ||
		state == IN_STRING)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/* Entry Point */
int main()
{
	/* Read program from stdin and check it */
	par_balance(stdin, stdout);

	return 0;
}

/* API Functions */
eParBalanceLine get_par_balance_in_line(char* szLine,
										unsigned int nLineLength,
										int* io_pCurlyBalance)
{
	eParBalanceLine eBalanced = E_PAR_LINE_BALANCED;
	char arrPars[MAX_LINE_LENGTH];
	int nParDepth = -1;
	int i = 0;
	int nCurrCharIndex = 0;
	int fIgnore = 0; /* When we are in the middle of a string, ignore chars */
	int nCurlyBalance = 0;

	/* Make sure the line's length is ok */
	if (nLineLength > MAX_LINE_LENGTH)
	{
		return E_PAR_LINE_ERROR;
	}
	else if (nLineLength == 0)
	{
		return E_PAR_LINE_BALANCED;
	}

	/* Go over the entire line and check for balancing */
	for (i = nCurrCharIndex; (i < MAX_LINE_LENGTH) && (i < nLineLength); ++i)
	{
		/* Set the ignore flag as needed */
		fIgnore = toggle_ignore(szLine[i]);

		/* Not in ignore mode */
		if (!(fIgnore == 1))
		{
			/* Check for parenthesis */
			switch (szLine[i])
			{
			/* An opening parenthesis */
			case '{':
			{
				/* Count curly separately */
				nCurlyBalance++;
				/* Continue to the rest of the handling normally */
			}
			case '(':
			case '[':
			{
				/* Don't count these as valid if we already short of parenthesis */
				if (nParDepth >= -1)
				{
					nParDepth = opening_parenthesis(szLine[i], arrPars, nParDepth);
				}
				break;
			}
			/* A closing parenthesis */
			case '}':
			{
				/* Count curly separately */
				nCurlyBalance--;
				/* Continue to the rest of the handling normally */
			}
			case ')':
			case ']':
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

	/* Curly braces not balanced */
	if (nCurlyBalance != 0)
	{
		eBalanced = E_PAR_LINE_NOT_BALANCED_CURLY;
		*io_pCurlyBalance += nCurlyBalance;
	}

	return eBalanced;
}
int par_balance(FILE* in_stream, FILE* out_stream)
{
	char szLine[MAX_LINE_LENGTH];
	int nCurlyBlockBalance = 0;
	int fProgramBalanced = 1;

	/* Read the program line-by-line */
	while (fgets(szLine, MAX_LINE_LENGTH, in_stream) != NULL)
	{
		/* Remove the newline at the end of the line before we print */
		szLine[strlen(szLine) - 1] = '\0';

		fprintf(out_stream, "Line: '%s' is: ", szLine);

		/* Check if the line is balanced */
		switch (get_par_balance_in_line(szLine, strlen(szLine), &nCurlyBlockBalance))
		{
			case E_PAR_LINE_BALANCED:
			{
				fprintf(out_stream, "balanced.\n");
				break;
			}
			case E_PAR_LINE_NOT_BALANCED_CURLY:
			{
				/* If there was a block opening - The program might
				 * still balance out so don't be hasty to decide
				 * its not balanced
				 */
				if (nCurlyBlockBalance >= 0)
				{
					fprintf(out_stream, "not balanced (might still balance out).\n");
					break;
				}
				/* Continue to the next case handling */
			}
			case E_PAR_LINE_NOT_BALANCED:
			{
				fProgramBalanced = 0;
				fprintf(out_stream, "not balanced.\n");
				break;
			}
			case E_PAR_LINE_ERROR:
			default:
			{
				fprintf(out_stream, "not a valid C line.\n");
				break;
			}
		}
	}

	/* Finally make sure that the blocks balanced out */
	if (nCurlyBlockBalance != 0)
	{
		fProgramBalanced = 0;
	}

	if (fProgramBalanced)
	{
		fprintf(out_stream, "Program is balanced.\n");
	}
	else
	{
		fprintf(out_stream, "Program not balanced.\n");
	}

	return fProgramBalanced;
}
