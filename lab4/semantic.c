#include "semantic.h"

int SYMstruct = 0;
int var_id = 0;

void SemanticError(int num, int line, char* mg){
    printf("Error type %d at Line %d: %s\n",num,line,mg);
}

bool StructhasName(FieldList field, char* name){
    FieldList tempfield = field->type->u.structure;
    while(tempfield != NULL){
        if(strcmp(tempfield->name,name) == 0)
            return true;
        tempfield = tempfield->tail;     
    }
    return false;
}

bool EqualType(Type type1,Type type2){
    if(type1 == NULL || type2 == NULL){
        return false;
    }
    else{
        if(type1->kind == type2->kind){
            if(type1->kind == BASIC){
                if(type1->u.basic == type2->u.basic)
                    return true;
                else
                    return false;
            }
            if(type1->kind == ARRAY){
                //printf("here now in\n");
                int vec1 = 0;
                int vec2 = 0;
                //printf("vec1 = %d\n",vec1);
                //if(type1->u.array.elem == NULL)
                //    printf("vec1 = %d\n",vec1);
                Type newtype1 = type1->u.array.elem;
                //printf("vec1 now = %d\n",vec1);
                while(newtype1->kind != BASIC){
                    newtype1 = newtype1->u.array.elem;
                     //printf("vec1 = %d\n",vec1);
                    vec1++;
                }
                
                Type newtype2 = type2->u.array.elem;
                while(newtype2->kind != BASIC){
                    newtype2 = newtype2->u.array.elem;
                     //printf("vec2 = %d\n",vec2);
                    vec2++;
                }
                //printf("vec2 = %d\n",vec2);
                if((vec1 == vec2) && newtype1->u.basic == newtype2->u.basic)    return true;
                else    return false;
            }
            if(type1->kind == STRUCTURE){
                FieldList field1 = type1->u.structure;
                FieldList field2 = type2->u.structure;
                while(field1 != NULL && field2 != NULL){
                    if(EqualType(field1->type,field2->type) == false){
                        return false;
                    }
                    field1 = field1->tail;
                    field2 = field2->tail;
                }
                if(field1 != NULL || field2 != NULL)    return false;
                else    return true;
            }
            if(type1->kind == FUNCTION){
                printf("something wrong\n");
                return false;
            }
        }
        else{
            return false;
        }
    }
}

FieldList FindStructMember(FieldList field,char* name){
    FieldList tempfield = field->type->u.structure;
    while(tempfield != NULL){
        if(strcmp(tempfield->name,name) == 0)
            return tempfield;
        tempfield = tempfield->tail;
    }
    return NULL;
}

void insert_read_write(){
    FieldList newfield_read = (FieldList) malloc (sizeof(struct FieldList_));
    FuncList func_read = (FuncList) malloc (sizeof(struct FuncList_));
    Type type_read = (Type) malloc (sizeof(struct Type_));
    type_read->kind = BASIC;
    type_read->u.basic = 0;

    func_read->numofparam = 0;
    func_read->ret = type_read;
    func_read->next = NULL;
            
    newfield_read->name = "read";
    newfield_read->tail = NULL;
    newfield_read->type = (Type) malloc (sizeof(struct Type_));
    newfield_read->type->kind = FUNCTION;

    newfield_read->type->u.function = func_read;

    FieldList newfield_write = (FieldList) malloc (sizeof(struct FieldList_));
    FuncList func_write = (FuncList) malloc (sizeof(struct FuncList_));
    Type type_write = (Type) malloc (sizeof(struct Type_));
    type_write->kind = BASIC;
    type_write->u.basic = 0;

    func_write->numofparam = 1;
    func_write->ret = type_write;
    FieldList paramfield = (FieldList) malloc (sizeof(struct FieldList_));
    paramfield->name = "";
    paramfield->tail = NULL;
    paramfield->type = type_write;

    func_write->next = paramfield;
            
    newfield_write->name = "write";
    newfield_write->tail = NULL;
    newfield_write->type = (Type) malloc (sizeof(struct Type_));
    newfield_write->type->kind = FUNCTION;

    newfield_write->type->u.function = func_write;
    insertHashtable(newfield_read);
    insertHashtable(newfield_write);
}

