#ifndef __Semantic__
#define __Semantic__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "Hashtable.h"
#include "tree.h"

void insert_read_write();
void SemanticError(int num, int line, char* mg);
bool StructhasName(FieldList field, char* name);
bool EqualType(Type type1,Type type2);
FieldList FindStructMember(FieldList field,char* name);

void UnitProgram(struct TreeNode* Node); //Program : ExtDefList
void UnitExtDefList(struct TreeNode* Node); //ExtDefList : ExtDef ExtDefList
void UnitExtDef(struct TreeNode* Node); //Specifier ExtDecList SEMI | Specifier SEMI | Specifier FunDec CompSt
void UnitExtDecList(struct TreeNode* Node,Type type);
Type UnitSpecifier(struct TreeNode* Node);
Type UnitStructSpecifier(struct TreeNode* Node);
char* UnitOptTag(struct TreeNode* Node, char* name);
char* UnitTag(struct TreeNode* Node);
char* UnitVarDec(struct TreeNode* Node,Type type, FieldList field);
void UnitFunDec(struct TreeNode* Node,Type type);
void UnitVarList(struct TreeNode* Node,FieldList field);
void UnitParamDec(struct TreeNode* Node,FieldList field);


void UnitCompSt(struct TreeNode* Node,Type type);
void UnitStmtList(struct TreeNode* Node,Type type);
void UnitStmt(struct TreeNode* Node,Type type);

void UnitDefList(struct TreeNode* Node, FieldList field);
void UnitDef(struct TreeNode* Node, FieldList field);
void UnitDecList(struct TreeNode* Node,Type type, FieldList field);
void UnitDec(struct TreeNode* Node,Type type,FieldList field);

Type UnitExp(struct TreeNode* Node);
void UnitArgs(struct TreeNode* Node, FieldList field,int num);

#endif