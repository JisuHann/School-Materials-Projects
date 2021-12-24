/* printtoken.c - Classify functions of classified token cases	
* programmer - 박기은, 이혜인, 한지수
* date - 27/04/2021
*/
#include <stdio.h>
#include <stdlib.h>
#include "tn.h"
#include "glob.h"
extern void reporterror(char* string);
extern void countline(char* string);
extern yylex();
extern char* yytext;

void printtoken(enum tokentypes tn) {

	if (tn == TSEPARATOR) (void)0;
	else if (tn == TLINE) {
		line++;
		return;
	}
	else {
		printf("%11d\t", line);
		switch (tn) {


		case TCONST: printf("Constant\t"); break;
		case TELSE: printf("Else\t"); break;
		case TIF: printf("If\t"); break;
		case TINT: printf("Integer\t"); break;
		case TRETURN: printf("Return\t"); break;
		case TVOID: printf("Void\t"); break;
		case TWHILE: printf("While\t"); break;

		case TADD: printf("Add\t"); break;
		case TSUB: printf("Subract\t"); break;
		case TMUL: printf("Multiply\t"); break;
		case TDIV: printf("Divide\t"); break;
		case TMOD: printf("Mod\t"); break;

		case TASSIGN: printf("Assign\t"); break;
		case TADDASSIGN: printf("Add and assign\t"); break;
		case TSUBASSIGN: printf("Subtract and assign\t"); break;
		case TMULASSIGN: printf("Multiply and assign\t"); break;
		case TDIVASSIGN: printf("Divide and assign\t"); break;
		case TMODASSIGN: printf("Mod and assign\t"); break;

		case TNOT: printf("Not\t"); break;
		case TAND: printf("And\t"); break;
		case TOR: printf("Or\t"); break;

		case TEQUAL: printf("Equal\t"); break;
		case TNOTEQU: printf("Not_Equal\t"); break;
		case TLESS: printf("Less\t"); break;
		case TGREAT: printf("Great\t"); break;
		case TLESSE: printf("Less equal\t"); break;
		case TGREATE: printf("Great equal\t"); break;

		case TINC: printf("Increase\t"); break;
		case TDEC: printf("Decrease\t"); break;

		case TLSBRACKET: printf("Left Small Bracket\t"); break;
		case TRSBRACKET: printf("Right Small Bracket\t"); break;
		case TLMBRACKET: printf("Left Medium Bracket\t"); break;
		case TRMBRACKET: printf("Right Medium Bracket\t"); break;
		case TLLBRACKET: printf("Left Large Bracket\t"); break;
		case TRLBRACKET: printf("Right Large Bracket\t"); break;
		case TCOMMA: printf("Comma\t"); break;
		case TSEMICOLON: printf("Semicolon\t"); break;

		case TSQUOTE: printf("Small Quote"); break;
		case TBQUOTE: printf("Big Quote"); break;

		case TIDENT: reporterror(yytext); break; //인식한 identifier의 오류를 점검
		case TNUMBER: printf("Number: %d\t", atoi(yytext)); break;
		case TFLOAT: printf("Float: %f\t", atof(yytext)); break;

		case TERROR: printerror(illsp, yytext); break; //illegal symbol일 때 출력
		case TILLID: printerror(illid, yytext); break; //숫자로 시작하는 identifier일 때 오류 출력

		case TCOMMENT_SINGLE: printf("Comment line\t");  break;
		case TCOMMENT_MULTI: printf("Comment line\t");  countline(yytext); break; //여러 줄 주석의 라인 개수 출력
		}
		printf("\n");
	}
}