void UnitProgram(struct TreeNode* Node){
    if(Node == NULL) return;
    initHashtable();
    insert_read_write();
    if(Node->Numofchild == 1){
        UnitExtDefList(Node->Child);
    }
    else{
        printf("wrong1\n");
    }
}

void UnitExtDefList(struct TreeNode* Node){
    if(Node == NULL) return;
    if(Node->Numofchild == 0) return;
    if(Node->Numofchild == 2){
        UnitExtDef(Node->Child);
        UnitExtDefList(Node->Child->Sibling);
    }
    else{
        printf("wrong2\n");
    }
}

void UnitExtDef(struct TreeNode* Node){
    if(Node == NULL) return;
    Type type = UnitSpecifier(Node->Child);
    if(Node->Numofchild == 2){   
    }
    else if(Node->Numofchild == 3){
        if(strcmp(Node->Child->Sibling->Name,"ExtDecList") == 0){
            UnitExtDecList(Node->Child->Sibling,type);
        }
        else if(strcmp(Node->Child->Sibling->Name,"FunDec") == 0){
            UnitFunDec(Node->Child->Sibling,type);
            UnitCompSt(Node->Child->Sibling->Sibling,type);
        }
    }
    else{
        printf("wrong3\n");
    }
}

void UnitExtDecList(struct TreeNode* Node,Type type){
    if(Node == NULL) return;
    if(Node->Numofchild == 1){
        UnitVarDec(Node->Child,type, NULL);  
    }
    else if(Node->Numofchild == 3){
        UnitVarDec(Node->Child,type,NULL);  
        UnitExtDecList(Node->Child->Sibling->Sibling,type);
    }
    else{
        printf("wrong\n");
    }
}

Type UnitSpecifier(struct TreeNode* Node){
    if(Node == NULL) return NULL;
    if(Node->Numofchild == 1){ 
        if(strcmp(Node->Child->Name,"TYPE") == 0){
            Type type = (Type) malloc (sizeof(struct Type_));
            type->kind = BASIC;
            if(strcmp(Node->Child->data.Charval,"int") == 0){
                type->u.basic = 0;
            }
            else if(strcmp(Node->Child->data.Charval,"float") == 0){
                type->u.basic = 1;
            }
            return type;
        }
        else if(strcmp(Node->Child->Name,"StructSpecifier") == 0){
            return UnitStructSpecifier(Node->Child);
        }
    }
    else{
        printf("wrong\n");
        return NULL;
    }
}

Type UnitStructSpecifier(struct TreeNode* Node){
    if(Node == NULL) return NULL;
    if(Node->Numofchild == 5){
        Type type = (Type) malloc (sizeof(struct Type_));
        FieldList field = (FieldList) malloc (sizeof(struct FieldList_));
        bool isredefined = false;
        char* name;
        name = UnitOptTag(Node->Child->Sibling,name);
        //if(findHashtable("0struct0") == findHashtable("0struct1")) printf("strange\n");
        if(findHashtable(name) != NULL){
            SemanticError(16,Node->Child->Sibling->Numofline,"Duplicated name");
            isredefined = true;
        }
        field->name = name;
        field->tail = NULL;
        Type newtype = (Type) malloc (sizeof(struct Type_));
        newtype->kind = STRUCTURE;
        newtype->u.structure = NULL;
        field->type = newtype;
        
        UnitDefList(Node->Child->Sibling->Sibling->Sibling, field);
        if(isredefined == false){
            insertHashtable(field);
            type->kind = STRUCTURE;
            type->u.structure = field;
            return type;
        }
        else{
            return NULL;
        }
    }
    else if(Node->Numofchild == 2){
        Type type = (Type) malloc (sizeof(struct Type_));
        char* name = UnitTag(Node->Child->Sibling);
        //printf("name = %s\n",name);
        FieldList tempfield = findHashtable(name);
        if(tempfield == NULL){
            SemanticError(17,Node->Child->Sibling->Numofline,"use undefined structure");
            return NULL; //maybe modify later
        }
        else if(tempfield->type->kind != STRUCTURE){
            SemanticError(17,Node->Child->Sibling->Numofline,"use undefined structure");
            return NULL; //maybe modify later
        }
        type->kind = STRUCTURE;
        
        type->u.structure = tempfield;
        return type;
    }
    else{
        printf("wrong\n");
        return NULL;
    }
}

