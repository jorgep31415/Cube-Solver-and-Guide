#include "menu.h"
using namespace std;

void menuProc(int& numLayers, int& option, int& show)
{
    clearScreen();
    askQuestion("Choose (enter number from 1-3):\n(1) Start from solved state\n(2) WCA scramble\n(3) Build your cube", option, 1, 3);
    
    askQuestion("How many layers? (choose from 2-7) ", numLayers, 2, 7);
    
    if (option == 2)
        askQuestion("Show scramble? (0.No, 1.Yes)", show, 0, 1);
    else if (option == 3 && numLayers < 4)
        askQuestion("Would you like to find the solution to this state? (0.No, 1.Yes)", show, 0, 1);
}

void askQuestion(string question, int& selection, int bRange, int tRange)
{
    bool asked = false;
    do{
        if (asked)
            cout << "Try again. ";
        cout << question << endl;
        cin >> selection;
        clearScreen();
        asked = true;
    } while(selection < bRange || selection > tRange);
}

void makeMoves(Cube* c)
{
    string sequence;
    string turn;        //sequence broken up into "turn(s)"
    bool disp;
    bool solved = false, oneSideN = false;
    int counter = 0;
    
    while (!solved)       //each sequence entered, make your moves
    {
        cout << "Using cube notation, make move(s): ";
        getline(cin,sequence);
        
        disp = true;
        for (int j = 0; j < sequence.size(); j++)
        {
            if (disp)
            {
                if (!(sequence[j] == ' '))        //if not a space yet
                    turn += sequence[j];         //goes into this one turn
                else
                {
                    if (!turn.empty())  //once you reach a space, will turn
                    {
                        if (turn == "q")
                            return;
                        disp = c->move(turn);
                        counter++;
                        turn = "";
                    }
                }
            }
        }
        
        if (!turn.empty() && disp)      //if you have a turn going on at the very end w/o space
        {
            if (turn == "q")
                return;
            disp = c->move(turn);
            counter++;
            turn = "";
        }
        
        if (disp)
            clearScreen();
        c->display();
        if (c->checkSide())
        {
            cout << "You solved one side in " << counter << " moves!" << endl;
            oneSideN = true;
        }
        if (c->checkSolved())
        {
            solved = true;
            cout << "You solved the cube in " << counter << " moves!" << endl;
        }
    }
}
