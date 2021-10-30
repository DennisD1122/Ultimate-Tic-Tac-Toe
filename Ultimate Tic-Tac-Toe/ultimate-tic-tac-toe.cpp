#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const char BLANK_CHAR = '.';
int total_search_depth;
char computer_char, computer_win_char;
char user_char, user_win_char;

void print_board(vector<vector<char>> board) {
	for (int row_global = 0; row_global <= 6; row_global += 3) {
		for (int col_global = 0; col_global <= 2; col_global++) {
			cout << board[row_global + col_global][0] << " ";
			cout << board[row_global + col_global][1] << " ";
			cout << board[row_global + col_global][2];
			if (col_global == 2) cout << endl;
			else cout << " | ";
		}
		for (int col_global = 0; col_global <= 2; col_global++) {
			cout << board[row_global + col_global][3] << " ";
			cout << board[row_global + col_global][4] << " ";
			cout << board[row_global + col_global][5];
			if (col_global == 2) cout << endl;
			else cout << " | ";
		}
		for (int col_global = 0; col_global <= 2; col_global++) {
			cout << board[row_global + col_global][6] << " ";
			cout << board[row_global + col_global][7] << " ";
			cout << board[row_global + col_global][8];
			if (col_global == 2) cout << endl;
			else cout << " | ";
		}
		if (row_global == 6) cout << endl << endl;
		else cout << "---------------------" << endl;
	}
}

char three_in_line(vector<char> partial_board) {
	for (int row = 0; row <= 6; row += 3) {
		if (partial_board[row] != BLANK_CHAR && partial_board[row] == partial_board[row+1] && partial_board[row] == partial_board[row+2])
			return partial_board[row];
	}

	for (int col = 0; col <= 2; col++) {
		if (partial_board[col] != BLANK_CHAR && partial_board[col] == partial_board[col+3] && partial_board[col] == partial_board[col+6])
			return partial_board[col];
	}

	if (partial_board[0] != BLANK_CHAR && partial_board[0] == partial_board[4] && partial_board[0] == partial_board[8])
		return partial_board[0];

	if (partial_board[2] != BLANK_CHAR && partial_board[2] == partial_board[4] && partial_board[2] == partial_board[6])
		return partial_board[2];

	return BLANK_CHAR;
}

char check_win(vector<vector<char>> board) {
	vector<char> global_board;
	for (auto local_board : board) {
		if (local_board[4] == computer_win_char) {
			global_board.push_back(computer_char);
		} else if (local_board[4] == user_win_char) {
			global_board.push_back(user_char);
		} else {
			global_board.push_back(BLANK_CHAR);
		}
	}
	return three_in_line(global_board);
}

bool is_draw(vector<vector<char>> board) {
	for (auto i : board) {
		for (auto j : i) {
			if (j == BLANK_CHAR) return false;
		}
	}
	return true;
}

char two_in_line(char c1, char c2, char c3) {
	if (c1 == c2 && c1 != BLANK_CHAR && c3 == BLANK_CHAR) return c1;
	if (c2 == c3 && c2 != BLANK_CHAR && c1 == BLANK_CHAR) return c2;
	if (c3 == c1 && c3 != BLANK_CHAR && c2 == BLANK_CHAR) return c3;
	return BLANK_CHAR;
}

int update_heuristic_two_in_line(int heuristic, int delta, vector<char> partial_board) {
	char c;

	for (int row = 0; row <= 6; row += 3) {
		c = two_in_line(partial_board[row], partial_board[row+1], partial_board[row+2]);
		if (c == computer_char) heuristic += delta;
		else if (c == user_char) heuristic -= delta;
	}

	for (int col = 0; col <= 2; col++) {
		c = two_in_line(partial_board[col], partial_board[col+3], partial_board[col+6]);
		if (c == computer_char) heuristic += delta;
		else if (c == user_char) heuristic -= delta;
	}

	c = two_in_line(partial_board[0], partial_board[4], partial_board[8]);
	if (c == computer_char) heuristic += delta;
	else if (c == user_char) heuristic -= delta;

	c = two_in_line(partial_board[2], partial_board[4], partial_board[6]);
	if (c == computer_char) heuristic += delta;
	else if (c == user_char) heuristic -= delta;

	return heuristic;
}