char* UnitOptTag(struct TreeNode* Node, char* name){
    if(Node->Numofchild == 0){
        char str[] = "0struct";
        char string[11] = {0};
        sprintf(string,"%d",SYMstruct);
        strcat(str,string);
        strcpy(name,str);
        SYMstruct++;
        return name;
    }
    else
        return Node->Child->data.Charval;
}

char* UnitTag(struct TreeNode* Node){
    return Node->Child->data.Charval;
}

char* UnitVarDec(struct TreeNode* Node,Type type, FieldList field){
    if(Node == NULL) return NULL;
    if(Node->Numofchild == 1){
        if(field == NULL){
            char* name = Node->Child->data.Charval;
            if(findHashtable(name) != NULL){
                SemanticError(3,Node->Numofline,"redefined variable");
                return NULL;
            }
            FieldList newfield = (FieldList) malloc (sizeof(struct FieldList_));
            newfield->name = name;
            newfield->tail = NULL;
            newfield->type = type;
            var_id ++;
            newfield->id = var_id;
            newfield->isarg = false;
            insertHashtable(newfield);
        }
        else{
            char* name = Node->Child->data.Charval;
            if(field->type->kind == STRUCTURE && field->type->u.structure == NULL){
                FieldList newfield = (FieldList) malloc (sizeof(struct FieldList_));
                newfield->name = name;
                newfield->tail = NULL;
                newfield->type = type;
                field->type->u.structure = newfield;
            }
            else if(field->type->kind == STRUCTURE && field->type->u.structure != NULL){
                if(StructhasName(field,name) == true){
                    SemanticError(15,Node->Numofline,"assignop wrong in a struct");
                    return NULL;
                }
                else{
                    FieldList tempfield = field->type->u.structure;
                    while(tempfield->tail != NULL){
                        
                        tempfield = tempfield->tail;
                    }
                    FieldList newfield = (FieldList) malloc (sizeof(struct FieldList_));
                    newfield->name = name;
                    newfield->tail = NULL;
                    newfield->type = type;
                    tempfield->tail = newfield;
                }
            }
            else if(field->type->kind == FUNCTION && field->type->u.function->next == NULL){
                FieldList newfield = (FieldList) malloc (sizeof(struct FieldList_));
                newfield->name = name;
                newfield->tail = NULL;
                newfield->type = type;
                field->type->u.function->next = newfield;
                field->type->u.function->numofparam++;
                FieldList tempfield = (FieldList) malloc (sizeof(struct FieldList_));
                if(findHashtable(name) != NULL){
                    SemanticError(3,Node->Numofline,"redefined variable");
                    return NULL;
                }
                tempfield->name = name;
                tempfield->tail = NULL;
                tempfield->type = type;
                var_id++;
                tempfield->id = var_id;
                tempfield->isarg = true;
                insertHashtable(tempfield);
            }
            else{
                FieldList tempfield = field->type->u.function->next;
                while(tempfield->tail != NULL){
                    tempfield = tempfield->tail;
                }
                FieldList newfield = (FieldList) malloc (sizeof(struct FieldList_));
                newfield->name = name;
                newfield->tail = NULL;
                newfield->type = type;
                tempfield->tail = newfield;
                field->type->u.function->numofparam++;
                if(findHashtable(name) != NULL){
                    SemanticError(3,Node->Numofline,"redefined variable");
                    return NULL;
                }
                FieldList tempfield1 = (FieldList) malloc (sizeof(struct FieldList_));
                tempfield1->name = name;
                tempfield1->tail = NULL;
                tempfield1->type = type;
                var_id++;
                tempfield1->id = var_id;
                tempfield1->isarg = true;
                insertHashtable(tempfield1);
            }
        }
        return Node->Child->data.Charval;
    }
    else if(Node->Numofchild == 4){
        Type newtype = (Type) malloc (sizeof(struct Type_));
        newtype->kind = ARRAY;
       
        newtype->u.array.elem = type;
        newtype->u.array.size = Node->Child->Sibling->Sibling->data.Intval;
        return UnitVarDec(Node->Child,newtype,field);
    }
    else{
        printf("wrong UnitVarDec\n");
    }
}

