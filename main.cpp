#include<iostream>

using namespace std;

int index;
char matrix[9] = { '_','_','_','_','_','_','_','_','_' };

int isFull() { 
	for (int i = 0; i < 9; i++)	{
		if (matrix[i] != 'X') {
			if (matrix[i] != 'O') {
				return 0;
			}
		}
	}
	return 1;
}

int person_won() { 
	int i = 0;
	while ( i < 9 ) {
		if ((matrix[i] == matrix[i + 1]) && (matrix[i + 1] == matrix[i + 2]) && (matrix[i] == 'O'))
			return 1;
		i += 3;
	}
	i = 0;
	while ( i < 3 ) {
		if ((matrix[i] == matrix[i + 3]) && (matrix[i + 3] == matrix[i + 6]) && (matrix[i] == 'O'))
			return 1;
		i++;
	}
	if ((matrix[0] == matrix[4]) && (matrix[4] == matrix[8]) && (matrix[0] == 'O')) {
		return 1;
	}
	if ((matrix[2] == matrix[4]) && (matrix[4] == matrix[6]) && (matrix[2] == 'O')) {
		return 1;
	}
	return 0;
}

int machine_won() {
	int i = 0;
	while (i < 9) {
		if ((matrix[i] == matrix[i + 1]) && (matrix[i + 1] == matrix[i + 2]) && (matrix[i] == 'X'))
			return 1;
		i += 3;
	}
	i = 0;
	while (i < 3) {
		if ((matrix[i] == matrix[i + 3]) && (matrix[i + 3] == matrix[i + 6]) && (matrix[i] == 'X'))
			return 1;
		i++;
	}
	if ((matrix[0] == matrix[4]) && (matrix[4] == matrix[8]) && (matrix[0] == 'X')) {
		return 1;
	}
	if ((matrix[2] == matrix[4]) && (matrix[4] == matrix[6]) && (matrix[2] == 'X')) {
		return 1;
	}
	return 0;
}

void print_matrix() { 
	cout << endl;
	cout << "|" << matrix[0] << "|" << matrix[1] << "|" << matrix[2] << "|" << endl;
	cout << "|" << matrix[3] << "|" << matrix[4] << "|" << matrix[5] << "|" << endl;
	cout << "|" << matrix[6] << "|" << matrix[7] << "|" << matrix[8] << "|" << endl;
}

int minimax(bool flag) { 
	int max_val = INT_MIN, min_val = INT_MAX;
	int depth = 9;
	int value = 1;
	if (machine_won() == 1) {
		return 10;
	}
	else if (person_won() == 1) {
		return -10;
	}
	else if (isFull() == 1)	{
		return 0;
	}
	int score[9] = { 1,1,1,1,1,1,1,1,1 };

	for (int i = 0; i < 9; i++) {
		if (matrix[i] == '_') {
			if (min_val > max_val) { 
				if (flag == true) {
					matrix[i] = 'X';
					value = minimax(false);
				}
				else {
					matrix[i] = 'O';
					value = minimax(true);
				}
				matrix[i] = '_';
				score[i] = value;
			}
		}
	}
	

	if (flag == true) {
		max_val = INT_MIN;
		for (int j = 0; j < 9; j++) {
			if (score[j] > max_val/2 && score[j] != 1) {
				max_val = score[j];
				index = j;
			}
		}
		return max_val;
	}
	if (flag == false) {
		min_val = INT_MAX;
		for (int j = 0; j < 9; j++) {
			if (score[j] < min_val/2 && score[j] != 1) {
				min_val = score[j];
				index = j;
			}
		}
		return min_val;
	}
}

int main() {
	int x, y, move, choice;
back: cout << "Who is going to play first? Input '1' for Player and '2' for AI" << endl << "Choose: ";
	cin >> choice;
	if (choice < 1 || choice > 2) {
		cout << "Invalid choice!" << endl;
		goto back;
	}
	if (choice == 1) {
		print_matrix();
	up:cout << endl << "Enter x, y: ";
		cin >> x >> y;
		move = (x - 1) * 3 + (y - 1) % 3 + 1;
		if (matrix[move - 1] == '_') {
			matrix[move - 1] = 'O';
			print_matrix();
		}
		else {
			cout << endl << "Invalid Move......Try different move";
			goto up;
		}
	}

	while (true) {
		cout << endl << "AI MOVE...." << endl;
		minimax(true);
		matrix[index] = 'X';
		print_matrix();
		if (machine_won() == 1) {
			cout << endl << "AI WON....." << endl;
			break;
		}
		if (isFull() == 1) {
			cout << endl << "Draw...." << endl;
			break;
		}
	again:cout << endl << "Enter x, y: ";
		cin >> x >> y;
		move = (x - 1) * 3 + (y - 1) % 3 + 1;
		if (matrix[move - 1] == '_') {
			matrix[move - 1] = 'O';
			print_matrix();
		}
		else {
			cout << endl << "Invalid Move......Try different move" << endl;
			goto again;
		}
		if (person_won() == 1) {
			cout << endl << "You Won......" << endl;
			break;
		}
		if (isFull() == 1) {
			cout << endl << "Draw...." << endl;
			break;
		}
	}
	char newGame;
	cout << "One more game?(y/n) ";
	cin >> newGame;
	if (newGame == 'y') {
		for (int i = 0; i < 9; i++) {
			matrix[i] = '_';
		}
		goto back;
	}
	else {
		cout << "Bye-Bye" << endl;
		system("pause");
		return 0;
	}

}