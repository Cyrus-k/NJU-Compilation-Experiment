%{
    #include<stdarg.h>
    #include<stdio.h>
    
    #include<string.h>
    #include "tree.h"
    extern int yylineno;
    extern int flagoferror;
    struct TreeNode* root = NULL;
%}
%locations

%union{
    int type_int;
    float type_float;
    char* type_string;
    struct TreeNode* Node;
}

%type <Node> Program
%type <Node> ExtDefList
%type <Node> ExtDef
%type <Node> ExtDecList
%type <Node> Specifier
%type <Node> StructSpecifier
%type <Node> OptTag
%type <Node> Tag
%type <Node> VarDec
%type <Node> FunDec
%type <Node> VarList
%type <Node> ParamDec
%type <Node> CompSt
%type <Node> StmtList
%type <Node> Stmt
%type <Node> DefList
%type <Node> Def
%type <Node> DecList
%type <Node> Dec
%type <Node> Exp
%type <Node> Args

%token SEMI COMMA DOT
%token LP RP LB RB LC RC
%token ASSIGNOP PLUS MINUS STAR DIV
%token AND OR NOT
%token STRUCT RETURN
%token IF ELSE WHILE
%token <type_int> INT
%token <type_float> FLOAT
%token <type_string> TYPE ID RELOP

%right ASSIGNOP
%left OR
%left AND
%left RELOP
%left PLUS MINUS
%left STAR DIV
%right NOT
%left NEGMINUS
%left LP RP LB RB DOT
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%
Program : ExtDefList {$$ = BuildTree("Program",TypeNontoken,@$.first_line,1,$1);root = $$; }
    ;
ExtDefList : ExtDef ExtDefList {$$ = BuildTree("ExtDefList",TypeNontoken,@$.first_line,2,$1,$2);}
    | {$$ = BuildTree("ExtDefList",TypeNontoken,@$.first_line,0,NULL);
        /*$$ = NULL;*/}
    ;
ExtDef : Specifier ExtDecList SEMI {struct TreeNode* nodeSEMI = CreateLeaf("SEMI", TypeToken, @3.first_line, Typenon);
                                    $$ = BuildTree("ExtDef",TypeNontoken,@$.first_line,3,$1,$2,nodeSEMI);}
    | Specifier ExtDecList error SEMI
    | Specifier error SEMI
    | Specifier ExtDecList error //{yyerror("Missing ';'");}
    | Specifier SEMI {struct TreeNode* nodeSEMI = CreateLeaf("SEMI", TypeToken, @2.first_line, Typenon);
                        $$ = BuildTree("ExtDef",TypeNontoken,@$.first_line,2,$1,nodeSEMI);}
    | error SEMI
    | Specifier error
    | Specifier FunDec CompSt {$$ = BuildTree("ExtDef",TypeNontoken,@$.first_line,3,$1,$2,$3);}
    | Specifier error CompSt
    | error CompSt
    ;
ExtDecList : VarDec {$$ = BuildTree("ExtDecList",TypeNontoken,@$.first_line,1,$1);}
    | VarDec COMMA ExtDecList {struct TreeNode* nodeCOMMA = CreateLeaf("COMMA", TypeToken, @2.first_line, Typenon);
                                $$ = BuildTree("ExtDecList",TypeNontoken,@$.first_line,3,$1,nodeCOMMA,$3);}
    ;

Specifier : TYPE {struct TreeNode* nodeTYPE = CreateLeaf("TYPE", TypeToken, @1.first_line, Typeid, $1);
                    $$ = BuildTree("Specifier",TypeNontoken,@$.first_line,1,nodeTYPE);}
    | StructSpecifier {$$ = BuildTree("Specifier",TypeNontoken,@$.first_line,1,$1);}
    ;
