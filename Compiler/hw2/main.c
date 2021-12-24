/* symtable.c - 각 token에 대한 출력
* programmer - 박기은, 이혜인, 한지수
* date - 27/04/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include "tn.h"
#include "glob.h"
extern void PrintHStable();
extern void SkipSeparators();
extern yylex();
extern char* yytext;

void main()
{
	enum tokentypes tn;  // token number
	enum errorTypes err;
	line = 1;
	printf("Start\n\n");
	printf("Line number\tToken type\tST-index\tToken\n");
	while ((tn = yylex()) != TEOF) {
		printtoken(tn);
	}
	if (errcnt == 0) printf("No errors detected");
	else printf("%d errors detected\n", errcnt);
	printf("\n\n");
	PrintHStable();
}