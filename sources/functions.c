#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <windows.h>

#include "../headers/functions.h"


void eat_char() {
	while (getchar() != '\n');
}


void print_line(int num_of_symb) {
	for (int i = 0; i < num_of_symb; i++) 
	{
		putchar('-');
	}
	printf("\n");
}


void correct_display(coefs quard_coefs, FILE* pf) {
	
	fprintf(pf, "Your eq looks like: ");
	if (quard_coefs.a_coef) {
		if (fabs(quard_coefs.a_coef) == 1) {
			fprintf(pf, "%cx^2 ", (quard_coefs.a_coef < 0)? '-' : ' ');
		} else {
			fprintf(pf, "%c %lgx^2 ", (quard_coefs.a_coef < 0)? '-' : ' ', fabs(quard_coefs.a_coef));
		}
	}
	if (quard_coefs.b_coef) {
		if (fabs(quard_coefs.b_coef) == 1) {
			fprintf(pf, "%cx ", (quard_coefs.b_coef < 0)? '-' : '+');
		} else {
			fprintf(pf, "%c%lgx ", (quard_coefs.b_coef < 0)? '-' : '+', fabs(quard_coefs.b_coef));
		}
	}
	if (quard_coefs.c_coef) {
		fprintf(pf, "%c%lg", (quard_coefs.c_coef < 0)? '-' : '+', fabs(quard_coefs.c_coef));
	}
	fprintf(pf, " = 0\n");
}


void look_on_dif_num (enum SOLUTONS_NUM root_status, double x1, double x2, FILE* file_pointer, coefs quard_coefs) {
	
	correct_display(quard_coefs, file_pointer);
	
	switch (root_status) {
		
	case TWO_SOLUTIONS:
		fprintf(file_pointer, "Your eq. has 2 sol:\n"
				"\tx1 = %.2lg\n"
				"\tx2 = %.2lg\n", 
				x1, x2);
		break;
		
	case ONE_SOLUTION:
		fprintf(file_pointer, "Your eq. has 1 sol:\n"
				"\tx1 = %.2lg\n", x1);
		break;
		
	case NO_SOLUTION:
		fprintf(file_pointer, "Your eq. has no solutions in real nums(\n");	

		
		if (quard_coefs.a_coef) {
			complex_num x1_c = { .real = 0, .imag = 0}, x2_c = {.real = 0, .imag = 0};
			complex_f(quard_coefs, &x1_c, &x2_c); display_complex(file_pointer, &x1_c, &x2_c);
		} else {
			fprintf(file_pointer, "Your eq. have even no solutions in complex nums(((\n");
		}

		break;
		
	case INF_SOLUTIONS:
		fprintf(file_pointer, "Your eq. has inf num of solutions!!!\n");
		break;
		
	default:
		fprintf(stderr, "ERROR, UB\n");
		exit(-1);
		break;
	}
}


bool check_if_txt(char* curr_input) {	
	assert(curr_input != NULL);
	
	if (strchr(curr_input, ' ') != NULL) 
		return false;
	
	char *ch_p = strchr(curr_input, '.');
	
	if (ch_p == NULL || !(*(ch_p + 1) == 't' && *(ch_p + 2) == 'x' && *(ch_p + 3) == 't' && *(ch_p + 4) == '\0')) {
		return false;
	}
	return true;
}


void complex_f(coefs quard_coefs, complex_num *x1, complex_num *x2) {
	assert(quard_coefs.a_coef != 0);
	assert(x1 != NULL); assert(x2 != NULL);
	
	x1 -> real = x2 -> real = -quard_coefs.b_coef / (2 * quard_coefs.a_coef);
	
	double min_D = -(quard_coefs.b_coef * quard_coefs.b_coef - 4 * quard_coefs.a_coef * quard_coefs.c_coef); 
	
	x1 -> imag = -(x2 -> imag = sqrt(min_D) / (2 * quard_coefs.a_coef));
}



void hello() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
	print_line(200);
	printf("Hi, this program can solve quadratic equalitions!!!\n"
		   "\tWritten by Ivan.\n"
		   "\n\t --help to see more info\n");
	print_line(200);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED);
	
}