StructSpecifier : STRUCT OptTag LC DefList RC {struct TreeNode* nodeSTRUCT = CreateLeaf("STRUCT", TypeToken, @1.first_line, Typenon);
                                                struct TreeNode* nodeLC = CreateLeaf("LC", TypeToken, @3.first_line, Typenon);
                                                struct TreeNode* nodeRC = CreateLeaf("RC", TypeToken, @5.first_line, Typenon);
                                                $$ = BuildTree("StructSpecifier",TypeNontoken,@$.first_line,5,nodeSTRUCT,$2,nodeLC,$4,nodeRC);}
    | STRUCT OptTag LC DefList error RC
    | STRUCT Tag {struct TreeNode* nodeSTRUCT = CreateLeaf("STRUCT", TypeToken, @1.first_line, Typenon);
                    $$ = BuildTree("StructSpecifier",TypeNontoken,@$.first_line,2,nodeSTRUCT,$2);}
    ;
OptTag : ID {struct TreeNode* nodeID = CreateLeaf("ID", TypeToken, @1.first_line, Typeid, $1);
            $$ = BuildTree("OptTag",TypeNontoken,@$.first_line,1,nodeID);}
    | {$$ = BuildTree("OptTag",TypeNontoken,@$.first_line,0,NULL);
        /*$$ = NULL;*/}
    ;
Tag : ID {struct TreeNode* nodeID = CreateLeaf("ID", TypeToken, @1.first_line, Typeid, $1);
            $$ = BuildTree("Tag",TypeNontoken,@$.first_line,1,nodeID);}
    ;

VarDec : ID {struct TreeNode* nodeID = CreateLeaf("ID", TypeToken, @1.first_line, Typeid, $1);
            $$ = BuildTree("VarDec",TypeNontoken,@$.first_line,1,nodeID);}
    | VarDec LB INT RB {struct TreeNode* nodeLB = CreateLeaf("LB", TypeToken, @2.first_line, Typenon);
                struct TreeNode* nodeINT = CreateLeaf("INT", TypeToken, @3.first_line, Typeint, $3);
                struct TreeNode* nodeRB = CreateLeaf("RB", TypeToken, @4.first_line, Typenon);
                $$ = BuildTree("VarDec",TypeNontoken,@$.first_line,4,$1,nodeLB,nodeINT,nodeRB);}
    ;
FunDec : ID LP VarList RP {struct TreeNode* nodeID = CreateLeaf("ID", TypeToken, @1.first_line, Typeid, $1);
                struct TreeNode* nodeLP = CreateLeaf("LP", TypeToken, @2.first_line, Typenon);
                struct TreeNode* nodeRP = CreateLeaf("RP", TypeToken, @4.first_line, Typenon);
                $$ = BuildTree("FunDec",TypeNontoken,@$.first_line,4,nodeID,nodeLP,$3,nodeRP);}
    | ID LP RP {struct TreeNode* nodeID = CreateLeaf("ID", TypeToken, @1.first_line, Typeid, $1);
                struct TreeNode* nodeLP = CreateLeaf("LP", TypeToken, @2.first_line, Typenon);
                struct TreeNode* nodeRP = CreateLeaf("RP", TypeToken, @3.first_line, Typenon);
                $$ = BuildTree("FunDec",TypeNontoken,@$.first_line,3,nodeID,nodeLP,nodeRP);}
    ;
VarList : ParamDec COMMA VarList {struct TreeNode* nodeCOMMA = CreateLeaf("COMMA", TypeToken, @2.first_line, Typenon);
                                    $$ = BuildTree("VarList",TypeNontoken,@$.first_line,3,$1,nodeCOMMA,$3);}
    | ParamDec {$$ = BuildTree("VarList",TypeNontoken,@$.first_line,1,$1);}
    ;
ParamDec : Specifier VarDec {$$ = BuildTree("ParamDec",TypeNontoken,@$.first_line,2,$1,$2);}
    ;

