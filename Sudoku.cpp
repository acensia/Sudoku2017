#include <iostream>	
#include <fstream>
#include <vector>

using namespace std;

class Sudoku {
public:
	void init_game_board(ifstream &infile);
	void show_game();
	void show_Answer();
	bool validate_at(int row, int col, int val);
	bool is_complete();
	void solve();
	void write_game_board(int row, int col, int val);
	void erase_game_board(int row, int col);
	void partially_solve();
	
private:
	int game_board[9][9];
	int Answer[9][9];
	/////////////////////////
	int fixed_board[9][9]; //
};

int main() {
	Sudoku newgame;
	ifstream gamefile;
	gamefile.open("Sudoku_test.txt");
	int gamemenu;
	
	newgame.init_game_board(gamefile);
	
	newgame.solve(); 

	cout << "--------------------" << endl;
	cout << "| SudoKU Game MENU |" << endl;
	cout << "--------------------" << endl;
	cout << "1: Game Start" << endl;
	cout << "0: Quit" << endl;
	cout << "--------------------" << endl;
	cin >> gamemenu;
	cout << "____________________" << endl;
	if (gamemenu == 0) return 0;
	while (gamemenu != 1) { 
		cout << "Press correct button please: ";
		cin >> gamemenu;
		if (gamemenu == 0) return 0; 
	}
	do {
		cout << endl;
		newgame.show_game();
		cin >> gamemenu;
		if (gamemenu == 1) {
			int row;
			int col;
			int val;
			cout << endl << "What row ? : ";
			cin >> row;     row--;
			cout << endl << "What col ? : ";
			cin >> col;		col--;
			cout << endl << "What val ? : ";
			cin >> val;
			while (val < 1 || val>9) {
				cout << "Select right value : ";
				cin >> val;
			}
			newgame.write_game_board(row, col, val);
		}
		else if (gamemenu == 2) {
			int row;
			int col;
			cout << endl << "What row ? : ";
			cin >> row;     row--;
			cout << endl << "What col ? : ";
			cin >> col;		col--;
			newgame.erase_game_board(row, col);
		}
		else if (gamemenu == 3) {
			newgame.partially_solve();
		}
		else if (gamemenu == 4) {
			if (!newgame.is_complete()) {
				cout << "Nooooo!!" << endl;
			}
			else {
				cout << "Congratulaton!" << endl;
				break;
			}
		}
		else if (gamemenu == 5) {
			newgame.show_Answer();
			cout << "BYE BYE" << endl;
			break;
		}
		else if (gamemenu == 0) break;
		else {
			cout << "Wrong command" << endl; 
		}
		
	} while (gamemenu != 0);

}////////////////////////////////////////////////////////////main�Լ�///////////////////////////////////

void Sudoku::init_game_board(ifstream &infile) {
	for (int a = 0; a < 9; a++) {
		for (int b = 0; b < 9; b++) {
			infile >> game_board[a][b];
		}
	}
	cout << "---------Loading---------" << endl;

	for (int a = 0; a < 9; a++) {
		for (int b = 0; b < 9; b++) {
			Answer[a][b] = game_board[a][b]; 
			fixed_board[a][b] = game_board[a][b]; 
		}
	}
}

void Sudoku::show_game() {
	cout<<"------------------------"<<endl;
	for (int a = 0; a < 9; a++) {
		for (int b = 0; b < 9; b++) {
			if (b % 3 == 0 && b != 0) cout << "| ";
			cout << game_board[a][b] << " ";
			if (b == 8) cout << endl;
		}
		if (a % 3 == 2) cout << "--------------------" << endl;
	}
	cout << "1 : Write" << endl;
	cout << "2 : Erase" << endl;
	cout << "3 : Partially solve" << endl;
	cout << "4 : Complete?!" << endl;
	cout << "5 : Solve" << endl;
	cout << "0 : Quit" << endl;
	cout << "--------------------" << endl;
}