enum SOLUTONS_NUM linear(double b_coef, double c_coef, double *x1) {	
	assert(x1 != NULL);
	
	if (double_eq(b_coef, 0, 1e-5)) {
		if (double_eq(c_coef, 0, 1e-5)) {
			return INF_SOLUTIONS;
		}
		return NO_SOLUTION;
	}
	*x1 = c_coef / b_coef;
	return ONE_SOLUTION;
}

enum SOLUTONS_NUM experimental_solve(coefs quard_coefs, double *x1, double *x2) {
	printf("Experiments will be here later, i m tired, sorry((\n");
}


enum SOLUTONS_NUM solve(coefs quard_coefs, double *x1, double *x2) {
	assert(x1 != NULL); assert(x2 != NULL); assert(x1 != x2);
	
	printf("Do you want to try some experiments?)) (y/n) ");
	if (getchar() == 'y') {
		eat_char();
		
		experimental_solve(quard_coefs, x1, x2);
		
		
	} else {
		eat_char();
	}
	
	if (double_eq(quard_coefs.a_coef, 0, 1e-5)) {
		return linear(quard_coefs.b_coef, quard_coefs.c_coef, x1);
	}
	
	double D = quard_coefs.b_coef * quard_coefs.b_coef - 4 * quard_coefs.a_coef * quard_coefs.c_coef;
	
	if (double_eq(D, 0, 1e-5)) {
		*x1 = -((double_eq(quard_coefs.b_coef, 0, 1e-5))? -quard_coefs.b_coef : quard_coefs.b_coef) / (2 * quard_coefs.a_coef);
		return ONE_SOLUTION;
	} else if (D < 0) {
		return NO_SOLUTION;
	} else {
		*x1 = (-quard_coefs.b_coef - sqrt(D)) / (2 * quard_coefs.a_coef);
		*x2 = (-quard_coefs.b_coef + sqrt(D)) / (2 * quard_coefs.a_coef);
		return TWO_SOLUTIONS;
	}
}


int read_from_file(char *f_name, FILE *point_file, coefs* quard_coefs) {
	
	assert(f_name != NULL); assert(point_file != NULL); assert(strlen(f_name) > 0); 
	
	if ((fscanf(point_file, "%lf %lf %lf", &(quard_coefs -> a_coef), &(quard_coefs -> b_coef), &(quard_coefs -> c_coef)) == 3) &&
		isfinite(quard_coefs ->a_coef) && isfinite(quard_coefs -> b_coef) && isfinite(quard_coefs -> c_coef)) {
		printf("We found eq. %.0lfx^2 %c_coef %.0lfx %c_coef %.0lf = 0 in your file %s.\n", quard_coefs -> a_coef, 
			   (quard_coefs -> b_coef < 0)? '-' : '+', fabs(quard_coefs -> b_coef), (quard_coefs -> c_coef < 0)? '-' : '+', 
			   fabs(quard_coefs -> c_coef), f_name);
		fclose(point_file);
		return OK;
	} else {
		printf("Check if you have format (%%lg %%lg %%lg) in your file %s, try again (enter any symb. to exit, c to continue).\n", f_name);
		fclose(point_file);
		return ENTER_ERROR;
	}
} 


void eat_spaces(const char **p) {
	while (isspace(**p)) (*p)++;
};


