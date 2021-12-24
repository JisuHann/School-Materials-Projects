%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <malloc.h>
#include <string.h>
#include "glob.h"

int type_int = 0;
int type_void = 0;
int type_float = 0;
int type_char = 0;
int type_string = 0;
int type_const = 0;
int type_param = 0;

void line(int);
extern yylex();
extern yyerror(s);
extern yytext;
%}

%union 
{
        char *string;
}	

%token <string> TIDEN

%token TDIGIT TLONG TERROR TOVERST TCONST TELSE TIF TINT TFLOAT TRETURN TVOID TWHILE TNUMBER TFNUMBER TCHAR TSTRING TILLCHAR
%token TADDASSIGN TSUBASSIGN TMULASSIGN TDIVASSIGN TMODASSIGN TSQUOTE TQUOTE TSENTENCE TCHARACTER
%token TGREAT TLESS TGREATE TLESSE TNOT TAND TOR TINC TDEC 
%token TPLUS TMINUS TMULTIPLY TDIVIDE TMOD TASSIGN TEQUAL TNOTEQU 
%token TLPAREN TRPAREN TCOMMA TSEMICOLON TLBRACKET TRBRACKET TLBRACE TRBRACE
%nonassoc LOWER_THEN_ELSE
%nonassoc TELSE
%left TPLUS TMINUS
%left TMULTIPLY TDIVIDE TMOD
%right TASSIGN

%%

mini_c			: translation_unit
			;
translation_unit		: external_dcl
			| translation_unit external_dcl
			;
external_dcl		: function_def
			| declaration
			| TIDEN TSEMICOLON
			| TDIGIT TSEMICOLON
			| TLONG TSEMICOLON
			| TIDEN error
			{
				yyerrok;
				yyerror("nosemi");		/* error - no semicolon */
			}
			| TDIGIT error
			{
				yyerrok;
				yyerror("nosemi");		/* error - no semicolon */
			}
			| TLONG error
			{
				yyerrok;
				yyerror("nosemi");		/* error - no semicolon */
			}
			;
function_def 		: function_header compound_st
			| function_header TSEMICOLON
			| function_header error 
			{
				/* identifier parse error */
				look_tmp->type = 0;

				yyerrok;
				yyerror("wrong_funcdef") ;		/* error - wrong function definition */
			}
			;
function_header 		: dcl_spec function_name formal_param
			;
dcl_spec			: dcl_specifiers
			;
dcl_specifiers 		: dcl_specifier
			| dcl_specifiers dcl_specifier
			;
dcl_specifier 		: type_qualifier
			| type_specifier
			;
type_qualifier 		: TCONST {type_const = 1;}	/* is constant */
			;
type_specifier 		: TINT {type_int=1; type_float=0; type_void=0; type_char = 0;type_string=0;}		/* type : integer */
			| TFLOAT {type_int=0; type_float=1; type_void=0; type_char = 0;type_string=0;}	/* type : float */
			| TCHAR {type_int = 0; type_float=0; type_void = 0; type_char = 1;type_string=0;}
			| TSTRING {type_int = 0; type_float=0; type_void = 0; type_char = 0;type_string=1;}
			| TVOID {type_int=0; type_float=0; type_void=1; type_char = 0;type_string=0;}	/* type : void */
			;
function_name 		: TIDEN
			{/* identifier about parse error or not defined identifier/function */
				function_val =$1;
				
				if (look_id->type==0 || look_id->type==100)
				{
					
					if(type_int ==1) look_id->type = 7; 		/* integer returning function name */
					else if(type_float == 1) look_id->type = 8;	/* float returning function name */
					else if(type_void == 1) look_id->type = 9;	/* void returning function name */
					/* char/string returning function name 보류
					else if(type_char ==1) look_id->type =28;
					else if(type_string==1)		 */
					type_int=0;		/* not integer */
					type_float=0;		/* not float */
					type_void=0;		/* not void */
					type_char=0;		/* not character*/
					type_string=0;		/* not string*/
					type_param=1;
					look_tmp = look_id;
				}
			}
			| TDIGIT
			|
			{
				yyerrok;
				yyerror("no_funcname"); 		/* error - no function name */
			}
			;
formal_param		: TLPAREN opt_formal_param TRPAREN
			{
				type_param=0;
			}
			| TLPAREN opt_formal_param error
			{
				yyerrok;
				yyerror("no_paren");		/* error - no parenthesis */
			}
			;