void Sudoku::show_Answer() {
	for (int a = 0; a < 9; a++) {
		for (int b = 0; b < 9; b++) {
			if (b % 3 == 0 && b != 0) cout << "| ";
			cout << Answer[a][b] << " ";
			if (b == 8) cout << endl;
		}
		if (a % 3 == 2) cout << "--------------------" << endl;
	}
}

bool Sudoku::is_complete() {
	bool truly = 0;
	for (int a = 0; a < 9; a++) {
		for (int b = 0; b < 9; b++) {
			truly = (Answer[a][b] == game_board[a][b]);
			if (!truly) return truly; 
		}
	}
	return truly;
}

void Sudoku::write_game_board(int row, int col, int val) {
	cout << endl;
	if (game_board[row][col] != 0) cout << "Already filled" << endl; 
	else game_board[row][col] = val;
}

void Sudoku::erase_game_board(int row, int col) {
	cout << endl;
	if (fixed_board[row][col] != 0) {
		cout << "That is a fixed number!" << endl;
		return;
	}
	if (game_board[row][col] == 0) cout << "Already blank" << endl;
	else game_board[row][col] = 0;
}

void Sudoku::partially_solve() {
	cout << endl;
	cout << "Which one do you want ?" << endl;
	cout << "1: sub-matrix" << endl;
	cout << "2: row" << endl;
	cout << "3: column" << endl;
	int wanted;
	cin >> wanted;
	if (wanted == 1) {
		cout << "What sub-matrix ? : ";
		cin >> wanted;
		for (int a = (wanted - 1) / 3 * 3; a < (wanted - 1) / 3 * 3 + 3; a++) {
			for (int b = (wanted - 1) % 3 * 3; b < (wanted - 1) % 3 * 3 + 3; b++) {
				game_board[a][b] = Answer[a][b];
			}
		}
	}
	else if (wanted == 2) {
		cout << "What row ? : ";
		cin >> wanted;
		for (int a = 0; a < 9; a++) {
			game_board[wanted][a] = Answer[wanted][a];
		}
	}
	else if (wanted == 3) {
		cout << "What column ? : ";
		cin >> wanted;
		for (int a = 0; a < 9; a++) {
			game_board[a][wanted] = Answer[a][wanted];
		}
	}

}

void Sudoku::solve() {
	cout << "@@@@@ Solving @@@@@@" << endl;
	
	vector<int> Save;

	for (int a = 0; a < 9; a++) {
		for (int b = 0; b < 9; b++) {

			if (game_board[a][b] == 0) {
				for (int c = 1; c < 10; c++) {
					if (!validate_at(a, b, c)) {
						Answer[a][b] = c;
						Save.push_back(100 * a + 10 * b + c);
						break;
					}
					while (c == 9 || b == 9 || a == 9) {
						if (Save.empty()) {
							cout << "No answer" << endl;
							Save.pop_back();  //������ ƨ�� ��������
						}
						a = Save.back() / 100;
						b = (Save.back() % 100) / 10;
						c = (Save.back() % 100) % 10;
						Answer[a][b] = 0;
						Save.pop_back();
					}


				}
			}



		}


	}
	cout << "Answer exist" << endl;
}

bool Sudoku::validate_at(int row, int col, int val) {
	bool result = 0; 

	for (int cl = 0; cl < 9; cl++) {
		result = (val == Answer[row][cl]);
		if (result)	break;
	}

	if (!result) {
		for (int rw = 0; rw < 9; rw++) {
			result = (val == Answer[rw][col]);
			if (result) break;
		}
	}
	if (!result) {
		for (int r1 = row / 3 * 3; r1 < row / 3 * 3 + 3; r1++) {
			int if_break = 0; 
			for (int c1 = col / 3 * 3; c1 < col / 3 * 3 + 3; c1++) {
				result = (val == Answer[r1][c1]);
				if (result) {
					if_break = 1; 
					break;
				}
			}
			if (if_break) break;
		}
	}


	return result;
}
