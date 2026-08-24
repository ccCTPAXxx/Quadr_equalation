#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <windows.h>

#include "functions.h"
#include "tester.h"
#include "ai.h"



int main(int argc, char** argv) 
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
	hello();
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED);
	
	if (argc > 1) {
		if(main_tester(argc, argv)) {
			return -1;
		} return 0;
	}

	coefs quard_coefc = {.a_coef = NAN, .b_coef = NAN, .c_coef = NAN};
	double x1 = NAN, x2 = NAN;

	char curr_input[BUFFSIZE] = {};
	char choose_ans_num = '\0';
	
	int tokens = random_num(10, 30);
	ai_speak(hConsole, "YO, you have $ tokens!\n", tokens);
	

	while (true) 
	{
		bool first_time_f = true;
		quard_coefc = (coefs){.a_coef = NAN, .b_coef = NAN, .c_coef = NAN};
		x1 = NAN, x2 = NAN;
		
		for (int i = 0; i < BUFFSIZE; i++) {
			curr_input[i] = 0;
		}
		choose_ans_num = '\0';

		while (enter_coef(&quard_coefc, &first_time_f, curr_input)) 
		{
			continue;
		}

		enum SOLUTONS_NUM number_of_solutions = solve(quard_coefc, &x1, &x2);

		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
		look_on_dif_num(number_of_solutions, x1, x2, stdout, quard_coefc);
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED);

		print_line(200);
		
		tokens = ai_count_tokens(quard_coefc, tokens);
		ai_speak(hConsole, "You have $ tokens left\n", tokens);
		printf("Enter c if you want to try another eq., enter f if you want to write your answer to file, enter p if u wanna see a parabola: ");

		if ((choose_ans_num = getchar()) != 'c') 
		{
			if (choose_ans_num == 'f') {
				eat_char();
				write_to_file(quard_coefc, x1, x2, number_of_solutions);
				continue;
			}
			if (choose_ans_num == 'p') {
				eat_char();
				draw_parabola(quard_coefc);
				continue;
			}
			break;
		}
		eat_char();
	}

	return 0;
}

