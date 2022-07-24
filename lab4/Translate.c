#include "Translate.h"

void initArrayPair()
{
    pointer = 0;
    for(int i=0;i<Pair_size;i++){
        arraypair[i] = NULL;
    }
}

Operand ArrayCopy(Operand left,Operand right){
    assert((left->kind == VARRAY ||left->kind == TEMP) && (right->kind == VARRAY ||right->kind == TEMP));
    int min_size = 0;
    if(left->kind == VARRAY)
        min_size = get_size(left->u.array_id.type) * left->u.array_id.size;
    else if(left->kind == TEMP)
        min_size = get_size(left->u.temp_id.type) * left->u.temp_id.size;
    int right_size = 0;
    if(right->kind == VARRAY)
        right_size = get_size(right->u.array_id.type) * right->u.array_id.size;
    else if(right->kind == TEMP)
        right_size = get_size(right->u.temp_id.type) * right->u.temp_id.size;
    if(min_size > right_size)
        min_size = right_size;
    Operand left_ref = (Operand)malloc(sizeof(struct Operand_));
    Operand right_ref = (Operand)malloc(sizeof(struct Operand_));
    left_ref = left;
    right_ref = right;
    Operand left_temp = left;
    Operand right_temp = right;
    if(left->kind == VARRAY && left->u.array_id.isaddr == false)
    {
        left_temp = createOperand(TEMP,0,"","",NULL,true);
        left_ref = createOperand(REF,0,"","",left,false);
        add_node(createAssign(IC_ASSIGN,left_ref,left_temp));
    }
    if(right->kind == VARRAY && right->u.array_id.isaddr == false)
    {
        right_temp = createOperand(TEMP,0,"","",NULL,true);
        right_ref = createOperand(REF,0,"","",right,false);
        add_node(createAssign(IC_ASSIGN,right_ref,right_temp));
    }
    add_node(createAssign(IC_ASSIGN,createOperand(DEREF,0,"","",right_temp,false),createOperand(DEREF,0,"","",left_temp,false)));
    Operand left_ret = createOperand(TEMP,0,"","",NULL,true);
    Operand right_ret = createOperand(TEMP,0,"","",NULL,true);
    for(int i = 4;i<min_size;i = i + 4){
        Operand offset = createOperand(CONSTANT,i,"","",NULL,false);
        add_node(createBinop(IC_ADD,left_ret,left_temp,offset));
        add_node(createBinop(IC_ADD,right_ret,right_temp,offset));
        add_node(createAssign(IC_ASSIGN,createOperand(DEREF,0,"","",right_ret,false),createOperand(DEREF,0,"","",left_ret,false)));
    }
    return left_temp;
}

int get_size(Type type) {
    if (type == NULL) return 0;
    if (type->kind == BASIC) {
        return 4;
    } else if (type->kind == ARRAY) {
        return type->u.array.size * get_size(type->u.array.elem);
    } else if (type->kind == STRUCTURE) {
        printf("error: struct variable appeared\n");
        exit(-1);
    } else {
        assert(0);
    }
    return 0;
}

int GetArraySize(FieldList field){
    Type field_type = field->type;
    int size = 1;
    while(field_type != NULL){
        if(field_type->kind == ARRAY){
            size = size * field_type->u.array.size;
        }
        else if(field_type->kind == BASIC){
            size = size * 4;
            break;
        }
        else{
            printf("error\n");
        }
        field_type = field_type->u.array.elem;
    }
    return size;
}

void TranslateProgram(struct TreeNode* Node){
    if(Node == NULL) return;
    init_list();
    initArrayPair();
    if(Node->Numofchild == 1){
        TranslateExtDefList(Node->Child);
    }
    else{
        printf("wrong1\n");
    }
}

void TranslateExtDefList(struct TreeNode* Node){
    if(Node == NULL) return;
    if(Node->Numofchild == 0) return;
    if(Node->Numofchild == 2){
        TranslateExtDef(Node->Child);
        TranslateExtDefList(Node->Child->Sibling);
    }
    else{
        printf("wrong2\n");
    }
}

