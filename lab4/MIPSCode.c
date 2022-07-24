#include "MIPSCode.h"

int func_num = 0;
int temp_func = 0;
int arg_num = 0;
int param_num = 0;

void get_func_block(){
    InterCodeList temp = head;
    while(temp->next != NULL){
        if(temp->next->code->codekind == IC_FUNCTION)
            func_num++;
        temp = temp->next;
    }
    //printf("%d\n",func_num);
}

void init_func_varlist(){
    func_varlist = (Varlist) malloc (func_num*sizeof(struct Varlist_));
    all_offset = (int*) malloc(func_num*sizeof(int));
    for(int i=0;i<func_num;i++){
        func_varlist[i].next = NULL;
        func_varlist[i].variable = NULL;
        all_offset[i] = 0;
    }
}

void create_func_varlist(InterCode code){
    switch (code->codekind)
    {
    case IC_LABEL:
        break;
    case IC_FUNCTION:
    {
        param_num = 0;
        break;
    }
    case IC_ASSIGN:
        insert_var(code->u.assign.left,false,0);
        insert_var(code->u.assign.right,false,0);
        break;
    case IC_ADD:
        insert_var(code->u.binop.result,false,0);
        insert_var(code->u.binop.op1,false,0);
        insert_var(code->u.binop.op2,false,0);
        break;
    case IC_SUB:
        insert_var(code->u.binop.result,false,0);
        insert_var(code->u.binop.op1,false,0);
        insert_var(code->u.binop.op2,false,0);
        break;
    case IC_MUL:
        insert_var(code->u.binop.result,false,0);
        insert_var(code->u.binop.op1,false,0);
        insert_var(code->u.binop.op2,false,0);
        break;
    case IC_DIV:
        insert_var(code->u.binop.result,false,0);
        insert_var(code->u.binop.op1,false,0);
        insert_var(code->u.binop.op2,false,0);
        break;
    case IC_GOTO:
        break;
    case IC_IF_GOTO:
        insert_var(code->u.ifgoto.x,false,0);
        insert_var(code->u.ifgoto.y,false,0);
        break;
    case IC_RETURN:
        insert_var(code->u.unaryop.op,false,0);
        break;
    case IC_DEC:
        insert_var(code->u.dec.x,false,code->u.dec.size);
        break;
    case IC_ARG:
        insert_var(code->u.unaryop.op,false,0);
        break;
    case IC_CALL:
        insert_var(code->u.assign.left,false,0);
        break;
    case IC_PARAM:
        insert_var(code->u.unaryop.op,true,0);
        break;
    case IC_READ:
        insert_var(code->u.unaryop.op,false,0);
        break;
    case IC_WRITE:
        insert_var(code->u.unaryop.op,false,0);
        break;
    default:
        break;
    }
}

void insert_var(Operand op,bool isparam,int size){
    if(isparam == true){
        Var var = (Var)malloc(sizeof(struct Var_));
        var->offset = 8 + 4*param_num;
        var->op = op;
        var->reg_no = -1;
        insert_varlist(var);
        param_num++;
    }
    else{
        if(op->kind != CONSTANT ){
            if(op->kind == DEREF || op->kind == REF){
                if(find_var(op->u.addr) == NULL){
                    all_offset[temp_func-1] = all_offset[temp_func-1] - 4;
                    if(size != 0)
                        all_offset[temp_func-1] = all_offset[temp_func-1] - size + 4;
                    Var var = (Var)malloc(sizeof(struct Var_));
                    var->offset = all_offset[temp_func-1];
                    var->op = op->u.addr;
                    var->reg_no = -1;
                    insert_varlist(var);
                }
            }
            else{
                if(find_var(op) == NULL){
                    all_offset[temp_func-1] = all_offset[temp_func-1] - 4;
                    if(size != 0)
                        all_offset[temp_func-1] = all_offset[temp_func-1] - size + 4;
                    Var var = (Var)malloc(sizeof(struct Var_));
                    var->offset = all_offset[temp_func-1];
                    var->op = op;
                    var->reg_no = -1;
                    insert_varlist(var);
                }
            }
        }
    }
}

