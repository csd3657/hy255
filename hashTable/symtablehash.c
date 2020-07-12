#include "SymTable.h"
#define HASH_MULTIPLIER 65599
#define HASH_SIZE 509

typedef struct SymTable_{
    char *key;
    void *value;
    struct SymTable_ * next;
}*Sym_node;

struct SymTable{
    unsigned int length;
    Sym_node HashTable[HASH_SIZE];
};


int SymTable_hash(const char *pcKey){
    size_t ui;
    unsigned int uiHash = 0U;
    for (ui = 0U; pcKey[ui] != '\0'; ui++)
        uiHash = uiHash * HASH_MULTIPLIER + pcKey[ui];

    return (int)(uiHash % HASH_SIZE);
}

SymTable_T SymTable_new(void){
    int i;
    SymTable_T myHashTable;
    struct SymTable_ *temp;
    myHashTable = malloc(sizeof(struct SymTable));
    assert(myHashTable != NULL);

    for(i = 0; i < HASH_SIZE; i++){
        temp = malloc(sizeof(struct SymTable_));
        temp->key = NULL;
        temp->value = NULL;
        temp->next = NULL;
        myHashTable->HashTable[i] = temp;
    }
    myHashTable->length = 0;
    return myHashTable;
}

void SymTable_free(SymTable_T oSymTable){
    int i;
    assert(oSymTable != NULL);
    for(i = 0; i < HASH_SIZE; i++){
        if(oSymTable->HashTable[i]->key != NULL){
            
            free(oSymTable->HashTable[i]->key);
            free(oSymTable->HashTable[i]);
            
            oSymTable->length--;
        }
    }
    free(oSymTable);
    
}

unsigned int SymTable_getLength(SymTable_T oSymTable){
    return oSymTable->length;
}

int SymTable_contains(SymTable_T oSymTable, const char *pcKey){
    int i;
    SymTable_T tempSymTable = oSymTable;
    assert(oSymTable != NULL);
    assert(pcKey != NULL);
    i = SymTable_hash(pcKey);
    if(tempSymTable->HashTable[i]->key != NULL){
        return 1;
    }
    return 0;
}

int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue){
    
    int i;
    assert(oSymTable != NULL);
    assert(pcKey != NULL);
    i = SymTable_hash(pcKey);
    if(SymTable_contains(oSymTable, pcKey)){
        return 0;
    }
    oSymTable->HashTable[i]->key = malloc((strlen(pcKey) + 1)*sizeof(char));
    strcpy(oSymTable->HashTable[i]->key, (char*)pcKey);
    oSymTable->HashTable[i]->value = (void*)pvValue;
    oSymTable->length++;
    
    return 1;
}

int SymTable_remove(SymTable_T oSymTable, const char *pcKey){
    int i;
    assert(oSymTable != NULL);
    assert(pcKey != NULL);
    i = SymTable_hash(pcKey);
    if(!SymTable_contains(oSymTable, pcKey)){
        return 0;
    }
    free(oSymTable->HashTable[i]->key);
    free(oSymTable->HashTable[i]);
    
    oSymTable->HashTable[i]->key = NULL;
    oSymTable->length--;
    return 1;
}

void *SymTable_get(SymTable_T oSymTable, const char *pcKey){
    unsigned int i;
    assert(oSymTable != NULL);
    assert(pcKey != NULL);
    i = SymTable_hash(pcKey);
    if(oSymTable->HashTable[i]->key == pcKey){
        return oSymTable->HashTable[i]->value;
    }
    return NULL;
}
void SymTable_map(SymTable_T oSymTable, void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra), const void *pvExtra){
    int i;
    assert(oSymTable != NULL);
    
    for(i = 0; i < HASH_SIZE; i++){
        (*pfApply)((char*)(oSymTable->HashTable[i]->key), (void*)(oSymTable->HashTable[i]->value), (void *)pvExtra);
    }
}

