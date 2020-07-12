#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 

struct teams{
	char teamname[33];
	char country[20];
	int xwritikotita;
	int dinamiki;
	int vathmologia;
	int energitiko;
	int pathitiko;
	int f4;
	struct teams* next;
};

void printTeams(struct teams * teamsdata)
{
	struct teams * temp = teamsdata;
	while(temp != NULL){
		printf("%d - %s %s %d %d\n",temp->vathmologia, temp->teamname, temp->country, temp->xwritikotita, temp->dinamiki);
		temp = temp->next;
	}
}

void printTeamsAgyros(struct teams * teamsdata)
{
	struct teams * temp = teamsdata;

	printf("----- VATHMOLOGIA PRWTOS GYROS-----\n\n");
	printf("Score - Team, Country\n\n");
	while(temp != NULL){
		printf("  %d  - %s, %s\t\n", temp->vathmologia, temp->teamname, temp->country);
		temp = temp->next;
	}
}

void printTeamsBgyros(struct teams * teamsdata)
{
	struct teams * temp = teamsdata;

	printf("----- VATHMOLOGIA DEYTEROS GYROS-----\n\n");
	printf("Score - Team, Country\n\n");
	while(temp != NULL){
		printf("  %d  - %s, %s\t\n", temp->vathmologia, temp->teamname, temp->country);
		temp = temp->next;
	}
}

/* function to swap data of two nodes a and b*/
void swap(struct teams *a, struct teams *b) 
{ 
    int temp = a->vathmologia; 
	int temp1 = a->xwritikotita; 
	int temp2 = a->pathitiko; 
	int temp3 = a->energitiko; 
	int temp4 = a->dinamiki; 
	char temp5[33], temp6[20];
	strcpy(temp5, a->teamname);
	strcpy(temp6, a->country);

    a->vathmologia = b->vathmologia; 
	a->xwritikotita = b->xwritikotita;
	a->pathitiko = b->pathitiko;
	a->energitiko = b->energitiko; 
	a->dinamiki = b->dinamiki;
	strcpy(a->teamname, b->teamname);
	strcpy(a->country, b->country);

    b->vathmologia = temp;
	b->xwritikotita = temp1;
	b->pathitiko = temp2;
	b->energitiko = temp3; 
	b->dinamiki = temp4;
	strcpy(b->teamname, temp5);
	strcpy(b->country, temp6);
} 

void bubbleSort(struct teams *start) 
{ 
    int swapped, i; 
    struct teams *ptr1; 
    struct teams *lptr = NULL; 
  
    /* Checking for empty list */
    if (start == NULL) 
        return; 
  
    do
    { 
        swapped = 0; 
        ptr1 = start; 
  
        while (ptr1->next != lptr) 
        { 
            if (ptr1->vathmologia < ptr1->next->vathmologia) 
            {  
                swap(ptr1, ptr1->next); 
                swapped = 1; 
            } 
            ptr1 = ptr1->next; 
        } 
        lptr = ptr1; 
    } 
    while (swapped); 
} 
  




void prwtos_gyros(FILE * of, struct teams * teamsdata)
{
	int x;
	int team1points, team2points;
	struct teams * temp;
	struct teams * head;
	char buffer[1024];
	
	head = teamsdata;

	fputs("-----RESULTS PRWTOS GYROS-----\n\n", of);
	while(teamsdata != NULL)
	{
		temp = head;
		while(temp != NULL)
		{
			if(teamsdata->teamname != temp->teamname){
				team1points = 50 + rand( ) % (1 + teamsdata->dinamiki/2);
				team2points = 50 + rand( ) % (1 + temp->dinamiki/2);
				
				if(team1points == team2points){ //se periptwsi isopalias
					x = 1 + rand() % 2; 
					if(x == 1){
						team1points++;
					}else{
						team2points++;
					}
				}

				if(teamsdata->country != temp->country){ //bonus xwritikotitas gipedou
					if(teamsdata->xwritikotita >= 10 && teamsdata->xwritikotita <= 15){
						team1points += 3;
					}
					if(teamsdata->xwritikotita > 15){
						team1points += 5;
					}
				}

				teamsdata->energitiko += team1points;
				teamsdata->pathitiko += team2points;
				temp->energitiko += team2points;
				temp->pathitiko += team1points;

				snprintf(buffer, sizeof(buffer), "%s VS %s\t%d - %d\n", teamsdata->teamname, temp->teamname, team1points, team2points);
				fputs(buffer,of);
				if(team1points > team2points){
					teamsdata->vathmologia += 2;
					temp->vathmologia += 1;
				}else{
					teamsdata->vathmologia += 1;
					temp->vathmologia += 2;
				}
			}
			temp = temp->next;
		}
		teamsdata = teamsdata->next;
	}
	fputs("\n-----PRWTOS GYROS TELOS-----\n\n", of);
}

