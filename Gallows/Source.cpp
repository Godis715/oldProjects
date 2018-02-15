#include <iostream>
#include <fstream>
#include <conio.h>
#include <ctime>
#define MAX_ATTEMPTS 5
#define ESCAPE 27
#define ENTER 13

using namespace std;

bool dictionaryChecking() {
	ifstream dictionary;
	dictionary.open("dictionary.txt", ios_base::in);

	if (!dictionary.is_open()) {
		cout << "Oops, couldn't open the dictionary" << endl;
		return false;
	}

	int num = 0;
	if (!(dictionary >> num)) {
		cout << "Incorrect structure of dictionary" << endl;
		return false;
	}

	char buffer[256];
	for (int i = 0; i < num; ++i) {
		if (!(dictionary >> buffer)) {
			cout << "Incorrect structure of dictionary" << endl;
			return false;
		}
	}
	dictionary.close();
	return true;
}

void indentUp(int size = 6) {
	for (int i = 0; i < size; ++i) {
		cout << endl;
	}
}
void indentLeft(int size = 6) {
	for (int i = 0; i < size; ++i) {
		cout << '	';
	}
}

char* chooseWord(int &wordLength, char *&openedLetters) {
	
	ifstream dictionary;
	dictionary.open("dictionary.txt", ios_base::in);

	if (!dictionary.is_open()) {
		indentLeft();
		cout << "Oops, couldn't open the dictionary" << endl;
		_getch();
		exit(0);
	}

	int wordsNumber = 0;
	dictionary >> wordsNumber;

	srand(time(0));
	int wordPosition = rand() % wordsNumber + 1;
	char buffer[256];

	for (int i = 0; i < wordPosition; ++i) {
		dictionary >> buffer;
	}
	dictionary.close();


	char *word;
	{
		int i;
		for (i = 0; buffer[i] != '\0'; ++i) {
			
		}
		word = new char[i + 1];
		openedLetters = new char[i + 1];
		wordLength = i;
		for (int j = 0; j < i; ++j) {
			word[j] = buffer[j];
			openedLetters[j] = '_';
		}
		word[i] = '\0';
		openedLetters[i] = '\0';
	}

	return word;
}
// проверяет состояние игры: если, игра закончена, возвращает true, иначе false

bool gameIsOver(int &attempts, char* word, char* openedLetters) {
	if (attempts > MAX_ATTEMPTS) {
		cout << "YOU LOSE.";
		return true;
	}
	for (int i = 0; openedLetters[i] != '\0'; ++i) {
		if (openedLetters[i] == '_') {
			return false;
		}
	}
	cout << "!!!YOU WIN!!!";
	return true;
}
void gameDraw(char *openedLetters, int &attempts) {

	system("cls");
	indentUp();

	indentLeft();
	for (int i = 0; openedLetters[i] != '\0'; ++i) {
		cout << openedLetters[i] << " ";
	}
	cout << endl;
	cout << endl;
	indentLeft();

	ifstream gallow;

	switch (attempts) {
		case 0: {
			gallow.open("0.txt", ios_base::in);
			break;
		}
		case 1: {
			gallow.open("1.txt", ios_base::in);
			break;
		}
		case 2: {
			gallow.open("2.txt", ios_base::in);
			break;
		}
		case 3: {
			gallow.open("3.txt", ios_base::in);
			break;
		}
		case 4: {
			gallow.open("4.txt", ios_base::in);
			break;
		}
		case 5: {
			gallow.open("5.txt", ios_base::in);
			break; 
		}
		default: {
			gallow.open("lose.txt", ios_base::in);
			break;
		}
		
	}
	if (!gallow.is_open()) {
		indentLeft();
		cout << "Could'n open file " << attempts << ".txt";
		_getch();
		exit(0);
	}

	while(true) {
		char c;
		gallow.get(c);
		if (gallow.eof()) {
			break;
		}
		cout << c;
		if (c == '\n') {
			indentLeft();
		}
	}
	cout << endl;
	indentLeft();
	gallow.close();
}

bool eventHandler(char item, char *word, char *openedLetters, int &attempts) {
	bool isGuessed = false;
	if (item >= 'a' && item <= 'z' || item >= 'A' && item <= 'Z' || item == '-') {
		for (int i = 0; word[i] != '\0'; ++i) {
			if (word[i] == item) {
				if (openedLetters[i] == item) {
					cout << "You have already opened this letter" << endl;
					indentLeft();
					return false;
				}
				else {
					openedLetters[i] = item;
					isGuessed = true;
				}
			}
		}
		if (!isGuessed) {
			++attempts;
		}
	}
	return true;
}

int main() {

	if (!dictionaryChecking()) {
		_getch();
		return 0;
	}

	char contItem = 0;
	while (contItem != ESCAPE) {
		// var init
		int wordLength = 0;
		int attempts = 0;

		char *openedLetters = nullptr;
		char *word = chooseWord(wordLength, openedLetters);

		gameDraw(openedLetters, attempts);
		// game cycle
		do {
			char item = _getch();
			if (eventHandler(item, word, openedLetters, attempts)) {
				gameDraw(openedLetters, attempts);
			}

		} while (!gameIsOver(attempts, word, openedLetters));
		
		while (true) {
			contItem = _getch();
			if (contItem == ESCAPE || contItem == ENTER) {
				break;
			}
		}
	}
	return 0;
}