Var find_var(Operand op){
    if(func_varlist[temp_func-1].variable == NULL)
        return NULL;
    else if(func_varlist[temp_func-1].variable != NULL){
        if(func_varlist[temp_func-1].variable->op->kind == op->kind){
            switch (op->kind)
            {
            case VARIABLE:
                if(op->u.var_id == func_varlist[temp_func-1].variable->op->u.var_id) return func_varlist[temp_func-1].variable;
                break;
            case CONSTANT:
                break;
            case TEMP:
                if(op->u.temp_id.temp == func_varlist[temp_func-1].variable->op->u.temp_id.temp) return func_varlist[temp_func-1].variable;
                break;
            case RFUNCTION:
                break;
            case REF:
            {
                if(op->u.addr->kind == func_varlist[temp_func-1].variable->op->u.addr->kind){
                    if(op->u.addr->kind == VARIABLE){
                        if(op->u.addr->u.var_id == func_varlist[temp_func-1].variable->op->u.addr->u.var_id) return func_varlist[temp_func-1].variable;
                    }
                    else if(op->u.addr->kind == TEMP){
                        if(op->u.addr->u.temp_id.temp == func_varlist[temp_func-1].variable->op->u.addr->u.temp_id.temp) return func_varlist[temp_func-1].variable;
                    }
                    else if(op->u.addr->kind == VARRAY){
                        if(op->u.addr->u.array_id.array == func_varlist[temp_func-1].variable->op->u.addr->u.array_id.array) return func_varlist[temp_func-1].variable;
                    }
                }
                break;
            }
            case DEREF:
                if(op->u.addr->kind == func_varlist[temp_func-1].variable->op->u.addr->kind){
                    if(op->u.addr->kind == VARIABLE){
                        if(op->u.addr->u.var_id == func_varlist[temp_func-1].variable->op->u.addr->u.var_id) return func_varlist[temp_func-1].variable;
                    }
                    else if(op->u.addr->kind == TEMP){
                        if(op->u.addr->u.temp_id.temp == func_varlist[temp_func-1].variable->op->u.addr->u.temp_id.temp) return func_varlist[temp_func-1].variable;
                    }
                    else if(op->u.addr->kind == VARRAY){
                        if(op->u.addr->u.array_id.array == func_varlist[temp_func-1].variable->op->u.addr->u.array_id.array) return func_varlist[temp_func-1].variable;
                    }
                }
                break;
            case LABEL:
                break;
            case VARRAY:
                if(op->u.array_id.array == func_varlist[temp_func-1].variable->op->u.array_id.array) return func_varlist[temp_func-1].variable;
                break;
            default:
                break;
            }
        }
        Varlist temp = func_varlist[temp_func-1].next;
        while(temp != NULL){
            if(temp->variable->op->kind == op->kind){
                switch (op->kind)
                {
                case VARIABLE:
                    if(op->u.var_id == temp->variable->op->u.var_id) return temp->variable;
                    break;
                case CONSTANT:
                    break;
                case TEMP:
                    if(op->u.temp_id.temp == temp->variable->op->u.temp_id.temp) return temp->variable;
                    break;
                case RFUNCTION:
                    break;
                case REF:
                {
                    if(op->u.addr->kind == temp->variable->op->u.addr->kind){
                        if(op->u.addr->kind == VARIABLE){
                            if(op->u.addr->u.var_id == temp->variable->op->u.addr->u.var_id) return temp->variable;
                        }
                        else if(op->u.addr->kind == TEMP){
                            if(op->u.addr->u.temp_id.temp == temp->variable->op->u.addr->u.temp_id.temp) return temp->variable;
                        }
                        else if(op->u.addr->kind == VARRAY){
                            if(op->u.addr->u.array_id.array == temp->variable->op->u.addr->u.array_id.array) return temp->variable;
                        }
                    }
                    break;
                }
                case DEREF:
                {
                    if(op->u.addr->kind == temp->variable->op->u.addr->kind){
                        if(op->u.addr->kind == VARIABLE){
                            if(op->u.addr->u.var_id == temp->variable->op->u.addr->u.var_id) return temp->variable;
                        }
                        else if(op->u.addr->kind == TEMP){
                            if(op->u.addr->u.temp_id.temp == temp->variable->op->u.addr->u.temp_id.temp) return temp->variable;
                        }
                        else if(op->u.addr->kind == VARRAY){
                            if(op->u.addr->u.array_id.array == temp->variable->op->u.addr->u.array_id.array) return temp->variable;
                        }
                    }
                    break;
                }
                case LABEL:
                    break;
                case VARRAY:
                    if(op->u.array_id.array == temp->variable->op->u.array_id.array) return temp->variable;
                    break;
                default:
                    break;
                }
            }
            temp = temp->next;
        }
    }
    return NULL;
}

