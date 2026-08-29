#include "functions.h"
#include "ai.h"

#ifndef _TESTER
#define _TESTER

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Gives other files acsess to tester.c, link testers in a cool thing
//!
//! @return func_status (int)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
bool main_tester(int argc, char** argv, enum speak_mode* SPEAK_MODE, int* tokens);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Runs tests for a quard_eq from some file,
//! shows how good my solver is in solving eq.
//!
//! Gives error in great case
//!
//! @return func_status (int)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
int run_tests_quard();


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Runs tests for a parser from some file,
//! shows how good this parser at getting coefs.
//!
//! @return func_status (int)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
int run_tests_parser();


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Searches test for quard_tester in format %lg %lg %lg %lg %lg %lg
//! in some txt file
//!
//! Calculates a percentage of succesfull tests
//!
//! @param [in] file_name name of file to parse (char*)
//! @param [in] all_tests num of tests parsed (int*)
//! @param [in] succsesfull_tests num of tests tests, that are parsed successfuly (int*)
//! @return func_status (int)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
int parse_file(char* file_name, int* all_tests, int* succesfull_tests);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Runs the single test of quard
//!
//!
//! @param [in] quard_coefs (coefs)
//! @param [in] num_of_sol_ref num of solution, that this quard must have (solutions_state)
//! @param [in] x1_ref what first solution must be like (double)
//! @param [in] x2_ref what second solution must be like (double)
//! @return test status (int)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
int run_one_quard_test(coefs quard_coefs, solutions_state num_of_sol_ref, double x1_ref, double x2_ref);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Returns true if two complex nums equals to each other
//!
//! @param [in] x1 first complex num (complex_num*)
//! @param [in] x2 second complex num (complex_num*)
//!
//! @return is_equal (bool)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
bool struct_complex_eq(complex_num *x1, complex_num *x2);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Prints beautifull output for failed test
//!
//!
//! @param [in] quard_coefs (coefs)
//! @param [in] num_of_sol_ref num of solution, that this quard must have (solutions_state)
//! @param [in] x1_ref what first solution must be like (double)
//! @param [in] x2_ref what second solution must be like (double)
//! @param [in] num_of_sol count of solutions that my function got (solutions_state)
//! @param [in] x1_ref that my function got (double)
//! @param [in] x2_ref that my function got (double)
//! @return (void)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
void print_failed_test(coefs quard_coefs, int num_of_sol_ref, double x1_ref, double x2_ref, double x1, double x2, int num_of_sol);
#endif
