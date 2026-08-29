#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../headers/ai.h"

#define X_SIZE 3
#define Y_SIZE 3


bool check_win(char* position, char player) {
	for (int i = 0; i < Y_SIZE; i++) {
		if ((position[i * X_SIZE] == position[i * X_SIZE + 1]) && (position[i * X_SIZE + 1] == position[i * X_SIZE + 2]) &&
			(position[i * X_SIZE + 2] == player)) {
			return true;
		}
	}
	for (int i = 0; i < X_SIZE; i++) {
		if ((position[i] == position[i + 3]) && (position[i + 3] == position[i + 6]) &&
			(position[i + 6] == player)) {
			return true;
		}
	}
	
    if ((position[0] == position[4]) && (position[4] == position[8]) && (position[8] == player))
		return true;
	if ((position[2] == position[4]) && (position[4] == position[6]) && (position[6] == player))
		return true;
	
	return false;
}


bool check_avaivable(char* position) {
	for (int i = 0; i < Y_SIZE; i++) {
		for (int j = 0; j < X_SIZE; j++) {
			if (position[i * X_SIZE + j] == ' '){
				return true;
			}
		}
	}
	return false;
}


int minimax(char* position, unsigned int depth, bool is_maximazing) {
	if (check_win(position, 'X')) {
		return 10 - depth;
	}
	if (check_win(position, 'O')) {
		return depth - 10;
	}
	if (strchr(position, ' ') == NULL) {
		return 0;
	}
	
	if (is_maximazing) {
		int best_score = -1000;
		int score = -1000;
		for (int i = 0; i < X_SIZE * Y_SIZE; i++) {
			if (position[i] == ' ') {
				position[i] = 'X';
				score = minimax(position, depth + 1, false);
				position[i] = ' ';
				if (score > best_score) {
					best_score = score;
				}
			}
		}
		return best_score;
	} else {
		int best_score = 1000;
		int score = 1000;
		for (int i = 0; i < X_SIZE * Y_SIZE; i++) {
			if (position[i] == ' ') {
				position[i] = 'O';
				score = minimax(position, depth + 1, true);
				position[i] = ' ';
				if (score < best_score) {
					best_score = score;
				}
			}
		}
		return best_score;
	}
	
}

void computer_move(char* position, char player) {
	double random_chance = 0.0;
	int best_move = -1;
	
	double random = ((double)random_num(0, 100) / 100);
	
	if (random < random_chance) {
		int available_moves[X_SIZE * Y_SIZE] = {};
		int has_moves = 0;
		
		for (int i = 0; i < X_SIZE * Y_SIZE; i++) {
			if (position[i] == ' ') {
				available_moves[has_moves++] = i;
			}
		}
		
		printf("\nheh, Ai made a random move))\n");
		
		if (has_moves) {
			best_move = available_moves[random_num(0, has_moves - 1)];
			position[best_move] = player;
			return;
		}
	} 
	
	int best_score = 0, score = 0;
	
	if (player == 'X') best_score = -1000;
	else best_score = 1000;
	
	bool is_maximizing = (player == 'X');
	
	for (int i = 0; i < X_SIZE * Y_SIZE; i++) {
		if (position[i] ==' ') {
			position[i] = player;
			score = minimax(position, 0, !is_maximizing);
			position[i] = ' ';
			
			if (is_maximizing) {
				if (score > best_score) {
					best_score = score;
					best_move = i;
				}
			} else {
				if (score < best_score) {
					best_score = score;
					best_move = i;
				}
			}
		}
	}
	
	if (best_move != -1) {
		position[best_move] = player;
	}
}