void deyteros_gyros(FILE* of, struct teams * teamsdata)
{
	int x, y, z, team1points = 0, team2points = 0;
	struct teams * temp = teamsdata;
	struct teams * head = teamsdata;
	char buffer[1024];
	fputs("----- RESULTS DEYTEROS GYROS-----\n\n", of);
	printf("\n----- RESULTS DEYTEROS GYROS-----\n");
	y = 7;
	z = 0;
	for(x = 0; x < 4; x++){ //1i omada (1,2,3,4)
		temp = head;
		for(z = 0; z < y-x; z++){ //2i omada
			
			temp = temp->next;
		}

		team1points = 50 + rand( ) % (1 + teamsdata->dinamiki/2);
		team2points = 50 + rand( ) % (1 + temp->dinamiki/2);
		if(team1points == team2points){ //se periptwsi isopalias
			x = 1 + rand() % 2; 
			if(x == 1){
				team1points++;
			}else{
				team2points++;
			}
		}

		if(teamsdata->country != temp->country){ //bonus xwritikotitas gipedou
			if(teamsdata->xwritikotita >= 10 && teamsdata->xwritikotita <= 15){
				team1points += 3;
			}
			if(teamsdata->xwritikotita > 15){
				team1points += 5;
			}
		}
		printf("  %d - %d %s vs %s",team1points, team2points, teamsdata->teamname,  temp->teamname);
		snprintf(buffer, sizeof(buffer), "%s VS %s\t%d - %d\n", teamsdata->teamname, temp->teamname, team1points, team2points);
		fputs(buffer,of);
		if(team1points>team2points){
			teamsdata->f4 = x+1;
			printf(" ==> %s qualified to final4 %d\n",teamsdata->teamname, teamsdata->f4);
			
		}else{
			temp->f4 = x+1;
			printf(" ==> %s qualified to final4 %d\n",temp->teamname, temp->f4);
			
		}
		
		teamsdata = teamsdata->next;
	}
	teamsdata = head;
	fputs("\n-----DEYTEROS GYROS TELOS-----\n\n", of);
}