CompSt : LC DefList StmtList RC {struct TreeNode* nodeLC = CreateLeaf("LC", TypeToken, @1.first_line, Typenon);
                                struct TreeNode* nodeRC = CreateLeaf("RC", TypeToken, @4.first_line, Typenon);
                                $$ = BuildTree("CompSt",TypeNontoken,@$.first_line,4,nodeLC,$2,$3,nodeRC);}
    ;
StmtList : Stmt StmtList {$$ = BuildTree("StmtList",TypeNontoken,@$.first_line,2,$1,$2);}
    | {$$ = BuildTree("StmtList",TypeNontoken,@$.first_line,0,NULL);
        /*$$ = NULL;*/}
    ;
Stmt : Exp SEMI {struct TreeNode* nodeSEMI = CreateLeaf("SEMI", TypeToken, @2.first_line, Typenon);
                $$ = BuildTree("Stmt",TypeNontoken,@$.first_line,2,$1,nodeSEMI);}
    | error SEMI //{yyerror("Missing something");}
//    | Exp error {yyerror("Missing 'm'");}
    | CompSt {$$ = BuildTree("Stmt",TypeNontoken,@$.first_line,1,$1);}
    | RETURN Exp SEMI {struct TreeNode* nodeRETURN = CreateLeaf("RETURN", TypeToken, @1.first_line, Typenon);
                        struct TreeNode* nodeSEMI = CreateLeaf("SEMI", TypeToken, @3.first_line, Typenon);
                        $$ = BuildTree("Stmt",TypeNontoken,@$.first_line,3,nodeRETURN,$2,nodeSEMI);}
    | RETURN Exp error
    | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE {struct TreeNode* nodeIF = CreateLeaf("IF", TypeToken, @1.first_line, Typenon);
                            struct TreeNode* nodeLP = CreateLeaf("LP", TypeToken, @2.first_line, Typenon);
                            struct TreeNode* nodeRP = CreateLeaf("RP", TypeToken, @4.first_line, Typenon);
                            $$ = BuildTree("Stmt",TypeNontoken,@$.first_line,5,nodeIF,nodeLP,$3,nodeRP,$5);}
    | IF LP error RP Stmt %prec LOWER_THAN_ELSE
    | error Stmt {yyerrok;}
    | IF LP Exp RP Stmt ELSE Stmt {struct TreeNode* nodeIF = CreateLeaf("IF", TypeToken, @1.first_line, Typenon);
                            struct TreeNode* nodeLP = CreateLeaf("LP", TypeToken, @2.first_line, Typenon);
                            struct TreeNode* nodeRP = CreateLeaf("RP", TypeToken, @4.first_line, Typenon);
                            struct TreeNode* nodeELSE = CreateLeaf("ELSE", TypeToken, @6.first_line, Typenon);
                            $$ = BuildTree("Stmt",TypeNontoken,@$.first_line,7,nodeIF,nodeLP,$3,nodeRP,$5,nodeELSE,$7);}
    | IF LP error RP Stmt ELSE Stmt
    | WHILE LP Exp RP Stmt {struct TreeNode* nodeWHILE = CreateLeaf("WHILE", TypeToken, @1.first_line, Typenon);
                            struct TreeNode* nodeLP = CreateLeaf("LP", TypeToken, @2.first_line, Typenon);
                            struct TreeNode* nodeRP = CreateLeaf("RP", TypeToken, @4.first_line, Typenon);
                            $$ = BuildTree("Stmt",TypeNontoken,@$.first_line,5,nodeWHILE,nodeLP,$3,nodeRP,$5);}
    | WHILE LP error RP Stmt
    ;

DefList : Def DefList {$$ = BuildTree("DefList",TypeNontoken,@$.first_line,2,$1,$2);}
    | {$$ = BuildTree("DefList",TypeNontoken,@$.first_line,0,NULL);
        /*$$ = NULL;*/}
    ;
Def : Specifier DecList SEMI {struct TreeNode* nodeSEMI = CreateLeaf("SEMI", TypeToken, @3.first_line, Typenon);
                                $$ = BuildTree("Def",TypeNontoken,@$.first_line,3,$1,$2,nodeSEMI);}
    | Specifier error SEMI
    | Specifier DecList error SEMI
    ;