void TranslateExtDef(struct TreeNode* Node){
    if(Node == NULL) return;
    if(Node->Numofchild == 2){   
    }
    else if(Node->Numofchild == 3){
        if(strcmp(Node->Child->Sibling->Name,"ExtDecList") == 0){
            //UnitExtDecList(Node->Child->Sibling);
            printf("error: global variable appeared\n");
        }
        else if(strcmp(Node->Child->Sibling->Name,"FunDec") == 0){
            //
            TranslateFunDec(Node->Child->Sibling);
            //printf("good\n");
            TranslateCompSt(Node->Child->Sibling->Sibling);
        }
    }
    else{
        printf("wrong3\n");
    }
}

void TranslateFunDec(struct TreeNode* Node){
    if(Node == NULL) return;
    char* name = Node->Child->data.Charval;
    if(Node->Numofchild == 4){
        Operand func = createOperand(RFUNCTION,0,name,"",NULL,false);
        InterCode intercode_func = createUnaryop(IC_FUNCTION,func);
        add_node(intercode_func);
        FieldList func_field = findHashtable(name);
        FieldList arg_field = func_field->type->u.function->next;
        for(int i=0;i<func_field->type->u.function->numofparam;i++){
            if(arg_field == NULL) break;
            switch (arg_field->type->kind)
            {
            case BASIC:
            {
                Operand arg = createOperand(VARIABLE,0,"",arg_field->name,NULL,false);
                InterCode intercode_arg = createUnaryop(IC_PARAM,arg);
                add_node(intercode_arg);
                break;
            }
            case ARRAY:
            {
                Operand arg_array = createOperand(VARRAY,0,"",arg_field->name,NULL,true);
                InterCode intercode_arg_array = createUnaryop(IC_PARAM,arg_array);
                add_node(intercode_arg_array);
                break;
            }
            case STRUCTURE:
                printf("error: struct variable appeared\n");
                exit(-1);
                break;
            default:
                break;
            }
            arg_field = arg_field->tail;
        }
    }
    else if(Node->Numofchild == 3){
        Operand func = createOperand(RFUNCTION,0,name,"",NULL,false);
        InterCode intercode_func = createUnaryop(IC_FUNCTION,func);
        add_node(intercode_func);
    }
    else{
        printf("wrong UnitFunDec\n");
    }
}

void TranslateCompSt(struct TreeNode* Node){
    //printf("compst\n");
    if(Node == NULL) return;
    if(Node->Numofchild == 4){
        TranslateDefList(Node->Child->Sibling);
        TranslateStmtList(Node->Child->Sibling->Sibling);
    }
    else{
        printf("wrong UnitCompSt");
    }
}

void TranslateStmtList(struct TreeNode* Node){
    if(Node == NULL) return;
    if(Node->Numofchild == 0) return;
    if(Node->Numofchild == 2){
        TranslateStmt(Node->Child);
        TranslateStmtList(Node->Child->Sibling);
    }
    else{
        printf("wrong UnitStmtList");
    }
}

