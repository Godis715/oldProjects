#include <iostream>
#include <Windows.h>
#include <ctime>
#include <vector>

using namespace std;

enum ConsoleColor {
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

void drawWall(int number) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((Blue << 4) | Black));
	for (int i = 0; i < number; i++) {
		cout << " ";
	}
	SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | LightGray));
}

void drawField(int field[][3]) {
	system("cls");
	
	const int bigWall = 17;
	const int littleWall = 2;	

	for (int i = 0; i < 3; i++) {
		drawWall(bigWall);
		cout << endl;

		for (int j = 0; j < 3; j++) {
			drawWall(littleWall);

			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

			if (field[i][j] == 3 || field[i][j] == 4) {
				SetConsoleTextAttribute(hConsole, (WORD)((Green << 4) | Yellow));
			}
			else {
				if (field[i][j] != 0) {
					SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Yellow));
				}
			}

			cout << " ";

			switch (field[i][j]) {
				case 3:
				case 1: {
					cout << "X";
					break;
				}
				case 4:
				case 2: {
					cout << "O";
					break;
				}
				default: {
					cout << " ";
					break;
				}
			}

			cout << " ";
		}
		drawWall(littleWall);
		cout << endl;
	}
	drawWall(bigWall);
	cout << endl;
}

bool isDeadHeat(int field[][3]) {

	bool answer = true;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (field[i][j] == 0) {
				answer = false;
				break;
			}
		}
	}
	return answer;
}

int isVictory(int field[][3]) {
	for (int i = 1; i <= 3; i++) {
		if (field[i - 1][0] == field[i - 1][1] && field[i - 1][1] == field[i - 1][2] && field[i - 1][0] != 0) {
			return (i) * 1000 + 100 + (i) * 10 + 3;
		}
		if (field[0][i - 1] == field[1][i - 1] && field[1][i - 1] == field[2][i - 1] != 0 && field[0][i - 1] != 0) {
			return 1000 + (i) * 100 + 30 + (i);
		}
	}

	if (field[0][0] == field[1][1] && field[1][1] == field[2][2] && field[0][0] != 0) {
		return 1133;
	}

	if (field[0][2] == field[1][1] && field[1][1] == field[2][0] && field[0][2] != 0) {
		return 3113;
	}
	return 0;
}

int winnerFunc(int field[][3], int victoryCode) {
	int cellX1 = victoryCode % 10 - 1;
	victoryCode /= 10;
	int cellY1 = victoryCode % 10 - 1;
	victoryCode /= 10;
	int cellX2 = victoryCode % 10 - 1;
	victoryCode /= 10;
	int cellY2 = victoryCode % 10 - 1;

	int cellX3 = (cellX1 + cellX2) / 2;
	int cellY3 = (cellY1 + cellY2) / 2;

	int winner = field[cellY1][cellX1];
	field[cellY1][cellX1] = winner + 2;
	field[cellY2][cellX2] = winner + 2;
	field[cellY3][cellX3] = winner + 2;

	return winner;
}

void winnerOut(int field[][3], int victoryCode) {

	int winner = winnerFunc(field, victoryCode);

	drawField(field);

	cout << "Победил ";
	if (winner == 2) {
		cout << "O";
	}
	else {
		cout << "X";
	}
}

int main() {

	setlocale(LC_ALL, "Russian");
	srand(time(0));

	vector<pair<int, int> > data;

	int field[3][3]{};

	while (true) {
		int victoryCode = isVictory(field);

		if (victoryCode != 0) {

			winnerOut(field, victoryCode);
			break;
		}

		if (isDeadHeat(field)) {
			drawField(field);
			cout << "Ничья";

			break;
		}

		drawField(field);


		int playerCellX = 0;
		int playerCellY = 0;

		while (true) {

			cout << "Ход игрока ";
			cin >> playerCellX >> playerCellY;
			bool correctCoords = playerCellX >= 1 && playerCellX <= 3 &&
				playerCellY >= 1 && playerCellY <= 3 && field[playerCellY - 1][playerCellX - 1] == 0;

			if (correctCoords) {
				data.push_back(pair<int, int> { playerCellX, playerCellY } );
				break;
			}
			else {
				cout << "Некорректные координаты";
				cout << endl;
			}
		}

		field[playerCellY - 1][playerCellX - 1] = 1;

		victoryCode = isVictory(field);

		if (victoryCode != 0) {

			winnerOut(field, victoryCode);
			break;
		}

		if (isDeadHeat(field)) {
			drawField(field);
			cout << "Ничья";

			break;
		}

		drawField(field);

 		int compCellX = 0;
		int compCellY = 0;

		int maxValue = -1;

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				int randomNumber = rand() % 20;
				if (field[i][j] == 0 && randomNumber > maxValue) {
					compCellY = i;
					compCellX = j;
					maxValue = randomNumber;
				}
			}
		}

		data.push_back(pair<int, int> { compCellX, compCellY } );
		field[compCellY][compCellX] = 2;

	}
	cout << endl;
	system("pause");
	return 0;
}