int heuristic_value(vector<vector<char>> board) {
	if (is_draw(board)) return 0;

	int heuristic = 0;

	vector<char> global_board;
	for (auto local_board : board) {
		if (local_board[4] == computer_win_char) {
			global_board.push_back(computer_char);
			heuristic += 9;
		} else if (local_board[4] == user_win_char) {
			global_board.push_back(user_char);
			heuristic -= 9;
		} else {
			global_board.push_back(BLANK_CHAR);
		}
	}

	char c = three_in_line(global_board);
	if (c == computer_char) return INT_MAX;
	else if (c == user_char) return INT_MIN;

	heuristic = update_heuristic_two_in_line(heuristic, 9, global_board);

	for (auto local_board : board) {
		if (local_board[4] != computer_win_char && local_board[4] != user_win_char) {
			heuristic = update_heuristic_two_in_line(heuristic, 1, local_board);
		}
	}

	return heuristic;
}

vector<vector<char>> execute_move(vector<vector<char>> board, pair<int,int> square, char ch) {
	board[square.first][square.second] = ch;

	char til = three_in_line(board[square.first]);
	if (til == 'X') {
		board[square.first][0] = '\\';
		board[square.first][1] = ' ';
		board[square.first][2] = '/';
		board[square.first][3] = ' ';
		board[square.first][4] = 'x';
		board[square.first][5] = ' ';
		board[square.first][6] = '/';
		board[square.first][7] = ' ';
		board[square.first][8] = '\\';
	} else if (til == 'O') {
		board[square.first][0] = '/';
		board[square.first][1] = '-';
		board[square.first][2] = '\\';
		board[square.first][3] = '|';
		board[square.first][4] = 'o';
		board[square.first][5] = '|';
		board[square.first][6] = '\\';
		board[square.first][7] = '_';
		board[square.first][8] = '/';
	}

	return board;
}

vector<pair<int,int>> find_possible_next_squares(vector<vector<char>> board, pair<int,int> square) {
	vector<pair<int,int>> possible_next_squares;

	if (square.second != -1 && board[square.second][4] != computer_win_char && board[square.second][4] != user_win_char) {
		for (int j = 0; j < 9; j++) {
			if (board[square.second][j] == BLANK_CHAR) {
				possible_next_squares.push_back(make_pair(square.second,j));
			}
		}
	}

	if (possible_next_squares.empty()) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (board[i][j] == BLANK_CHAR) {
					possible_next_squares.push_back(make_pair(i,j));
				}
			}
		}
	}

	return possible_next_squares;
}

int alphabeta(vector<vector<char>> board, pair<int,int> square, int depth, int alpha, int beta, bool maximizing_player) {
	if (depth == 0) {
		//print_board(board);
		return heuristic_value(board);
	}

	if (is_draw(board)) {
		return 0;
	}

	char cw = check_win(board);
	if (cw == computer_char) return INT_MAX;
	else if (cw == user_char) return INT_MIN;

	if (maximizing_player) {
		int value = INT_MIN;
		vector<pair<int,int>> possible_next_squares = find_possible_next_squares(board, square);
		for (auto next_square : possible_next_squares) {
			vector<vector<char>> next_board = execute_move(board, next_square, computer_char);
			value = max(value, alphabeta(next_board, next_square, depth-1, alpha, beta, false));
			if (value >= beta) break;
			alpha = max(alpha, value);
		}
		return value;
	} else {
		int value = INT_MAX;
		vector<pair<int,int>> possible_next_squares = find_possible_next_squares(board, square);
		for (auto next_square : possible_next_squares) {
			vector<vector<char>> next_board = execute_move(board, next_square, user_char);
			value = min(value, alphabeta(next_board, next_square, depth-1, alpha, beta, true));
			if (value <= alpha) break;
			beta = min(beta, value);
		}
		return value;
	}
}

