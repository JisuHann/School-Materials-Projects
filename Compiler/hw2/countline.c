/* countline.c - \n, \r 에 따라 라인수 업로드 하는 함수
* programmer - 박기은, 이혜인, 한지수
* date - 27/04/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tn.h"
#include "glob.h"

// countline 함수:  여러줄 주석 /* */의  라인의 개수를 세기 위한 함수. /* */ 부분의 토큰에서 개행문자 ’\n’ 를 센다.
void countline(char* string)
{

	int i = 0;

	while (string[i] != '\0') {
		if (string[i] == '\n' || string[i] == '\r') line++;
		i++;
	}

}
