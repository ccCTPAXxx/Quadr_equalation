#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "headers/console_helper.h"
#include "headers/ai.h"
#include "headers/tester.h"

bool c_help(int argc, char** argv, enum speak_mode* SPEAK_MODE, int* tokens);
bool c_version(int argc, char** argv, enum speak_mode* SPEAK_MODE, int* tokens);
bool c_give_tokens(int argc, char** argv, enum speak_mode* SPEAK_MODE, int* tokens);
bool c_quiert(int argc, char** argv, enum speak_mode* SPEAK_MODE, int* tokens);
bool c_loud(int argc, char** argv, enum speak_mode* SPEAK_MODE, int* tokens);

typedef bool (*command_union)(int argc, char** argv, enum speak_mode* SPEAK_MODE, int* tokens);

typedef struct {
	const char* flag;
	command_union function;
} command;

bool main_helper(int argc, char** argv, enum speak_mode* SPEAK_MODE, int* tokens) {
	if ((argc != 3) && (argc != 2)) {
		
		printf("Wrong num of arguments %d, ERROR\n", argc); 
		return -1;
	}
		
	const command commands[] = {
		{"--tester",  main_tester},
		{"--help",    c_help},
		{"--version", c_version},
		{"--quiert",  c_quiert},
		{"--loud",    c_loud},
		{"--token",   c_give_tokens}
	};
	
	
	for (int i = 0; i < sizeof(commands) / sizeof(commands[0]); i++) {
		if (!strcmp(argv[1], commands[i].flag)) {
			return commands[i].function(argc, argv, SPEAK_MODE, tokens);
		}
	}
	return false;
}

bool c_help(int argc, char** argv, enum speak_mode* SPEAK_MODE, int* tokens) {
	printf("Program has next flags:\n"
		   "\t--help\n"
		   "\t--tester (quard, parser)\n"
		   "\t--version\n"
		   "\t--token n (admin mode)))\n"
		   "\t--quiert\n"
		   "\t--loud\n");
	
	printf("\nAlso program can work with files.txt (they must be in same folder with exe)"
		   "\nRun program without any flags to see more possibilites\n");
	
	ai_speak("Hehehe", NORMAL);
	
	return false;
}

bool c_version(int argc, char** argv, enum speak_mode* SPEAK_MODE, int* tokens) {
	printf("version: 67-67-1\n\n");
	ai_speak("\n"
			 "\n/\\_____/\\"
			 "\n/  o   o  \\"
			 "\n( ==  ^  == )"
			 "\n)         ("
			 "\n(           )"
			 "\n( (  )   (  ) )"
			 "\n(__(__)___(__)__)"
			 "\n", NORMAL);
	
	return false;
}

bool c_give_tokens(int argc, char** argv, enum speak_mode* SPEAK_MODE, int* tokens) {
	int n = atoi(argv[2]);
	ai_speak("Shhhhhh, hi admin, i gave u %d tokens\n", NORMAL, n);
	*tokens = n;
	return true;
}

bool c_quiert(int argc, char** argv, enum speak_mode* SPEAK_MODE, int* tokens) {
	*SPEAK_MODE = SILENCE;
	ai_speak("Tishi mishi ai spit\n", NORMAL);
	return true;
}

bool c_loud(int argc, char** argv, enum speak_mode* SPEAK_MODE, int* tokens) {
	*SPEAK_MODE = LOUD;
	ai_speak("AAAAAAAAAAAAAAAA, PTPTPTPT\n", NORMAL);
	return true;
}




