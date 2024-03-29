/*
 * par.h
 *
 *  Created on: Oct 27, 2012
 *      Author: Or Dahan 201644929
 */

#ifndef PAR_H_
#define PAR_H_

#include <stdio.h>

typedef enum
{
	E_PAR_LINE_BALANCED,
	E_PAR_LINE_NOT_BALANCED,
	E_PAR_LINE_NOT_BALANCED_CURLY,
	E_PAR_LINE_ERROR
}eParBalanceLine;

/**
 * Checks if the given line is balanced in terms of parenthesis
 *
 * @param szLine The line to check
 * @param nLineLength Length of the line (num of chars, not including newline char)
 * @param io_pCurlyBalance Number of blocks that opened so far and havn't been closed
 *
 * @return The status of the balance in the line
 */
eParBalanceLine get_par_balance_in_line(char* szLine, unsigned int nLineLength, int* io_pCurlyBalance);

/**
 * Reads a C program from given stream
 * and checks if its parenthesis-balanced.
 * Prints errors accordingly.
 *
 * @param in_stream An input stream to the function to read a C program from
 * @param out_stram An output stream to the function to print the results to
 *
 * @return 1 if program is balanced, 0 otherwise.
 */
int par_balance(FILE* in_stream, FILE* out_stream);
#endif /* PAR_H_ */