int parse(const char *s, coefs* quard_coefs) {
	
	assert(s != NULL); assert(quard_coefs != NULL);
	
	coefs ans = {.a_coef = 0, .b_coef = 0, .c_coef = 0};
	int side = 1, sign = 1, power = 0;
	double coef = 1;
	const char *p = s;
	
	while (*p) {
		eat_spaces(&p);
		//while (isspace(*p)) p++;
		if (!*p) break;
		
		if (*p == '=') {
			side = -1; p++; eat_spaces(&p);
			//while (isspace(*p)) p++;
			sign = 1;
			continue;
		}
		
		if (*p == '+' || *p == '-') {
			sign = (*p == '+') ? 1 : -1;
			p++; eat_spaces(&p);
			//while (isspace(*p)) p++;
		} else sign = 1;
		
		char *end = NULL;
		double val = strtod(p, &end);
		
		bool has_coef = (end != p);
		
		if (has_coef) {
			coef = val; p = end;
		} else {
			coef = 1;
		}
		
		eat_spaces(&p);
		//while (isspace(*p)) p++;
		
		power = 0;
		if (toupper(*p) == 'X') {
			p++;
			
			if (*p == '^') {
				p++;
				
				if      (*p == '2') power = 2;
				else if (*p == '1') power = 1;
				else 				/* ERR */;
				
				p++;
			} 
			
			else 	
				power = 1;
			
			if (!has_coef) coef = 1;
		}
		
		if (power == 2) ans.a_coef += coef * sign * side;
		if (power == 1) ans.b_coef += coef * sign * side;
		if (power == 0) ans.c_coef += coef * sign * side;
		
		sign = 0; eat_spaces(&p);
		//while (isspace(*p)) p++;
	}
	quard_coefs -> a_coef = ans.a_coef; quard_coefs -> b_coef = ans.b_coef; quard_coefs -> c_coef = ans.c_coef;
	return OK;
}


int enter_coef(coefs* quard_coefs, bool *first_time_f, char* curr_input) {
	
	assert((quard_coefs -> a_coef != quard_coefs -> b_coef) && 
		   (quard_coefs -> b_coef != quard_coefs -> c_coef) && 
		   (&(quard_coefs -> c_coef) != NULL));
	assert(first_time_f != NULL); assert(curr_input != NULL);
	
	char tryier = 0;
	char buffer[BUFFSIZE];
	char path_name[BUFFSIZE] = "examples/";
	
	if (!*first_time_f && tolower(getchar()) != 'c') {
		printf("You exited my program("); exit(0);
	} 
	
	if (!*first_time_f) {
		eat_char();
	}
	
	*first_time_f = false;
	
	printf("Please, enter a stream where you get info from (""name_of_file.txt"", stdin) ");
	
	fgets(curr_input, BUFFSIZE, stdin); *strchr(curr_input, '\n') = '\0';
	
	if (strchr(curr_input, ' ')) {
		printf("Make sure, that your input has one of this formats: (""name_of_file.txt"", stdin)."
			   "\nTry again (enter any symb. to exit, c to continue).\n");
		
		return FORMAT_ERROR;
	}
	
	if (!strcmp("stdin", curr_input)) {
		printf("Please, enter coef of quadr. eq. (a, b, c) (Enter the '_' first if you want to parse string): ");
		
		
		if ((tryier = getchar()) == '_') {
			fgets(buffer, BUFFSIZE, stdin); *strchr(buffer, '\n') = '\0';
			parse(buffer, quard_coefs);
		}
		
		else {
			ungetc(tryier, stdin);
			if ((scanf("%lg %lg %lg", &(quard_coefs -> a_coef), &(quard_coefs -> b_coef), &(quard_coefs -> c_coef)) != 3) ||
				!isfinite(quard_coefs -> a_coef) || !isfinite(quard_coefs -> b_coef) || !isfinite(quard_coefs -> c_coef)) {
				printf("Make sure, that you entered 3 nums in format (%%lg %%lg %%lg)."
					   "\nTry again (enter any symb. to exit, c to continue).");
				eat_char();
				return ENTER_ERROR;
				
			} 
			if ((tryier = getchar()) != '\n') {
				printf("Make sure, that you entered 3 nums in format (%%lg %%lg %%lg)."
					   "\nTry again (enter any symb. to exit, c to continue).");
				eat_char();
				return ENTER_ERROR;
			}
		}
		
		
	} else if (check_if_txt(curr_input)) {
		strcat(path_name, curr_input);
		FILE* pf = fopen(path_name, "r");
		if (pf == NULL) {
			printf("Error while opening file %s"
				   "\nTry again (enter any symb. to exit, c to continue).\n", path_name);
			
			return FILE_ERROR;
		} else {
			printf("file is open\n");
			
			return read_from_file(curr_input, pf, quard_coefs);
		}
	} else {
		printf("Make sure, that your input has one of this formats: (""name_of_file.txt"", stdin)"
			   "\nTry again (enter any symb. to exit, c to continue).\n"); 
		
		return FORMAT_ERROR;
	}
	
	
	correct_display(*quard_coefs, stdin);
	return OK;
}