void insert_varlist(Var var){
    if(func_varlist[temp_func-1].variable == NULL){
        func_varlist[temp_func-1].variable = var;
    }
    else{
        Varlist temp = (Varlist)malloc(sizeof(struct Varlist_));
        Varlist cur = func_varlist[temp_func-1].next;
        Varlist pre = cur;
        while(cur != NULL){
            pre = cur;
            cur = cur->next;
        }
        if(pre == NULL)
        {
            temp->next = NULL;
            temp->variable = var;
            func_varlist[temp_func-1].next = temp;
        }
        else{
            temp->next = NULL;
            temp->variable = var;
            pre->next = temp;
        }
    }
}

void create_varlist(){
    InterCodeList temp = head;
    while(temp->next != NULL){
        if(temp->next->code->codekind == IC_FUNCTION){
            temp_func++;
        }
        create_func_varlist(temp->next->code);
        temp = temp->next;
    }
    assert(temp_func == func_num);
    temp_func = 0;
}

void init_register()
{
    for(int i=0;i<RegisterNum;i++){
        reg[i].state = VACANT;
    }
    for(int i=0;i<RegisterNum;i++){
        if(i == 0){
            char name[] = "zero";
            strcpy(reg[i].name,name);
        }
        else if(i == 1){
            char name[] = "at";
            strcpy(reg[i].name,name);
        }
        else if(i > 1 && i <= 3){
            char name[] = "v";
            char str[2] = {0};
            sprintf(str,"%d",i-2);
            strcat(name,str);
            strcpy(reg[i].name,name);
        }
        else if(i > 3 && i <= 7){
            char name[] = "a";
            char str[2] = {0};
            sprintf(str,"%d",i-4);
            strcat(name,str);
            strcpy(reg[i].name,name);
        }
        else if(i > 7 && i <= 15){
            char name[] = "t";
            char str[2] = {0};
            sprintf(str,"%d",i-8);
            strcat(name,str);
            strcpy(reg[i].name,name);
        }
        else if(i > 15 && i <= 23){
            char name[] = "s";
            char str[2] = {0};
            sprintf(str,"%d",i-16);
            strcat(name,str);
            strcpy(reg[i].name,name);
        }
        else if(i > 23 && i <= 25){
            char name[] = "t";
            char str[2] = {0};
            sprintf(str,"%d",i-16);
            strcat(name,str);
            strcpy(reg[i].name,name);
        }
        else if(i > 25 && i <= 27){
            char name[] = "k";
            char str[2] = {0};
            sprintf(str,"%d",i-26);
            strcat(name,str);
            strcpy(reg[i].name,name);
        }
        else if(i == 28){
            char name[] = "gp";
            strcpy(reg[i].name,name);
        }
        else if(i == 29){
            char name[] = "sp";
            strcpy(reg[i].name,name);
        }
        else if(i == 30){
            char name[] = "fp";
            strcpy(reg[i].name,name);
        }
        else if(i == 31){
            char name[] = "ra";
            strcpy(reg[i].name,name);
        }
    }
}

void MIPSTranslate(FILE* file){
    get_func_block();
    init_func_varlist();
    init_register();
    create_varlist();
    MIPS_prepare(file);
    MIPS_print_list(file);
}

