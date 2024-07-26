#include "Player.h"
#include <iostream>


using namespace std;

Player::Player() {} // default constructor

string Player::GetName() { // method to get the players name.
	return m_name;
}

void Player::SetName(string n) { // set name
	m_name = n;
	name = n;
}

void Player::RollDice() { // method to generate 5 random numbers 1-6
	int i;
	for (i = 0; i < 5; i++) {
		dice[i] = rand() % 6 + 1;
	}
}

void Player::ShowDice() { // print the dice to the console 
	int i;
	for (i = 0; i < 5; i++) {
		cout << dice[i] << " ";
	}
}

void Player::CountDice() { // stores the number of each dice rolled by the player. 
	int x, y;

	for (x = 0; x < 6; x++) {
		diceCount[x] = 0;
	}

	for (y = 0; y < 5; y++) {
		diceCount[dice[y] - 1]++;
	}
}

