/*
* This is the header file for my Player class. It contains all the method definitions needed for the game.
*/
#include <iostream>
#pragma once

using namespace std;

class Player
{
private:
	
	int dice[5];
	string m_name;

public:

	int diceCount[6];
	string name;
	// constructor
	Player();

	// methods
	string GetName();
	void SetName(string);
	void RollDice();
	void ShowDice();
	void CountDice();

};