void UnitFunDec(struct TreeNode* Node,Type type){
    if(Node == NULL) return;
    char* name = Node->Child->data.Charval;
    FieldList tempfield = findHashtable(name);
    bool isredefined = false;
    if(tempfield != NULL && tempfield->type->kind == FUNCTION){
        SemanticError(4,Node->Numofline,"redefined function"); 
        isredefined = true;          
    }
        if(Node->Numofchild == 4){
            FieldList newfield = (FieldList) malloc (sizeof(struct FieldList_));
            FuncList func = (FuncList) malloc (sizeof(struct FuncList_));
            func->numofparam = 0;
            func->ret = type;
            func->next = NULL;
            
            newfield->name = name;
            newfield->tail = NULL;
            newfield->type = (Type) malloc (sizeof(struct Type_));
            newfield->type->kind = FUNCTION;
            
            newfield->type->u.function = func;
            UnitVarList(Node->Child->Sibling->Sibling,newfield);
            if(isredefined == false){
                insertHashtable(newfield);
            }
        }
        else if(Node->Numofchild == 3){
            
            FieldList newfield = (FieldList) malloc (sizeof(struct FieldList_));
            FuncList func = (FuncList) malloc (sizeof(struct FuncList_));
            func->numofparam = 0;
            func->ret = type;
            func->next = NULL;
            
            newfield->name = name;
            newfield->tail = NULL;
            newfield->type = (Type) malloc (sizeof(struct Type_));
            newfield->type->kind = FUNCTION;
            
            newfield->type->u.function = func;
            if(isredefined == false){
                insertHashtable(newfield);
            }
        }
        else{
            printf("wrong UnitFunDec\n");
        }
}

void UnitVarList(struct TreeNode* Node,FieldList field){
    if(Node == NULL) return;
    if(Node->Numofchild == 3){
        UnitParamDec(Node->Child,field);
        UnitVarList(Node->Child->Sibling->Sibling,field);
    }
    else if(Node->Numofchild == 1){
        UnitParamDec(Node->Child,field);
    }
    else{
        printf("wrong UnitVarList\n");
    }
}

void UnitParamDec(struct TreeNode* Node,FieldList field){
    if(Node == NULL) return;
    if (Node->Numofchild == 2){
        Type type = UnitSpecifier(Node->Child);
        UnitVarDec(Node->Child->Sibling,type,field);
    }
    else{
        printf("wrong UnitParamDec\n");
    }
}

void UnitDefList(struct TreeNode* Node, FieldList field){
    if(Node == NULL) return;
    if(Node->Numofchild == 0) return;
    if(Node->Numofchild == 2){
        UnitDef(Node->Child, field);
        UnitDefList(Node->Child->Sibling, field);
    }
    else{
        printf("wrong UnitDefList\n");
    }
}

void UnitDef(struct TreeNode* Node, FieldList field){
    if(Node == NULL) return;
    if(Node->Numofchild == 3){
        Type type = UnitSpecifier(Node->Child);
        UnitDecList(Node->Child->Sibling,type,field);
    }
    else{
        printf("wrong UnitDef\n");
    }
}

