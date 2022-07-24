#include <stdio.h>
#include <stdlib.h>
#include "InterCode.h"

int temp_no = 0;
int label_no = 0;

void init_list(){
    InterCodeList node = (InterCodeList)malloc(sizeof(struct InterCodeList_));
    node->code = NULL;
    node->pre = NULL;
    node->next = NULL;
    head = node;
    tail = node;
}

void add_node(InterCode node){
    if(node == NULL) return;
    InterCodeList temp = (InterCodeList)malloc(sizeof(struct InterCodeList_));
    temp->code = node;
    temp->next = NULL;
    tail->next = temp;
    temp->pre = tail;
    tail = temp;
}

void delete_node(InterCodeList node){
    if(node->next == NULL){
        InterCodeList pre = node->pre;
        pre->next = NULL;
        free(node->code);
        free(node);
    }
    else{
        node->pre->next = node->next;
        node->next->pre = node->pre;
        free(node->code);
        free(node);
    }
}

void print_operand(Operand op,FILE* file){
    switch (op->kind)
    {
    case VARIABLE:
        fprintf(file, "v%d",op->u.var_id);
        break;
    case CONSTANT:
        fprintf(file, "#%d",op->u.constant);
        break;
    case TEMP:
        fprintf(file, "t%d",op->u.temp_id.temp);
        break;
    case RFUNCTION:
        fprintf(file, "%s",op->u.func);
        break;
    case REF:
        fprintf(file, "&");
        print_operand(op->u.addr,file);
        break;
    case DEREF:
        fprintf(file, "*");
        print_operand(op->u.addr,file);
        break;
    case LABEL:
        fprintf(file, "label%d",op->u.label);
        break;
    case VARRAY:
        fprintf(file, "v%d",op->u.array_id.array);
        break;
    default:
        break;
    }
}

void print_intercode(InterCode code,FILE* file){
    switch (code->codekind)
    {
    case IC_LABEL:
        fprintf(file, "LABEL ");
        print_operand(code->u.unaryop.op,file);
        fprintf(file, " :\n");
        break;
    case IC_FUNCTION:
        fprintf(file, "FUNCTION ");
        print_operand(code->u.unaryop.op,file);
        fprintf(file, " :\n");
        break;
    case IC_ASSIGN:
        print_operand(code->u.assign.left,file);
        fprintf(file, " := ");
        print_operand(code->u.assign.right,file);
        fprintf(file, "\n");
        break;
    case IC_ADD:
        print_operand(code->u.binop.result,file);
        fprintf(file, " := ");
        print_operand(code->u.binop.op1,file);
        fprintf(file, " + ");
        print_operand(code->u.binop.op2,file);
        fprintf(file, "\n");
        break;
    case IC_SUB:
        print_operand(code->u.binop.result,file);
        fprintf(file, " := ");
        print_operand(code->u.binop.op1,file);
        fprintf(file, " - ");
        print_operand(code->u.binop.op2,file);
        fprintf(file, "\n");
        break;
    case IC_MUL:
        print_operand(code->u.binop.result,file);
        fprintf(file, " := ");
        print_operand(code->u.binop.op1,file);
        fprintf(file, " * ");
        print_operand(code->u.binop.op2,file);
        fprintf(file, "\n");
        break;
    case IC_DIV:
        print_operand(code->u.binop.result,file);
        fprintf(file, " := ");
        print_operand(code->u.binop.op1,file);
        fprintf(file, " / ");
        print_operand(code->u.binop.op2,file);
        fprintf(file, "\n");
        break;
    case IC_GOTO:
        fprintf(file, "GOTO ");
        print_operand(code->u.unaryop.op,file);
        fprintf(file, "\n");
        break;
    case IC_IF_GOTO:
        fprintf(file, "IF ");
        print_operand(code->u.ifgoto.x,file);
        switch (code->u.ifgoto.kind)
        {
        case EQ:
            fprintf(file, " == ");
            break;
        case NEQ:
            fprintf(file, " != ");
            break;
        case LT:
            fprintf(file, " < ");
            break;
        case GT:
            fprintf(file, " > ");
            break;
        case LE:
            fprintf(file, " <= ");
            break;
        case GE:
            fprintf(file, " >= ");
            break;
        default:
            break;
        }
        print_operand(code->u.ifgoto.y,file);
        fprintf(file, " GOTO ");
        print_operand(code->u.ifgoto.z,file);
        fprintf(file, "\n");
        break;
    case IC_RETURN:
        fprintf(file, "RETURN ");
        print_operand(code->u.unaryop.op,file);
        fprintf(file, "\n");
        break;
    case IC_DEC:
        fprintf(file, "DEC ");
        print_operand(code->u.dec.x,file);
        fprintf(file, " %d\n",code->u.dec.size);
        break;
    case IC_ARG:
        fprintf(file, "ARG ");
        print_operand(code->u.unaryop.op,file);
        fprintf(file, "\n");
        break;
    case IC_CALL:
        print_operand(code->u.assign.left,file);
        fprintf(file, " := CALL ");
        print_operand(code->u.assign.right,file);
        fprintf(file, "\n");
        break;
    case IC_PARAM:
        fprintf(file, "PARAM ");
        print_operand(code->u.unaryop.op,file);
        fprintf(file, "\n");
        break;
    case IC_READ:
        fprintf(file, "READ ");
        print_operand(code->u.unaryop.op,file);
        fprintf(file, "\n");
        break;
    case IC_WRITE:
        fprintf(file, "WRITE ");
        print_operand(code->u.unaryop.op,file);
        fprintf(file, "\n");
        break;
    default:
        break;
    }
}