opt_formal_param		: formal_param_list			
			|	
			{
				type_param=0;
			}			
			;
formal_param_list 		: param_dcl
			;
param_dcl 		: dcl_spec init_dcl_list
			;
compound_st 		: TLBRACE compound TRBRACE
			| TLBRACE compound error
			{
				yyerrok;
				yyerror("nobrace"); 		/* error - no brace */
			}
			;
compound 		: opt_dcl_list opt_stat_list
			;
opt_dcl_list 		: declaration_list
			|
			;
declaration_list 		: declaration
			| declaration_list declaration
			;
declaration 		: dcl_spec init_dcl_list TSEMICOLON
			{
				type_int=0;	/* not integer */
				type_float=0;	/* not float */
				type_void=0;	/* not void */
				type_const = 0;	/* not constant */	
				type_char = 0; 	/* not character */
				type_string=0;			
			}
			| dcl_spec init_dcl_list error
			{
				look_tmp->type = 0; /* identifier about parse error */
				yyerrok;
				type_int = 0; 	/* not integer */
				type_float = 0;	/* not float */
				type_void = 0; 	/* not void */
				type_const = 0;	/* not constant */
				type_char = 0; 	/* not character */
				type_string = 0; 	/* not character */
				
				yyerror("nosemi"); /* error - no semicolon */
			}
			;
init_dcl_list 		: init_declarator
			| init_dcl_list TCOMMA init_declarator
			| init_dcl_list init_declarator error
			{
				yyerrok;
				yyerror("no_comma");
			}
			
			;
init_declarator 		: declarator
			| declarator TASSIGN TNUMBER
			| declarator TASSIGN TMINUS TNUMBER
			| declarator TASSIGN TFNUMBER
			| declarator TASSIGN TMINUS TFNUMBER
			| declarator TASSIGN TIDEN
			| declarator TASSIGN TCHARACTER TSQUOTE
			| declarator TASSIGN TSENTENCE TQUOTE
			;
declarator 		: TIDEN
			{
				if(look_id->type==0) 
				{
					if( type_param ==0){
						if( type_const == 0){
							if(type_int==1) 		/* type : integer */
								look_id->type = 1;	/* integer scalar variable */
							else if(type_float==1)	/* type : float */
								look_id->type = 2;	/* float scalar variable */
							else if(type_void==1) 	/* type : void */
								look_id->type = 3;	/* void scalar variable */
							else if(type_char==1)	/* type : character */
								look_id->type=22;	/* character scalar variable */
							else if(type_string==1)	/* type : string*/
								look_id->type=25;	/* string scalar variable */
						}
						else if( type_const == 1){
							if(type_int==1) 		/* type : integer */
								look_id->type = 10;	/* integer scalar constant */
							else if(type_float==1)	/* type : float */
								look_id->type = 11;	/* float scalar constant */
							else if(type_void==1) 	/* type : void */
								look_id->type = 12;	/* void scalar constant */
							else if(type_char==1)	/* type : character */
								look_id->type=23;	/* character scalar constant */
							else if(type_string==1)	/* type : string*/
								look_id->type=26;	/* string scalar constant */
						}
					}
					else if( type_param ==1){
							if(type_int==1) 		/* type : integer */
								look_id->type = 16;	/* integer scalar parameter */
							else if(type_float==1)	/* type : float */
								look_id->type = 17;	/* float scalar parameter */
							else if(type_void==1) 	/* type : void */
								look_id->type = 18;	/* void scalar parameter */
							else if(type_char==1)	/* type : character */
								look_id->type=24;	/* character scalar parameter */
							else if(type_string==1)	/* type : string*/
								look_id->type=27;	/* string scalar parameter*/
							
					}
				}
				look_id->function=function_val;
				look_tmp = look_id;
				
			}
			| TDIGIT
			| TLONG
			| TIDEN TLBRACKET opt_number TRBRACKET
			{
				if(look_id->type==0) 
				{
					if( type_param ==0){
						if(type_const==0)
						{
							if(type_int == 1) look_id->type = 4; 		/* array integer variable */
							else if(type_float == 1) look_id->type = 5;	/* array float variable */
							else if(type_void == 1) look_id->type = 6;	/* array void variable */
						}
						else if(type_const==1)
						{
							if(type_int == 1) look_id->type = 13; 		/* array integer constant */
							else if(type_float == 1) look_id->type = 14;	/* array float constant */
							else if(type_void == 1) look_id->type = 15;	/* array void constant */
						}
					}
					else if( type_param ==1){
							if(type_int==1) 		/* type : integer */
								look_id->type = 19;	/* integer array parameter */
							else if(type_float==1)	/* type : float */
								look_id->type = 20;	/* float array parameter */
							else if(type_void==1) 	/* type : void */
								look_id->type = 21;	/* void array parameter */
							
					}
					
				}
				look_id->function=function_val;
				look_tmp = look_id;
				
			}
			| TDIGIT TLBRACKET opt_number TRBRACKET
			| TLONG TLBRACKET opt_number TRBRACKET
			| TIDEN TLBRACKET opt_number error
			{
				yyerrok;
				yyerror("nobracket"); /* error - no bracket */
			}
			| TDIGIT TLBRACKET opt_number error
			{
				yyerrok;
				yyerror("nobracket"); /* error - no bracket */
			}
			| TLONG TLBRACKET opt_number error
			{
				yyerrok;
				yyerror("nobracket"); /* error - no bracket */
			}