void UnitDecList(struct TreeNode* Node,Type type, FieldList field){
    if(Node == NULL) return;
    if(Node->Numofchild == 1){
        UnitDec(Node->Child,type,field);
    }
    else if(Node->Numofchild == 3){
        UnitDec(Node->Child,type,field);
        UnitDecList(Node->Child->Sibling->Sibling,type,field);
    }
    else{
        printf("wrong UnitDecList\n");
    }
}

void UnitDec(struct TreeNode* Node,Type type,FieldList field){
    if(Node == NULL) return;
    if(Node->Numofchild == 1){
        UnitVarDec(Node->Child,type,field);
    }
    else if(Node->Numofchild == 3){
        char* name = UnitVarDec(Node->Child,type,field);
        FieldList dec_field = findHashtable(name);
        
        if(field != NULL){
            SemanticError(15,Node->Child->Numofline,"assignop wrong in a struct");
        }
        Type newtype = UnitExp(Node->Child->Sibling->Sibling);
        if(EqualType(dec_field->type,newtype) == false){
            SemanticError(5,Node->Child->Numofline,"assignop left and right not matched");
        }
        
    }
    else{
        printf("wrong UnitDec\n");
    }
}

void UnitCompSt(struct TreeNode* Node,Type type){
    if(Node == NULL) return;
    if(Node->Numofchild == 4){
        UnitDefList(Node->Child->Sibling, NULL);
        UnitStmtList(Node->Child->Sibling->Sibling,type);
    }
    else{
        printf("wrong UnitCompSt");
    }
}

void UnitStmtList(struct TreeNode* Node,Type type){
    if(Node == NULL) return;
    if(Node->Numofchild == 0) return;
    if(Node->Numofchild == 2){
        UnitStmt(Node->Child,type);
        UnitStmtList(Node->Child->Sibling,type);
    }
    else{
        printf("wrong UnitStmtList");
    }
}

void UnitStmt(struct TreeNode* Node,Type type){
    if(Node == NULL) return;
    if(Node->Numofchild == 2){
        Type newtype = UnitExp(Node->Child);
    }
    else if(Node->Numofchild == 1){
        UnitCompSt(Node->Child,type);
    }
    else if(Node->Numofchild == 3){
        Type newtype = UnitExp(Node->Child->Sibling);
        if(EqualType(type,newtype) == false){
            SemanticError(8,Node->Numofline,"return wrong");
        }
    }
    else if(Node->Numofchild == 5){
        if(strcmp(Node->Child->Name,"IF") == 0){
            Type newtype = UnitExp(Node->Child->Sibling->Sibling);
            UnitStmt(Node->Child->Sibling->Sibling->Sibling->Sibling,type);

        }
        else if(strcmp(Node->Child->Name,"WHILE") == 0){
            Type newtype = UnitExp(Node->Child->Sibling->Sibling);
            UnitStmt(Node->Child->Sibling->Sibling->Sibling->Sibling,type);
        }
    }
    else if(Node->Numofchild == 7){
        Type newtype = UnitExp(Node->Child->Sibling->Sibling);
        UnitStmt(Node->Child->Sibling->Sibling->Sibling->Sibling,type);
        UnitStmt(Node->Child->Sibling->Sibling->Sibling->Sibling->Sibling->Sibling,type);
    }
    else{
        printf("wrong UnitStmt\n");
    }
}

