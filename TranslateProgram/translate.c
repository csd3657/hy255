/*
 *	Dimitris Milathianakis
 *  csd3657
 * 	assignment 1
 *  2020
 */

#include <stdio.h>

#define N_gr	205
#define n_gr	237
#define M_gr	204
#define m_gr	236
#define T_gr	212
#define t_gr	244
#define N_lat	78
#define n_lat	110
#define M_lat	77
#define m_lat	109
#define	tonos	39
#define	dialit	34

enum state {ANY = 0, M, m, N, n}; /*state_machne*/

char map_gr[255][3];

void init_map(void) {
	int i,j;
	for(i=0; i<256; i++){
		for(j=0; j<3; j++){
			map_gr[i][j] = -1;
		}
	}
	/*first =170 elements 
	.
	.
	.
	are same on both iso's*/
	map_gr[168][0] = dialit;
	map_gr[180][0] = tonos;
	map_gr[181][0] = tonos; map_gr[181][1] = dialit;
	map_gr[182][0] = tonos; map_gr[182][1] = 65;
	map_gr[184][0] = tonos; map_gr[184][1] = 69;
	map_gr[185][0] = tonos; map_gr[185][1] = 72;
	map_gr[186][0] = tonos; map_gr[186][1] = 73;
	map_gr[188][0] = tonos; map_gr[188][1] = 79;
	map_gr[190][0] = tonos; map_gr[190][1] = 89;
	map_gr[191][0] = tonos; map_gr[191][1] = 87;
	map_gr[192][0] = 105;   map_gr[192][1] = tonos; map_gr[192][2] = dialit;
	map_gr[193][0] = 65;
	map_gr[194][0] = 86;
	map_gr[195][0] = 71;
	map_gr[196][0] = 68;
	map_gr[197][0] = 69;
	map_gr[198][0] = 90;
	map_gr[199][0] = 72;
	map_gr[200][0] = 56;
	map_gr[201][0] = 73;
	map_gr[202][0] = 75;
	map_gr[203][0] = 76;
	map_gr[204][0] = 77;
	map_gr[205][0] = 78;
	map_gr[206][0] = 75;	 map_gr[206][1] = 83;
	map_gr[207][0] = 79;
	map_gr[208][0] = 80;
	map_gr[209][0] = 82;
	map_gr[211][0] = 83;
	map_gr[212][0] = 84;
	map_gr[213][0] = 89;
	map_gr[214][0] = 70;
	map_gr[215][0] = 88;
	map_gr[216][0] = 80; 	 map_gr[216][1] = 83;
	map_gr[217][0] = 87;
	map_gr[218][0] = dialit; map_gr[218][1] = 73;
	map_gr[219][0] = dialit; map_gr[218][1] = 89;
	map_gr[220][0] = 97; 	 map_gr[220][1] = tonos;
	map_gr[221][0] = 101;	 map_gr[221][1] = tonos;
	map_gr[222][0] = 104;	 map_gr[222][1] = tonos;
	map_gr[223][0] = 105;	 map_gr[223][1] = tonos;
	map_gr[224][0] = 121;	 map_gr[224][1] = tonos; 	map_gr[224][2] = dialit;
	map_gr[225][0] = 97;
	map_gr[226][0] = 118;
	map_gr[227][0] = 103;
	map_gr[228][0] = 100;
	map_gr[229][0] = 101;
	map_gr[230][0] = 122;
	map_gr[231][0] = 104;
	map_gr[232][0] = 56;
	map_gr[233][0] = 105;
	map_gr[234][0] = 107;
	map_gr[235][0] = 108;
	map_gr[236][0] = 109;
	map_gr[237][0] = 110;
	map_gr[238][0] = 107; 	map_gr[238][1] = 115;
	map_gr[239][0] = 111;
	map_gr[240][0] = 112;
	map_gr[241][0] = 114;
	map_gr[242][0] = 115;
	map_gr[243][0] = 115;
	map_gr[244][0] = 116;
	map_gr[245][0] = 121;
	map_gr[246][0] = 102;
	map_gr[247][0] = 120;
	map_gr[248][0] = 112;	 map_gr[248][1] = 115;
	map_gr[249][0] = 119;
	map_gr[250][0] = 105;	 map_gr[250][1] = dialit;
	map_gr[251][0] = 121;	 map_gr[251][1] = dialit;
	map_gr[252][0] = 111;	 map_gr[252][1] = tonos;
	map_gr[253][0] = 121;	 map_gr[253][1] = tonos;
	map_gr[254][0] = 119;	 map_gr[254][1] = tonos;
}