int simple_enter(coefs* quard_coefs) {
	
	printf("Please, enter coef of quadr. eq. (a, b, c): ");
	
	if ((scanf("%lg %lg %lg", &(quard_coefs -> a_coef), &(quard_coefs -> b_coef), &(quard_coefs -> c_coef)) != 3) ||
		!isfinite(quard_coefs -> a_coef) || !isfinite(quard_coefs -> b_coef) || !isfinite(quard_coefs -> c_coef)) {
		printf("Make sure, that you entered 3 nums in format (%%lg %%lg %%lg)."
			   "\nTry again (enter any symb. to exit, c to continue).");
		eat_char();
		return ENTER_ERROR;
		
	} 
	if ((getchar()) != '\n') {
		printf("Make sure, that you entered 3 nums in format (%%lg %%lg %%lg)."
			   "\nTry again (enter any symb. to exit, c to continue).");
		eat_char();
		return ENTER_ERROR;
	}
	
	correct_display(*quard_coefs, stdin);
	return OK;
}


void swap(double* a, double* b) {
	double temp = *a;
	*a = *b;
	*b = temp;
}


bool double_eq(double a, double b, double w) {
	return (a - w < b && b < a + w);
}


void display_complex(FILE *pf, complex_num *x1, complex_num *x2) {	
	assert((x1 != x2) && (x1 != NULL));
	
	fprintf(pf, "Your eq. has 2 complex solutions:\n\tx1 = %.2lg %c %.2lgi\n\tx2 = %.2lg %c %.2lgi\n", 
		   x1 -> real, (x1 -> imag < 0)? '-' : '+', fabs(x1 -> imag), 
		   x2 -> real, (x2 -> imag < 0)? '-' : '+', fabs(x2 -> imag)
		   );
}


enum RETURN_CODES write_to_file(coefs quard_coefs, double x1, double x2, enum SOLUTONS_NUM root_status) {
	char save_file[BUFFSIZE];
	char path_name[BUFFSIZE] = "examples/";
	FILE *fp = NULL;
	
	while (true) {
		printf("Enter the name of file, where you want to save results: ");
		fgets(save_file, BUFFSIZE, stdin); *strchr(save_file, '\n') = '\0'; 
		if (!check_if_txt(save_file)) {
			printf("You entered invalid txt file. Want to try again? y/n ");
			if (getchar() == 'n') {
				eat_char();
				return FORMAT_ERROR;
			}
			eat_char();
		}
		else break;
	}
	
	if ((fp = fopen(strcat(path_name, save_file), "w")) == NULL) {
		printf("Unable to open file %s", save_file); return FILE_ERROR;
	}
	
	look_on_dif_num(root_status, x1, x2, fp, quard_coefs);
	
	fclose(fp);
	print_line(100);
	return OK;
}


