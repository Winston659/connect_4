#include <iostream>
#include <cassert>

#ifndef MARMOSET_TESTING
int main();
#endif
bool check_win( char board[][7], char &p_winner);
void winner_row( char *p_start, char dir );
void print_board( char board[][7] );
void input_to_bottom( char board[][7], char player, int column);

#ifndef MARMOSET_TESTING
int main(){
	bool win{false}, x{true}, play_again{true};
	char winner{'n'}, again{};
	int column{};
	while ( play_again == true ){
		x = true;
		char board[6][7] = {
			{'_', '_', '_', '_', '_', '_', '_'},
			{'_', '_', '_', '_', '_', '_', '_'},
			{'_', '_', '_', '_', '_', '_', '_'},
			{'_', '_', '_', '_', '_', '_', '_'},
			{'_', '_', '_', '_', '_', '_', '_'},
			{'_', '_', '_', '_', '_', '_', '_'}
		};
		while ( win == false ){
			if ( x == true ){
				print_board ( board );
				std::cout << "Turn: x" << std::endl;
				std::cout << "Enter a col: ";
				std::cin >> column;
				assert ( column >= 0 && column < 7);
				input_to_bottom( board, 'x', column );
				x = false;
				win = check_win( board, winner );
				if ( win == true ){
					print_board ( board );
					std::cout << winner << " won" << std::endl;
				}
			} else {
				print_board ( board );
				std::cout << "Turn: o" << std::endl;
				std::cout << "Enter a col: ";
				std::cin >> column;
				assert ( column >= 0 && column <= 7);
				input_to_bottom( board, 'o', column );
				x = true;
				win = check_win( board, winner );
				if ( win == true ){
					print_board ( board );
					std::cout << winner << " won" << std::endl;
				}
			}
		}
		std::cout << "Play again? (y, n) ";
		std::cin >> again;
		if ( again == 'n' ){
			play_again = false;
		} else {
			win = false;
		}
	}
}
#endif

void print_board( char board[][7] ){
	std::cout << "0 1 2 3 4 5 6 " << std::endl;
	for ( int k{0}; k < 6; k++ ){
		for ( int l{0}; l < 7; l++ ){
			std::cout << board[k][l] << " ";
		}
		std::cout << std::endl;
	}
}

void input_to_bottom( char board[][7], char player, int column ){
	int row{5};
	while ( board[row][column] == 'x' || board[row][column] == 'o' ){
		--row;
	}
	if ( player == 'x' ){
		board[row][column] = 'x';
	} else if ( player == 'o' ){
		board[row][column] = 'o';
	}
}

bool check_win( char board[][7], char &p_winner){
	bool win{false};
	char direction{'n'}, row{}, column{};
	for (int k{0}; k < 6; ++k ){
		for ( int l{0}; l < 7; ++l ){
			if (board[k][l] == 'x' || board[k][l] == 'o' ){
				if ( board[k][l] == board[k][l + 1] && board[k][l] == board[k][l + 2] &&
					board[k][l] == board[k][l + 3] && l < 4 ){
					win = true;
					if ( board[k][l] == 'x' ){
						p_winner = 'X';
					} else {
						p_winner = 'O';
					}
					direction = 'h';
					row = k;
					column = l;
				}
				if ( board[k][l] == board[k + 1][l] && board[k][l] == board[k + 2][l] &&
				     board[k][l] == board[k + 3][l] ){
					win = true;
					if ( board[k][l] == 'x' ){
						p_winner = 'X';
					} else {
						p_winner = 'O';
					}
					direction = 'v';
					row = k;
					column = l;
				}
			}
		}
	}
	for (int k{6}; k > 0; --k ){
			for ( int l{0}; l < 4; ++l ){
				if (board[k][l] == 'x' || board[k][l] == 'o' ){
					if ( board[k][l] == board[k - 1][l + 1] && board[k][l] == board[k - 2][l + 2] &&
						 board[k][l] == board[k - 3][l + 3] ){
						win = true;
						if ( board[k][l] == 'x' ){
							p_winner = 'X';
						} else {
							p_winner = 'O';
						}
						direction = 'f';
						row = k;
						column = l;
					}
					if ( board[k][l] == board[k + 1][l + 1] && board[k][l] == board[k + 2][l + 2] &&
						 board[k][l] == board[k + 3][l + 3] ){
							win = true;
							if ( board[k][l] == 'x' ){
								p_winner = 'X';
							} else {
								p_winner = 'O';
							}
							direction = 'd';
							row = k;
							column = l;
					}
				}
			}
	}
	if ( win == true ){
		winner_row( &board[row][column], direction );
	}
	return win;
}

void winner_row( char *p_start, char dir ){
	if ( dir == 'h' ){
		*p_start = '*';
		*(p_start + 1) = '*';
		*(p_start + 2) = '*';
		*(p_start + 3) = '*';
	} else if ( dir == 'v' ){
		*p_start = '*';
		*(p_start + 7) = '*';
		*(p_start + 14) = '*';
		*(p_start + 21) = '*';
	} else if ( dir == 'f' ){
		*p_start = '*';
		*(p_start - 6) = '*';
		*(p_start - 12) = '*';
		*(p_start - 18) = '*';
	} else if ( dir == 'd' ){
		*p_start = '*';
		*(p_start + 8) = '*';
		*(p_start + 16) = '*';
		*(p_start + 24) = '*';
	}
}
