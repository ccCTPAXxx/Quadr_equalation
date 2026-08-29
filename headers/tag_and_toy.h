#ifndef _TAG_AND_TOY
#define _TAG_AND_TOY


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Makes a best move of computer in Ai tag and toy game
//!
//!
//! @param [in] position game_position right now (char*)
//! @param [in] player character of comp ('X') (char)
//! @return (void)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
void computer_move(char* position, char player);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Calculates a best move forcomputer in Ai tag and toy game by the recursion algorythm
//!
//!
//! @param [in] position game_position right now (char*)
//! @param [in] depth depth of recursion, (bigger recursion -> smaller abs of score) (unsigned int)
//! @param [in] is_maximazing (bool)
//! @return score score of cell for comp (int)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
int minimax(char* position, unsigned int depth, bool is_maximazing);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Cheks if there any avaivable cells
//!
//! @param [in] position game_position right now (char*)
//! @return has_avaivable (bool)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
bool check_avaivable(char* position);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Cheks if player won
//!
//! @param [in] position game_position right now (char*)
//! @param [in] player the guy whoose position is needed to check (char)
//! @return has_avaivable (bool)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐---------------
bool check_win(char* position, char player);

#endif