void TranslateStmt(struct TreeNode* Node){
    if(Node == NULL) return;
    if(Node->Numofchild == 2){
        Operand op = TranslateExp(Node->Child);
    }
    else if(Node->Numofchild == 1){
        TranslateCompSt(Node->Child);
    }
    else if(Node->Numofchild == 3){
        Operand op = TranslateExp(Node->Child->Sibling);
        InterCode intercode_ret = createUnaryop(IC_RETURN,op);
        add_node(intercode_ret);
    }
    else if(Node->Numofchild == 5){
        if(strcmp(Node->Child->Name,"IF") == 0){
            Operand label1 = createOperand(LABEL,0,"","",NULL,false);
            Operand label2 = createOperand(LABEL,0,"","",NULL,false);
            TranslateCondExp(Node->Child->Sibling->Sibling,label1,label2);
            InterCode intercode_true = createUnaryop(IC_LABEL,label1);
            add_node(intercode_true);
            TranslateStmt(Node->Child->Sibling->Sibling->Sibling->Sibling);
            InterCode intercode_false = createUnaryop(IC_LABEL,label2);
            add_node(intercode_false);
        }
        else if(strcmp(Node->Child->Name,"WHILE") == 0){
            Operand label1 = createOperand(LABEL,0,"","",NULL,false);
            Operand label2 = createOperand(LABEL,0,"","",NULL,false);
            Operand label3 = createOperand(LABEL,0,"","",NULL,false);
            InterCode intercode_begin = createUnaryop(IC_LABEL,label1);
            InterCode intercode_true = createUnaryop(IC_LABEL,label2);
            InterCode intercode_next = createUnaryop(IC_LABEL,label3);
            InterCode intercode_goto = createUnaryop(IC_GOTO,label1);
            add_node(intercode_begin);
            TranslateCondExp(Node->Child->Sibling->Sibling,label2,label3);
            add_node(intercode_true);
            TranslateStmt(Node->Child->Sibling->Sibling->Sibling->Sibling);
            add_node(intercode_goto);
            add_node(intercode_next);
        }
    }
    else if(Node->Numofchild == 7){
        Operand label1 = createOperand(LABEL,0,"","",NULL,false);
        Operand label2 = createOperand(LABEL,0,"","",NULL,false);
        Operand label3 = createOperand(LABEL,0,"","",NULL,false);
        InterCode intercode_begin = createUnaryop(IC_LABEL,label1);
        InterCode intercode_true = createUnaryop(IC_LABEL,label2);
        InterCode intercode_next = createUnaryop(IC_LABEL,label3);
        InterCode intercode_goto = createUnaryop(IC_GOTO,label3);
        TranslateCondExp(Node->Child->Sibling->Sibling,label1,label2);
        add_node(intercode_begin);
        TranslateStmt(Node->Child->Sibling->Sibling->Sibling->Sibling);
        add_node(intercode_goto);
        add_node(intercode_true);
        TranslateStmt(Node->Child->Sibling->Sibling->Sibling->Sibling->Sibling->Sibling);
        add_node(intercode_next);
    }
    else{
        printf("wrong UnitStmt\n");
    }
}


void TranslateCondExp(struct TreeNode* Node, Operand Truelabel, Operand Falselabel){
    if(Node == NULL) return;
    if(Node->Numofchild == 2 && strcmp(Node->Child->Name,"NOT") == 0){
        TranslateCondExp(Node->Child->Sibling,Falselabel,Truelabel);
    }
    else if(Node->Numofchild == 3){
        if(strcmp(Node->Child->Sibling->Name,"AND") == 0){
            Operand label1 = createOperand(LABEL,0,"","",NULL,false);
            InterCode intercode_label1 = createUnaryop(IC_LABEL,label1);
            TranslateCondExp(Node->Child,label1,Falselabel);
            add_node(intercode_label1);
            TranslateCondExp(Node->Child->Sibling->Sibling,Truelabel,Falselabel);
        }
        else if(strcmp(Node->Child->Sibling->Name,"OR") == 0){
            Operand label1 = createOperand(LABEL,0,"","",NULL,false);
            InterCode intercode_label1 = createUnaryop(IC_LABEL,label1);
            TranslateCondExp(Node->Child,Truelabel,label1);
            add_node(intercode_label1);
            TranslateCondExp(Node->Child->Sibling->Sibling,Truelabel,Falselabel);
        }
        else if(strcmp(Node->Child->Sibling->Name,"RELOP") == 0){
            Operand op1 = TranslateExp(Node->Child);
            Operand op2 = TranslateExp(Node->Child->Sibling->Sibling);
            enum RelopKind kind;
            if(strcmp(Node->Child->Sibling->data.Charval,"==") == 0)
                kind = EQ;
            else if(strcmp(Node->Child->Sibling->data.Charval,"!=") == 0)
                kind = NEQ;
            else if(strcmp(Node->Child->Sibling->data.Charval,"<") == 0)
                kind = LT;
            else if(strcmp(Node->Child->Sibling->data.Charval,">") == 0)
                kind = GT;
            else if(strcmp(Node->Child->Sibling->data.Charval,"<=") == 0)
                kind = LE;
            else if(strcmp(Node->Child->Sibling->data.Charval,">=") == 0)
                kind = GE;
            InterCode intercode_ifgoto = createIfgoto(IC_IF_GOTO,op1,op2,Truelabel,kind);
            add_node(intercode_ifgoto);
            InterCode intercode_goto = createUnaryop(IC_GOTO,Falselabel);
            add_node(intercode_goto);
        }
        else{
            Operand op = TranslateExp(Node);
            InterCode intercode_ifgoto = createIfgoto(IC_IF_GOTO,op,createOperand(CONSTANT,0,"","",NULL,false),Truelabel,NEQ);
            add_node(intercode_ifgoto);
            InterCode intercode_goto = createUnaryop(IC_GOTO,Falselabel);
            add_node(intercode_goto);
        }
    }
    else{
        Operand op = TranslateExp(Node);
        InterCode intercode_ifgoto = createIfgoto(IC_IF_GOTO,op,createOperand(CONSTANT,0,"","",NULL,false),Truelabel,NEQ);
        add_node(intercode_ifgoto);
        InterCode intercode_goto = createUnaryop(IC_GOTO,Falselabel);
        add_node(intercode_goto);
    }
}