void final4(FILE * of, struct teams * teamsdata){
	struct teams * temp;
	struct teams * head;

	struct teams * team1;
	struct teams * team2;
	struct teams * team3;
	struct teams * team4;

	int x, team1points, team2points, team3points, team4points, big1points, big2points,small1points, small2points;

	char buffer[1024];

	fputs("-----RESULTS F4-----\n\n", of);
	printf("\n-----RESULTS F4-----\n");


	temp = teamsdata;
	for(x = 0; x < 8; x++){
		if(temp->f4 == 1){
			team1 = temp;
			//printf("%s", team1->teamname);
		}
		if(temp->f4 == 2){
			team2 = temp;
			//printf("%s", team2->teamname);
		}
		if(temp->f4 == 3){
			team3 = temp;
			//printf("%s", team3->teamname);
		}
		if(temp->f4 == 4){
			team4 = temp;
			//printf("%s", team4->teamname);
		}
		temp = temp->next;
	}
	team1points = 50 + rand( ) % (1 + team1->dinamiki/2);
	team2points = 50 + rand( ) % (1 + team2->dinamiki/2);
	team3points = 50 + rand( ) % (1 + team3->dinamiki/2);
	team4points = 50 + rand( ) % (1 + team4->dinamiki/2);

	printf("  %d - %d %s vs %s\n",team1points, team4points, team1->teamname,  team4->teamname);
	printf("  %d - %d %s vs %s\n\n",team2points, team3points, team2->teamname,  team3->teamname);

	printf("\n------FINAL 4---------\n");
	if(team1points > team4points && team2points > team3points){
		//printf("\n\n1AAAAAAAAAAAAA\n\n");
		big1points = 50 + rand( ) % (1 + team1->dinamiki/2);
		big2points = 50 + rand( ) % (1 + team2->dinamiki/2);
		small1points = 50 + rand( ) % (1 + team4->dinamiki/2);
		small2points = 50 + rand( ) % (1 + team3->dinamiki/2);

		printf("FINAL:        %d - %d %s vs %s\n",big1points, big2points, team1->teamname,  team2->teamname);
		printf("SMALL FINAL:  %d - %d %s vs %s\n\n",small1points, small2points, team4->teamname,  team3->teamname);
		
		snprintf(buffer, sizeof(buffer), "FINAL\n%s VS %s\t%d - %d\n", team1->teamname, team2->teamname, big1points, big2points);
		fputs(buffer,of);

		snprintf(buffer, sizeof(buffer), "SMALL FINAL\n%s VS %s\t%d - %d\n", team4->teamname, team3->teamname, small1points, small2points);
		fputs(buffer,of);

		printf("\n------------FINAL 4, TELIKI KATATAXI----------\n");

		if(big1points>big2points){
			printf("\n1) %s \n2) %s", team4->teamname, team2->teamname);
		}else{
			printf("\n1) %s \n2) %s", team2->teamname, team4->teamname);
		}
		if(small1points>small2points){
			printf("\n3) %s \n4) %s", team1->teamname, team3->teamname);
		}else{
			printf("\n3) %s \n4) %s", team3->teamname, team1->teamname);
		}

	}
	if(team1points < team4points && team2points > team3points){
		//printf("\n\n2AAAAAAAAAAAAA\n\n");
		big1points = 50 + rand( ) % (1 + team4->dinamiki/2);
		big2points = 50 + rand( ) % (1 + team2->dinamiki/2);
		small1points = 50 + rand( ) % (1 + team1->dinamiki/2);
		small2points = 50 + rand( ) % (1 + team3->dinamiki/2);

		printf("FINAL:        %d - %d %s vs %s\n",big1points, big2points, team4->teamname,  team2->teamname);
		printf("SMALL FINAL:  %d - %d %s vs %s\n\n",small1points, small2points, team1->teamname,  team3->teamname);

		snprintf(buffer, sizeof(buffer), "FINAL\n%s VS %s\t%d - %d\n", team4->teamname, team2->teamname, big1points, big2points);
		fputs(buffer,of);

		snprintf(buffer, sizeof(buffer), "SMALL FINAL\n%s VS %s\t%d - %d\n", team1->teamname, team3->teamname, small1points, small2points);
		fputs(buffer,of);
//printf("\n1 %s \n2 %s\n3 %s \n4 %s", team1->teamname, team2->teamname, team3->teamname, team4->teamname);
		printf("\n------------FINAL 4, TELIKI KATATAXI----------\n");

		if(big1points>big2points){
			printf("\n1) %s \n2) %s", team4->teamname, team2->teamname);
		}else{
			printf("\n1) %s \n2) %s", team2->teamname, team4->teamname);
		}
		if(small1points>small2points){
			printf("\n3) %s \n4) %s", team1->teamname, team3->teamname);
		}else{
			printf("\n3) %s \n4) %s", team3->teamname, team1->teamname);
		}
	}
	if(team1points < team4points && team2points < team3points){
		//printf("\n\n3AAAAAAAAAAAAA\n\n");
		big1points = 50 + rand( ) % (1 + team4->dinamiki/2);
		big2points = 50 + rand( ) % (1 + team3->dinamiki/2);
		small1points = 50 + rand( ) % (1 + team1->dinamiki/2);
		small2points = 50 + rand( ) % (1 + team2->dinamiki/2);

		printf("FINAL:        %d - %d %s vs %s\n",big1points, big2points, team4->teamname,  team3->teamname);
		printf("SMALL FINAL:  %d - %d %s vs %s\n\n",small1points, small2points, team1->teamname,  team2->teamname);

		snprintf(buffer, sizeof(buffer), "FINAL\n%s VS %s\t%d - %d\n", team4->teamname, team3->teamname, big1points, big2points);
		fputs(buffer,of);

		snprintf(buffer, sizeof(buffer), "SMALL FINAL\n%s VS %s\t%d - %d\n", team1->teamname, team2->teamname, small1points, small2points);
		fputs(buffer,of);

		printf("\n------------FINAL 4, TELIKI KATATAXI----------\n");

		if(big1points>big2points){
			printf("\n1) %s \n2) %s", team4->teamname, team2->teamname);
		}else{
			printf("\n1) %s \n2) %s", team2->teamname, team4->teamname);
		}
		if(small1points>small2points){
			printf("\n3) %s \n4) %s", team1->teamname, team3->teamname);
		}else{
			printf("\n3) %s \n4) %s", team3->teamname, team1->teamname);
		}
	}
	if(team1points > team4points && team2points < team3points){
		//printf("\n\n4AAAAAAAAAAAAA\n\n");
		big1points = 50 + rand( ) % (1 + team1->dinamiki/2);
		big2points = 50 + rand( ) % (1 + team3->dinamiki/2);
		small1points = 50 + rand( ) % (1 + team4->dinamiki/2);
		small2points = 50 + rand( ) % (1 + team2->dinamiki/2);

		printf("FINAL:        %d - %d %s vs %s\n",big1points, big2points, team1->teamname,  team3->teamname);
		printf("SMALL FINAL:  %d - %d %s vs %s\n\n",small1points, small2points, team4->teamname,  team2->teamname);

		snprintf(buffer, sizeof(buffer), "FINAL\n%s VS %s\t%d - %d\n", team1->teamname, team3->teamname, big1points, big2points);
		fputs(buffer,of);

		snprintf(buffer, sizeof(buffer), "SMALL FINAL\n%s VS %s\t%d - %d\n", team4->teamname, team2->teamname, small1points, small2points);
		fputs(buffer,of);

		printf("\n------------FINAL 4, TELIKI KATATAXI----------\n");

		if(big1points>big2points){
			printf("\n1) %s \n2) %s", team4->teamname, team2->teamname);
		}else{
			printf("\n1) %s \n2) %s", team2->teamname, team4->teamname);
		}
		if(small1points>small2points){
			printf("\n3) %s \n4) %s", team1->teamname, team3->teamname);
		}else{
			printf("\n3) %s \n4) %s", team3->teamname, team1->teamname);
		}
	}

	teamsdata = head;
}

