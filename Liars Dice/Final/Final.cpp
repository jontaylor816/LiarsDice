/*
Jonathan Taylor
IT 312
Assignment 7-1

This is a program that emulates the game "Liar's Dice", a multiplayer dice game of deception. The user is propted to provide the number of players, then the progam "rolls" 5 dice for each player. The players then take turns "bidding" 
on the number of die that have been rolled. For example, player 1 may bid on 5 2's. The next player has the option to call player 1 a liar, or continue bidding. If player 2 continues, their bid must be higher than the previous players,
either in respect to the die face, or the ammout bid. Once a player is called a liar, all the dice are revealed and counted. If the bid is found to be correct, the bidding player wins. Otherwise, the player who called liar is the winner.

The proccess for developing this program was made much easier thanks to the assignments that have led up to this. Several of our previous assignments had us develop code that we would need for this project. And so, the methods for 
reading the rules.txt file, the dice rolling mechanisms and the class definitions were pretty much taken straight from the assignments. Even so, this project presented many challenges and there was much work to do. The first thing I
decided to tackle was the creation of header files and classes. Once this structure was in place, I defined all the methods in my classes that I believed I would need at the start. I then began working on the main code for the game.

I started with the begining of the game, asking how many players would be playing, and continued on coding as if I was playing the game also. This helped to keep me focused and not get overwhelmed. I continued this way untill
I started to work on the actual logic of the game itself, with the bidding and call out mechanics. Those aspects, as well as making sure that the correct players were interacting, were the most challenging parts of this
project. But by slowing down and working through one line at a time, with ample testing, I got through it and the code executes and does what I intended it to do.

I ran into some errors along the way while working on this project. Most of them were just simple mistakes, syntax errors, and forgetting to #include one of my header files. The main struggle I had was in working on the turn
order and making sure that the correct players where interacting. For the bulk of development, I had been testing with only 2 players, just for the sake of time. For most things, this was fine. However, in the main game loop, if 
I added more than 2 players, the turn order would get messed up. I did two things to fix this. First, I added a section of code that would only run on the first turn, then switch to another loop for turns beyond the first. The second
thing was to check whos turn it was with if (i - 1 < 0). So when it came to be player 1's turn again, they interect with the last player, numPlayers-1. 
*/

#include <iostream>
#include <string>
#include <vector>
#include "Game.h"
#include "Player.h"
 
using namespace std;


