
/*CSD3657*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "grid.h"

/*returns the values of i,j.*/
int grid_read_value(Grid_T g, int i, int j){
    assert(i<10 && i>=0 && j<10 && j>=0);
    return g.elements[i][j].value;
}

/* updates the values of i,j to n */
void grid_update_value ( Grid_T *g, int i, int j, int n){
    assert(g);
    assert(n>=0 && n<10);
    g->elements[i][j].value = n;
    return;
}

/* set to 0 the choice n for elt i,j. */
void grid_clear_choice(Grid_T *g, int i, int j, int n){
    assert(g);
    assert(n>=0 && n<10);
    assert(i<10 && i>=0 && j<10 && j>=0);
    g->elements[i][j].choices.num[n] = 0;
    return;
}

/* returns true if the choice n for elt i,j is v alid. */
int grid_choice_is_valid(Grid_T g, int i, int j, int n){
    assert(n>=0 && n<10);
    assert(i<10 && i>=0 && j<10 && j>=0);
    return (g.elements[i][j].choices.num[n]);
}

/* set to 1 choice n for elt i,j. */
void grid_set_choice(Grid_T *g, int i, int j, int n){
    assert(g);
    assert(n>=0 && n<10);
    assert(i<10 && i>=0 && j<10 && j>=0);
    g->elements[i][j].choices.num[n] = 1;
    return;
}


/* returns the count for elt i,j. */
int grid_read_count(Grid_T g, int i, int j){
    assert(i<10 && i>=0 && j<10 && j>=0);
    return (g.elements[i][j].choices.possible_choices);
}

/* returns the value of flag for g. */
int grid_read_unique(Grid_T g){
    return (g.is_unique);
}

/* Removes the n from choices of elt i,j and counts if n is
   valid choice for elt i,j. */
void grid_remove_choice(Grid_T *g, int i, int j, int n){
    assert(g);
    assert(n>=0 && n<10);
    assert(i<10 && i>=0 && j<10 && j>=0);
    if (grid_choice_is_valid(*g,i,j,n)){
        g->elements[i][j].choices.num[n] = 0;
        g->elements[i][j].choices.possible_choices--;
    }
}



/* sets the value of flag --> 1*/
void grid_set_unique(Grid_T *g){
    assert(g);
    g->is_unique = 1;
    return;
}

/* sets the value of flag --> 0.*/
void grid_clear_unique(Grid_T *g){
    assert(g);
    g->is_unique = 0;
    return;
}


/* sets the count --> 0 for elt i, j. */
void grid_clear_count(Grid_T *g, int i, int j){
    assert(g);
    assert(i<10 && i>=0 && j<10 && j>=0);
    g->elements[i][j].choices.possible_choices = 0;
}

/* sets the count --> 9 for elt i, j. */
void grid_set_count(Grid_T *g, int i, int j){
    assert(g);
    assert(i<10 && i>=0 && j<10 && j>=0);
    g->elements[i][j].choices.possible_choices = 9;
    return;
}