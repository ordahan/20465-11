#include "../par.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

int test_line_balance(char* szLine,
		eParBalanceLine expected,
		int nCurlyBalance,
		int nExpectedCurlyBalanced)
{
	int l_nCurlyBalance = nCurlyBalance;
	return (get_par_balance_in_line(szLine, strlen(szLine), &l_nCurlyBalance) == expected &&
			l_nCurlyBalance == nExpectedCurlyBalanced);
}

int test_par_balance(const char* szProgram)
{
	int fBalance = 0;
	char c;
    char* pInBuf = NULL;
    char* pOutBuf = NULL;
    size_t nInSize, nOutSize;
    FILE *fInStream = open_memstream(&pInBuf, &nInSize);
    FILE *fOutStream = open_memstream(&pOutBuf, &nOutSize);

    printf("Running on program:\n%s\n", szProgram);

    /* Send the program to the stream that will be read from */
    fputs(szProgram, fInStream);
    fputc('\n', fInStream);

    /* Run the algorithm */
    fBalance = par_balance(fInStream, fOutStream);

    /* Print the results */
    while ((c = fgetc(fOutStream)) != EOF)
    {
    	putchar(c);
    }

    printf("\n");

    return fBalance;
}

int test_main()
{
	/* 1 Single line status */

	/* 1.1 Balanced */
	assert(test_line_balance("", E_PAR_LINE_BALANCED, 0, 0));
	assert(test_line_balance("()", E_PAR_LINE_BALANCED, 0, 0));
	assert(test_line_balance("(2132avdcs)", E_PAR_LINE_BALANCED, 0, 0));
	assert(test_line_balance("(){}[]", E_PAR_LINE_BALANCED, 0, 0));
	assert(test_line_balance("(())", E_PAR_LINE_BALANCED, 0, 0));
	assert(test_line_balance("(abcdefghijkl[abcd]weqqwaas)", E_PAR_LINE_BALANCED, 0, 0));
	assert(test_line_balance("(\"()\")", E_PAR_LINE_BALANCED, 0, 0));
	assert(test_line_balance("(\"[\")", E_PAR_LINE_BALANCED, 0, 0));
	assert(test_line_balance("(\'[\')", E_PAR_LINE_BALANCED, 0, 0));

	/* 1.2 Unbalanced */
	assert(test_line_balance("(", E_PAR_LINE_NOT_BALANCED, 0, 0));
	assert(test_line_balance(")", E_PAR_LINE_NOT_BALANCED, 0, 0));
	assert(test_line_balance("([)]", E_PAR_LINE_NOT_BALANCED, 0, 0));
	assert(test_line_balance("[)()", E_PAR_LINE_NOT_BALANCED, 0, 0));

	/* 1.3 Start block */
	assert(test_line_balance("{", E_PAR_LINE_NOT_BALANCED_CURLY, 0, 1));
	assert(test_line_balance("{(){{{", E_PAR_LINE_NOT_BALANCED_CURLY, 0, 4));
	assert(test_line_balance("a dasd {", E_PAR_LINE_NOT_BALANCED_CURLY, 0, 1));
	assert(test_line_balance("{ adsa (){}", E_PAR_LINE_NOT_BALANCED_CURLY, 0, 1));
	assert(test_line_balance("{ adsa (){}(", E_PAR_LINE_NOT_BALANCED_CURLY, 0, 1));

	/* Not rly sure about these... */
	/* 1.4 End block */
	assert(test_line_balance("}", E_PAR_LINE_NOT_BALANCED_CURLY, 0, -1));
	assert(test_line_balance("}}", E_PAR_LINE_NOT_BALANCED_CURLY, 0, -2));
	assert(test_line_balance("a dasd }", E_PAR_LINE_NOT_BALANCED_CURLY, 0, -1));
	assert(test_line_balance("{ adsa ()}} }", E_PAR_LINE_NOT_BALANCED_CURLY, 0, -2));
	assert(test_line_balance("{ adsa ()} (}", E_PAR_LINE_NOT_BALANCED_CURLY, 0, -1));

	/* 2 Check entire program */
	assert(test_par_balance("") == 1);
	assert(test_par_balance("()") == 1);
	assert(test_par_balance(")") == 0);
	assert(test_par_balance("(") == 0);
	assert(test_par_balance("(\n)") == 0);
	assert(test_par_balance("{") == 0);
	assert(test_par_balance("()\n[\n") == 0);
	assert(test_par_balance("{}\n[]\n") == 1);
	assert(test_par_balance("{\n}") == 1);
	assert(test_par_balance("()\n{\n()[(())]}") == 1);
	assert(test_par_balance("()\n{{}\n()[(())]}") == 1);
	assert(test_par_balance("()\n{{\n}()[(())]}") == 1);
	assert(test_par_balance("{{{\n}}\n}") == 1);
	assert(test_par_balance("()\n\"[\"\n") == 1);
	assert(test_par_balance("()\n\"[\"]\n") == 0);
	assert(test_par_balance("/*)*/") == 1);
	assert(test_par_balance("/*(*/)") == 0);

	printf("All tests run successfully\n");

	return 0;
}
