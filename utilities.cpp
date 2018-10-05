#include "utilities.h"
#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>

using namespace std;

Move::Move(){counts = true;}

Pair::Pair(){pos = -1;}

Stamp::Stamp(){attempts = 0; moveCountAfter = -1;}

// Return a random int from min to max, inclusive
int randInt(int min, int max)
{
    if (max < min)
        swap(max, min);
    static random_device rd;
    static mt19937 generator(rd());
    uniform_int_distribution<> distro(min, max);
    return distro(generator);
}

std::string intToTurn(int num)
{
    string turn;
    int origFrac = num % 18;
    int origRem = num / 18;
    int frac = origFrac / 3;
    int rem = origFrac % 3;
    
    if (origRem == 2)
        turn = "3";
    
    switch(frac)
    {
        case 0: turn += "F"; break;
        case 1: turn += "R"; break;
        case 2: turn += "U"; break;
        case 3: turn += "B"; break;
        case 4: turn += "L"; break;
        case 5: turn += "D"; break;
    }
    
    if (origRem > 0)
        turn += "w";
    
    switch(rem)
    {
        case 1: turn += "2"; break;
        case 2: turn += "'"; break;
    }
    return turn;
}

bool restrct(int input, Pair* done, int pairsDone)
{
    bool p[4] = {false, false, false, false};
    if (pairsDone == 2)
    {
        for (int i = 0; i < 2; i++)
        {
            switch(done[i].pos)
            {
                case 0: p[0] = true; break;
                case 1: p[1] = true; break;
                case 2: p[2] = true; break;
                case 3: p[3] = true; break;
            }
        }
        if (p[0] && p[1] && input < 3) return false;
        else if (p[0] && p[2] && (input / 3 == 4)) return false;
        else if (p[1] && p[3] && (input / 3 == 1)) return false;
        else if (p[2] && p[3] && (input / 3 == 3)) return false;
    }
    else if (pairsDone == 3)
    {
        for (int i = 0; i < 3; i++)
        {
            switch(done[i].pos)
            {
                case 0: p[0] = true; break;
                case 1: p[1] = true; break;
                case 2: p[2] = true; break;
                case 3: p[3] = true; break;
            }
        }
        if (p[0] && p[1] && p[2] && ((input < 3) || (input / 3 == 4))) return false;
        else if (p[0] && p[1] && p[3] && (input < 6)) return false;
        else if (p[0] && p[2] && p[3] && (input > 8)) return false;
        else if (p[1] && p[2] && p[3] && ((input / 3 == 1) || (input / 3 == 3))) return false;
    }
    return true;
}

bool counterCheck(int* counters, int sizeArray, int num)
{
    for (int i = 0; i < sizeArray; i++)
        if (counters[i] != num)
            return false;
    return true;
}

void resetCounters(int* counters, int sizeArray)
{
    for (int i = 0; i < sizeArray; i++)
        counters[i] = 0;
}

char opp(char input)
{
    switch(input)
    {
        case 'W': return 'Y'; case 'Y': return 'W';
        case 'O': return 'R'; case 'R': return 'O';
        case 'G': return 'B'; case 'B': return 'G';
    }
    return input;
}

string OLLindex(int num)
{
    switch(num)
    {
        case 1: return "1";
        case 2: return "2";
        case 3: return "3";
        case 4: return "4";
        case 5: return "5";
        case 6: return "6";
        case 7: return "7";
        case 8: return "8";
        case 9: return "9";
        case 10: return "10";
        case 11: return "11";
        case 12: return "12";
        case 13: return "13";
        case 14: return "14";
        case 15: return "15";
        case 16: return "16";
        case 17: return "17";
        case 18: return "18";
        case 19: return "19";
        case 20: return "20";
        case 21: return "21";
        case 22: return "22";
        case 23: return "23";
        case 24: return "24";
        case 25: return "25";
        case 26: return "26";
        case 27: return "27";
        case 28: return "28";
        case 29: return "29";
        case 30: return "30";
        case 31: return "31";
        case 32: return "32";
        case 33: return "33";
        case 34: return "34";
        case 35: return "35";
        case 36: return "36";
        case 37: return "37";
        case 38: return "38";
        case 39: return "39";
        case 40: return "40";
        case 41: return "41";
        case 42: return "42";
        case 43: return "43";
        case 44: return "44";
        case 45: return "45";
        case 46: return "46";
        case 47: return "47";
        case 48: return "48";
        case 49: return "49";
        case 50: return "50";
        case 51: return "51";
        case 52: return "52";
        case 53: return "53";
        case 54: return "54";
        case 55: return "55";
        case 56: return "56";
        case 57: return "57";
    }
    return "skip";
}


string PLLindex(int num)
{
    switch(num)
    {
        case 1: return "Aa";
        case 2: return "Ab";
        case 3: return "E";
        case 4: return "F";
        case 5: return "Ga";
        case 6: return "Gb";
        case 7: return "Gc";
        case 8: return "Gd";
        case 9: return "H";
        case 10: return "Ja";
        case 11: return "Jb";
        case 12: return "Na";
        case 13: return "Nb";
        case 14: return "Ra";
        case 15: return "Rb";
        case 16: return "T";
        case 17: return "Ua";
        case 18: return "Ub";
        case 19: return "V";
        case 20: return "Y";
        case 21: return "Z";
    }
    return "PLL skip";
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANY CODE BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++ UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

#ifdef _MSC_VER  //  Microsoft Visual C++

#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                               &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Microsoft Visual C++, so assume UNIX interface

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen()  // will just write a newline in an Xcode output window
{
    static const char* term = getenv("TERM");
    if (term == nullptr  ||  strcmp(term, "dumb") == 0)
        cout << endl;
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}

#endif