void MIPS_prepare(FILE* file){
    fprintf(file, ".data\n");
    fprintf(file, "_prompt: .asciiz \"Enter an integer:\"\n");
    fprintf(file, "_ret: .asciiz \"\\n\"\n");
    fprintf(file, ".globl main\n");
    fprintf(file, ".text\n");
    fprintf(file, "read:\n");
    fprintf(file, "  li $v0, 4\n");
    fprintf(file, "  la $a0, _prompt\n");
    fprintf(file, "  syscall\n");
    fprintf(file, "  li $v0, 5\n");
    fprintf(file, "  syscall\n");
    fprintf(file, "  jr $ra\n");
    fprintf(file, "write:\n");
    fprintf(file, "  li $v0, 1\n");
    fprintf(file, "  syscall\n");
    fprintf(file, "  li $v0, 4\n");
    fprintf(file, "  la $a0, _ret\n");
    fprintf(file, "  syscall\n");
    fprintf(file, "  move $v0, $0\n");
    fprintf(file, "  jr $ra\n");
    fprintf(file, "  \n");
}

void MIPS_print_list(FILE* file){
    InterCodeList temp = head;
    while(temp->next != NULL){
        MIPS_print_intercode(temp->next->code,file);
        temp = temp->next;
    }
}

void MIPS_print_intercode(InterCode code,FILE* file){
    switch (code->codekind)
    {
    case IC_LABEL:
        MIPSLabel(code,file);
        //printf("label\n");
        break;
    case IC_FUNCTION:
    {
        temp_func++;
        MIPSFunction(code,file);
        break;
    }
    case IC_ASSIGN:
        MIPSAssign(code,file);
        //printf("assign\n");
        break;
    case IC_ADD:
        MIPSAdd(code,file);
        //printf("ADD\n");
        break;
    case IC_SUB:
        MIPSSub(code,file);
        break;
    case IC_MUL:
        MIPSMul(code,file);
        //printf("MUL\n");
        break;
    case IC_DIV:
        MIPSDiv(code,file);
        break;
    case IC_GOTO:
        MIPSGoto(code,file);
        break;
    case IC_IF_GOTO:
        MIPSIfgoto(code,file);
        break;
    case IC_RETURN:
        MIPSReturn(code,file);
        break;
    case IC_DEC:
        break;
    case IC_ARG:
        MIPSArg(code,file);
        break;
    case IC_CALL:
        MIPSCall(code,file);
        break;
    case IC_PARAM:
        break;
    case IC_READ:
        MIPSRead(code,file);
        //printf("read\n");
        break;
    case IC_WRITE:
        MIPSWrite(code,file);
        //printf("write\n");
        break;
    default:
        break;
    }
}

int GetFreeReg(){
    for(int i = 8;i <= 15;i++)
    {
        if(reg[i].state == VACANT)
            return i;
    }
}

void StoreMemory(int reg_no, FILE* file){
    if(reg[reg_no].var != NULL)
        fprintf(file, "  sw $%s, %d($fp)\n", reg[reg_no].name, reg[reg_no].var->offset);
}

void FreeReg(int reg_no){
    reg[reg_no].state = VACANT;
    reg[reg_no].var = NULL;
}

int MIPSOperand(Operand op ,FILE* file){
    switch (op->kind)
    {
    case VARIABLE:
    {
        int reg_no = GetFreeReg();
        reg[reg_no].state = BUSY;
        Var var = find_var(op);
        var->reg_no = reg_no;
        reg[reg_no].var = var;
        fprintf(file,"  lw $%s, %d($fp)\n", reg[reg_no].name, var->offset);
        return reg_no;
        break;
    }
    case CONSTANT:
    {
        int reg_no = GetFreeReg();
        reg[reg_no].state = BUSY;
        fprintf(file, "  li $%s, %d\n", reg[reg_no].name, op->u.constant);
        return reg_no;
        break;
    }
    case TEMP:
    {
        int reg_no = GetFreeReg();
        reg[reg_no].state = BUSY;
        Var var = find_var(op);
        var->reg_no = reg_no;
        reg[reg_no].var = var;
        fprintf(file,"  lw $%s, %d($fp)\n", reg[reg_no].name, var->offset);
        return reg_no;
        break;
    }
    case RFUNCTION:
        break;
    case REF:
    {
        int reg_no = GetFreeReg();
        reg[reg_no].state = BUSY;
        //printf("REF0\n");
        Var var = find_var(op->u.addr);
        //printf("REF1\n");
        var->reg_no = reg_no;
        reg[reg_no].var = var;
        fprintf(file, "  addi $%s, $fp, %d\n", reg[reg_no].name, var->offset);
        //printf("REF\n");
        return reg_no;
        break;
    }
    case DEREF:
    {
        int reg_no = GetFreeReg();
        reg[reg_no].state = BUSY;
        Var var = find_var(op->u.addr);
        var->reg_no = reg_no;
        reg[reg_no].var = var;
        fprintf(file, "  lw $%s, %d($fp)\n", reg[reg_no].name, var->offset);
        int reg_no_2 = GetFreeReg();
        reg[reg_no_2].state = BUSY;
        reg[reg_no_2].var = var;
        var->reg_no = reg_no_2;
        fprintf(file, "  lw $%s, 0($%s)\n", reg[reg_no_2].name, reg[reg_no].name);
        FreeReg(reg_no);
        return reg_no_2;
        break;
    }
    case LABEL:
        break;
    case VARRAY:
    {
        int reg_no = GetFreeReg();
        reg[reg_no].state = BUSY;
        Var var = find_var(op);
        var->reg_no = reg_no;
        reg[reg_no].var = var;
        fprintf(file, "  addi $%s, $fp, %d\n", reg[reg_no].name, var->offset);
        return reg_no;
        break;
    }
    default:
        break;
    }
}

