/* reporterror.c - Check identifier error
* programmer - 박기은, 이혜인, 한지수
* date - 27/04/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tn.h"
#include "glob.h"
#define isWord(x) ((((x>='a'&&(x)<='z') || ((x)>='A'&&(x)<='Z')) || (x=='_')))
#define isNum(x) ((x) >= '0' && (x) <= '9')
extern void symtable(char* string);
typedef enum errorTypes ERROR;
ERROR errr = noerror;

int errflag = 0;
errcnt = 0;

//PrintError 함수: ERRORtypes 객체 내용을 바탕으로 ERROR 정보를 출력
// error: illsp(허용되지 않는 문자 사용한 식별자 에러)
//        illid(숫자와 함께 시작하는 식별자 에러)
//        overst(식별자길이idlen을 넘는 식별자 에러)
//        overfl(크기로 overflow 발생)
void printerror(ERROR err, char* string)
{
	if (err == illid) {
		printf("**Error**\t\t%s Illegal IDENT", string);
		errcnt++;
	}
	else if (err == overst) {
		printf("**Error**\t\t\t%s over 12 words", string);
		errcnt++;
	}
	else if (err == illsp) {
		printf("**Error**\t\t%s Illegal Symbol", string);
		errcnt++;
	}

	else if (err == overfl) {
		printf("**Error**\t overflow occured\n");
		errcnt++;
	}
}


//reporterror 함수: overst(string 길이가 12자 이상) 에러 감지
void reporterror(char* string) {
	if (strlen(string) > 12) {
		errr = overst;
		printerror(errr, string);
	}

	else {
		printf("Identifier\t");
		symtable(string);
	}
}