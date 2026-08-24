#include <stdio.h>
#include <stdbool.h>

#ifndef _MY_FUNC
#define _MY_FUNC

#define BUFFSIZE 256
#define ACCURACY 1e-5

////////////PARABOLA///////////////
#define WIDTH 210
#define HEIGHT 120
#define X_MIN -15.0
#define X_MAX 15.0
#define Y_MIN -15.0
#define Y_MAX 15.0
////////////PARABOLA///////////////

typedef enum SOLUTONS_NUM 
{
	NO_SOLUTION, 
	ONE_SOLUTION, 
	TWO_SOLUTIONS, 
	INF_SOLUTIONS
} solutions_state;

typedef enum RETURN_CODES 
{
	OK, 
	ENTER_ERROR, 
	FORMAT_ERROR, 
	FILE_ERROR,
	MEMORY_ERROR
} return_codes;


typedef struct Complex_num {
	double real;
	double imag;
} complex_num;

typedef struct {double a_coef, b_coef, c_coef;} coefs;


void hello();

int enter_coef
(
	coefs* quard_coefs, 
	bool *first_time_f, 
	char* curr_input
);

solutions_state solve
(
	coefs quard_coefs,
	double *x1, 
	double *x2
);

void eat_char();

bool double_eq
(
	double a_num, 
	double b_num, 
	double epsilon
);

void complex_f
(
	coefs quard_coefs,
	complex_num *x1, 
	complex_num *x2
);

void display_complex
(
	FILE *pointer_file, 
	complex_num *x1, 
	complex_num *x2
);


return_codes write_to_file
(
	coefs quard_coefs,
	double x1, 
	double x2, 
	enum SOLUTONS_NUM root_status
);

void look_on_dif_num 
(
	enum SOLUTONS_NUM root_status, 
	double x1, 
	double x2, 
	FILE* fp, 
	coefs quard_coefs
);

void print_line(int num_of_chars);
bool check_if_txt(char* curr_input);
int parse(const char *s, coefs* quard_coefs);
void draw_parabola(coefs quard_coefs);
double absolute(double n);
void swap(double* a, double* b);

#endif
