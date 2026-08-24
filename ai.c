#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h>

#include "functions.h"
#include "data_tag_n_tay_ai.h"
#define POLE_WIDTH 3
#define POLE_HIGHT 3

int random_num(int from, int to) {
	srand(time(NULL));
	
	return (rand() % (to + 1 - from)) + from;
}

void swap_chars (char* a, char* b) {
	char temp = *a;
	*a = *b; *b = temp; 
}

void mirror_matrix_vert(char pole[POLE_HIGHT][POLE_WIDTH]) {
	for (int i = 0; i < POLE_HIGHT; i++) {
		swap_chars(&pole[i][0], &pole[i][2]);
	}
}

void mirror_matrix_hor(char pole[POLE_HIGHT][POLE_WIDTH]) {
	for (int i = 0; i < POLE_WIDTH; i++) {
		swap_chars(&pole[0][i], &pole[2][i]);
	}
}

void copy(char to[3][3], char from[3][3]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			to[i][j] = from[i][j];
		}
	}
}

void povernut_matrica(char pole[POLE_HIGHT][POLE_WIDTH]) {
	char good[POLE_HIGHT][POLE_WIDTH] = {
		{pole[1/3][1%3], pole[2/3][2%3], pole[5/3][5%3]},
		{pole[0/3][0%3], pole[4/3][4%3], pole[8/3][8%3]},
		{pole[3/3][3%3], pole[6/3][6%3], pole[7/3][7%3]}
	};
	memcpy(pole, good, sizeof(char) * POLE_HIGHT * POLE_WIDTH);
	
	copy(pole, good);
}

void display_matrix(char pole[POLE_HIGHT][POLE_WIDTH]) {
	for (int i = 0; i < POLE_HIGHT; i++) {
		for (int j = 0; j < POLE_WIDTH; j++) {
			printf(" '%c' ", pole[i][j]);
		}
		printf("\n");
	}
}


int ai_count_tokens(coefs coefs_quard, int tokens) {
	return tokens - (fabs(coefs_quard.a_coef) + fabs(coefs_quard.b_coef) + fabs(coefs_quard.c_coef));
}


void ai_speak(HANDLE hConsole, char* phrase, int number) {
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
	
	printf("nanoAI: ");
	if (number == INFINITY) {
		puts(phrase);
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED);
		return;
	}

	for (int i = 0; i < strlen(phrase); i++) {
		if (phrase[i] != '$') {
			putchar(phrase[i]);
		} else {
			printf("%d", number);
		}
	}
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED);
}


int get_player_choice(char* pole) {
	int player_choice = 0;
	scanf("%d", &player_choice); getchar();
	*(pole + player_choice) = 'O';
	
	return 0;
}

bool situations_eq(char* pole, char* ref) {
	for (int i = 0; i < 3 * 3; i++) {
		if (*(pole + i) != *(ref + i)) {
			return false;
		}
	}
	return true;
}


//bool check_if_eq(char* pole, int round) {
//	if (round == 4) {
//		if (pole)
//	}
//}


int ai_game(HANDLE handle) {
	ai_speak(handle, "Hehehe, you have no tokens, win me to get more", (int)INFINITY);
	int round = 0;
	int choice = 0;
	char pole[3][3];
	memcpy(pole, _POLE_1_0, sizeof(char) * 9);
	
	printf("Round: %d\n", round++);
	display_matrix(pole);
	
	choice = random_num(0, 1);
	
	if(choice) {
		memcpy(pole, _POLE_2_0, sizeof(char) * 9);
	} else {
		memcpy(pole, _POLE_2_1, sizeof(char) * 9);
	}
	printf("Round: %d\n", round++);
	display_matrix(pole);
	get_player_choice(&pole[0][0]);
	display_matrix(pole);
	printf("Round: %d\n", round++);
	
	
	
	
	return 0;
}

void ai_is_thinking(HANDLE handle, time_t time_to_think) {
	ai_speak(handle, "Thinking...\n", (int)INFINITY);
	time_t start_thinking = time(NULL);
	while((time(NULL) - start_thinking) < time_to_think) {
		continue;
	}
	if (!(random_num(0, 100) % 5)) ai_speak(handle, "\nPTPTPT\n", (int)INFINITY);
	ai_speak(handle, "Oh, here is what I think: \n", (int)INFINITY);
}


int main() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	ai_game(hConsole);
	
	
}