pair<int,int> get_computer_move(vector<vector<char>> board, pair<int,int> prev_square) {
	int best_value = INT_MIN;
	pair<int,int> best_square;
	vector<pair<int,int>> possible_next_squares = find_possible_next_squares(board, prev_square);
	for (auto next_square : possible_next_squares) {
		vector<vector<char>> next_board = execute_move(board, next_square, computer_char);
		int value = alphabeta(next_board, next_square, total_search_depth, INT_MIN, INT_MAX, false);
		if (value > best_value) {
			best_value = value;
			best_square = next_square;
		}
	}
	return best_square;
}

bool is_full(vector<char> local_board) {
	for (int i = 0; i < 9; i++) {
		if (local_board[i] == BLANK_CHAR) {
			return false;
		}
	}
	return true;
}

pair<int,int> get_user_move(vector<vector<char>> board, pair<int,int> prev_square) {
	pair<int,int> square;

	if (prev_square.first == -1 || is_full(board[prev_square.second])) {
		while (true) {
			cout << "Enter the local board of your move (1-9):" << endl;

			try {
				string input;
				getline(cin, input);
				square.first = stoi(input) - 1;
			} catch (...) {
				cout << "Invalid entry. Try again." << endl;
				continue;
			}

			if (square.first < 0 || square.first > 8) {
				cout << "Invalid entry. Try again." << endl;
				continue;
			}

			if (is_full(board[square.first])) {
				cout << "Cannot play in local board " << 1+square.first << ". Try again." << endl;
				continue;
			}

			cout << "Enter the square of your move within local board " << 1+square.first << " (1-9):" << endl;

			try {
				string input;
				getline(cin, input);
				square.second = stoi(input) - 1;
			} catch (...) {
				cout << "Invalid entry. Try again. (Note: you are being asked again for the local board.)" << endl;
				continue;
			}

			if (square.second < 0 || square.second > 8) {
				cout << "Invalid entry. Try again. (Note: you are being asked again for the local board.)" << endl;
				continue;
			}

			if (board[square.first][square.second] != BLANK_CHAR) {
				cout << "Square " << 1+square.second << " in local board " << 1+square.first << " has already been played. Try again." << endl;
				continue;
			}

			break;
		}

	} else {
		while (true) {
			square.first = prev_square.second;

			cout << "You must play in local board " << 1+square.first << "." << endl;
			cout << "Enter the square of your move within local board " << 1+square.first << " (1-9):" << endl;

			try {
				string input;
				getline(cin, input);
				square.second = stoi(input) - 1;
			} catch (...) {
				cout << "Invalid entry. Try again." << endl;
				continue;
			}

			if (square.second < 0 || square.second > 8) {
				cout << "Invalid entry. Try again." << endl;
				continue;
			}

			if (board[square.first][square.second] != BLANK_CHAR) {
				cout << "Square " << 1+square.second << " in local board " << 1+square.first << " has already been played. Try again." << endl;
				continue;
			}

			break;
		}
	}

	return square;
}