void TranslateDefList(struct TreeNode* Node){
    if(Node == NULL) return;
    if(Node->Numofchild == 0) return;
    if(Node->Numofchild == 2){
        TranslateDef(Node->Child);
        TranslateDefList(Node->Child->Sibling);
    }
    else{
        printf("wrong UnitDefList\n");
    }
}   

void TranslateDef(struct TreeNode* Node){
    if(Node == NULL) return;
    if(Node->Numofchild == 3){
        TranslateDecList(Node->Child->Sibling);
    }
    else{
        printf("wrong UnitDef\n");
    }
}

void TranslateDecList(struct TreeNode* Node){
    if(Node == NULL) return;
    if(Node->Numofchild == 1){
        TranslateDec(Node->Child);
    }
    else if(Node->Numofchild == 3){
        TranslateDec(Node->Child);
        TranslateDecList(Node->Child->Sibling->Sibling);
    }
    else{
        printf("wrong UnitDecList\n");
    }
}

void TranslateDec(struct TreeNode* Node){
    if(Node == NULL) return;
    if(Node->Numofchild == 1){
        Operand op = TranslateVarDec(Node->Child);
    }
    else if(Node->Numofchild == 3){
        Operand op = TranslateVarDec(Node->Child);
        Operand exp = TranslateExp(Node->Child->Sibling->Sibling);
        if(op->kind == VARIABLE){
        InterCode intercode_assign = createAssign(IC_ASSIGN,exp,op);
        add_node(intercode_assign);
        }
        else if(op->kind == VARRAY){
            ArrayCopy(op,exp);
        }
        //need to be modified
    }
    else{
        printf("wrong UnitDec\n");
    }
}

Operand TranslateVarDec(struct TreeNode* Node){
    if(Node == NULL) return NULL;
    if(Node->Numofchild == 1){
        char* name = Node->Child->data.Charval;
        FieldList var = findHashtable(name);
        switch (var->type->kind)
        {
        case BASIC:
        {
            Operand op = createOperand(VARIABLE,0,"",name,NULL,false);
            return op;
            break;
        }
        case ARRAY:
        {
            Operand op_array = createOperand(VARRAY,0,"",name,NULL,false);
            op_array->u.array_id.type = var->type->u.array.elem;
            op_array->u.array_id.size = var->type->u.array.size;
            int size = GetArraySize(var);
            InterCode intercode_array = createDec(IC_DEC,op_array,size);
            add_node(intercode_array);
            return op_array;
            break;
        }
        case STRUCTURE:
            printf("error: struct variable appeared\n");
            exit(-1);
            break;
        default:
            break;
        }
    }
    else if(Node->Numofchild == 4){
        return TranslateVarDec(Node->Child);
    }
    else{
        printf("wrong VarDec\n");
    }
}

