#ifndef __MIPSCode__
#define __MIPSCode__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "InterCode.h"

#define RegisterNum 32
#define BUSY 1
#define VACANT 2

int* all_offset;
typedef struct Var_* Var;
typedef struct Register_* Register;
typedef struct Varlist_* Varlist;

struct Var_
{
    Operand op;
    int offset;
    int reg_no;
};

struct Register_
{
    char name[5];
    int state;
    Var var;
};

struct Varlist_
{
    Var variable;
    Varlist next;
};

Varlist func_varlist;
struct Register_ reg[RegisterNum];

void MIPSTranslate(FILE* file);
void get_func_block();
void init_func_varlist();
void create_varlist();
void create_func_varlist(InterCode code);
void insert_var(Operand op,bool isparam,int size);
Var find_var(Operand op);
void insert_varlist(Var var);
void init_register();
void MIPS_print_list(FILE* file);
void MIPS_print_intercode(InterCode code,FILE* file);
void MIPS_prepare(FILE* file);

int GetFreeReg();
void StoreMemory(int reg_no,FILE* file);
void FreeReg(int reg_no);
int MIPSOperand(Operand op ,FILE* file);
void MIPSLabel(InterCode code,FILE* file);
void MIPSFunction(InterCode code,FILE* file);
void MIPSAssign(InterCode code,FILE* file);
void MIPSAdd(InterCode code,FILE* file);
void MIPSSub(InterCode code,FILE* file);
void MIPSMul(InterCode code,FILE* file);
void MIPSDiv(InterCode code,FILE* file);
void MIPSGoto(InterCode code,FILE* file);
void MIPSIfgoto(InterCode code,FILE* file);
void MIPSReturn(InterCode code,FILE* file);

void MIPSArg(InterCode code,FILE* file);
void MIPSCall(InterCode code,FILE* file);
void MIPSRead(InterCode code,FILE* file);
void MIPSWrite(InterCode code,FILE* file);

#endif
