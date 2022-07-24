%{

#include "syntax.tab.h"
#include<stdlib.h>
//now nothing
int yycolumn = 1;
extern int flagoferror;
#define YY_USER_ACTION \
    yylloc.first_line = yylloc.last_line = yylineno; \
    yylloc.first_column = yycolumn; \
    yylloc.last_column = yycolumn + yyleng - 1; \
    yycolumn += yyleng;
%}

%option yylineno
DIGIT [0-9]
SEMI ;
COMMA ,
ASSIGNOP =
RELOP >|<|>=|<=|==|!=
PLUS \+
MINUS -
STAR \*
DIV \/
AND &&
OR \|\|
DOT \.
NOT !
TYPE int|float
LP \(
RP \)
LB \[
RB \]
LC \{
RC \}
STRUCT struct
RETURN return
IF if
ELSE else
WHILE while
DEC {DIGIT}|[1-9]{DIGIT}+
OCT 0[0-7]+
HEX 0[xX][0-9a-fA-F]+
INT {DEC}
EXP ({DIGIT}*{DOT}{DIGIT}+|{DIGIT}+{DOT}{DIGIT}*)[Ee][+-]?{DIGIT}+
FLOAT {DIGIT}+{DOT}{DIGIT}+
ID [a-zA-Z_][a-zA-Z_0-9]*

%%
{SEMI} {/*printf("SEMI\n");*/return SEMI;}
{COMMA} {/*printf("COMMA\n");*/return COMMA;}
{ASSIGNOP} {/*printf("ASSIGNOP\n");*/return ASSIGNOP;}
{RELOP} {/*printf("RELOP\n");*/yylval.type_string = strdup(yytext);return RELOP;}
{PLUS} {/*printf("PLUS\n");*/return PLUS;}
{MINUS} {/*printf("MINUS\n");*/return MINUS;}
{STAR} {/*printf("STAR\n");*/return STAR;}
{DIV} {/*printf("DIV\n");*/return DIV;}
{AND} {/*printf("AND\n");*/return AND;}
{OR} {/*printf("OR\n");*/return OR;}
{DOT} {/*printf("DOT\n");*/return DOT;}
{NOT} {/*printf("NOT\n");*/return NOT;}
{TYPE} {/*printf("TYPE\n");*/yylval.type_string = strdup(yytext);/*printf("t=%s",yylval.type_string);*/return TYPE;}
{LP} {/*printf("LP\n");*/return LP;}
{RP} {/*printf("RP\n");*/return RP;}
{LB} {/*printf("LB\n");*/return LB;}
{RB} {/*printf("RB\n");*/return RB;}
{LC} {/*printf("LC\n");*/return LC;}
{RC} {/*printf("RC\n");*/return RC;}
{STRUCT} {/*printf("STRUCT\n");*/return STRUCT;}
{RETURN} {/*printf("RETURN\n");*/return RETURN;}
{IF} {/*printf("IF\n");*/return IF;}
{ELSE} {/*printf("ELSE\n");*/return ELSE;}
{WHILE} {/*printf("WHILE\n");*/return WHILE;}
{INT} {/*printf("INT\n");*/ yylval.type_int = atoi(yytext); return INT;}
{FLOAT} {/*printf("FLOAT\n");*/ yylval.type_float = atof(yytext);return FLOAT;}
{ID} {/*printf("ID\n");*/yylval.type_string = strdup(yytext);/*printf("id = %s",yylval.type_string);*/return ID;}
"\n" {/*printf("Linebreak\n");*/ yycolumn = 1;}
[ \t\r\v] {}
"//" {
    /*printf("single line comment\n");*/
    char c = input();
    while(c!='\n') c = input();
    unput(c);
}
"/*" {
    /*printf("multiple line comment\n");*/
    char c = input();
    int t = 1;
    while(1)
    {
        t++;
        c = input();
        if(c == '*')
        {
            char nextc = input();
            if(nextc == '/') break;
            else
                unput(nextc);
        }
        if(c == '\0')
        {
            /*printf("end of file line: %d\n",yylineno);*/
            break;
        }
    }
}
<<EOF>> {return 0;}
. {flagoferror++;printf("Error type A at Line %d: Mysterious characters \'%s'\n",yylineno,yytext);}

%%
