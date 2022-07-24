#include <stdio.h>
#include "syntax.tab.h"
#include "semantic.h"
#include "Translate.h"
#include "tree.h"
#include "Optimize.h"
#include "MIPSCode.h"

extern FILE* yyin;
extern int yylex();
extern int yyparse();
extern void yyrestart(FILE *input_file);
extern void PrintTree(struct TreeNode* node,int space);
extern struct  TreeNode* root;
int flagoferror = 0;

int main(int argc,char* argv[])
{
    /*if (argc>1){
        if(!(yyin = fopen(argv[1],"r") )){
            perror(argv[1]);
            return 1;
        }
    }
    while (yylex()!=0)
        ;

    */
    if (argc <= 2) return 1;
    FILE* f = fopen(argv[1], "r");
    if (!f)
    {
        perror(argv[1]);
        return 1;
    }
    yyrestart(f);
    yyparse();
    if(flagoferror == 0){
        //PrintTree(root,0);
        UnitProgram(root);
        TranslateProgram(root);
        FILE* ff = fopen(argv[2], "w");
        if (!ff) {
            perror(argv[2]);
            return 1;
        }
        //Optimize();
        //print_list(ff);
        MIPSTranslate(ff);
        fclose(ff);
    }
    fclose(f);
    return 0;  
}