opt_number 		: TNUMBER
			|
			;
opt_stat_list 		: statement_list
			|
			;
statement_list 		: statement
			| statement_list statement
			| statement_list declaration
			;
statement 		: compound_st
			| expression_st
			| if_st
			| while_st
			| return_st
			;
expression_st 		: opt_expression TSEMICOLON
			| expression error
			{
				yyerrok;
				yyerror("nosemi"); /* error - no semicolon */
			}
			;
opt_expression 		: expression
			|
			;
if_st 			: TIF TLPAREN expression TRPAREN statement %prec LOWER_THEN_ELSE
			| TIF TLPAREN expression TRPAREN statement TELSE statement
			| TIF TLPAREN expression error
			{
				yyerrok;
				yyerror("no_paren");	/* error - no parenthesis */
			}
			| TIF TLPAREN TRPAREN
			{
				yyerrok;
				yyerror("wrong_funcdef");
			}
			;
while_st 			: TWHILE TLPAREN expression TRPAREN statement
			| TWHILE TLPAREN expression error
			{
				yyerrok;
				yyerror("no_paren");	/* error - no parenthesis */
			}
			| TWHILE TLPAREN TRPAREN
			{
				yyerrok;
				yyerror("wrong_funcdef");
			}
			;
return_st 		: TRETURN opt_expression TSEMICOLON
			| TRETURN expression error
			{
				yyerrok;
				yyerror("nosemi");		/* error - no semicolon */
			}
			| TRETURN error
			{
				yyerrok;
				yyerror("no_return");	/* error - wrong statement */
			}
			;
expression 		: assignment_exp
			;
assignment_exp 		: logical_or_exp
			| unary_exp1 TASSIGN assignment_exp
			| unary_exp1 TADDASSIGN assignment_exp
			| unary_exp1 TSUBASSIGN assignment_exp
			| unary_exp1 TMULASSIGN assignment_exp
			| unary_exp1 TDIVASSIGN assignment_exp
			| unary_exp1 TMODASSIGN assignment_exp
			| unary_exp1 TASSIGN
			{
				yyerrok;
				yyerror("wrong_st");	
			}
			| unary_exp1 TADDASSIGN
			{
				yyerrok;
				yyerror("wrong_st");	
			}
			| unary_exp1 TSUBASSIGN
			{
				yyerrok;
				yyerror("wrong_st");	
			}
			| unary_exp1 TMULASSIGN
			{
				yyerrok;
				yyerror("wrong_st");	
			}
			| unary_exp1 TDIVASSIGN
			{
				yyerrok;
				yyerror("wrong_st");	
			}
			| unary_exp1 TMODASSIGN
			{
				yyerrok;
				yyerror("wrong_st");	
			}
			| unary_exp2 TASSIGN assignment_exp
			{
				yyerrok;
				yyerror("wrong_assign"); 	/* error - wrong assignment */
			}
			| unary_exp2 TADDASSIGN assignment_exp
			{
				yyerrok;
				yyerror("wrong_assign"); 	/* error - wrong assignment */
			}
			| unary_exp2 TSUBASSIGN assignment_exp
			{
				yyerrok;
				yyerror("wrong_assign"); 	/* error - wrong assignment */
			}
			| unary_exp2 TMULASSIGN assignment_exp
			{
				yyerrok;
				yyerror("wrong_assign"); 	/* error - wrong assignment */
			}
			| unary_exp2 TDIVASSIGN assignment_exp
			{
				yyerrok;
				yyerror("wrong_assign"); 	/* error - wrong assignment */
			}
			| unary_exp2 TMODASSIGN assignment_exp
			{
				yyerrok;
				yyerror("wrong_assign"); 	/* error - wrong assignment */
			}
			;
