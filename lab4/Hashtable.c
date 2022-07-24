#include "Hashtable.h"

void initHashtable(){
    for(int i=0;i<=HASH_SIZE;i++){
        Hashtable[i] = NULL;
    }
}

void insertHashtable(FieldList symbol)
{
    unsigned int hashnum = hash_pjw(symbol->name);
    if(Hashtable[hashnum] == NULL){
        HashNode node = (HashNode) malloc (sizeof(struct HashNode_));
        node->data = symbol;
        node->next = NULL;
        Hashtable[hashnum] = node;
    }
    else{
        HashNode node = (HashNode) malloc (sizeof(struct HashNode_));
        node->data = symbol;
        node->next = Hashtable[hashnum];
        Hashtable[hashnum] = node;
    }
}

FieldList findHashtable(char* name)
{
    unsigned int hashnum = hash_pjw(name);
    HashNode node = Hashtable[hashnum];
    while(node != NULL){
        if(strcmp(node->data->name,name) == 0){
            return node->data;
        }
        else{
            node = node->next;
        }
    }
    return NULL;
}

unsigned int hash_pjw(char* name)
{
    unsigned int val = 0, i;
    for (; *name; ++name)
    {
        val = (val << 2) + *name;
        if (i = val & ~HASH_SIZE) val = (val ^ (i >> 12)) & HASH_SIZE;
    }
    return val;
}