int main() {
	cout << "Ultimate Tic-Tac-Toe" << endl << endl;

	vector<vector<char>> board = {
		{BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR},
		{BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR},
		{BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR},
		{BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR},
		{BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR},
		{BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR},
		{BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR},
		{BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR},
		{BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR,BLANK_CHAR}};
	print_board(board);

	cout << "Each dot above represents a square, for a total of 81 squares divided into 9 sections.\n" << endl;
	cout << "Each small 3 x 3 tic-tac-toe board is referred to as a local board,\nand the larger 3 x 3 board is referred to as the global board.\n" << endl;
	cout << "The game starts with X playing wherever they want in any of the 81 empty spots.\nThis move \"sends\" their opponent to its relative location.\nFor example, if X played in the top right square of their local board,\nthen O needs to play next in the local board at the top right of the global board.\nO can then play in any one of the nine available spots in that local board,\neach move sending X to a different local board.\n" << endl;
	cout << "If a move is played so that it is to win a local board by the rules of normal tic-tac-toe,\nthen the entire local board is marked as a victory for the player in the global board.\n" << endl;
	cout << "Once a local board is won by a player or it is filled completely, no more moves may be played in that board.\nIf a player is sent to such a board, then that player may play in any other board.\n" << endl;
	cout << "Game play ends when either a player wins the global board or there are no legal moves remaining,\nin which case the game is a draw.\n" << endl;
	cout << "Let's begin!" << endl << endl << endl;

	bool is_user_turn;

	while (true) {
		cout << "Do you want to play first (the X's) or second (the O's)? Enter X or O:" << endl;
		string input;
		getline(cin, input);
		if (input == "X" || input == "x") {
			user_char = 'X';
			user_win_char = 'x';
			computer_char = 'O';
			computer_win_char = 'o';
			is_user_turn = true;
			break;
		} else if (input == "O" || input == "o") {
			user_char = 'O';
			user_win_char = 'o';
			computer_char = 'X';
			computer_win_char = 'x';
			is_user_turn = false;
			break;
		} else {
			cout << "Invalid entry. Try again." << endl;
		}
	}

	cout << endl;

	while (true) {
		cout << "Enter the computer's search depth (non-negative integer):" << endl;
		cout << "This represents how many moves ahead the computer looks." << endl;
		cout << "If you want the game to be easy, choose 0. If you want it to be hard, choose 5. You can choose anything in between as well." << endl;
		cout << "Larger values are possible, but the computer might take too long to figure out its move."<< endl;
		try {
			string input;
			getline(cin, input);
			total_search_depth = stoi(input);
		} catch (...) {
			cout << "Invalid entry. Try again." << endl;
			continue;
		}
		if (total_search_depth < 0) {
			cout << "Invalid entry. Try again." << endl;
			continue;
		}
		break;
	}

	cout << endl;
	cout << "Computer's search depth: " << total_search_depth << endl << endl;
	cout << "When making your move, use the integers 1-9, which represent the following locations on the board:" << endl;
	cout << "1 2 3" << endl;
	cout << "4 5 6" << endl;
	cout << "7 8 9" << endl;
	cout << "This applies both when choosing the local board and when choosing the individual square." << endl;
	cout << "You will be prompted first for the local board, and then for the square." << endl;
	cout << "However, if you are forced to play in a particular local board, you will only be prompted for the square." << endl << endl;
	cout << "The game begins now." << endl << endl;

	pair<int,int> square = make_pair(-1,-1);

	while (true) {
		print_board(board);

		char cw = check_win(board);
		if (cw == user_char) {
			cout << "You win." << endl;
			break;
		}
		if (cw == computer_char) {
			cout << "Computer wins." << endl;
			break;
		}
		if (is_draw(board)) {
			cout << "Draw." << endl;
			break;
		}

		if (is_user_turn) {
			cout << "It's your turn." << endl;
			square = get_user_move(board, square);
			cout << "Your move (local board, square): " << "(" << 1+square.first << ", " << 1+square.second << ")" << endl;
			board = execute_move(board, square, user_char);
		} else {
			cout << "It's the computer's turn." << endl << "Thinking..." << endl;
			square = get_computer_move(board, square);
			cout << "Computer's move (local board, square): " << "(" << 1+square.first << ", " << 1+square.second << ")" << endl;
			board = execute_move(board, square, computer_char);
		}

		cout << endl;

		is_user_turn = !is_user_turn;
	}

	cout << "Press enter to exit." << endl;
	getchar();
}
