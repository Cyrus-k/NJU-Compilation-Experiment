#ifndef __INTERCODE__
#define __INTERCODE__
#include <stdbool.h>
#include <stdio.h>
#include "semantic.h"

typedef struct InterCode_* InterCode;
typedef struct InterCodeList_* InterCodeList;
typedef struct Operand_* Operand;

InterCodeList head;
InterCodeList tail;

extern int temp_no;
extern int label_no;

enum OperandKind{VARIABLE, CONSTANT, TEMP, RFUNCTION, REF, DEREF, LABEL, VARRAY};

struct Operand_{
    enum OperandKind kind;//REF& DEREF*
    union{
        int var_id;
        int constant;
        struct{int temp;bool isaddr;Type type;int size;} temp_id;
        char* func;
        Operand addr;
        int label;
        struct{int array;bool isaddr;Type type;int size;} array_id;
    }u;
};

enum CodeKind{IC_LABEL,IC_FUNCTION,IC_ASSIGN,IC_ADD,IC_SUB,IC_MUL,IC_DIV,IC_GOTO,IC_IF_GOTO,IC_RETURN,IC_DEC,IC_ARG,IC_CALL,IC_PARAM,IC_READ,IC_WRITE};
enum RelopKind{EQ, NEQ, LT, GT, LE, GE };

struct InterCode_
{
    enum CodeKind codekind;
    union{
        struct{
            Operand op;
        }unaryop;//label,func,goto,return,arg,param,read,write
        struct{
            Operand right,left;
        }assign;//assign,call
        struct {
            Operand result,op1,op2;
        }binop;//add,sub,mul,div
        struct{
            Operand x,y,z;
            enum RelopKind kind;
        }ifgoto;//if_goto
        struct{
            Operand x;
            int size;
        }dec;//dec
    } u;
};

struct InterCodeList_{
    InterCode code;
    InterCodeList pre, next;
};

void init_list();
void add_node(InterCode node);
void delete_node(InterCodeList node);
void print_operand(Operand op,FILE* file);
void print_intercode(InterCode code,FILE* file);
void print_list(FILE* file);

Operand createOperand(enum OperandKind operandkind, int constant,char* func_name, char* name,Operand var_temp,bool isaddr);
InterCode createUnaryop(enum CodeKind kind,Operand op);
InterCode createAssign(enum CodeKind kind,Operand right,Operand left);
InterCode createBinop(enum CodeKind kind,Operand res,Operand op1,Operand op2);
InterCode createIfgoto(enum CodeKind kind,Operand x,Operand y,Operand z,enum RelopKind relopkind);
InterCode createDec(enum CodeKind kind,Operand x, int size);

#endif