void print_list(FILE* file){
    InterCodeList temp = head;
    while(temp->next != NULL){
        print_intercode(temp->next->code,file);
        temp = temp->next;
    }
}

Operand createOperand(enum OperandKind operandkind, int constant,char* func_name,char* name,Operand var_temp,bool isaddr){
    Operand node = (Operand)malloc(sizeof(struct Operand_));
    node->kind = operandkind;
    switch (operandkind)
    {
    case VARIABLE:
    {
        FieldList tempnode = findHashtable(name);
        if(tempnode != NULL)
            node->u.var_id = tempnode->id;
        break;
    }
    case CONSTANT:
        node->u.constant = constant;
        break;
    case TEMP:
        temp_no++;
        node->u.temp_id.temp = temp_no;
        node->u.temp_id.isaddr = isaddr;
        break;
    case RFUNCTION:
        node->u.func = func_name;
        break;
    case REF:
        node->u.addr = var_temp;
        break;
    case DEREF:
        node->u.addr = var_temp;
        break;
    case LABEL:
        label_no++;
        node->u.label = label_no;
        break;
    case VARRAY:
    {
        FieldList tempnode = findHashtable(name);
        node->u.array_id.array = tempnode->id;
        node->u.array_id.isaddr = isaddr;
        break;
    }
    default:
        break;
    }
    return node;
}

InterCode createUnaryop(enum CodeKind kind,Operand op){
    InterCode code = (InterCode)malloc(sizeof(struct InterCode_));
    code->codekind = kind;
    code->u.unaryop.op = op;
    return code;
}

InterCode createAssign(enum CodeKind kind,Operand right,Operand left){
    InterCode code = (InterCode)malloc(sizeof(struct InterCode_));
    code->codekind = kind;
    code->u.assign.right = right;
    code->u.assign.left = left;
    return code;
}

InterCode createBinop(enum CodeKind kind,Operand res,Operand op1,Operand op2){
    InterCode code = (InterCode)malloc(sizeof(struct InterCode_));
    code->codekind = kind;
    code->u.binop.result = res;
    code->u.binop.op1 = op1;
    code->u.binop.op2 = op2;
    return code;
}

InterCode createIfgoto(enum CodeKind kind,Operand x,Operand y,Operand z,enum RelopKind relopkind){
    InterCode code = (InterCode)malloc(sizeof(struct InterCode_));
    code->codekind = kind;
    code->u.ifgoto.x = x;
    code->u.ifgoto.y = y;
    code->u.ifgoto.z = z;
    code->u.ifgoto.kind = relopkind;
    return code;
}

InterCode createDec(enum CodeKind kind,Operand x, int size){
    InterCode code = (InterCode)malloc(sizeof(struct InterCode_));
    code->codekind = kind;
    code->u.dec.x = x;
    code->u.dec.size = size;
    return code;
}