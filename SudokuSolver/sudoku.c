
/*csd3657*/
#include <assert.h>
#include "sudoku.h"
#include <ctype.h>
#define BOX_SIZE 3
#define SIZE 9

/* check the puzzle for error and returs
 the value true or the value false */
int has_errors(Grid_T g){
    int i, j, k, l, num;
    int flag = 0;
    for (i = 0; i<SIZE; i++)
        for (j = 0; j<SIZE; j++){
            num = grid_read_value(g,i,j);
            if (num == 0)
                continue;
            for (k = 0; k<SIZE; k++){
                
                if (num == grid_read_value(g, i, k) && k!=j) flag = 1; /* rows checking */
                
                if (num == grid_read_value(g, k, j) && k!=i) flag = 1;/* columns checking */
            }
          /*   check puzzle (3*3)  */
            for (k = (i/BOX_SIZE)*BOX_SIZE; k < (i/BOX_SIZE)*BOX_SIZE+BOX_SIZE; k++)
                for (l = (j/BOX_SIZE)*BOX_SIZE; l < (j/BOX_SIZE)*BOX_SIZE+BOX_SIZE; l++)
                    if ( (((k!=i) && (l==j))||((k==i) && (l!=j))) && num == grid_read_value(g, k, l))
                        flag = 1;
        }
    return flag;
}




/* Prints all the rows, cols, sub-grid errors|conflicts found in puzzle g. */
void sudoku_print_errors(Grid_T g) {
	int i, j, k, l, num;
	for (i = 0; i<SIZE; i++) {
		for (j = 0; j<SIZE; j++) {
			num = grid_read_value(g, i, j);
			if (num == 0)
				continue;
			for (k = 0; k<SIZE; k++) {
				
				if (num == grid_read_value(g, i, k) && k != j) {/* rows checking */
					printf("Row error : [%d , %d] and [%d , %d]\n", i, j, i, k);
				}
				
				if (num == grid_read_value(g, k, j) && k != i) {/* columns checking */
					printf("Column error: [%d , %d] and [%d , %d]\n", i, j, k, j);
				}
			}
			/*   check puzzle (3*3)  */
			for (k = (i / BOX_SIZE)*BOX_SIZE; k<(i / BOX_SIZE)*BOX_SIZE + BOX_SIZE; k++) {
				for (l = (j / BOX_SIZE)*BOX_SIZE; l<(j / BOX_SIZE)*BOX_SIZE + BOX_SIZE; l++) {
					if ((((k != i) && (l == j)) || ((k == i) && (l != j))) && num == grid_read_value(g, k, l)) {
						printf("Box error: [%d,%d] and [%d,%d]\n", i, j, k, l);
					}
				}
			}
		}
	}
	return;
}




/* Iinitialize all grid choises */
void sudoku_init_choices(Grid_T *g){
    int i, j, k, l, m, choice;
    grid_set_unique(g);
    for (i = 0; i < SIZE; i++) { /* sets all the choices */
        for (j = 0; j < SIZE; j++){
	    grid_clear_choice(g,i,j,0);
            grid_set_count(g,i,j);
            for (m = 1; m <= SIZE; m++)
                grid_set_choice(g, i, j, m);
        }
    }
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++){
            m = grid_read_value(*g,i,j);
            if (m != 0){ /* cell is not empty */
                grid_clear_count(g,i,j);
                for (m=1; m <= SIZE; m++)
                    grid_clear_choice(g, i, j, m);
                continue;
            }
            for (k = 0; k < SIZE; k++){ /* cell is empty */
                choice = grid_read_value(*g, k, j);
                   /* clear COLUMN */
                grid_remove_choice(g, i, j, choice);
                choice = grid_read_value(*g, i, k);
                   /* clear ROW */
                grid_remove_choice(g, i, j, choice);
            }
	              /* clear (3x3) puzzle */
            for (k = (i/BOX_SIZE)*BOX_SIZE; k < (i/BOX_SIZE)*BOX_SIZE+BOX_SIZE; k++)
                for (l = (j/BOX_SIZE)*BOX_SIZE; l < (j/BOX_SIZE)*BOX_SIZE+BOX_SIZE; l++){
                    choice = grid_read_value(*g, k, l);
                    grid_remove_choice(g, i, j, choice);
                }
            }
     }
     return;
}

/* sets to element i,j the better(we prefer) choice */
static void sudoku_apply_choice(Grid_T *g, int i, int j, int n){
  grid_update_value(g, i, j, n);
  return;
}

