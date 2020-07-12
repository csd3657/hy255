#include "SymTable.h"

int FirstInsertion = 1;

struct SymTable{
    char * key;
    void * value;
    struct SymTable * next;
};

void print_SymTable(SymTable_T oSymTable){
    SymTable_T temp = oSymTable;
    while(temp != NULL){
        printf("\n %s \n",  temp->key);
        temp = temp->next;
    }
}

SymTable_T SymTable_new(void){
    SymTable_T newSymTable_T;
    newSymTable_T = malloc(sizeof(struct SymTable));
    newSymTable_T->next = NULL;
    
    return newSymTable_T;
}

void SymTable_free(SymTable_T oSymTable){
    SymTable_T next;

    while(oSymTable != NULL){
        next = oSymTable->next;
        free(oSymTable->key);
        free(oSymTable);
        
        oSymTable = next;
    }
}

unsigned int SymTable_getLength(SymTable_T oSymTable){
    SymTable_T temp = oSymTable;
    unsigned int length = 0;
    assert(oSymTable != NULL);
    if(FirstInsertion){
        return 0;
    }
    while(temp != NULL){
        printf("\nLen: %s", temp->key);
       /* printf("\n %s - Q \n", temp->key);*/
        length++;
        
        temp = temp->next;
    }
    return length;
}

int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue){
    SymTable_T head = oSymTable;
    SymTable_T prev = head;
    SymTable_T new;
    assert(oSymTable != NULL);
    assert(pcKey != NULL);
    if(FirstInsertion){
        oSymTable->key = malloc(sizeof(char)*(strlen(pcKey)+1));
        strcpy(oSymTable->key, (char *)pcKey);
        oSymTable->value = (void *)pvValue;
        FirstInsertion = 0;
        return 1;
    }
    while(oSymTable != NULL){
        if(strcmp(pcKey, oSymTable->key)==0){
            /*an vreis na yparxei idio key return*/
            return 0;
        }
        prev = oSymTable;
        oSymTable = oSymTable->next;
    }
    /*eisagwgi new key sto telos tis listas*/
    new = SymTable_new();
    new->key = malloc(sizeof(char)*(strlen(pcKey)+1)); /* +1 for '\0' */
    strcpy(new->key, (char *)pcKey);
    new->value = (void *)pvValue;
    new->next = NULL;
    prev->next = new;  
    oSymTable = head;
    
    return 1;
}

int SymTable_remove(SymTable_T oSymTable, const char *pcKey){
    SymTable_T head = oSymTable;
    SymTable_T prev = head;
    SymTable_T tempNext = head->next;
    assert(oSymTable != NULL);
    assert(pcKey != NULL);
    while(oSymTable != NULL){
        if(strcmp(pcKey, oSymTable->key)==0){
            if(prev == head){
               head = head->next;
               free(oSymTable->key);
               free(oSymTable);
               oSymTable = tempNext;
               printf("%s",oSymTable->key);
                return 1;
            }
            free(oSymTable->key);
            free(oSymTable);
            oSymTable = prev;
            oSymTable->next = tempNext;
            oSymTable = head;
            return 1;
        }
        prev = oSymTable;
        oSymTable = oSymTable->next;
        if(tempNext != NULL && tempNext->next != NULL){
            tempNext = tempNext->next;
        }else{
            tempNext = NULL;
        }
    }
    oSymTable = head;
    return 0;
}

int SymTable_contains(SymTable_T oSymTable, const char *pcKey){
    SymTable_T temp = oSymTable;
    assert(oSymTable != NULL);
    assert(pcKey != NULL);
    while(temp != NULL && temp->key != NULL){
        if(strcmp(pcKey, temp->key)==0){
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

void *SymTable_get(SymTable_T oSymTable, const char *pcKey){
    SymTable_T temp = oSymTable;
    assert(temp != NULL);
    assert(pcKey != NULL);

    while(temp != NULL){
        if(strcmp(pcKey, temp->key)==0){
            return temp->value;
        }
        temp = temp->next;
    }
    return NULL;
}

void SymTable_map(SymTable_T oSymTable, void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra), const void *pvExtra){

    SymTable_T temp = oSymTable;
    assert(temp != NULL);
    assert(pfApply != NULL);

    while (temp != NULL){
        (*pfApply)((char*)(temp->key), (void*)(temp->value), (void *)pvExtra);
        temp = temp->next;
    }
}