DecList : Dec {$$ = BuildTree("DecList",TypeNontoken,@$.first_line,1,$1);}
    | Dec COMMA DecList {struct TreeNode* nodeCOMMA = CreateLeaf("COMMA", TypeToken, @2.first_line, Typenon);
                        $$ = BuildTree("DecList",TypeNontoken,@$.first_line,3,$1,nodeCOMMA,$3);}
    ;
Dec : VarDec {$$ = BuildTree("Dec",TypeNontoken,@$.first_line,1,$1);}
    | VarDec ASSIGNOP Exp {struct TreeNode* nodeASSIGNOP = CreateLeaf("ASSIGNOP", TypeToken, @2.first_line, Typenon);
                            $$ = BuildTree("Dec",TypeNontoken,@$.first_line,3,$1,nodeASSIGNOP,$3);}
    ;

Exp : Exp ASSIGNOP Exp {struct TreeNode* nodeASSIGNOP = CreateLeaf("ASSIGNOP", TypeToken, @2.first_line, Typenon);
                        $$ = BuildTree("Exp",TypeNontoken,@$.first_line,3,$1,nodeASSIGNOP,$3);}
    | Exp ASSIGNOP error //{yyerror("missing1");}
    | Exp AND Exp {struct TreeNode* nodeAND = CreateLeaf("AND", TypeToken, @2.first_line, Typenon);
                    $$ = BuildTree("Exp",TypeNontoken,@$.first_line,3,$1,nodeAND,$3);}
    | Exp AND error //{yyerror("missing1");}
    | Exp OR Exp {struct TreeNode* nodeOR = CreateLeaf("OR", TypeToken, @2.first_line, Typenon);
                    $$ = BuildTree("Exp",TypeNontoken,@$.first_line,3,$1,nodeOR,$3);}
    | Exp OR error //{yyerror("missing1");}
    | Exp RELOP Exp {struct TreeNode* nodeRELOP = CreateLeaf("RELOP", TypeToken, @2.first_line, Typeid, $2);
                    $$ = BuildTree("Exp",TypeNontoken,@$.first_line,3,$1,nodeRELOP,$3);}
    | Exp RELOP error
    | Exp PLUS Exp {struct TreeNode* nodePLUS = CreateLeaf("PLUS", TypeToken, @2.first_line, Typenon);
                    $$ = BuildTree("Exp",TypeNontoken,@$.first_line,3,$1,nodePLUS,$3);}
    | Exp PLUS error
    | Exp MINUS Exp {struct TreeNode* nodeMINUS = CreateLeaf("MINUS", TypeToken, @2.first_line, Typenon);
                    $$ = BuildTree("Exp",TypeNontoken,@$.first_line,3,$1,nodeMINUS,$3);}
    | Exp MINUS error
    | Exp STAR Exp {struct TreeNode* nodeSTAR = CreateLeaf("STAR", TypeToken, @2.first_line, Typenon);
                    $$ = BuildTree("Exp",TypeNontoken,@$.first_line,3,$1,nodeSTAR,$3);}
    | Exp STAR error
    | Exp DIV Exp {struct TreeNode* nodeDIV = CreateLeaf("DIV", TypeToken, @2.first_line, Typenon);
                    $$ = BuildTree("Exp",TypeNontoken,@$.first_line,3,$1,nodeDIV,$3);}
    | Exp DIV error
    | LP Exp RP {struct TreeNode* nodeLP = CreateLeaf("LP", TypeToken, @1.first_line, Typenon);
                struct TreeNode* nodeRP = CreateLeaf("RP", TypeToken, @3.first_line, Typenon);
                $$ = BuildTree("Exp",TypeNontoken,@$.first_line,3,nodeLP,$2,nodeRP);}
    | LP error RP
    | MINUS Exp %prec NEGMINUS {struct TreeNode* nodeMINUS = CreateLeaf("MINUS", TypeToken, @1.first_line, Typenon);
                                $$ = BuildTree("Exp",TypeNontoken,@$.first_line,2,nodeMINUS,$2);}
    | MINUS error %prec NEGMINUS
    | NOT Exp {struct TreeNode* nodeNOT = CreateLeaf("NOT", TypeToken, @1.first_line, Typenon);
                $$ = BuildTree("Exp",TypeNontoken,@$.first_line,2,nodeNOT,$2);}
    | NOT error
    | ID LP Args RP {struct TreeNode* nodeID = CreateLeaf("ID", TypeToken, @1.first_line, Typeid ,$1);
                struct TreeNode* nodeLP = CreateLeaf("LP", TypeToken, @2.first_line, Typenon);
                struct TreeNode* nodeRP = CreateLeaf("RP", TypeToken, @4.first_line, Typenon);
                $$ = BuildTree("Exp",TypeNontoken,@$.first_line,4,nodeID,nodeLP,$3,nodeRP);}
    | ID LP error RP
    | ID LP RP {struct TreeNode* nodeID = CreateLeaf("ID", TypeToken, @1.first_line, Typeid ,$1);
                struct TreeNode* nodeLP = CreateLeaf("LP", TypeToken, @2.first_line, Typenon);
                struct TreeNode* nodeRP = CreateLeaf("RP", TypeToken, @3.first_line, Typenon);
                $$ = BuildTree("Exp",TypeNontoken,@$.first_line,3,nodeID,nodeLP,nodeRP);}
    | Exp LB Exp RB {struct TreeNode* nodeLB = CreateLeaf("LB", TypeToken, @2.first_line, Typenon);
                    struct TreeNode* nodeRB = CreateLeaf("RB", TypeToken, @4.first_line, Typenon);
                    $$ = BuildTree("Exp",TypeNontoken,@$.first_line,4,$1,nodeLB,$3,nodeRB);}
    | Exp LB error RB //{yyerror("missing1");}
 //   | Exp LB Exp error {yyerror("missing2");}
    | Exp DOT ID {struct TreeNode* nodeDOT = CreateLeaf("DOT", TypeToken, @2.first_line, Typenon);
                struct TreeNode* nodeID = CreateLeaf("ID", TypeToken, @3.first_line, Typeid ,$3);
                $$ = BuildTree("Exp",TypeNontoken,@$.first_line,3,$1,nodeDOT,nodeID);}
    | ID {struct TreeNode* nodeID = CreateLeaf("ID", TypeToken, @1.first_line, Typeid ,$1);
            //printf("id1 = %s\n",$1);
            $$ = BuildTree("Exp",TypeNontoken,@$.first_line,1,nodeID);}
    | INT {struct TreeNode* nodeINT = CreateLeaf("INT", TypeToken, @1.first_line, Typeint ,$1);
            $$ = BuildTree("Exp",TypeNontoken,@$.first_line,1,nodeINT);}
    | FLOAT {struct TreeNode* nodeFLOAT = CreateLeaf("FLOAT", TypeToken, @1.first_line, Typefloat ,$1);
            $$ = BuildTree("Exp",TypeNontoken,@$.first_line,1,nodeFLOAT);}
    ;
Args : Exp COMMA Args {struct TreeNode* nodeCOMMA = CreateLeaf("COMMA", TypeToken, @2.first_line, Typenon);
                        $$ = BuildTree("Args",TypeNontoken,@$.first_line,3,$1,nodeCOMMA,$3);}
    | Exp {$$ = BuildTree("Args",TypeNontoken,@$.first_line,1,$1);}
    ;

%%
#include "lex.yy.c"
yyerror(char* msg){
    flagoferror++;
    //fprintf(stderr, "Error type B at Line %d: %s\n", yylineno,msg);
    printf("Error type B at Line %d: %s\n",yylineno,msg);
}