#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#include "headers/tester.h"
#include "headers/functions.h"


bool main_tester(int argc, char** argv, enum speak_mode* SPEAK_MODE, int* tokens) {
	if (argc != 3) {
		printf("Wrong num of arguments, ERROR\n"); 
		return -1;
	}
	
	
	if (!strcmp(argv[2], "quard")) run_tests_quard();
	else if (!strcmp(argv[2], "parser")) run_tests_parser();
	else {
		printf("Unknown argument %s, ERROR\n", argv[2]);
		return -1;
	}
}

void print_failed_test(coefs quard_coefs, int num_of_sol_ref, double x1_ref, double x2_ref, double x1, double x2, int num_of_sol) {
	printf("\n");
	
	print_line(200);
	printf("TEST FAILED:\n\ta = %lg\n\tb = %lg\n\tc = %lg\n\n", quard_coefs.a_coef, quard_coefs.b_coef, quard_coefs.c_coef);
	printf("Expected: \n\tnum_of_sol = %d\n\tx1 = %lg\n\tx2 = %lg\n\n", num_of_sol_ref, x1_ref, x2_ref);
	printf("Got:\n\tnum_of_sol = %d\n\tx1 = %lg\n\tx2 = %lg\n",num_of_sol, x1, x2); 
	print_line(200);
	
	printf("\n");
}


bool struct_complex_eq(complex_num *x1, complex_num *x2) {
	if ((x1 -> real == x2 -> real) && (x1 -> imag == x2 -> imag)) return true;
	return false;
}

int run_one_quard_test(coefs quard_coefs, solutions_state num_of_sol_ref, double x1_ref, double x2_ref) {
	double x1 = NAN, x2 = NAN;
	solutions_state num_of_sol = solve(quard_coefs, &x1, &x2);
	printf("TEST\n");
	
	if (!double_eq(num_of_sol, num_of_sol_ref, ACCURACY)) {
		print_failed_test(quard_coefs, num_of_sol_ref, x1_ref, x2_ref, x1, x2, num_of_sol);
		return -1;
	}

	if (num_of_sol == TWO_SOLUTIONS) {
		if (x1 < x2) swap(&x1, &x2);
		if (x1_ref < x2_ref) swap(&x1, &x2);
		
		if ((x1 == x1_ref) && (x2 == x2_ref)) {printf("ERROR"); return 0;}
		else {
			print_failed_test(quard_coefs, num_of_sol_ref, x1_ref, x2_ref, x1, x2, num_of_sol);
			return -1;
		}
		
	}
	
	if (num_of_sol == ONE_SOLUTION) {
		if (x1 == x1_ref) return 0;
		else {
			print_failed_test(quard_coefs, num_of_sol_ref, x1_ref, x2_ref, x1, x2, num_of_sol);
			return -1;
		}
	}
	
	if (num_of_sol == INF_SOLUTIONS) return 0;
	
	//TODO
	
	if (num_of_sol == NO_SOLUTION) return 0;
	
	//TODO
}

int parse_file(char* file_name, int* all_tests, int* succsesfull_tests) {
	
	char path_name[BUFFSIZE] = "files/"; 
	coefs quard_coefs = {.a_coef = NAN, .b_coef = NAN, .c_coef = NAN};
	int solution_ref = -1;
	double x1_ref = NAN, x2_ref = NAN;

	
	
	if (check_if_txt(file_name)) 
	{
		FILE *pf = fopen(strcat(path_name, file_name), "r");
		if (pf == NULL) {
			printf("Error while opening file %s"
				   "\nTry again (enter any symb. to exit, c to continue).\n", file_name);
			fclose(pf);
			return FILE_ERROR;
		} else 
		{
			printf("file is open\n");
			
			
			while ((fscanf(pf, "%lf %lf %lf %d %lf %lf", &(quard_coefs.a_coef), &(quard_coefs.b_coef), &(quard_coefs.c_coef),
						   &solution_ref, &x1_ref, &x2_ref) == 6) && getc(pf) == '\n') {
				
				*all_tests += 1;
				
				*succsesfull_tests += 1 + run_one_quard_test(quard_coefs, solution_ref, x1_ref, x2_ref);
			}
			fclose(pf);
			return OK;
		}
	} else {
		printf("Make sure, that your input has one of this formats: (""name_of_file.txt"", stdin)"
			   "\nTry again (enter any symb. to exit, c to continue).\n"); 
		return FORMAT_ERROR;
	}
}


int run_tests_quard () {
	char buffer[BUFFSIZE];
	
	printf("Hi, this is quard_tester!\n");
	
	
	while (true) {	
		int all_tests = 0;
		int succsesfull_tests = 0;
		
		printf("Enter the name of file.txt where you want to test quard: ");
		fgets(buffer, BUFFSIZE, stdin); *strchr(buffer, '\n') = '\0';
		
		parse_file(buffer, &all_tests, &succsesfull_tests);
		
		if (all_tests) {
			printf("Succsesfull %%: %lg\n", (double)succsesfull_tests / all_tests)	;
		} else {
			printf("No tests runned(((\n");
		}
		
		
		if (tolower(getchar()) != 'c') break;
		eat_char();
	}
	
}

int run_tests_parser () {
	char buffer[BUFFSIZE] = {};
	char path_name[BUFFSIZE] = "files/";
	FILE *pf = NULL;
	
	printf("Hi, this is parser_tester!\n");
	
	while (true) {
		printf("Enter the name of file.txt where you want to test parser: ");
		fgets(buffer, BUFFSIZE, stdin); *strchr(buffer, '\n') = '\0';
		pf = fopen(strcat(path_name, buffer), "r");
		if(!(pf == NULL)) printf("Opened \n");
		while (fgets(buffer, BUFFSIZE, pf)) {
			*strchr(buffer, '\n') = '\0';
			coefs quard_coefc = {.a_coef = NAN, .b_coef = NAN, .c_coef = NAN};
			parse(buffer, &quard_coefc);
			printf("%-30s --> a=%+6.2f b=%+6.2f c=%+6.2f\n",
				   buffer, quard_coefc.a_coef, quard_coefc.b_coef, quard_coefc.c_coef);
		}
		fclose(pf);
		
		if (getchar() != 'c') break;
	}
	return 0;
}