int main(int argc, char * argv[])
{
	struct teams * teamsdata;
	struct teams * temp;
	struct teams * head;
    char c;
	int n = 0;
	int nextTeam = 0;
	FILE * fp = fopen("teams.txt", "r");
	FILE * of = fopen("results.txt", "w+");
	if (fp == NULL) return 1;

	//prwti eisagwgi sto struct teams
	temp = malloc(sizeof(struct teams));
	fscanf(fp, "%s %s %d %d", temp->teamname, temp->country, &(temp->xwritikotita), &(temp->dinamiki));
	//printf("\n%s %s %d %d", temp->teamname, temp->country, temp->xwritikotita, temp->dinamiki);
	temp->vathmologia = 0;
	temp->next = NULL;
	//--------------------------------

	head = teamsdata = temp;

	while(n++ < 17) //diavase tis upoloipes 17 omades tou teams.txt
	{
		temp = malloc(sizeof(struct teams));
		fscanf(fp, "%s %s %d %d\n", temp->teamname, temp->country, &(temp->xwritikotita), &(temp->dinamiki));
		//printf("\n%s %s %d %d", temp->teamname, temp->country, temp->xwritikotita, temp->dinamiki);
		temp->vathmologia = 0;
		temp->next = NULL;

		teamsdata->next = temp;
		teamsdata = teamsdata->next;
	}
	
	teamsdata = head;
	
	prwtos_gyros(of, teamsdata);
	//printTeams(head);
	bubbleSort(head);
	printTeamsAgyros(head);

	teamsdata = head;
	deyteros_gyros(of, teamsdata);

	teamsdata = head;
	final4(of, teamsdata);

	fclose(fp);
	fclose(of);
 
	return 0;
}