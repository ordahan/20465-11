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
	E_PAR_LINE_END_BLOCK
}eParBalanceLine;

eParBalanceLine get_par_balance_in_line(char* szLine);

#endif /* PAR_H_ */
