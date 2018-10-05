#ifndef utilities_h
#define utilities_h
#include <string>
#include "timer.h"

///////////////////////////////////////////////////////////////////////////
//  Constants
///////////////////////////////////////////////////////////////////////////

const int CW          = 0;
const int CCW         = 1;

const int UP          = 1;
const int LEFT        = 4;
const int FRONT       = 5;
const int RIGHT       = 6;
const int BACK        = 7;
const int DOWN        = 9;

const int FACES       = 12;

const std::string F2L = "/Users/Jorge/Desktop/CubeSolver2.5/F2L Algs.txt";
const std::string OLL = "/Users/Jorge/Desktop/CubeSolver2.5/OLL Algs.txt";
const std::string PLL = "/Users/Jorge/Desktop/CubeSolver2.5/PLL Algs.txt";

///////////////////////////////////////////////////////////////////////////
//  Utility functions
///////////////////////////////////////////////////////////////////////////

struct Pair;

int randInt(int min, int max);
std::string intToTurn(int num);
bool restrct(int input, Pair* done, int pairsDone);
bool counterCheck(int* counters, int sizeArray, int num);
void resetCounters(int* counters, int sizeArray);
char opp(char input);
void clearScreen();
std::string OLLindex(int num);
std::string PLLindex(int num);

struct Move
{
    std::string turn;
    bool counts;
    Move();
};

struct Pair
{
    char c[3];  //the three different colors that characterize the pair (the first only applies to the corner)
    int pos;    //4 pair positions for 3x3, when cross on bottom: 0 - LF, 1 - RF, 2 - LB, 3 - RB
    Pair();
};

struct Stamp
{
    int attempts;
    int moveCountAfter;
    Timer t;
    std::string info;
    Stamp();
};

#endif /* utilities_h */
