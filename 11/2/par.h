/*
 * par.h
 *
 *  Created on: Oct 27, 2012
 *      Author: nika123
 */

#ifndef PAR_H_
#define PAR_H_

typedef enum
{
	E_PAR_LINE_BALANCED,
	E_PAR_LINE_NOT_BALANCED,
	E_PAR_LINE_START_BLOCK,
	E_PAR_LINE_ERROR
}eParBalanceLine;

/**
 * Checks if the given line is balanced in terms of parenthesis
 *
 * @param szLine The line to check
 * @param nLineLength Length of the line (num of chars, not including newline char)
 * @param nStartBlock Number of blocks that opened so far and havn't been closed
 *
 * @return The status of the balance in the line
 */
eParBalanceLine get_par_balance_in_line(char* szLine, unsigned int nLineLength, unsigned int nStartBlock);

#endif /* PAR_H_ */