void MIPSLabel(InterCode code,FILE* file){
    fprintf(file,"label%d:\n", code->u.unaryop.op->u.label);
}

void MIPSFunction(InterCode code,FILE* file){
    fprintf(file,"%s:\n", code->u.unaryop.op->u.func);
    fprintf(file,"  move $fp, $sp\n");
    fprintf(file,"  addi $sp, $sp, %d\n",all_offset[temp_func-1]);
}

void MIPSAssign(InterCode code,FILE* file){
    if(code->u.assign.left->kind == DEREF){
        int left = MIPSOperand(code->u.assign.left->u.addr,file);
        int right = MIPSOperand(code->u.assign.right,file);
        fprintf(file, "  sw $%s, 0($%s)\n", reg[right].name, reg[left].name);
        FreeReg(left);
        FreeReg(right);
    }
    else{
        int left = MIPSOperand(code->u.assign.left,file);
        //printf("left op \n");
        int right = MIPSOperand(code->u.assign.right,file);
        //printf("right op \n");
        fprintf(file, "  move $%s, $%s\n", reg[left].name, reg[right].name);
        StoreMemory(left, file);
        FreeReg(left);
        FreeReg(right);
    }
}

void MIPSAdd(InterCode code,FILE* file){
    int res = MIPSOperand(code->u.binop.result, file);
    int op1 = MIPSOperand(code->u.binop.op1, file);
    int op2 = MIPSOperand(code->u.binop.op2, file);
    fprintf(file, "  add $%s, $%s, $%s\n", reg[res].name, reg[op1].name, reg[op2].name);
    StoreMemory(res, file);
    FreeReg(res);
    FreeReg(op1);
    FreeReg(op2);
}

void MIPSSub(InterCode code,FILE* file){
    int res = MIPSOperand(code->u.binop.result, file);
    int op1 = MIPSOperand(code->u.binop.op1, file);
    int op2 = MIPSOperand(code->u.binop.op2, file);
    fprintf(file, "  sub $%s, $%s, $%s\n", reg[res].name, reg[op1].name, reg[op2].name);
    StoreMemory(res, file);
    FreeReg(res);
    FreeReg(op1);
    FreeReg(op2);
}

void MIPSMul(InterCode code,FILE* file){
    int res = MIPSOperand(code->u.binop.result, file);
    int op1 = MIPSOperand(code->u.binop.op1, file);
    int op2 = MIPSOperand(code->u.binop.op2, file);
    fprintf(file, "  mul $%s, $%s, $%s\n", reg[res].name, reg[op1].name, reg[op2].name);
    StoreMemory(res, file);
    FreeReg(res);
    FreeReg(op1);
    FreeReg(op2);
}

void MIPSDiv(InterCode code,FILE* file){
    int res = MIPSOperand(code->u.binop.result, file);
    int op1 = MIPSOperand(code->u.binop.op1, file);
    int op2 = MIPSOperand(code->u.binop.op2, file);
    fprintf(file, "  div $%s, $%s\n", reg[op1].name, reg[op2].name);
    fprintf(file, "  mflo $%s\n", reg[res].name);
    StoreMemory(res, file);
    FreeReg(res);
    FreeReg(op1);
    FreeReg(op2);
}

