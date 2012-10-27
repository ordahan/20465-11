#include "../par.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int test_main()
{
	assert(get_par_balance_in_line("") == E_PAR_LINE_BALANCED);


	return 0;
}