logical_or_exp 		: logical_and_exp
			| logical_or_exp TOR logical_and_exp
			| logical_or_exp TOR
			{
				yyerrok;
				yyerror("wrong_st");
			}
			;
logical_and_exp 		: equality_exp
			| logical_and_exp TAND equality_exp
			| logical_and_exp TAND
			{
				yyerrok;
				yyerror("wrong_st");
			}
			;
equality_exp 		: relational_exp
			| equality_exp TEQUAL relational_exp
			| equality_exp TNOTEQU relational_exp
			| equality_exp TEQUAL
			{
				yyerrok;
				yyerror("wrong_st");
			}
			| equality_exp TNOTEQU
			{
				yyerrok;
				yyerror("wrong_st");
			}
			;
relational_exp 		: addtive_exp
			| relational_exp TGREAT addtive_exp
			| relational_exp TLESS addtive_exp
			| relational_exp TGREATE addtive_exp
			| relational_exp TLESSE addtive_exp
			| relational_exp TGREAT
			{
				yyerrok;
				yyerror("wrong_st");
			}
			| relational_exp TLESS
			{
				yyerrok;
				yyerror("wrong_st");
			}
			| relational_exp TGREATE
			{
				yyerrok;
				yyerror("wrong_st");
			}
			| relational_exp TLESSE
			{
				yyerrok;
				yyerror("wrong_st");
			}
			;
addtive_exp 		: multiplicative_exp
			| addtive_exp TPLUS multiplicative_exp
			| addtive_exp TMINUS multiplicative_exp
			| addtive_exp TPLUS
			{
				yyerrok;
				yyerror("wrong_st");
			}
			| addtive_exp TMINUS
			{
				yyerrok;
				yyerror("wrong_st");
			}
			;
multiplicative_exp 		: unary_exp1
			| multiplicative_exp TMULTIPLY unary_exp1
			| multiplicative_exp TDIVIDE unary_exp1
			| multiplicative_exp TMOD unary_exp1
			| unary_exp2
			| multiplicative_exp TMULTIPLY unary_exp2
			| multiplicative_exp TDIVIDE unary_exp2
			| multiplicative_exp TMOD unary_exp2
			| multiplicative_exp TMULTIPLY
			{
				yyerrok;
				yyerror("wrong_st");
			}
			| multiplicative_exp TDIVIDE
			{
				yyerrok;
				yyerror("wrong_st");
			}
			| multiplicative_exp TMOD
			{
				yyerrok;
				yyerror("wrong_st");
			}
			;
unary_exp1 		: postfix_exp
			| TMINUS unary_exp1
			| TNOT unary_exp1
			| TINC unary_exp1
			| TDEC unary_exp1
			;
unary_exp2 		: primary_exp2
			| TMINUS unary_exp2
			;
postfix_exp 		: primary_exp
			| postfix_exp TLBRACKET expression TRBRACKET
			| postfix_exp TLPAREN opt_actual_param TRPAREN
			| postfix_exp TINC
			| postfix_exp TDEC
			| postfix_exp TLBRACKET expression error
			{
				yyerrok;
				yyerror("nobracket"); /* error - no bracket */
			}
			| postfix_exp TLPAREN opt_actual_param error
			{
				yyerrok;
				yyerror("no_paren"); /* error - no parenthesis */
			}
			;
opt_actual_param 		: actual_param
			|
			;
actual_param 		: actual_param_list
			;
actual_param_list 		: assignment_exp
			| actual_param_list TCOMMA assignment_exp
			;
primary_exp 		: TIDEN
			{
				if(look_id->type==0) 
					look_id->type = 100; /* not defined identifier/function */
			}
			| TDIGIT
			| TLONG
			;
primary_exp2		: TNUMBER
			| TFNUMBER
			| TCHARACTER
			| TSENTENCE
			| TLPAREN expression TRPAREN
			| TLPAREN expression error
			{
				yyerrok;
				yyerror("no_paren");	/* error - no parenthesis */
			}
			;


%%
void line(int n){
printf("\t %d \t",n);
}