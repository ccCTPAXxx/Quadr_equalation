#include <windows.h>
#include <time.h>
#include "functions.h"

#ifndef _AI_LIB
#define _AI_LIB

int random_num(int from, int to);
void ai_speak(HANDLE hConsole, char* phrase, int number);
int ai_count_tokens(coefs coefs_quard, int tokens);
void ai_is_thinking(HANDLE handle, time_t time_to_think);

#endif
