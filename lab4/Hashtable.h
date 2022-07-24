#ifndef __Hashtable__
#define __Hashtable__

#define HASH_SIZE 0x3fff

#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include<string.h>
#include<stdarg.h>

typedef struct Type_* Type;
typedef struct FieldList_* FieldList;
typedef struct FuncList_* FuncList;
typedef struct HashNode_* HashNode;
HashNode Hashtable[HASH_SIZE+1];

struct Type_
{
    enum { BASIC, ARRAY, STRUCTURE, FUNCTION } kind;
    union
    {
    int basic;// 基本类型 0:int 1:float
    struct { Type elem; int size; } array;// 数组类型信息包括元素类型与数组大小构成
    FieldList structure;// 结构体类型信息是一个链表
    FuncList function;//函数类型是一个结构体
    } u;
};

struct FieldList_
{
    char* name; // 域的名字
    Type type; // 域的类型
    FieldList tail; // 下一个域
    bool isarg;// is func arg
    int id;//var id
};

struct FuncList_
{
    int numofparam;
    Type ret;
    FieldList next;
};

struct HashNode_ {
    FieldList data;
    HashNode next;
};

void initHashtable();
unsigned int hash_pjw(char* name);
void insertHashtable(FieldList symbol);
FieldList findHashtable(char* name);

#endif