void draw_parabola(coefs quard_coefs) {
	print_line(200);
	
	char *screen = (char*)calloc(HEIGHT * WIDTH, sizeof(char));
	if (screen == NULL) {
		printf("Memory ERROR\n");
		return;
	}
	
	//init with ' '
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			screen[i * WIDTH + j] = ' ';
		}
	}
	
	int center_x = (int)(0.5 * WIDTH);
	int center_y = HEIGHT - (int)(0.5 * HEIGHT);
	
	// axes
	for (int j = 0; j < WIDTH; j++) {
		screen[center_y * WIDTH + j] = '-';
	}
	for (int i = 0; i < HEIGHT; i++) {
		screen[i * WIDTH + center_x] = '|';
	}
	screen[center_y * WIDTH + center_x] = '+';
	
	
	//X axe
	for (int x = X_MIN; x <= X_MAX; x += 1) {
		if (x == 0) continue;
		
		int spaces_to_x = (int)((x - X_MIN) / (X_MAX - X_MIN) * WIDTH);
		screen[center_y * WIDTH + spaces_to_x] = '|';
		
		// print numbers
		
		int digit = abs(x);
		if (digit < 10) {
			if (x > 0) {
				screen[(center_y + 1) * WIDTH + spaces_to_x] = '0' + digit;
			} else {
				screen[(center_y + 1) * WIDTH + spaces_to_x] = '-';
				screen[(center_y + 1) * WIDTH + spaces_to_x + 1] = '0' + digit;
			}
			
		}
	}
	
	// Y axe
	for (int y = -15; y <= 15; y += 1) {
		if (y == 0) continue;
		
		int spaces_to_y = HEIGHT - 1 - (int)((y - Y_MIN) / (Y_MAX - Y_MIN) * HEIGHT);
		screen[spaces_to_y * WIDTH + center_x] = '-';
		
		// print numbers
		int digit = abs(y);
		if (digit < 10) {
			if (y > 0) {
				screen[spaces_to_y * WIDTH + center_x - 2] = '0' + digit;
			} else {
				screen[spaces_to_y * WIDTH + center_x - 2] = '-';
				screen[spaces_to_y * WIDTH + center_x - 1] = '0' + digit;
			}
			
		}
	}
	
	// draw
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			double x = (double)j / WIDTH * (X_MAX - X_MIN) + X_MIN;
			double y = quard_coefs.a_coef * x * x + quard_coefs.b_coef * x + quard_coefs.c_coef;
			
			int spaces_to_y = HEIGHT - ((y + Y_MAX) / (Y_MAX - Y_MIN) * HEIGHT);
			if (spaces_to_y == i) {
				char cur = screen[i * WIDTH + j];
				if (cur == ' ') {
					screen[i * WIDTH + j] = '*';
				} else if (cur == '-' || cur == '|') {
					screen[i * WIDTH + j] = '+';
				}
			}
		}
	}
	
	//out
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			printf("%c", screen[i * WIDTH + j]);
		}
		printf("\n");
	}
	
	free(screen);
	print_line(200);
	
	little_parabolka();
	
}


void little_parabolka() {
		printf("Wanna draw parabola in other dots? (y/n): ");
	if (getchar() == 'y') {
		eat_char();
		
		struct dot dot1 = {}, dot2 = {}, dot3 = {};
		
		while (true) {
			printf("Enter dots, where you want to build a parabola (x1, y1, x2, y2, x3, y3)\n");
			if (scanf("%lg %lg %lg %lg %lg %lg", &(dot1.x), &(dot1.y), &(dot2.x), &(dot2.y), &(dot3.x), &(dot3.y)) == 6 && isfinite(dot1.x) && isfinite(dot1.y) && 
				isfinite(dot2.x) && isfinite(dot2.y) && isfinite(dot3.x) && isfinite(dot3.y)) {
				
				eat_char();
				
				double A1 = -pow(dot1.x, 2) + pow(dot2.x, 2), B1 = dot2.x - dot1.x, D1 = dot2.y - dot1.y,
				A2 = pow(dot3.x, 2) - pow(dot2.x, 2), B2 = dot3.x - dot2.x, D2 = dot3.y - dot2.y;
				
				double B_mult = -(B2/B1), A3 = B_mult * A1 + A2, D3 = B_mult * D1 + D2;
				double a_coef = D3/A3, b_coef = (D1 - A1 * a_coef) / B1, c_coef = dot1.y - a_coef * pow(dot1.x, 2) - b_coef * dot1.x; 
				
				
				coefs coefs_by_dots = {
					.a_coef = a_coef,
					.b_coef = b_coef,
					.c_coef = c_coef
				};
				
				draw_parabola(coefs_by_dots);
				break;
			}
			
			else {
				printf("Make sure that you are in format (%%lg %%lg %%lg %%lg %%lg %%lg) and try again\n");
				eat_char();
			}
		}
	}
	else {
		eat_char();
	}
}
