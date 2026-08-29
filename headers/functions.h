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
	OK, /**< everything is fine*/
	ENTER_ERROR, /** you entered some of the programm comands incorrectly*/
	FORMAT_ERROR, /**< incorrect file format given*/
	FILE_ERROR, /**< error while working with file*/
	MEMORY_ERROR /**< cant malloc() enoght memory*/
} return_codes;


typedef struct Complex_num {
	double real;
	double imag;
} complex_num;

/*
* @brief saves coefs of your quard eq. 
*/
typedef struct {
	double a_coef, b_coef, c_coef; /**< coefs of your eq*/
} coefs;


/*
 * @brief Shows where the dot is
*/
struct dot {
	double x, y; /**< coords of your dot*/
};


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Says hello to user!
//!
//! @return (void)
//!
//! @note Adds a bit friendly interface
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
void hello();


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Solves a square equation ax^2 + bx + c = 0
//!
//! @param [in] a a‐coefficient (double)
//! @param [in] b b‐coefficient (double)
//! @param [in] c c‐coefficient (double)
//! @param [out] x1 Pointer to the 1st root (double*)
//! @param [out] x2 Pointer to the 2nd root (double*)
//!
//! @return Number of roots (int)
//!
//! @note In case of infinite number of roots,
//! returns INF_SOLUTIONS.
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
enum SOLUTONS_NUM solve(coefs quard_coefs, double *x1, double *x2);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Solves a square linear bx + c = 0
//!
//! @param [in] b b‐coefficient (double)
//! @param [in] c c‐coefficient (double)
//! @param [out] x1 Pointer to the root (double*)
//!
//! @return Number of roots (int)
//!
//! @note In case of infinite number of roots,
//! returns INF_SOLUTIONS.
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
enum SOLUTONS_NUM linear(double b_coef, double c_coef, double *x1);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Eats all chars to \n
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
void eat_char();


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Solves a square equation ax^2 + bx + c = 0 in complex numbers
//!
//! @param [in] a a‐coefficient (double)
//! @param [in] b b‐coefficient (double)
//! @param [in] c c‐coefficient (double)
//! @param [out] x1 Pointer to the 1st root (complex_num*)
//! @param [out] x2 Pointer to the 2nd root (complex_num*)
//!
//! @return (void)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
void complex_f(coefs quard_coefs, complex_num *x1, complex_num *x2);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Displays the answer on eq, looking on the number of solutions
//!
//! @param [in] root_status (SOLUTION_NUM)
//! @param [in] x1 (double)
//! @param [in] x2 (double)
//! @param [in] file_pointer (FILE*)
//! @param [in] quard_coefs (coefs)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
void look_on_dif_num (enum SOLUTONS_NUM root_status, double x1, double x2, FILE* fp, coefs quard_coefs);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Checks if file is txt.
//!
//! @param [in] curr_input name of file (char*)
//!
//! @return if file is txt (true)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
bool check_if_txt(char* curr_input);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Draw a graph for a square equation ax^2 + bx + c = 0 in console
//!
//! @param [in] quard_coefs (coefs)
//!
//! @return (void)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
void draw_parabola(coefs quard_coefs);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Swapping two double values
//!
//! @param [out] a (double*)
//! @param [out] b (double*)
//!
//! @return (void)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
void swap(double* a, double* b);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Getting coefs for a square equation ax^2 + bx + c = 0 with --quiert param, only stdin
//!
//! @param [out] quard_coefs (coefs*)
//!
//! @return func_status (int)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
int simple_enter(coefs* quard_coefs);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Prints a line of '-'
//!
//! @param [in] num_of_symb (int)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
void print_line(int num_of_symb);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Displays eq without any front 0 and 1
//!
//! @param [in] quard_coefs (coefs)
//! @param [in] pf pointer to file (FILE*)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
void correct_display(coefs quard_coefs, FILE* pf);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Draw a graph for a square equation ax^2 + bx + c = 0 in console, when 3 dots are given
//!
//! @return (void)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
void little_parabolka();


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Writes an answer for a square equation ax^2 + bx + c = 0 in file
//!
//! @param [in] quard_coefs coefficients of quard_eq (coefs)
//! @param [in] x1 solution1 (double)
//! @param [in] x2 solution2 (double)
//! @param [in] root_status (SOLUTIONS_NUM);
//!
//! @return func_status (int)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
enum RETURN_CODES write_to_file(coefs quard_coefs, double x1, double x2, enum SOLUTONS_NUM root_status);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Displays two complex colutions
//!
//! @param [in] x1 Pointer to the 1st root (complex_num*)
//! @param [in] x2 Pointer to the 2nd root (complex_num*)
//!
//! @return (void)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
void display_complex(FILE *pf, complex_num *x1, complex_num *x2);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Says if two double nums almost same
//!
//! @param [in] a first-num (double)
//! @param [in] b second-num (double)
//! @param [in] w err_var (double)
//!
//! @return Equalition of double nums (bool)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
bool double_eq(double a, double b, double w);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Getting coefs for a square equation ax^2 + bx + c = 0 with --quiert param, only stdin
//!
//! @param [out] quard_coefs (coefs*)
//!
//! @return func_status (int)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
int simple_enter(coefs* quard_coefs);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Getting coefs for a square equation ax^2 + bx + c = 0
//!
//! @param [out] quard_coefs (coefs*)
//!
//! @return (void)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
int enter_coef(coefs* quard_coefs, bool *first_time_f, char* curr_input);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! parses a coeficents of quard eq into quard_coefs
//!
//! @param [in] p pointer on str (const char**)
//! @param [in] quard_coefs struct of eq coefs (const char**)
//!
//! @return func_status (int)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
int parse(const char *s, coefs* quard_coefs);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Eats all spaces to first character
//!
//! @param [in] p pointer on str (const char**)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
void eat_spaces(const char **p);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Reads a, b, c koeffs for quadr. eq. from file
//!
//! @param [out] a a‐coefficient (double*)
//! @param [out] b b‐coefficient (double*)
//! @param [out] c c‐coefficient (double*)
//! @param [in] pf Pointer to the file (FILE*)
//! @param [in] f_name name of file (char*)
//!
//! @return func_status (int)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
int read_from_file(char *f_name, FILE *point_file, coefs* quard_coefs);
#endif
