%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tn.h"
#include "glob.h"

int i;
extern void printToken(enum tokentypes tn);
%}

%s CMT

%%

"const"		return(TCONST);
"else"		return(TELSE);
"if"		return(TIF);
"int"		return(TINT);
"float"		return(TFLOAT);
"char"		return(TCHAR);
"string" 		return(TSTRING);
"return"		return(TRETURN);
"void"		return(TVOID);
"while"		return(TWHILE);

"+"		return(TPLUS); 		
"-"		return(TMINUS);
"*"		return(TMULTIPLY);		
"/"		return(TDIVIDE);		
"%"		return(TMOD);
"="		return(TASSIGN);
"=="		return(TEQUAL);
"!="		return(TNOTEQU);
"<"		return(TLESS);
">"		return(TGREAT);
"<="		return(TLESSE);
">="		return(TGREATE);
"!"		return(TNOT);
"&&"		return(TAND);
"||"		return(TOR);
"++"		return(TINC);
"--"		return(TDEC);
"+="		return(TADDASSIGN);
"-="		return(TSUBASSIGN);
"*="		return(TMULASSIGN);
"/="		return(TDIVASSIGN);
"%="		return(TMODASSIGN);
"("		return(TLPAREN);		
")"		return(TRPAREN);		
","		return(TCOMMA);
";"		return(TSEMICOLON);	
"["		return(TLBRACKET);	
"]"		return(TRBRACKET);
"{"		return(TLBRACE); 
"}"		return(TRBRACE);	
"'"		return(TSQUOTE);
"\""		return(TQUOTE);

[A-Za-z_][A-Za-z0-9_]*	{
	
		printToken(TIDEN);
		
		yylval.string=strdup(yytext); 
		
		return(TIDEN);
	
}

'.*'		{
			if (yyleng>3) printToken(TILLCHAR);
			else return(TCHARACTER);
		}
\".*\"		return(TSENTENCE);

0|[1-9][0-9]*		return(TNUMBER); //정수형
0[xX][0-9A-Fa-f]+		return(TNUMBER); //정수형
[0-9]+"."[0-9]+(e[+-]?[0-9]+)?	return(TFNUMBER); //실수형


[0-9]+[A-Za-z_][A-Za-z0-9_]*	{
		//첫 글자가 숫자로 시작하는 identifier인 경우
		printToken(TDIGIT);
		return(TDIGIT);
		}

[ \t]			;
"\n"			cLine++;
"//".*			;


"/*"([^*]|"*"+[^*/])*"*"+"/"	{
		//주석 처리 (토큰으로 받지 않고 라인만 처리)
		while (yytext[i] != '\0') {
			if (yytext[i] == '\n' || yytext[i] == '\r') cLine++;
			i++;
		}
}
.			{printToken(TERROR);}

%%

int yywrap() {
	return 1;
}