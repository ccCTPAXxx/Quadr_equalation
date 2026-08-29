#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h>


#include "console_helper.h"
#include "tag_and_toy.h"
#include "functions.h"


#define POLE_WIDTH 3
#define POLE_HIGHT 3



double get_good_time() {
	struct timespec now;
	clock_gettime(CLOCK_REALTIME, &now);
	
	return now.tv_sec + now.tv_nsec * 1e-9;
}


int slow_printf(const char* format, double think_time, ...) {
	char buffer[BUFFSIZE] = {};
	
	va_list ap;
	va_start(ap, think_time);
	
	vsnprintf(buffer, BUFFSIZE, format, ap);
	
	for (const char* p = buffer; *p != '\0'; ++p) {
		
		double start_time = get_good_time(); 
		
		if (*p == ' ') {
			while (get_good_time() - start_time < think_time) {
				continue;
			}
		}
		
		putc(*p, stdout);
	}
	
	va_end(ap);
	return 0;
}


int random_num(int from, int to) {
	return (rand() % (to + 1 - from)) + from;
}


int ai_count_tokens(coefs coefs_quard, int tokens) {
	return tokens - (fabs(coefs_quard.a_coef) + fabs(coefs_quard.b_coef) + fabs(coefs_quard.c_coef));
}


void ai_speak(const char* format, enum speak_mode MODE, ...) {
	
	va_list ap;
	va_start(ap, MODE);
	
	char buffer[BUFFSIZE];
	char* p = buffer;
	
	double think_time = 0.2;
	
	strcpy(buffer, format);
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE);
	
	if (MODE == LOUD) {
		slow_printf("SHOUTINGnanoAI: ", think_time);
		while (*p) {
			*p = toupper(*p);
			p++;
		}
	} else {
		slow_printf("nanoAI: ", think_time);	
	}
	
	slow_printf(buffer, 0.2, va_arg(ap, int));
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED);
	
	va_end(ap);
}


int get_player_choice(char* pole) {
	int player_choice = 0;
	scanf("%d", &player_choice); getchar();
	*(pole + player_choice) = 'O';
	
	return 0;
}


void display_board(const char* position) {
	printf("\n\n"
		   
		   " %c | %c | %c \n"
		   "---+---+---\n"
		   " %c | %c | %c \n"
		   "---+---+---\n"
		   " %c | %c | %c \n" "\n\n",
		   (position[0] == ' ')? '0' + 0 : position[0], 
		   (position[1] == ' ')? '0' + 1 : position[1],
		   (position[2] == ' ')? '0' + 2 : position[2],
		   (position[3] == ' ')? '0' + 3 : position[3], 
		   (position[4] == ' ')? '0' + 4 : position[4],
		   (position[5] == ' ')? '0' + 5 : position[5],
		   (position[6] == ' ')? '0' + 6 : position[6],
		   (position[7] == ' ')? '0' + 7 : position[7],
		   (position[8] == ' ')? '0' + 8 : position[8]
		   );
			   
	

}


int tries_another_game(int tokens, enum speak_mode MODE) {
	ai_speak("Wanna try again? (y/n)\n", INFINITE, MODE);
	
	if (getchar() == 'y') {
		eat_char();
		ai_speak("Oh, another great game!))\n", MODE);
		return 0;
	}
	eat_char();
	
	if (tokens >= 0) {
		ai_speak("Come back, when you want to get more tokens, you are the nice player)) Good luck!\n", MODE);
		return 1;
	}
	
	ai_speak("Idi guliay, loser\n", MODE);
	return -1;
	
}

void reset_game(char* game_position, int* player_choice, int* game_round) {
	for (int i = 0; i < 9; i++) {
		game_position[i] = ' ';
	}
	
	*player_choice = -1;
	*game_round = 0;  
}


int ai_game(int* tokens, enum speak_mode MODE) {
	ai_speak("Hehehe, you have no tokens, win me to get more\n", MODE);
	
	int repeat_choice;
	
	char game_position[10] = {
		' ', ' ', ' ',
		' ', ' ', ' ',
		' ', ' ', ' ',
		'\0'
	};
	
	int player_choice = -1;
	int game_round = 0;  
	
	while (true) {
		
		printf("Round: %d", ++game_round);
			
		computer_move(game_position, 'X');
		
		display_board(game_position);
		
		if (check_win(game_position, 'X')) {
			printf("Game ended, AI won(\n");
			if ((repeat_choice = tries_another_game(*tokens, MODE)) == 0) {
				reset_game(game_position, &player_choice, &game_round);
				continue;
			}
			return repeat_choice;
		}
		if (!check_avaivable(game_position)) {
			printf("Draw\n");
			if ((repeat_choice = tries_another_game(*tokens, MODE)) == 0) {
				reset_game(game_position, &player_choice, &game_round);
				continue;
			}
			return repeat_choice;
		}
		
		bool good_enter = false;
		while (true) {
			
			printf("Please enter the cell, where you want to place 0: ");
			
			good_enter = scanf("%d", &player_choice); eat_char();
			
			if (0 > player_choice || player_choice > 8 || good_enter == false) {
				printf("Your enter is incorrect, enter 0 - 8 num, try again\n");
				continue;
			}
			
			if (game_position[player_choice] != ' ') {
				printf("This position is already set, try again\n");
				continue;
			}
			
			break;
		}
		
		game_position[player_choice] = 'O';
		
		display_board(game_position);
		
		if (check_win(game_position, 'O')) {
			printf("Game ended, you won!!!!!\n");
			if (*tokens <= 0) *tokens = random_num(10, 30);
			else *tokens += random_num(10, 30);
			ai_speak("YO, you have %d tokens!\n", MODE, *tokens);
			if ((repeat_choice = tries_another_game(*tokens, MODE)) == 0) {
				reset_game(game_position, &player_choice, &game_round);
				continue;
			}
			return repeat_choice;
		}
		if (!check_avaivable(game_position)) {
			printf("Draw\n");
			if ((repeat_choice = tries_another_game(*tokens, MODE)) == 0) {
				reset_game(game_position, &player_choice, &game_round);
				continue;
			}
			return repeat_choice;
		}
		
	}

	printf("UB, ERROR"); exit(-1);
	return -1;
}

//void ai_is_thinking(time_t time_to_think, enum speak_mode MODE) {
//	ai_speak("Thinking...\n", MODE);
//	time_t start_thinking = time(NULL);
//	
//	while((time(NULL) - start_thinking) < time_to_think) {
//		continue;
//	}
//	
//	if (!(random_num(0, 100) % 5)) ai_speak("\nPTPTPT\n", MODE);
//	ai_speak("Oh, here is what I think: \n", MODE);
//}
//


