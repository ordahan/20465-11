#include "../par.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

int test_line_balance(char* szLine, eParBalanceLine expected, unsigned int nStartBlock)
{
	return get_par_balance_in_line(szLine, strlen(szLine), nStartBlock) == expected;
}

int test_main()
{
	/* 1 Single line status */

	/* 1.1 Balanced */
	assert(test_line_balance("", E_PAR_LINE_BALANCED, 0));
	assert(test_line_balance("()", E_PAR_LINE_BALANCED, 0));
	assert(test_line_balance("(2132avdcs)", E_PAR_LINE_BALANCED, 0));
	assert(test_line_balance("(){}[]", E_PAR_LINE_BALANCED, 0));
	assert(test_line_balance("(())", E_PAR_LINE_BALANCED, 0));
	assert(test_line_balance("(abcdefghijkl[abcd]weqqwaas)", E_PAR_LINE_BALANCED, 0));
	assert(test_line_balance("(\"()\")", E_PAR_LINE_BALANCED, 0));
	assert(test_line_balance("(\"[\")", E_PAR_LINE_BALANCED, 0));

	/* 1.2 Unbalanced */
	assert(test_line_balance("(", E_PAR_LINE_NOT_BALANCED, 0));
	assert(test_line_balance(")", E_PAR_LINE_NOT_BALANCED, 0));
	assert(test_line_balance("([)]", E_PAR_LINE_NOT_BALANCED, 0));
	assert(test_line_balance("[}()", E_PAR_LINE_NOT_BALANCED, 0));

	/* 1.3 Start block */
	assert(test_line_balance("{", E_PAR_LINE_START_BLOCK, 0));
	assert(test_line_balance("a dasd {", E_PAR_LINE_NOT_BALANCED, 0));
	assert(test_line_balance("{ adsa (){}", E_PAR_LINE_START_BLOCK, 0));
	assert(test_line_balance("{ adsa (){}(", E_PAR_LINE_NOT_BALANCED, 0));

	/* Not rly sure about these... */
	/* 1.4 End block */
	assert(test_line_balance("}", E_PAR_LINE_NOT_BALANCED, 0));
	assert(test_line_balance("a dasd }", E_PAR_LINE_NOT_BALANCED, 0));
	assert(test_line_balance("{ adsa ()} }", E_PAR_LINE_NOT_BALANCED, 0));
	assert(test_line_balance("{ adsa ()} (}", E_PAR_LINE_NOT_BALANCED, 0));

	/* 2 Check entire program */


	printf("All tests run successfully\n");

	return 0;
}
