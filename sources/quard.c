#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>

#include "../headers/functions.h"
#include "../headers/tester.h"
#include "../headers/ai.h"
#include "../headers/console_helper.h"


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Works with a square equation ax^2 + bx + c = 0 by the simple way(--quiert only)
//!
//! @param [in] quard_coefs coefficients of quard_eq (coefs)
//! @param [in] x1 solution1 (double)
//! @param [in] x2 solution2 (double)
//!
//! @return func_status (int)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
int simple_solution(coefs* quard_coefs, double* x1, double* x2);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Linking all parts, that work in our on solving square eq.
//!
//! @param [in] quard_coefs coefficients of quard_eq (coefs)
//! @param [in] x1 solution1 (double*)
//! @param [in] x2 solution2 (double*)
//! @param [in] tokens avaivable tokens for nanoAi (int*)
//! @param [in] speak_mode speaking mode for nanoAi (enum speak_mode*)
//!
//! @return func_status (int)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
int do_all_work(coefs* quard_coefs, double* x1, double* x2, int* tokens, enum speak_mode SPEAK_MODE);


int main(int argc, char** argv) {
	srand(time(NULL));
	
	hello();
	
	int admin_tokens = -INFINITE;
	enum speak_mode SPEAK_MODE = NORMAL;
	
	if (argc > 1) {
		if (!main_helper(argc, argv, &SPEAK_MODE, &admin_tokens)) return -1;
	}

	coefs quard_coefc = {.a_coef = NAN, .b_coef = NAN, .c_coef = NAN};
	double x1 = NAN, x2 = NAN;
	
	int tokens = 0;
	
	if (SPEAK_MODE == SILENCE) {
		return simple_solution(&quard_coefc, &x1, &x2);
	}

	if (admin_tokens != -INFINITE) {
		tokens = admin_tokens;
	} else {
		tokens = random_num(10, 30);
	}

	ai_speak("YO, you have %d tokens!\n", SPEAK_MODE, tokens);

	while (true) {
		quard_coefc = (coefs){.a_coef = NAN, .b_coef = NAN, .c_coef = NAN};
		x1 = NAN, x2 = NAN;
		
		if (do_all_work(&quard_coefc, &x1, &x2, &tokens, SPEAK_MODE)) {
			return -1;
		}
		
		if (tokens <= 0) {
			ai_speak("Hmmmmm, I see, that you dont have tokens((\t(FUUUUU, %d tokens, bad boy)\n", SPEAK_MODE, tokens);
			if (ai_game(&tokens, SPEAK_MODE) == -1) return 0;
		}
		
	}

	return 0;
}


int do_all_work(coefs* quard_coefs, double* x1, double* x2, int* tokens, enum speak_mode SPEAK_MODE) {
	char curr_input[BUFFSIZE] = {};
	bool first_time_f = true;
	
	for (int i = 0; i < BUFFSIZE; i++) {
		curr_input[i] = 0;
	}
	
	while (enter_coef(quard_coefs, &first_time_f, curr_input)) {
		continue;
	}
	
	enum SOLUTONS_NUM number_of_solutions = solve(*quard_coefs, x1, x2);
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
	look_on_dif_num(number_of_solutions, *x1, *x2, stdout, *quard_coefs);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED);
	print_line(200);
	
	*tokens = ai_count_tokens(*quard_coefs, *tokens);
	ai_speak("You have %d tokens left\n", SPEAK_MODE, *tokens);

	printf("Enter c if you want to try another eq., enter f if you want to write your answer to file, enter p if u wanna see a parabola: ");
	
	char choose_ans_num = '\0';
	
	
	if ((choose_ans_num = getchar()) != 'c') {
		if (choose_ans_num == 'f') {
			eat_char();
			write_to_file(*quard_coefs, *x1, *x2, number_of_solutions);
			return 0;
		}
		if (choose_ans_num == 'p') {
			eat_char();
			draw_parabola(*quard_coefs);
			return 0;
		}
		printf("You exited my program((");
		return -1;
	}
	
	eat_char();
	return 0;
}


int simple_solution(coefs* quard_coefs, double* x1, double* x2) {
	while (true) {
		
		while (simple_enter(quard_coefs)) {
			continue;
		}
		
		enum SOLUTONS_NUM number_of_solutions = solve(*quard_coefs, x1, x2);
		
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
		look_on_dif_num(number_of_solutions, *x1, *x2, stdout, *quard_coefs);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED);
		printf("enter q if you want to quit, any other symb to continue ");
		
		if (getchar() == 'q') {
			return 0;
		}
		eat_char();
	}
}

