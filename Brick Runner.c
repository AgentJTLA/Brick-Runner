//2702228734 - Giovano Julian Somantry
//2702261580 - Jayson Kelvin
//2702262564 - Reynard Adrian Tjakrasendjaja

//Brick Runner

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>
#include <string.h>

struct position{
	int x;
	int y;
};
struct position border;
struct position player;
struct position obstacle;
struct position obstacle2;
struct position obstacle3;

struct data{
	char name[10];
	float score;
};
struct data easy[101];
struct data medium[101];
struct data hard[101];
struct data insane[101];
struct data overall[404];
struct data searched;

int i, j, gameover, flag, diff, rep = 0, ea = 0, me = 0, ha = 0, in = 0, m = 101;
float dur, score, speed;

void swap(struct data *a, struct data *b){
	struct data temp = *a;
	*a = *b;
	*b = temp;
}

void bubbleSort(struct data lb[], int n){
	for(int a=0;a<n-1;a++){
		for(int b=0;b<n-a-1;b++){
			if(lb[b+1].score<lb[b+2].score) swap(&lb[b+1], &lb[b+2]);
			else if(lb[b+1].score==lb[b+2].score){
				if(strcmp(lb[b+1].name, lb[b+2].name)>0) swap(&lb[b+1], &lb[b+2]);
			}
		}
	}
}

void welcome();

void tutorial(){
	system("cls");
	printf("A brief tutorial:\n");
	printf("- This is your character: {*}\n");
	printf("- If you see this object: [=], dodge it!\n");
	printf("- Press 'a', 's', or 'd' to switch lane and dodge obstacles.\n");
	printf("- 'a': left lane, 's': mid lane, 'd': right lane\n");
	printf("Got it?\n");
	printf("\nPress r: return to main menu\n");
	char ret = getch();
	switch(ret){
		case 'r': welcome(); break;
		default: break;
	}
}

void saveto(){
	system("cls");
	bubbleSort(overall, rep);
	FILE *fp = fopen("ldrbrd.txt", "a+");
	for(int u=1;u<=rep;u++){
		fprintf(fp, "%s#%.2f\n", overall[u].name, overall[u].score);
	}
	fclose(fp);
	printf("Successfully saved to ldrbrd.txt.\n");
	printf("\nPress r: return to main menu\n");
	char ret = getch();
	switch(ret){
		case 'r': welcome(); break;
		default: break;
	}
}

void leaderboard(){
	system("cls");
	if(rep==0) printf("No data\n\nStart playing and climb the leaderboard!\n");
	else{
		printf("Easy:                         Medium:                       Hard:                         Insane:                       \n");
		bubbleSort(easy, m-1); bubbleSort(medium, m-1); bubbleSort(hard, m-1); bubbleSort(insane, m-1);
		printf("No. %-10s -    Score     No. %-10s -    Score     No. %-10s -    Score     No. %-10s -    Score\n", "Name", "Name", "Name", "Name");
		for(int k=1;k<11;k++){
			printf("%2d. %-10s - %8.2f     %2d. %-10s - %8.2f     %2d. %-10s - %8.2f     %2d. %-10s - %8.2f\n", k, easy[k].name, easy[k].score, k, medium[k].name, medium[k].score, k, hard[k].name, hard[k].score, k, insane[k].name, insane[k].score);
		}
	}
	printf("\nPress r: return to main menu\n");
	if(rep>0) printf("Press s: save leaderboard to device\n");
	char ret = getch();
	switch(ret){
		case 'r': welcome(); break;
		case 's': saveto(); 
		default: break;
	}
}

void search(){
	system("cls");
	char key[10];
	int found = 0, exit = 0;
	FILE *fp = fopen("ldrbrd.txt", "r");
	if(fp==NULL){
		fclose(fp);
		printf("No previous record stored in ldrbrd.txt.\nStart playing and climb the leaderboard!\n");
		printf("\nPress r: return to main menu\n");
		exit = 1;
		char ret = getch();
		switch(ret){
			case 'r': welcome(); break;
			default: break;
		}
	}
	if(exit!=1){
		printf("Input name to search from ldrbrd.txt: "); scanf("%s", &key); getchar();
		while(!feof(fp)){
			fscanf(fp, "%[^#]#%f\n", &searched.name, &searched.score);
			if(strcmp(key, searched.name)==0){
				printf("Name %s found with score: %.2f\n", key, searched.score);
				found = 1;
				break;
			}
		}
		fclose(fp);
		if(found!=1) printf("Name %s not found.\n", key);
		printf("\nPress r: return to main menu\n");
		char ret = getch();
		switch(ret){
			case 'r': welcome(); break;
			default: break;
		}
	}
}