Operand TranslateExp(struct TreeNode* Node){
    if(Node == NULL) return NULL;
    if(Node->Numofchild == 3){
        if(strcmp(Node->Child->Sibling->Name,"ASSIGNOP") == 0){
            Operand op_left = TranslateExp(Node->Child);
            Operand op_right = TranslateExp(Node->Child->Sibling->Sibling);
            switch (op_left->kind)
            {
            case VARIABLE:
            {
                InterCode intercode_assign = createAssign(IC_ASSIGN,op_right,op_left);
                add_node(intercode_assign);
                break;
            }
            case VARRAY:
                ArrayCopy(op_left,op_right);
                break;
            case TEMP:
            {
                assert(op_left->u.temp_id.isaddr == true && op_right->u.temp_id.isaddr == true);
                ArrayCopy(op_left,op_right);
                break;
            }
            case DEREF:
            {
                InterCode intercode_assign = createAssign(IC_ASSIGN,op_right,op_left);
                add_node(intercode_assign);
                break;
            }
            default:
                break;
            }
            return op_right;
        }
        else if(strcmp(Node->Child->Name,"LP") == 0){
            return TranslateExp(Node->Child->Sibling);
        }
        else if(strcmp(Node->Child->Name,"ID") == 0){
            char* name = Node->Child->data.Charval;
            FieldList field = findHashtable(name);
            if(strcmp(field->name,"read") == 0){
                Operand temp = createOperand(TEMP,0,"","",NULL,false);
                InterCode intercode_read = createUnaryop(IC_READ,temp);
                add_node(intercode_read);
                return temp;
            }
            else{
                Operand func = createOperand(RFUNCTION,0,name,"",NULL,false);
                Operand temp = createOperand(TEMP,0,"","",NULL,false);
                InterCode intercode_call = createAssign(IC_CALL,func,temp);
                add_node(intercode_call);
                return temp;
            }
        }
        else if(strcmp(Node->Child->Sibling->Name,"DOT") == 0){
            printf("error: struct variable appeared\n");
            exit(-1);
            return NULL;
        }
        else if(strcmp(Node->Child->Sibling->Name,"AND") == 0 || strcmp(Node->Child->Sibling->Name,"OR") == 0 || strcmp(Node->Child->Sibling->Name,"RELOP") == 0){
            Operand label1 = createOperand(LABEL,0,"","",NULL,false);
            Operand label2 = createOperand(LABEL,0,"","",NULL,false);
            Operand op_ret = createOperand(TEMP,0,"","",NULL,false);
            add_node(createAssign(IC_ASSIGN,createOperand(CONSTANT,0,"","",NULL,false),op_ret));
            TranslateCondExp(Node,label1,label2);
            add_node(createUnaryop(IC_LABEL,label1));
            add_node(createAssign(IC_ASSIGN,createOperand(CONSTANT,1,"","",NULL,false),op_ret));
            add_node(createUnaryop(IC_LABEL,label2));
            return op_ret;
        }
        else{
            Operand op_left = TranslateExp(Node->Child);
            Operand op_right = TranslateExp(Node->Child->Sibling->Sibling);
            if(strcmp(Node->Child->Sibling->Name,"PLUS") == 0){
                if (op_left->kind == CONSTANT && op_right->kind == CONSTANT) {
                    return createOperand(CONSTANT,op_left->u.constant+op_right->u.constant,"","",NULL,false);
                }
                else{
                    if (op_left->kind == CONSTANT && op_left->u.constant == 0){
                        return op_right;
                    } else if (op_right->kind == CONSTANT && op_right->u.constant == 0) {
                        return op_left;
                    }
                    else{
                        Operand op_ret = createOperand(TEMP,0,"","",NULL,false);
                        add_node(createBinop(IC_ADD,op_ret,op_left, op_right));
                        return op_ret;
                    }
                }
            }
            else if(strcmp(Node->Child->Sibling->Name,"MINUS") == 0){
                if (op_left->kind == CONSTANT && op_right->kind == CONSTANT) {
                    return createOperand(CONSTANT,op_left->u.constant-op_right->u.constant,"","",NULL,false);
                }
                else{
                    if (op_right->kind == CONSTANT && op_right->u.constant == 0) {
                        return op_left;
                    }
                    else{
                        Operand op_ret = createOperand(TEMP,0,"","",NULL,false);
                        add_node(createBinop(IC_SUB,op_ret,op_left, op_right));
                        return op_ret;
                    }
                }
            }
            else if(strcmp(Node->Child->Sibling->Name,"STAR") == 0){
                if (op_left->kind == CONSTANT && op_right->kind == CONSTANT) {
                    return createOperand(CONSTANT,op_left->u.constant*op_right->u.constant,"","",NULL,false);
                }
                else{
                    if (op_left->kind == CONSTANT && op_left->u.constant == 0)
                        return createOperand(CONSTANT,0,"","",NULL,false);
                    else if (op_left->kind == CONSTANT && op_left->u.constant == 1) return op_right;
                    else if (op_right->kind == CONSTANT && op_right->u.constant == 0)
                        return createOperand(CONSTANT,0,"","",NULL,false);
                    else if (op_right->kind == CONSTANT && op_right->u.constant == 1) return op_left;
                    else{
                        Operand op_ret = createOperand(TEMP,0,"","",NULL,false);
                        add_node(createBinop(IC_MUL,op_ret,op_left, op_right));
                        return op_ret;
                    }
                }
            }
            else if(strcmp(Node->Child->Sibling->Name,"DIV") == 0){
                if (op_left->kind == CONSTANT && op_right->kind == CONSTANT) {
                    if(op_left->u.constant > 0 && op_right->u.constant < 0){
                        return createOperand(CONSTANT,(op_left->u.constant - op_right->u.constant - 1)/op_right->u.constant,"","",NULL,false);
                    }
                    else if(op_left->u.constant < 0 && op_right->u.constant > 0){
                        return createOperand(CONSTANT,(op_left->u.constant - op_right->u.constant + 1)/op_right->u.constant,"","",NULL,false);
                    }
                    else{
                        if(op_right->u.constant == 0)
                            return createOperand(CONSTANT,0,"","",NULL,false);
                        else
                            return createOperand(CONSTANT,op_left->u.constant/op_right->u.constant,"","",NULL,false);
                    }
                }
                else{
                    if (op_left->kind == CONSTANT && op_left->u.constant == 0)
                        return createOperand(CONSTANT,0,"","",NULL,false);
                    else if (op_right->kind == CONSTANT && op_right->u.constant == 1) return op_left;
                    else{
                        Operand op_ret = createOperand(TEMP,0,"","",NULL,false);
                        add_node(createBinop(IC_DIV,op_ret,op_left, op_right));
                        return op_ret;
                    }
                }
            }
        }
    }
    else if(Node->Numofchild == 2){
        if(strcmp(Node->Child->Name,"MINUS") == 0){
            Operand op = TranslateExp(Node->Child->Sibling);
            if(op->kind == CONSTANT)
                return createOperand(CONSTANT,0-op->u.constant,"","",NULL,false);
            else{
                Operand op_ret = createOperand(TEMP,0,"","",NULL,false);
                add_node(createBinop(IC_SUB,op_ret,createOperand(CONSTANT,0,"","",NULL,false),op));
                return op_ret;
            }
        }
        else if(strcmp(Node->Child->Name,"NOT") == 0){
            Operand label1 = createOperand(LABEL,0,"","",NULL,false);
            Operand label2 = createOperand(LABEL,0,"","",NULL,false);
            Operand op_ret = createOperand(TEMP,0,"","",NULL,false);
            add_node(createAssign(IC_ASSIGN,createOperand(CONSTANT,0,"","",NULL,false),op_ret));
            TranslateCondExp(Node,label1,label2);
            add_node(createUnaryop(IC_LABEL,label1));
            add_node(createAssign(IC_ASSIGN,createOperand(CONSTANT,1,"","",NULL,false),op_ret));
            add_node(createUnaryop(IC_LABEL,label2));
            return op_ret;
        }
    }
    else if(Node->Numofchild == 4){
        if(strcmp(Node->Child->Sibling->Name,"LP") == 0){
            char* name = Node->Child->data.Charval;
            FieldList field = findHashtable(name);
            if(strcmp(field->name,"write") == 0){
                Operand op = TranslateArgs(Node->Child->Sibling->Sibling,true);
                add_node(createUnaryop(IC_WRITE,op));
                return createOperand(CONSTANT,0,"","",NULL,false);
            }
            else{
                Operand op = TranslateArgs(Node->Child->Sibling->Sibling,false);
                Operand op_func = createOperand(RFUNCTION,0,name,"",NULL,false);
                Operand op_ret = createOperand(TEMP,0,"","",NULL,false);
                InterCode intercode_call = createAssign(IC_CALL,op_func,op_ret);
                add_node(intercode_call);
                return op_ret;
            }
        }
        else if(strcmp(Node->Child->Sibling->Name,"LB") == 0){
            Operand op1 = TranslateExp(Node->Child);
            assert(op1->kind == TEMP || op1->kind == DEREF || op1->kind == VARRAY);
            Operand op2 = TranslateExp(Node->Child->Sibling->Sibling);
            Operand offset = (Operand)malloc(sizeof(struct Operand_));
            Operand op_ret = createOperand(TEMP,0,"","",NULL,false);
            int width = get_size(op1->u.array_id.type);
            if (op2->kind == CONSTANT) {
                offset = createOperand(CONSTANT,width*op2->u.constant,"","",NULL,false);
            } else {
                offset = createOperand(TEMP,0,"","",NULL,false);
                add_node(createBinop(IC_MUL,offset,op2,createOperand(CONSTANT,width,"","",NULL,false)));
            }
            op_ret->u.temp_id.isaddr = true;
            if (op1->kind == VARRAY) {  
                if (offset->kind == CONSTANT && offset->u.constant == 0) {
                    if(op1->u.array_id.isaddr == true){
                        add_node(createAssign(IC_ASSIGN,op1,op_ret));
                        arraypair[pointer] = (ArrayPair)malloc(sizeof(struct ArrayPair_));
                        arraypair[pointer]->need_to_replace = createOperand(TEMP,0,"","",NULL,true);
                        arraypair[pointer]->need_to_replace->u.temp_id.temp = op_ret->u.temp_id.temp;
                        arraypair[pointer]->replace = (Operand)malloc(sizeof(struct Operand_));
                        arraypair[pointer]->replace->kind = VARRAY;
                        arraypair[pointer]->replace->u.array_id.array = op1->u.array_id.array;
                        pointer++;
                    }
                    else{
                        add_node(createAssign(IC_ASSIGN,createOperand(REF,0,"","",op1,false),op_ret));
                        arraypair[pointer] = (ArrayPair)malloc(sizeof(struct ArrayPair_));
                        arraypair[pointer]->need_to_replace = createOperand(TEMP,0,"","",NULL,true);
                        arraypair[pointer]->need_to_replace->u.temp_id.temp = op_ret->u.temp_id.temp;
                        arraypair[pointer]->replace = createOperand(REF,0,"","",op1,false);
                        pointer++;
                    }
                } else {
                    if(op1->u.array_id.isaddr == true)
                        add_node(createBinop(IC_ADD,op_ret,op1,offset));
                    else
                        add_node(createBinop(IC_ADD,op_ret,createOperand(REF,0,"","",op1,false),offset));
                }
            } else if (op1->kind == TEMP && op1->u.temp_id.isaddr == true) { 
                if (offset->kind == CONSTANT && offset->u.constant == 0) {
                    add_node(createAssign(IC_ASSIGN,op1,op_ret));
                    arraypair[pointer] = (ArrayPair)malloc(sizeof(struct ArrayPair_));
                    arraypair[pointer]->need_to_replace = createOperand(TEMP,0,"","",NULL,true);
                    arraypair[pointer]->need_to_replace->u.temp_id.temp = op_ret->u.temp_id.temp;
                    arraypair[pointer]->replace = createOperand(TEMP,0,"","",NULL,true);
                    arraypair[pointer]->replace->u.temp_id.temp = op1->u.temp_id.temp;
                    pointer++;
                }
                else 
                    add_node(createBinop(IC_ADD,op_ret,op1,offset));
            } 

            if ((op1->kind == VARRAY && op1->u.array_id.type->kind == BASIC) || (op1->kind == TEMP && op1->u.temp_id.type->kind == BASIC)) {  // 数组解析完毕
                op_ret->u.temp_id.type = NULL;
                op_ret->u.temp_id.size = 0;
                
                return createOperand(DEREF,0,"","",op_ret,false);
            } else if ((op1->kind == VARRAY && op1->u.array_id.type->kind == ARRAY) || (op1->kind == TEMP && op1->u.temp_id.type->kind == ARRAY)) {
                op_ret->u.temp_id.type = op1->u.temp_id.type->u.array.elem;
                op_ret->u.temp_id.size = op1->u.temp_id.type->u.array.size;
                return op_ret;
            }
            
        }
    }
    else if(Node->Numofchild == 1){
        if(strcmp(Node->Child->Name,"ID") == 0){
            char* name = Node->Child->data.Charval;
            FieldList field = findHashtable(name);
            switch (field->type->kind)
            {
            case BASIC:
            {
                Operand op = createOperand(VARIABLE,0,"",name,NULL,false);
                return op;
                break;
            }
            case ARRAY:
            {
                Operand op = (Operand)malloc(sizeof(struct Operand_));
                if(field->isarg == true)
                    op = createOperand(VARRAY,0,"",name,NULL,true);
                else    
                    op = createOperand(VARRAY,0,"",name,NULL,false);
                op->u.array_id.type = field->type->u.array.elem;
                op->u.array_id.size = field->type->u.array.size;
                return op;
                break;
            }
            case STRUCTURE:
                printf("error: struct variable appeared\n");
                exit(-1);
                return NULL;
                break;
            default:
                break;
            }
        }
        else if(strcmp(Node->Child->Name,"INT") == 0){
            Operand op = createOperand(CONSTANT,Node->Child->data.Intval,"","",NULL,false);
            return op;
        }
        else if(strcmp(Node->Child->Name,"FLOAT") == 0){
            printf("error: float num appeared\n");
            return NULL;
        }
    }
    else{
        printf("wrong Exp\n");
        return NULL;
    }
}

Operand TranslateArgs(struct TreeNode* Node,bool iswrite){
    if(Node == NULL) return NULL;
    if(Node->Numofchild == 1){
    }
    else if(Node->Numofchild == 3){
        if(iswrite == true) {
            printf("wrong func write\n");
            return NULL;
        }
        TranslateArgs(Node->Child->Sibling->Sibling,false);
    }
    Operand op = TranslateExp(Node->Child);
    if(iswrite == true){
        //Operand op_ret = createOperand(TEMP,0,"","",NULL,false);
        //InterCode intercode_assign = createAssign(IC_ASSIGN,op,op_ret);
        //add_node(intercode_assign);
        return op;
    }
    else{
        if(op->kind == VARRAY){
            Operand op_ref;
            if(op->u.array_id.isaddr == true)
                op_ref = op;
            else
                op_ref = createOperand(REF,0,"","",op,false);
            InterCode intercode_arg = createUnaryop(IC_ARG,op_ref);
            add_node(intercode_arg);
        }
        else {
            InterCode intercode_arg = createUnaryop(IC_ARG,op);
            add_node(intercode_arg);
        }
        return NULL;
    }
}