#include "tree.h"

struct TreeNode* BuildTree(char* nodeName, enum NodeType nodeType, int lineNum,int childNum,...){
    struct TreeNode* newnode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if(flagoferror == 0){
    newnode->Name = nodeName;
    newnode->nodetype = nodeType;
    newnode->Numofline = lineNum;
    newnode->Numofchild = childNum;
    newnode->Child = NULL;
    newnode->Sibling = NULL;

    va_list valist;
    va_start(valist, childNum);
    struct TreeNode* firstChild = NULL;
    struct TreeNode* lastSibiling = NULL;
    int j = 0;
    for (int i = 0; i < childNum; i++) {
        struct TreeNode* curnode = va_arg(valist, struct TreeNode*);
        if(curnode!= NULL)
        {
            firstChild = curnode;
            lastSibiling = firstChild;
            j = i + 1;
            break;
        }
    }
    
    for(; j < childNum;j++){
        //printf("j=%d, %d\n",j,childNum);
        lastSibiling->Sibling = va_arg(valist, struct TreeNode*);
        if(lastSibiling->Sibling != NULL) 
            lastSibiling = lastSibiling->Sibling;
    }
    va_end(valist);
    newnode->Child = firstChild;
    }
    return newnode;
}

struct TreeNode* CreateLeaf(char* nodeName, enum NodeType nodeType, int lineNum, enum TokenType tokentype, ...)
{
    struct TreeNode* newnode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newnode->Name = nodeName;
    newnode->nodetype = nodeType;
    newnode->Numofline = lineNum;
    newnode->Child = NULL;
    newnode->Sibling = NULL;
    newnode->tokentype = tokentype;
    newnode->Numofchild = -1;
    switch(newnode->tokentype){
        case Typeint:
        {
            va_list valist;
            va_start(valist,tokentype);
            newnode->data.Intval = va_arg(valist, int);
            va_end(valist);
            break;
        }
        case Typefloat:
        {
            va_list valist;
            va_start(valist,tokentype);
            newnode->data.Floatval = va_arg(valist, double);
            va_end(valist);
            break;
        }
        case Typeid:
        {
            va_list valist;
            va_start(valist,tokentype);
            newnode->data.Charval = va_arg(valist, char*);
            //printf("%s\n",newnode->data.Charval);
            va_end(valist);
            break;
        }
        case Typenon:
            break;
        default: break;
    }

    return newnode;
}

void PrintTree(struct TreeNode* Node,int Space)
{
    if (Node == NULL)
        return;
    //printf("%s\n",Node->Name);
    //printf("good\n");
    if(Node->Numofchild == 0){
        //printf("%s\n",Node->Name);
        PrintTree(Node->Sibling,Space);
        return;
    }
    for(int i = 0;i < Space;i++){
        printf(" ");
    }
    printf("%s",Node->Name);
    switch(Node->nodetype){
        case TypeToken:{
            switch(Node->tokentype){
                case Typeint:
                    printf(": %d\n",Node->data.Intval);
                    break;
                case Typefloat:
                    printf(": %f\n",Node->data.Floatval);
                    break;
                case Typeid:
                    printf(": %s\n",Node->data.Charval);
                    //printf("\n");
                    break;
                case Typenon:
                    printf("\n");
                    break;
                default: break;
            }
            break;
        }
        case TypeNontoken:{
            printf(" (%d)\n",Node->Numofline);
            break;
        }
        default: break;
    }
    int newSpace = Space + 2;
    PrintTree(Node->Child,newSpace);
    PrintTree(Node->Sibling,Space);
}