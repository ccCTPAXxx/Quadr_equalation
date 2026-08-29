#include <windows.h>
#include <time.h>
#include "functions.h"
#include "console_helper.h"

#ifndef _AI_LIB
#define _AI_LIB


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Returns random num from a to b [a:b]
//!
//!
//! @param [in] from left border (int)
//! @param [in] to right border (int)
//! @return random num (int)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
int random_num(int from, int to);

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Runs a game in tag and toy with nanoAi
//!
//!
//! @param [out] tokens that you will get if you win(int*)
//! @param [in] MODE the tone in which ai will speak with you(speak_mode)
//! @return game status (int)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
int ai_game(int* tokens, enum speak_mode MODE);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Resets game in tag and toy with nanoAi
//!
//!
//! @param [in] game_position the playing board (char*)
//! @param [in] player_choice the cell, picked by player(int*)
//! @param [in] number of game round (int*)
//! @return (void)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
void reset_game(char* game_position, int* player_choice, int* game_round);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Ask user if he wants to play another game (pleeease, sir)
//!
//!
//! @param [out] tokens that you have, it helps ai to choose mood(int*)
//! @param [in] MODE the tone in which ai will speak with you(speak_mode)
//! @return test status (int)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
int tries_another_game(int tokens, enum speak_mode MODE);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Displays the current board position
//!
//!
//! @param [in] quard_coefs (coefs)
//! @param [in] position the playing board (char*)
//! @return (void)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
void display_board(const char* position);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Playses player char on some position
//!
//! @param [in] pole the playing board (char*)
//! @return (void)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
int get_player_choice(char* pole);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Function for synthesizing nanoAi speach
//!
//! @param [in] format template of speach (char*)
//! @param [in] MODE the tone in which ai will speak with you(speak_mode)
//! @return (void)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
void ai_speak(const char* format, enum speak_mode MODE, ...);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Function to help nanoAi count tokens, that user uses to solve eq.
//!
//! @param [in] coefs_quard things to summ up (coefs)
//! @param [in] tokens num of tokens, that user got now (int)
//! @return new number of tokens (int)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
int ai_count_tokens(coefs coefs_quard, int tokens);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Function for synthesizing nanoAi speach (gives slow out, "thinking" think_time seconds on ' ' char)
//!
//! @param [in] format template of speach (char*)
//! @param [in] think_time time to think on ' ' (double)
//! @return func_status (int)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
int slow_printf(const char* format, double think_time, ...);

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Returns exact time (1e-9) (time * 1e9 (ns))
//!
//! @return time (double)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
double get_good_time();
#endif
