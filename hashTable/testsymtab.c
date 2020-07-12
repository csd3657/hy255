#include "SymTable.h"

int main(){
    SymTable_T mySymTab = SymTable_new();

    if(SymTable_put(mySymTab, "aa", (int*)1))
        printf("\n1Length is : %d\n", SymTable_getLength(mySymTab));
    if(SymTable_put(mySymTab, "ab", (int*)2))
        printf("\n2Length is : %d\n", SymTable_getLength(mySymTab));
    if(SymTable_put(mySymTab, "a1a", (int*)1))
        printf("\n3Length is : %d\n", SymTable_getLength(mySymTab));
    if(SymTable_put(mySymTab, "a1b", (int*)2))
        printf("\n4Length is : %d\n", SymTable_getLength(mySymTab));
    if(SymTable_put(mySymTab, "aa", (int*)3))
        printf("\n5Length is : %d\n", SymTable_getLength(mySymTab));
    else
        printf("\nYPARXEI IDIO");
    
    if(SymTable_contains(mySymTab, "a1a"))
        printf("\n1Contains\n");
    else
        printf("\n1NOTContains\n");
    
    if(SymTable_remove(mySymTab, "a1a"))
        printf("\n NOW Length is : %u\n", SymTable_getLength(mySymTab));
    if(SymTable_contains(mySymTab, "a1a"))
        printf("\nContains\n");
    else
        printf("\nNOTContains\n");

    printf("\nBEFORE FREE\n");
    SymTable_free(mySymTab);
    printf("\nWELL DONE!\n");
    return 0;
    
}