void MIPSGoto(InterCode code,FILE* file){
    fprintf(file, "  j label%d\n", code->u.unaryop.op->u.label);
}

void MIPSIfgoto(InterCode code,FILE* file){
    int x = MIPSOperand(code->u.ifgoto.x,file);
    int y = MIPSOperand(code->u.ifgoto.y,file);
    switch (code->u.ifgoto.kind){
        case EQ:
            fprintf(file, "  beq $%s, $%s, label%d\n", reg[x].name, reg[y].name, code->u.ifgoto.z->u.label);
            break;
        case NEQ:
            fprintf(file, "  bne $%s, $%s, label%d\n", reg[x].name, reg[y].name, code->u.ifgoto.z->u.label);
            break;
        case LT:
            fprintf(file, "  blt $%s, $%s, label%d\n", reg[x].name, reg[y].name, code->u.ifgoto.z->u.label);
            break;
        case GT:
            fprintf(file, "  bgt $%s, $%s, label%d\n", reg[x].name, reg[y].name, code->u.ifgoto.z->u.label);
            break;
        case LE:
            fprintf(file, "  ble $%s, $%s, label%d\n", reg[x].name, reg[y].name, code->u.ifgoto.z->u.label);
            break;
        case GE:
            fprintf(file, "  bge $%s, $%s, label%d\n", reg[x].name, reg[y].name, code->u.ifgoto.z->u.label);
            break;
        default:
            break;
    }
    FreeReg(x);
    FreeReg(y);
}

void MIPSReturn(InterCode code,FILE* file){
    int op = MIPSOperand(code->u.unaryop.op,file);
    fprintf(file, "  move $v0, $%s\n", reg[op].name);
    fprintf(file, "  jr $ra\n");
    FreeReg(op);
}

void MIPSArg(InterCode code,FILE* file){
    arg_num++;
    int op = MIPSOperand(code->u.unaryop.op, file);
    fprintf(file, "  addi $sp, $sp, -4\n");
    fprintf(file, "  sw $%s, 0($sp)\n", reg[op].name);
    FreeReg(op);
}

void MIPSCall(InterCode code,FILE* file){
    fprintf(file, "  addi $sp, $sp, -8\n");
    fprintf(file, "  sw $fp, 0($sp)\n");
    fprintf(file, "  sw $ra, 4($sp)\n");
    fprintf(file, "  jal %s\n", code->u.assign.right->u.func);
    fprintf(file, "  move $sp, $fp\n");
    fprintf(file, "  lw $ra, 4($sp)\n");
    fprintf(file, "  lw $fp, 0($sp)\n");
    fprintf(file, "  addi $sp, $sp, %d\n", 8 + arg_num * 4);
    int left = MIPSOperand(code->u.assign.left, file);
    fprintf(file, "  move $%s, $v0\n", reg[left].name);
    StoreMemory(left, file);
    FreeReg(left);
    arg_num = 0;
}

void MIPSRead(InterCode code,FILE* file){
    fprintf(file, "  addi $sp, $sp, -4\n");
    fprintf(file, "  sw $ra, 0($sp)\n");
    fprintf(file, "  jal read\n");
    fprintf(file, "  lw $ra, 0($sp)\n");
    fprintf(file, "  addi $sp, $sp, 4\n");
    int op = MIPSOperand(code->u.unaryop.op, file);
    fprintf(file, "  move $%s, $v0\n", reg[op].name);
    StoreMemory(op, file);
    FreeReg(op);
}

void MIPSWrite(InterCode code,FILE* file){
    int op = MIPSOperand(code->u.unaryop.op, file);
    fprintf(file, "  move $a0, $%s\n", reg[op].name);
    fprintf(file, "  addi $sp, $sp, -4\n");
    fprintf(file, "  sw $ra, 0($sp)\n");
    fprintf(file, "  jal write\n");
    fprintf(file, "  lw $ra, 0($sp)\n");
    fprintf(file, "  addi $sp, $sp, 4\n");
    FreeReg(op);
}