#ifndef __Tree__
#define __Tree__

#include<stdarg.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

extern int flagoferror;

enum NodeType{TypeToken,TypeNontoken};
enum TokenType{Typeint,Typefloat,Typeid,Typenon};
struct TreeNode{
    char* Name;
    int Numofline;
    int Numofchild;
    enum NodeType nodetype;
    enum TokenType tokentype;
    union{
        int Intval;
        float Floatval;
        char* Charval;
    }data;
    struct TreeNode* Child;
    struct TreeNode* Sibling;
};

struct TreeNode* BuildTree(char* nodeName, enum NodeType nodeType, int lineNum, int childNum ,...);
struct TreeNode* CreateLeaf(char* nodeName, enum NodeType nodeType,int lineNum, enum TokenType tokentype, ...);
void PrintTree(struct TreeNode* Node, int Space);

#endif