void setup(){
	gameover = 0, score = 0;
	border.x = 13; border.y = 21;
	player.x = 6; player.y = 19;
	x:
		obstacle.x = rand()%13;
		if(obstacle.x==0||obstacle.x==1||obstacle.x==3||obstacle.x==4||obstacle.x==5||obstacle.x==7||obstacle.x==8||obstacle.x==9||obstacle.x==11||obstacle.x==12||obstacle.x==obstacle2.x||obstacle3.x==obstacle.x) goto x;
	y:
		obstacle.y = 1;
		if(obstacle.y==20) goto y;
	x2:
		obstacle2.x = rand()%13;
		if(obstacle2.x==0||obstacle2.x==1||obstacle2.x==3||obstacle2.x==4||obstacle2.x==5||obstacle2.x==7||obstacle2.x==8||obstacle2.x==9||obstacle2.x==11||obstacle2.x==12||obstacle2.x==obstacle.x||obstacle2.x==obstacle3.x) goto x2;
	y2: 
		obstacle2.y = -3;
		if(obstacle2.y==20) goto y2;
	x3:
		obstacle3.x = rand()%13;
		if(obstacle3.x==0||obstacle3.x==1||obstacle3.x==3||obstacle3.x==4||obstacle3.x==5||obstacle3.x==7||obstacle3.x==8||obstacle3.x==9||obstacle3.x==11||obstacle3.x==12||obstacle3.x==obstacle2.x||obstacle3.x==obstacle.x) goto x3;
	y3: 
		obstacle3.y = -7;
		if(obstacle3.y==20) goto y3;
}

void welcome(){
	welcome:
		system("cls");
		gameover = 1;
		for(i=0;i<21;i++){
			for(j=0;j<36;j++){
				if(j==0&&i!=0||j==35&&i!=0) printf("|");
				else if(i==0||i==20) printf("_");
				else if(i==3&&j==12){
					printf("Brick Runner");
					j=23;
				}
				else if(i==7&&j==9){
					printf("Select difficulty:");
					j=26;
				}
				else if(i==8&&j==3){
					printf("1. Easy  : start at 0.5x speed");
					j=32;
				}
				else if(i==9&&j==3){
					printf("2. Medium: start at 1.0x speed");
					j=32;
				}
				else if(i==10&&j==3){
					printf("3. Hard  : start at 2.0x speed");
					j=32;
				}
				else if(i==11&&j==3){
					printf("4. Insane: start at 4.0x speed");
					j=32;
				}
				else if(i==14&&j==3){
					printf("Press t: view tutorial");
					j=24;
				}
				else if(i==15&&j==3){
					printf("Press l: view leaderboard");
					j=27;
				}
				else if(i==16&&j==3){
					printf("Press s: search from ldrbrd.txt");
					j=33;
				}
				else if(i==17&&j==3){
					printf("Press x: exit game");
					j=20;
				}
				else printf(" ");
			}
			printf("\n");
		}
		char option = getch();
		switch(option){
			case 't': tutorial(); break;
			case 'l': leaderboard(); break;
			case 's': search(); break;
			case 'x': exit(1);
			case '1': ea++; diff = 1; dur = 400000; speed = 0.5; setup(); break;
			case '2': me++; diff = 2; dur = 200000; speed = 1.0; setup(); break;
			case '3': ha++; diff = 3; dur = 100000; speed = 2.0; setup(); break;
			case '4': in++; diff = 4; dur = 50000; speed = 4.0; setup(); break;
			default: goto welcome;
		}
}

void input(){
	if(kbhit()){
		char key = getch();
		switch(key){
			case 'a': flag = 1; break;
			case 's': flag = 2; break;
			case 'd': flag = 3; break;
			case 'r': welcome(); break;
			default: break;
		}
		if (key != 'w' && key != 's' && key != 'a' && key != 'd') flag = 0;
	}
}