/*prints latin char who responds to greek*/
void simle_state_print(int c) {
	int i = 0;
	if(map_gr[c][i] == -1){
		/*if map_gr[x][0] is "-1" nothing changes 
		between two iso's and print
		 simple input*/
		putchar(c); /*ot*/
	}else{
		while (i < 3 && map_gr[c][i] != -1) {/*mexri na vrw -1 antikathistw me chars*/
			putchar(map_gr[c][i]);
			/*ok*/
			i++;
		}
	}
}

enum state action_ANY(int c) {
	/*the simplest action*/
	
	switch (c) {
		/* if we see M, m, N, n (enum state) return changed state
	****else  print the char and  stay at this sTate*/
		case M_gr:
			return M;
		case m_gr:
			return m;
		case N_gr:
			return N;
		case n_gr:
			return n;
		default:
			simle_state_print(c);
			return ANY;
	}
}

enum state action_m(int c) {
	/*if we have read m then:*/
	switch (c) {
		case N_gr:/*if we read N we print m and go the the state N*/
			putchar(m_lat);
			return N;
		case n_gr:/*if we read n we print m and go to the state n*/
			putchar(m_lat);
			return n;
		case M_gr:/*if we read M we print m and go to the state M*/
			putchar(m_lat);
			return M;
		case m_gr:/*if we read again m we print one m and remain at the same state*/
			putchar(m_lat);
			return m;
		case 208:	/*if we read (greek) P we print b and go to the state ANY*/		
			putchar(98);	/*b=98 greek P=208*/
			return ANY;
		case 240:			/*if we read (greek) p we print b and go to the state ANY*/
			putchar(98);	/*b=98   greek p=240*/
			return ANY;
		default:
			putchar(m_lat);/*else we print m and and the other char and we go to the state ANY*/
			simle_state_print(c);
			return ANY;
	}
}

enum state action_M(int c) {
	/*read M*/
	switch (c) {
		case N_gr:/*if you read N, print M and go t0 state N*/
			putchar(M_lat);
			return N;
		case n_gr:/*if you read n we print M and go toe state n*/
			putchar(M_lat);
			return n;
		case M_gr: /*if you read again M, print M and stay at the same state*/
			putchar(M_lat);
			return M;
		case m_gr:/*if you read m, print M and go to state m*/
			putchar(M_lat);
			return m;
		case 208:			/*if you read (greek) P we print B and go to state any*/
			putchar(66);	/*B=66  ,   greek P=208*/
			return ANY;
		
		case 240:		/*if we read (greek) p we print B and go to state any*/	
			putchar(66);	/*B=66       greek p=240*/
			return ANY;
		
		default: /*else we print M and and the other char and we go to the state ANY*/
			putchar(M_lat);
			simle_state_print(c);
			return ANY;
	}
}

enum state action_n(int c) {
	/*if read n*/
	switch (c) {
		case N_gr:/*if we read N we print n and go to the state N*/
			putchar(n_lat);
			return N;
		case n_gr:/*if we read n we print n and remain at state n*/
			putchar(n_lat);
			return n;
		case M_gr:/*if we read M we print n and go to the state M*/
			putchar(n_lat);
			return M;
		case m_gr:/*if we read m we print n and go to the state m*/
			putchar(n_lat);
			return m;
		case T_gr:/*if we read (greek) T we print d and go to the state any*/
			putchar(100);	/*d=100*/
			return ANY;
		
		case t_gr:/*if we read (greek) t we print d and go to the state any*/
			putchar(100);	/*d=100*/
			return ANY;
		default:
			putchar(n_lat);/*else we print n and and the other char and we go to the state ANY*/
			simle_state_print(c);
			return ANY;
	}
}
enum state action_N(int c) {
	/*if read N*/
	switch (c) {
		case N_gr:/*if we read N we print N and remain at the same state*/
			putchar(N_lat);
			return N;
		case n_gr:/*if we read n we print N and go to the state n*/
			putchar(N_lat);
			return n;
		case M_gr:/*if we read M we print N and go to the state M*/
			putchar(N_lat);
			return M;
		case m_gr:/*if we read m we print N and go to the state m*/
			putchar(N_lat);
			return m;
		case T_gr:/*if we read (greek) T we print D and go to the state ANY*/
			putchar(68);	/* =>D=68.*/
			return ANY;
		case t_gr:/*if we read (greek) t we print D and go to the state ANY*/
			putchar(68);	/* =>D=68.*/
			return ANY;
		default:
		/*else we print N and and the other char and we go to the state ANY*/
			putchar(N_lat);
			simle_state_print(c);
			return ANY;
	}
}

enum state(*action[])(int c) = { action_ANY, action_M, action_m, action_N, action_n };
int main(void) {
	int c;
	enum state curr_state;
	init_map();
	curr_state = ANY;

	printf("\n=== TRASLATE PROGRAMM ===\n");
	printf("\nWrite your text and press enter...\n");
	
	while ((c = getchar()) != EOF) {
		curr_state = (action[curr_state])(c);
	}
	return 0;
}