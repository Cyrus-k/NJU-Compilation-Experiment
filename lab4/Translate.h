#ifndef __TRANSLATE__
#define __TRANSLATE__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "tree.h"
#include "InterCode.h"
#include "Hashtable.h"

#define Pair_size 100

typedef struct ArrayPair_* ArrayPair;
int pointer;

struct ArrayPair_
{
    Operand need_to_replace;
    Operand replace;
};

ArrayPair arraypair[Pair_size];

int GetArraySize(FieldList field);
int get_size(Type type);
void initArrayPair();
//no need to translate struct
void TranslateProgram(struct TreeNode* Node);
void TranslateExtDefList(struct TreeNode* Node); 
void TranslateExtDef(struct TreeNode* Node); 
void TranslateFunDec(struct TreeNode* Node); 

void TranslateCompSt(struct TreeNode* Node); 
void TranslateStmtList(struct TreeNode* Node);
void TranslateStmt(struct TreeNode* Node);
void TranslateCondExp(struct TreeNode* Node, Operand Truelabel, Operand Falselabel);

void TranslateDefList(struct TreeNode* Node);
void TranslateDef(struct TreeNode* Node);
void TranslateDecList(struct TreeNode* Node);
void TranslateDec(struct TreeNode* Node);

Operand TranslateExp(struct TreeNode* Node);
Operand TranslateVarDec(struct TreeNode* Node);
Operand ArrayCopy(Operand left,Operand right);
Operand TranslateArgs(struct TreeNode* Node,bool iswrite);

#endif