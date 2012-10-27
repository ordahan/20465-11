#include "../par.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int test_main()
{
	/* 1 Single line status */

	/* 1.1 Balanced */
	assert(get_par_balance_in_line("") == E_PAR_LINE_BALANCED);
	assert(get_par_balance_in_line("()") == E_PAR_LINE_BALANCED);
	assert(get_par_balance_in_line("(2132avdcs)") == E_PAR_LINE_BALANCED);
	assert(get_par_balance_in_line("(){}[]") == E_PAR_LINE_BALANCED);
	assert(get_par_balance_in_line("(())") == E_PAR_LINE_BALANCED);
	assert(get_par_balance_in_line("(abcdefghijkl[abcd]weqqwaas)") == E_PAR_LINE_BALANCED);
	assert(get_par_balance_in_line("(\"()\")") == E_PAR_LINE_BALANCED);
	assert(get_par_balance_in_line("(\"[\")") == E_PAR_LINE_BALANCED);

	/* 1.2 Unbalanced */
	assert(get_par_balance_in_line("(") == E_PAR_LINE_NOT_BALANCED);
	assert(get_par_balance_in_line(")") == E_PAR_LINE_NOT_BALANCED);
	assert(get_par_balance_in_line("([)]") == E_PAR_LINE_NOT_BALANCED);
	assert(get_par_balance_in_line("[}()") == E_PAR_LINE_NOT_BALANCED);

	/* 1.3 Start block */
	assert(get_par_balance_in_line("{") == E_PAR_LINE_START_BLOCK);
	assert(get_par_balance_in_line("a dasd {") == E_PAR_LINE_START_BLOCK);
	assert(get_par_balance_in_line("{ adsa ()} {") == E_PAR_LINE_START_BLOCK);
	assert(get_par_balance_in_line("{ adsa ()} {(") == E_PAR_LINE_NOT_BALANCED);

	/* 1.4 End block */
	assert(get_par_balance_in_line("}") == E_PAR_LINE_END_BLOCK);
	assert(get_par_balance_in_line("a dasd }") == E_PAR_LINE_END_BLOCK);
	assert(get_par_balance_in_line("{ adsa ()} }") == E_PAR_LINE_END_BLOCK);
	assert(get_par_balance_in_line("{ adsa ()} (}") == E_PAR_LINE_NOT_BALANCED);

	return 0;
}