int main(){

    srand(time(NULL)); // seeding random number generator using current time.
    Game game; 
    game.Welcome();
    int numPlayers;


    // get the number of players from user input
    cout << "\nHow many players?\n";
    cin >> numPlayers;
    while (numPlayers < 2) {
        cout << "Liar's dice is for 2 or more players. Please enter a number greater than 2.";
        cin >> numPlayers;
        cout << endl;
    }
    vector<Player> Players(numPlayers); // number of players stored in a vector for dynamic memory allocation
    string n;

    for (int i = 0; i < numPlayers; i++) { // get and set players names.
        cout << "Enter player " << i + 1 << "'s name: ";
        cin >> n;
        Players[i].SetName(n);
    }

    int diceTotal[6] = { 0, 0, 0, 0, 0, 0 }; // array to store the dice totals for each players roll, used to compare with bids when a player is called out.
    bool keepLooping;
    do { // using a do while loop to allow the game to be easily replayed with the same players.

        // rolling dice for each player and storing the results of the rolls.
        for (int x = 0; x < numPlayers; x++) {
            Players[x].RollDice();
            Players[x].CountDice();
            for (int y = 0; y < 6; y++) {
                diceTotal[y] += Players[x].diceCount[y];
            }
        }

        string show;
        bool stop = false;
        char clr;
        int check;

        // let players check on their dice.
        while (!stop) {
            check = 0;
            cout << "If you would like to see your dice, enter your name. Once all players have viewed their dice, enter q." << endl;
            cin >> show;
            cout << endl;
            for (int i = 0; i < numPlayers; i++) {
                if (show.compare(Players[i].name) == 0) {
                    cout << "Player " << i + 1 << "'s dice:\n";
                    Players[i].ShowDice();
                    cout << endl << "Press any key to continue...\n";
                    clr = getchar();
                    while (cin.get() != '\n') {} // clearing the input buffer
                    game.Clear();
                    check++;
                }
            }
            if (show.compare("q") == 0) {
                stop = true;
            }
            else if (check == 0 && show.compare("q") != 0) {
                cout << "Invalid input. Try again.\n\n";
                while (cin.get() != '\n') {} // clearing input buffer
            }
        }

        game.Clear();
        cout << "Now that everyone has seen their dice, its time to play....\n\n";
        cout << "**********************************************************\n";
        cout << "                      LIARS DICE                          \n";
        cout << "**********************************************************\n\n\n\n\n";

        // main game loop

        int dieFace = 0;
        int dieNum = 0;
        bool run = true;
        bool inputCheck;
        bool turnOne = true;
        char accept;

        while (run) {

            for (int i = 0; i < numPlayers; i++) {

                cout << Players[i].name << "'s turn!\n";

                if (turnOne) { // code only runs on the first turn of play
                    do { // get player 1's bid and validate it
                        inputCheck = false;
                        cout << Players[i].name << ", enter a number, 1-6, to bid on: ";
                        cin >> dieFace;
                        if (dieFace <= 0 || dieFace > 6) {
                            cout << "Invalid input, try again! \n\n";
                        }
                        else {
                            cout << "How many " << dieFace << "'s are there? \n";
                            cin >> dieNum;
                            if (dieNum <= 0 || dieNum > numPlayers * 5) {
                                cout << "Invalid input, Try again!\n\n";
                            }
                            else {
                                cout << Players[i].name << " has called " << dieNum << " " << dieFace << "'s!" << endl;
                                // store player1's bid
                                game.SetAmmout(dieNum);
                                game.SetFace(dieFace);
                                inputCheck = true;
                                turnOne = false;
                            }
                        }
                    } while (!inputCheck);
                }

                else { // codes runs on turns after the first

                    if (i - 1 < 0) { // this check keeps turn order correct so that player one responds to numPlayers - 1's bid.
                        cout << Players[i].name << ", do you accept " << Players[numPlayers - 1].name << "'s bid? (Y)es or (N)o\n";
                    }

                    else {
                        cout << Players[i].name << ", do you accept " << Players[i - 1].name << "'s bid? (Y)es or (N)o\n";
                    }
                    cin >> accept;

                    while (accept != 'y' && accept != 'n' && accept != 'Y' && accept != 'N') {
                        cout << "Invalid input. Please enter 'Y' for yes or 'N' for no: ";
                        cin >> accept;
                    }

                    if (accept == 'N' || accept == 'n') { // code to run if a player does not accept the previous players bid
                        run = false;
                        cout << Players[i].name << " has called!\n\n";
                        cout << "All players, reveal your dice!\n";
                        for (int i = 0; i < numPlayers; i++) {
                            cout << Players[i].name << "'s dice: \n";
                            Players[i].ShowDice();
                            cout << endl;
                        }
                        if (game.GetAmmount() == diceTotal[game.GetFace() - 1]) { // check if the bid matches actual rolls.
                            if (i - 1 < 0) {
                                cout << "*********************************************\n";
                                cout << Players[numPlayers - 1].name << " Wins!\n";
                                cout << "*********************************************\n";
                            }
                            else {
                                cout << "*********************************************\n";
                                cout << Players[i - 1].name << " Wins!\n";
                                cout << "*********************************************\n";
                            }

                        }
                        else {
                            if (i - 1 < 0) {
                                cout << "*********************************************\n";
                                cout << Players[i].name << " Wins!\n";
                                cout << "*********************************************\n";
                            }
                            else {
                                cout << "*********************************************\n";
                                cout << Players[i].name << " Wins!\n";
                                cout << "*********************************************\n";
                            }
                        }
                        break;
                    }
                    else { // code if no callout. Contiues game normally.
                        do {
                            inputCheck = false;
                            cout << Players[i].name << ", enter a number, 1-6, to bid on: ";
                            cin >> dieFace;
                            if (dieFace <= 0 || dieFace > 6) {
                                cout << "Invalid input, try again! \n\n";
                            }
                            else {
                                cout << "How many " << dieFace << "'s are there? \n";
                                cin >> dieNum;
                                if (dieNum <= 0 || dieNum > numPlayers * 5) {
                                    cout << "Invalid input, Try again!\n\n";
                                }
                                else if (dieFace <= game.GetFace() && dieNum <= game.GetAmmount()) {
                                    cout << "Invalid input! Please make sure that either the number or ammount is higher than the previous players bid.\n";
                                }
                                else {
                                    cout << Players[i].name << " has called " << dieNum << " " << dieFace << "'s!" << endl;
                                    inputCheck = true;
                                    game.SetAmmout(dieNum);
                                    game.SetFace(dieFace);
                                }
                            }
                        } while (!inputCheck);
                    }
                }

            }
        }
        // allow the player to play again with the same players.
        char repeat;
        cout << "Would you like to play again? (Y)es or (N)o\n ";
        cin >> repeat;
        while (repeat != 'y' && repeat != 'n') {
            cout << "Invalid input. Please enter y for yest or n for no.\n";
            cin >> repeat;
        }
        if (repeat == 'y') {
            keepLooping = true;
            game.Clear();
        }
        else {
            keepLooping = false;
        }
    } while (keepLooping);
    return 0;

}