Type UnitExp(struct TreeNode* Node){
    if(Node == NULL) return NULL;
    if(Node->Numofchild == 3){
        if(strcmp(Node->Child->Sibling->Name,"ASSIGNOP") == 0){
            Type lefttype = UnitExp(Node->Child);
            Type righttype = UnitExp(Node->Child->Sibling->Sibling);
            if (EqualType(lefttype,righttype) == false){
                SemanticError(5,Node->Numofline,"assignop left and right not matched");
            }
            if((Node->Child->Numofchild == 1 && strcmp(Node->Child->Child->Name,"ID") == 0) || (Node->Child->Numofchild == 4 && strcmp(Node->Child->Child->Sibling->Name,"LB") == 0) || (Node->Child->Numofchild == 3 && strcmp(Node->Child->Child->Sibling->Name,"DOT") == 0)){

            }
            else{
                SemanticError(6,Node->Numofline,"right value at left of assignop");
            }
            if(lefttype != NULL) return lefttype;
            else return righttype;
        }
        else if(strcmp(Node->Child->Name,"LP") == 0){
            Type newtype = UnitExp(Node->Child->Sibling);
            return newtype;
        }
        else if(strcmp(Node->Child->Name,"ID") == 0){
            char* name = Node->Child->data.Charval;
            FieldList field = findHashtable(name);
            if(field == NULL){
                SemanticError(2,Node->Numofline,"use undefined function");
                return NULL;
            }
            else if(field->type->kind != FUNCTION){
                SemanticError(11, Node->Numofline,"not a func but use ()");
                return NULL;
            }
            else if(field->type->kind == FUNCTION && field->type->u.function->numofparam != 0){
                SemanticError(9,Node->Numofline,"unmatched function args");
                return field->type->u.function->ret;
            }
            else{
                return field->type->u.function->ret;
            }
        }
        else if(strcmp(Node->Child->Sibling->Name,"DOT") == 0){
            Type type = UnitExp(Node->Child);
            if(type !=NULL){
                if(type->kind != STRUCTURE){
                    SemanticError(13,Node->Numofline,"illegal use of .");
                    return NULL;
                }
                else{
                    FieldList tempfield = type->u.structure;
                    if(StructhasName(tempfield,Node->Child->Sibling->Sibling->data.Charval) == false){
                        SemanticError(14,Node->Numofline,"undefined name in struct");
                        return NULL;
                    }
                    else{
                        return FindStructMember(tempfield,Node->Child->Sibling->Sibling->data.Charval)->type;
                    }
                }
            }
            else{
                return NULL;
            }
        }
        else if(strcmp(Node->Child->Sibling->Name,"AND") == 0 || strcmp(Node->Child->Sibling->Name,"OR") == 0 || strcmp(Node->Child->Sibling->Name,"RELOP") == 0){
            Type lefttype = UnitExp(Node->Child);
            Type righttype = UnitExp(Node->Child->Sibling->Sibling);
            if(lefttype!= NULL && righttype!=NULL){
                if(!(lefttype->kind == BASIC && lefttype->u.basic == 0 && righttype->kind == BASIC && righttype->u.basic == 0)){
                    printf("nice\n");
                    SemanticError(7,Node->Numofline,"unmatched operator");
                }
            }
            else{
                SemanticError(7,Node->Numofline,"unmatched operator");
            }
            Type type = (Type) malloc(sizeof(struct Type_));
            type->kind = BASIC;
            
            type->u.basic = 0;
            return type;
        }
        else{
            Type lefttype = UnitExp(Node->Child);
            Type righttype = UnitExp(Node->Child->Sibling->Sibling);
            if(lefttype!= NULL && righttype!=NULL){
                if(lefttype->kind != BASIC || righttype->kind != BASIC){
                    SemanticError(7,Node->Numofline,"unmatched operator");
                }
                else{
                    if(EqualType(lefttype,righttype) == false){
                        SemanticError(7,Node->Numofline,"unmatched operator");
                    }
                }
            }
            else{
                SemanticError(7,Node->Numofline,"unmatched operator");
            }
            if(lefttype != NULL) return lefttype;
            else return righttype;
        }
    }
    else if(Node->Numofchild == 2){
        if(strcmp(Node->Child->Name,"MINUS") == 0){
            Type type = UnitExp(Node->Child->Sibling);
            if(type!= NULL){
                if(type->kind != BASIC){
                    SemanticError(7,Node->Numofline,"unmatched operator");
                }
            }
            return type;
        }
        else if(strcmp(Node->Child->Name,"NOT") == 0){
            Type type = UnitExp(Node->Child->Sibling);
            if(type!=NULL){
                if(!(type->kind == BASIC && type->u.basic == 0)){
                    SemanticError(7,Node->Numofline,"unmatched operator");
                }
            }
            Type newtype = (Type) malloc(sizeof(struct Type_));
            newtype->kind = BASIC;
            newtype->u.basic = 0;
            return newtype;
        }
    }
    else if(Node->Numofchild == 4){
        if(strcmp(Node->Child->Sibling->Name,"LP") == 0){
            char* name = Node->Child->data.Charval;
            FieldList field = findHashtable(name);
            if(field == NULL){
                SemanticError(2,Node->Numofline,"use undefined function");
                return NULL;
            }
            else if(field->type->kind != FUNCTION){
                SemanticError(11, Node->Numofline,"not a func but use ()");
                return NULL;
            }
            else if(field->type->kind == FUNCTION){
                //printf("good\n");
                //printf("%s\n",Node->Child->Sibling->Sibling->Child->Child->data.Charval);
                UnitArgs(Node->Child->Sibling->Sibling,field->type->u.function->next,field->type->u.function->numofparam);
                //printf("return\n");
                return field->type->u.function->ret;
            }
            else{
                return field->type->u.function->ret;
            }
        }
        else if(strcmp(Node->Child->Sibling->Name,"LB") == 0){
            Type type1 = UnitExp(Node->Child);
            Type type2 = UnitExp(Node->Child->Sibling->Sibling);
            if(type1 == NULL) return NULL;
            if(type1->kind != ARRAY){
                SemanticError(10,Node->Numofline,"not a array");
                if(type2 == NULL){
                    SemanticError(12,Node->Numofline,"between [] is not an integer");
                }
                else if(!(type2->kind == BASIC && type2->u.basic == 0)){
                    SemanticError(12,Node->Numofline,"between [] is not an integer");
                }
                return NULL;
            }
            if(type2 == NULL){
                SemanticError(12,Node->Numofline,"between [] is not an integer");
            }
            else if(!(type2->kind == BASIC && type2->u.basic == 0)){
                SemanticError(12,Node->Numofline,"between [] is not an integer");
            }
            return type1->u.array.elem;
        }
    }
    else if(Node->Numofchild == 1){
        if(strcmp(Node->Child->Name,"ID") == 0){
            char* name = Node->Child->data.Charval;
            FieldList field = findHashtable(name);
            if(field == NULL){
                SemanticError(1,Node->Numofline,"undefined variable");
                return NULL;
            }
            else if(field->type->kind == FUNCTION){
                SemanticError(1,Node->Numofline,"undefined variable");
                return NULL;
            }
            else{
                return field->type;
            }
        }
        else if(strcmp(Node->Child->Name,"INT") == 0){
            Type type = (Type) malloc (sizeof(struct Type_));
            type->kind = BASIC;
            type->u.basic = 0;
            return type;
        }
        else if(strcmp(Node->Child->Name,"FLOAT") == 0){
            Type type = (Type) malloc (sizeof(struct Type_));
            type->kind = BASIC;
            type->u.basic = 1;
            return type;
        }
    }
    else{
        printf("wrong UnitExp\n");
        return NULL;
    }
}

void UnitArgs(struct TreeNode* Node, FieldList field,int num){
    if(Node == NULL) return;
    if(Node->Numofchild == 1){
        if(num != 1){
            SemanticError(9,Node->Numofline,"unmatched function args");
        }
        else{
            Type type = UnitExp(Node->Child);
            if(EqualType(type,field->type) == false){
                SemanticError(9,Node->Numofline,"unmatched function args");
            }
        }
    }
    else if(Node->Numofchild == 3){
        //printf("here\n");
        Type type = UnitExp(Node->Child);
        //printf("here now\n");
        if(field == NULL || EqualType(type,field->type) == false){
            SemanticError(9,Node->Numofline,"unmatched function args");
            return;
        }
        //if(field == NULL) return;
        
        UnitArgs(Node->Child->Sibling->Sibling,field->tail,num-1);
    }
    else{
        printf("wrong UnitArgs\n");
    }
}