/* finds a unique choice-cell and returns answer or returns answer to cell with minimum choices */
static int sudoku_try_next_random(Grid_T g, int *row, int *col){
    int i, j, k, n;
    int minchoice = 10;
    for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++){
		    n = grid_read_count(g, i, j);
		    if (n > 0 && n < minchoice) { /* if there is an element with the less choices */
			minchoice = n;
		    }
		}
    }
    for(i=0; i<SIZE; i++){
	for(j=0; j<SIZE; j++){
	    n = grid_read_count(g, i, j);
	    if (n == minchoice) {
                while (1) {
                    k = rand()%(SIZE + 1);
                    if (grid_choice_is_valid(g, i, j, k)) { /* apply the random choices k to i,j */
                        *row = i;
                        *col = j;
                        return k;
                    }
                }
            }
	}
    }
    return 0;
}

/* removes the values from grid */
static int sudoku_remove_choice(Grid_T *g, int i, int j, int n){
	int choices;
	choices = grid_read_count(*g, i, j);
	grid_remove_choice(g, i, j, n);
	return choices;
}

/* updates the choices after remove of the value */
static void sudoku_eliminate_choice(Grid_T *g, int row, int col, int n){
  int i, j;
  for (i = 0; i < SIZE; i++) {
    grid_remove_choice(g, row, i, n);
    grid_remove_choice(g, i, col, n);
  }
  /* compute sub-grid */
  for (i = (row/BOX_SIZE)*BOX_SIZE; i < (row/BOX_SIZE)*BOX_SIZE+BOX_SIZE; i++) {
    for (j = (col/BOX_SIZE)*BOX_SIZE; j < (col/BOX_SIZE)*BOX_SIZE+BOX_SIZE; j++) {
      /* remove from sub-grid */
      grid_remove_choice(g, i, j, n);
    }
  }
  return;
}

static Grid_T sudoku_generate_complete(void){
  Grid_T new_g;
  int i, j, n, tries;
  int ready_puzzle[SIZE*SIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9,
                                  4, 5, 6, 7, 8, 9, 1, 2, 3,
                             	  7, 8, 9, 1, 2, 3, 4, 5, 6,
                            	  2, 3, 4, 5, 6, 7, 8, 9, 1,
                             	  5, 6, 7, 8, 9, 1, 2, 3, 4,
                             	  8, 9, 1, 2, 3, 4, 5, 6, 7,
                            	  3, 4, 5, 6, 7, 8, 9, 1, 2,
                            	  6, 7, 8, 9, 1, 2, 3, 4, 5,
                            	  9, 1, 2, 3, 4, 5, 6, 7, 8 };
  tries = SIZE + 1;
  while ((tries) != 0) {
    tries--;
    for (i = 0; i < SIZE; i++) {
            /* Initialize elements to zero.*/
      for (j = 0; j < SIZE; j++){
	  grid_update_value(&new_g, i, j, 0);
      }
    }
    sudoku_init_choices(&new_g);
    while ((n = sudoku_try_next_random(new_g, &i, &j))) {
      sudoku_apply_choice(&new_g, i, j, n);
      sudoku_remove_choice(&new_g, i, j, n);
      sudoku_eliminate_choice(&new_g, i, j, n);
    }
    if (sudoku_is_correct(new_g)) return new_g;
  }
  n = 0;
  for (i = 0; i < SIZE; i++) {
    for (j = 0; j < SIZE; j++){
      grid_update_value(&new_g, i, j, ready_puzzle[n]);
      n++;
    }
  }
  sudoku_init_choices(&new_g);
  return new_g;
}

/* Sovle the puzzle of grid and
 returns the solved puzzle. */
Grid_T sudoku_solve(Grid_T g){
    int i, j, n, choice;
    Grid_T tmp, solved;
    while ((n = sudoku_try_next_random(g, &i, &j))){
        choice = sudoku_remove_choice(&g, i, j, n);
        if (choice == 1){
            sudoku_apply_choice(&g, i, j, n);
            sudoku_eliminate_choice(&g, i, j, n);
        }
        else {
            grid_clear_unique(&g);
            tmp = g;
            sudoku_apply_choice(&tmp, i, j, n);
            solved = sudoku_solve(tmp);
            if (sudoku_is_correct(solved))
                return solved;
        }
    }
    return g;
}


/* Returns 1 if solution g, as returned by sudoku_solve, has a
   unique choice for each step computed with the use of sudoku_solve.) */
int sudoku_solution_is_unique(Grid_T g){
    return (grid_read_unique(g));
}

/* 
Generate and returns a sudoku puzzle with "approximately" nelts
   elements having non-0 value. If unique=1 the puzzle must have a
   unique choice at each step of finding the solution.
    */