void logic(){
	usleep(dur);
	score++, dur/=1.001, speed*=1.001;
    switch (flag) {
        case 1: player.x = 2; break;  
        case 2: player.x = 6; break;  
        case 3: player.x = 10; break;
        default: break;
    }
    obstacle.y++, obstacle2.y++, obstacle3.y++;
    if(obstacle.x==player.x && obstacle.y==player.y || obstacle2.x==player.x && obstacle2.y==player.y || obstacle3.x==player.x && obstacle3.y==player.y){
    	gameover = 1;
	}
    if(obstacle.y==20){
    	resety:
    		obstacle.y = 1;
			if(obstacle.y==20) goto resety;
		resetx:
			obstacle.x = rand()%13;
			if(obstacle.x==0||obstacle.x==1||obstacle.x==3||obstacle.x==4||obstacle.x==5||obstacle.x==7||obstacle.x==8||obstacle.x==9||obstacle.x==11||obstacle.x==12) goto resetx;
		score++, dur/=1.01, speed*=1.01;
	}
	if(obstacle2.y==20){
    	resety2:
    		obstacle2.y = 1;
			if(obstacle2.y==20) goto resety2;
		resetx2:
			obstacle2.x = rand()%13;
			if(obstacle2.x==0||obstacle2.x==1||obstacle2.x==3||obstacle2.x==4||obstacle2.x==5||obstacle2.x==7||obstacle2.x==8||obstacle2.x==9||obstacle2.x==11||obstacle2.x==12||obstacle2.x==obstacle.x||obstacle2.x==obstacle3.x) goto resetx2;
		score++, dur/=1.01, speed*=1.01;
	}
	if(obstacle3.y==20){
		resety3: 
		obstacle3.y = -7;
		if(obstacle3.y==20) goto resety3;
		resetx3:
		obstacle3.x = rand()%13;
		if(obstacle3.x==0||obstacle3.x==1||obstacle3.x==3||obstacle3.x==4||obstacle3.x==5||obstacle3.x==7||obstacle3.x==8||obstacle3.x==9||obstacle3.x==11||obstacle3.x==12||obstacle3.x==obstacle2.x||obstacle3.x==obstacle.x) goto resetx3;
		score++, dur/=1.01, speed*=1.01;
	}
}

void draw(){
	system("cls");
	int i, j;
	for(i=0;i<border.y;i++){
		for(j=0;j<border.x;j++){
			if(i==0&&j==2||i==border.y-1&&j==2) printf("a");
			else if(i==0&&j==6||i==border.y-1&&j==6) printf("s");
			else if(i==0&&j==10||i==border.y-1&&j==10) printf("d");
			else if(i==0||i==border.y-1||j==0||j==border.x-1) printf("#");
			else if(j>0 && j<border.x-1 && j%4==0) printf("|");
			else if(j==player.x && i==player.y) printf("*");
			else if(j==player.x-1 && i==player.y) printf("{");
			else if(j==player.x+1 && i==player.y) printf("}");
			else if(j==obstacle.x && i==obstacle.y) printf("=");
			else if(j==obstacle.x-1 && i==obstacle.y) printf("[");
			else if(j==obstacle.x+1 && i==obstacle.y) printf("]");
			else if(j==obstacle2.x && i==obstacle2.y) printf("=");
			else if(j==obstacle2.x-1 && i==obstacle2.y) printf("[");
			else if(j==obstacle2.x+1 && i==obstacle2.y) printf("]");
			else if(j==obstacle3.x && i==obstacle3.y) printf("=");
			else if(j==obstacle3.x-1 && i==obstacle3.y) printf("[");
			else if(j==obstacle3.x+1 && i==obstacle3.y) printf("]");
			else printf(" ");
		}
		printf("\n");
	}
	printf("Score = %.0f\n", score);
	printf("Speed = %.3fx\n", speed);
	printf("\nPress r: return to main menu\n");
}

void save(char curname[10]){
	overall[rep].score = score*speed; strcpy(overall[rep].name, curname);
	switch(diff){
		case 1: easy[ea].score = score*speed; strcpy(easy[ea].name, curname); break;
		case 2: medium[me].score = score*speed; strcpy(medium[me].name, curname); break;
		case 3: hard[ha].score = score*speed; strcpy(hard[ha].name, curname); break;
		case 4: insane[in].score = score*speed; strcpy(insane[in].name, curname); break;
		default: break;
	}
}

int main(){
	for(i=1;i<=m-1;i++){
		strcpy(easy[i].name, "EMPTY"); easy[i].score = 0;
		strcpy(medium[i].name, "EMPTY"); medium[i].score = 0;
		strcpy(hard[i].name, "EMPTY"); hard[i].score = 0;
		strcpy(insane[i].name, "EMPTY"); insane[i].score = 0;
	}
	restart:
		welcome();
		while(!gameover){
			draw();
			input();
			logic();
		}
		system("cls");
		printf("Game over!\n");
		printf("Your final score: %.2f\n", score*speed);
		char curname[10];
		printf("Enter your name: "); scanf("%[^\n]", &curname); getchar();
		rep = ea+me+ha+in;
		save(curname);
		goto restart;
	return 0;
}