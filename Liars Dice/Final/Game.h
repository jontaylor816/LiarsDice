/*
This is the header file for my Game class. It includes all the declaration of methods used in the game.
*/

#pragma once
class Game
{
private: 
	int face;
	int ammount;

public:
	Game();

	void Welcome();	
	void Clear();
	int GetFace();
	int GetAmmount();
	void SetFace(int);
	void SetAmmout(int);
};