Grid_T sudoku_generate(int nelts, int unique){
    Grid_T sudok, tmp;
    int i, j, total = SIZE*SIZE;
    sudok = sudoku_generate_complete();
    while (total != nelts){
        i = rand()%SIZE;
	j = rand()%SIZE;
        if (grid_read_value(sudok, i, j) == 0)/* if '0' continue */
            continue;
        grid_update_value(&tmp,i,j,0);
        sudoku_init_choices(&tmp);
        if (unique == 0){
            sudoku_init_choices(&sudok);
            grid_update_value(&sudok,i,j,0);
	    total--;
        }
        else{
	    tmp = sudok;
            if (sudoku_solution_is_unique(sudoku_solve(tmp))){
                sudoku_init_choices(&sudok);
                grid_update_value(&sudok, i, j, 0);
		total--;
	    }
        }
    }
    return sudok;
}

/* Prints the sudoku puzzle defined by g to stream s in the same format
   as expected by sudoku_read(). */
void sudoku_print(FILE *s, Grid_T g){
    int i,j;
    for (i = 0; i<SIZE; i++){
        for (j = 0; j<SIZE; j++)
            fprintf(s,"%d ",grid_read_value(g, i, j));
        fprintf(s,"\n");
    }
    return;
}

/*
 * reads  sudoku grid from stdin and return an object Grid_T
 * initialized to these values
 * the input has the format:

 *  1 2 3 4 5 6 7 8 9
 *  4 5 6 7 8 9 1 2 3
 *  7 8 9 1 2 3 4 5 6
 *  2 3 4 5 6 7 8 9 1
 *  5 6 7 8 9 1 2 3 4
 *  8 9 1 2 3 4 5 6 7
 *  3 4 5 6 7 8 9 1 2
 *  6 7 8 9 1 2 3 4 5
 *  9 1 2 3 4 5 6 7 8

 * each number is followed by a space. Each line is terminated with
 * \n. Values of 0 indicate empty grid cells.
 */
Grid_T sudoku_read(void){
    Grid_T sudok;
    int n,i = 0, j = 0;
    int count = 0;
    char c[2];
    c[1] = '\0';
    while ((c[0]=getchar())!=EOF){
        if (c[0]=='\n'){
            i++;
            j = 0;
            continue;
        }
        if ( isdigit((int)c[0]) ){
            n = atoi(c);
            if (n>SIZE || n<0){
                printf("All elements must between 0 and 9\n");
                exit(EXIT_FAILURE);
            }
            grid_update_value(&sudok,i,j,n);
            j++;
            count++;
        }
        else if(c[0]==' '){
            continue;
        }
    }
    if (count!=SIZE*SIZE){
        printf("Input must be 81 elements\n");
        exit(EXIT_FAILURE);
    }
    return sudok;
}

/* Returns true if the g puzzle is correct. */
int sudoku_is_correct(Grid_T g){
    int i,j;
    for (i = 0; i<SIZE; i++){
        for (j = 0; j<SIZE; j++){
            if (grid_read_value(g,i,j) == 0) return 0;
        }
    }
    if (has_errors(g)==0) return 1;
    return 0;
}

int main(int argc, char **argv){
  Grid_T input, output;
  int n, flag = 1;
  /* check how many  arguments are and we go to each case, 
  1 argument=sudoku*/
  if(argc == 1){
    input = sudoku_read();
    sudoku_print(stderr, input);
    sudoku_init_choices(&input);
    output = sudoku_solve(input);
    if (sudoku_is_correct(output)) {
      if (sudoku_solution_is_unique(output))
        fprintf(stderr, "Puzzle has a unique solution:\n");
      else
        fprintf(stderr, "Puzzle has a solution:\n");
    }
    else {
      fprintf(stderr, "Puzzle does not have solution:\n");
    }
    sudoku_print(stdout, output);
    sudoku_print_errors(output);
    }else if (argc == 2){/*2 arguments=sudoku -c*/
      if (argv[1][0] == '-' &&
          argv[1][1] == 'c' &&
          argv[1][2] == '\0') {
        input = sudoku_read();
        sudoku_print(stderr, input);
        if (sudoku_is_correct(input))
            fprintf(stderr, "Puzzle solution is correct.\n");
        else
          fprintf(stderr, "Puzzle solution is not correct.\n");
        sudoku_print_errors(input);
      }
    }else if (argc == 3){/*3 arguments=sudoku -g nelts*/
      if (argv[1][0] == '-' && argv[1][1] == 'g' && argv[1][2] == '\0') {
        n = 0;
        while (argv[2][n] != '\0')
          if (!isdigit((int)argv[2][n++])) {
            flag = 0;
        }
        if (flag) {
          n = atoi(argv[2]);
	  if(n>81) {
		printf("Error: Nelts can not be more than 81!\n");
		return 0;
          }
	  output = sudoku_generate(n, 0);
          sudoku_print(stdout, output);
        }
      }
    }else fprintf(stderr,"Expected format:\n sudoku \n sudoku -c  \n sudoku -g nelts\n");
  return 0;
}