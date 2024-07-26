#include "Game.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Game::Game() {} // default constructor

void Game::Welcome() { // welcome method opens a txt file and prints its contents to the console.
	fstream file;
	string read;

	file.open("rules.txt", ios::in); 

	while (getline(file, read)) { 
		cout << read << endl;
	}

	file.close();
}

void Game::Clear() { // print 200 blank lines to clear the screen.
	int count = 0;

	while (count < 200) {
		cout << endl;
		count++;
	}
}

int Game::GetFace() { // gets the die face bid on
	return face;
}

int Game::GetAmmount() { // gets the ammout bid
	return ammount;
}

void Game::SetAmmout(int am) { // sets the ammout bid
	ammount = am;
}

void Game::SetFace(int fa) { // sets the die face bid on
	face = fa;
}


