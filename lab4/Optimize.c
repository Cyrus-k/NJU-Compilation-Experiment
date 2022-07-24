#include "Optimize.h"

void OptimizeArray(){
    for(int i=pointer-1;i>=0;i--){
        InterCodeList temp = head;
        InterCodeList need_to_delete;
        bool isfind = false;
        while(temp->next != NULL){
            if(temp->next->code->codekind == IC_ASSIGN){
                if(temp->next->code->u.assign.left->kind == TEMP && temp->next->code->u.assign.left->u.temp_id.temp == arraypair[i]->need_to_replace->u.temp_id.temp){
                    need_to_delete = temp->next;
                    isfind = true;
                }
            }
            if(isfind == true){
                if(temp->next->code->codekind == IC_ASSIGN){
                    if(temp->next->code->u.assign.right->kind == TEMP && temp->next->code->u.assign.right->u.temp_id.temp == arraypair[i]->need_to_replace->u.temp_id.temp){
                        temp->next->code->u.assign.right = arraypair[i]->replace;
                    }
                    else if(temp->next->code->u.assign.right->kind == DEREF && temp->next->code->u.assign.right->u.addr->kind == TEMP && temp->next->code->u.assign.right->u.addr->u.temp_id.temp == arraypair[i]->need_to_replace->u.temp_id.temp){
                        if(arraypair[i]->replace->kind == REF){
                            temp->next->code->u.assign.right = arraypair[i]->replace->u.addr;
                        }
                        else
                            temp->next->code->u.assign.right->u.addr = arraypair[i]->replace;
                    }
                    else if(temp->next->code->u.assign.left->kind == DEREF && temp->next->code->u.assign.left->u.addr->kind == TEMP && temp->next->code->u.assign.left->u.addr->u.temp_id.temp == arraypair[i]->need_to_replace->u.temp_id.temp){
                        if(arraypair[i]->replace->kind == REF){
                            temp->next->code->u.assign.left = arraypair[i]->replace->u.addr;
                        }
                        else
                            temp->next->code->u.assign.left->u.addr = arraypair[i]->replace;
                    }
                }
                else if(temp->next->code->codekind == IC_ADD || temp->next->code->codekind == IC_MUL|| temp->next->code->codekind == IC_SUB || temp->next->code->codekind == IC_DIV){
                    if(temp->next->code->u.binop.op1->kind == TEMP && temp->next->code->u.binop.op1->u.temp_id.temp == arraypair[i]->need_to_replace->u.temp_id.temp){
                        temp->next->code->u.binop.op1 = arraypair[i]->replace;
                    }
                    else if(temp->next->code->u.binop.op1->kind == DEREF && temp->next->code->u.binop.op1->u.addr->u.temp_id.temp == arraypair[i]->need_to_replace->u.temp_id.temp){
                        if(arraypair[i]->replace->kind == REF){
                            temp->next->code->u.binop.op1 = arraypair[i]->replace->u.addr;
                        }
                        else
                            temp->next->code->u.binop.op1->u.addr = arraypair[i]->replace;
                    }
                    if(temp->next->code->u.binop.op2->kind == TEMP && temp->next->code->u.binop.op2->u.temp_id.temp == arraypair[i]->need_to_replace->u.temp_id.temp){
                        temp->next->code->u.binop.op2 = arraypair[i]->replace;
                    }
                    else if(temp->next->code->u.binop.op2->kind == DEREF && temp->next->code->u.binop.op2->u.addr->u.temp_id.temp == arraypair[i]->need_to_replace->u.temp_id.temp){
                        if(arraypair[i]->replace->kind == REF){
                            temp->next->code->u.binop.op2 = arraypair[i]->replace->u.addr;
                        }
                        else
                            temp->next->code->u.binop.op2->u.addr = arraypair[i]->replace;
                    }
                }
                else if(temp->next->code->codekind == IC_ARG || temp->next->code->codekind == IC_RETURN || temp->next->code->codekind == IC_WRITE){
                    if(temp->next->code->u.unaryop.op->kind == TEMP && temp->next->code->u.unaryop.op->u.temp_id.temp == arraypair[i]->need_to_replace->u.temp_id.temp){
                        temp->next->code->u.unaryop.op = arraypair[i]->replace;
                    }
                    else if(temp->next->code->u.unaryop.op->kind == DEREF && temp->next->code->u.unaryop.op->u.addr->u.temp_id.temp == arraypair[i]->need_to_replace->u.temp_id.temp){
                        if(arraypair[i]->replace->kind == REF){
                            temp->next->code->u.unaryop.op = arraypair[i]->replace->u.addr;
                        }
                        else
                            temp->next->code->u.unaryop.op->u.addr = arraypair[i]->replace;
                    }
                }
                else if(temp->next->code->codekind == IC_IF_GOTO){
                    if(temp->next->code->u.ifgoto.x->kind == TEMP && temp->next->code->u.ifgoto.x->u.temp_id.temp == arraypair[i]->need_to_replace->u.temp_id.temp){
                        temp->next->code->u.ifgoto.x = arraypair[i]->replace;
                    }
                    else if(temp->next->code->u.ifgoto.x->kind == DEREF && temp->next->code->u.ifgoto.x->u.addr->u.temp_id.temp == arraypair[i]->need_to_replace->u.temp_id.temp){
                        if(arraypair[i]->replace->kind == REF){
                            temp->next->code->u.ifgoto.x = arraypair[i]->replace->u.addr;
                        }
                        else
                            temp->next->code->u.ifgoto.x->u.addr = arraypair[i]->replace;
                    }
                    if(temp->next->code->u.ifgoto.y->kind == TEMP && temp->next->code->u.ifgoto.y->u.temp_id.temp == arraypair[i]->need_to_replace->u.temp_id.temp){
                        temp->next->code->u.ifgoto.y = arraypair[i]->replace;
                    }
                    else if(temp->next->code->u.ifgoto.y->kind == DEREF && temp->next->code->u.ifgoto.y->u.addr->u.temp_id.temp == arraypair[i]->need_to_replace->u.temp_id.temp){
                        if(arraypair[i]->replace->kind == REF){
                            temp->next->code->u.ifgoto.y = arraypair[i]->replace->u.addr;
                        }
                        else
                            temp->next->code->u.ifgoto.y->u.addr = arraypair[i]->replace;
                    }
                }
            }
            temp = temp->next;
        }
        delete_node(need_to_delete);
    }
}

void OptimizeCal(){
    InterCodeList temp = head;
    while(temp->next != NULL){
        InterCode curnode = temp->next->code;
        if((curnode->codekind == IC_ADD || curnode->codekind == IC_SUB || curnode->codekind == IC_MUL || curnode->codekind == IC_DIV) && curnode->u.binop.result->kind == TEMP){
            InterCode nextnode = temp->next->next->code;
            if(nextnode->codekind == IC_ASSIGN && nextnode->u.assign.left->kind == VARIABLE && nextnode->u.assign.right->kind == TEMP && nextnode->u.assign.right->u.temp_id.temp == curnode->u.binop.result->u.temp_id.temp){
                curnode->u.binop.result = nextnode->u.assign.left;
                delete_node(temp->next->next);
            }
        }
        temp = temp->next;
    }
}

void Optimize(){
    OptimizeArray();
    OptimizeCal();
}