#include <iostream>
#include "cube.h"
#include "face.h"
#include "menu.h"
#include "utilities.h"
#include "timer.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int numLayers, option, show;
    menuProc(numLayers, option, show);    //asks for what user wants and what kind of cube
    
    
    Cube c(numLayers);          //how many layers you want, create the cube
    Timer t;
    
    if (option == 2)    //scramble the cube WCA style
        c.scramble(show);
    
    if (option == 3)
        c.buildYourCube();
    
    if (option == 3 && show)
    {
        Stamp step[7];
        step[0].info = "Cross"; step[1].info = "1st pair"; step[2].info = "2nd pair"; step[3].info = "3rd pair"; step[4].info = "4th pair";
        int moveCount = 0, allMove = 0, totalAttempts = 0;
        t.start();
        vector<Move> solution = c.findSolution(step);
        t.saveTimeStamp();
        cout << "Solution found:" << endl;
        for (vector<Move>::iterator it = solution.begin() ; it != solution.end(); it++)
        {
            cout << (*it).turn << " ";
            allMove++;
            for (int i = 0; i < 7; i++)
                if (allMove == step[i].moveCountAfter)
                {
                    cout << "// " << step[i].info << endl;
                }
            if ((*it).counts) moveCount++;
        }
        cout << endl;
        
        if (numLayers == 3)
        {
            cout << endl << "Cross attempts: " << step[0].attempts << " - " << setprecision(3) << fixed << step[0].t.getTimeStamp() << "s";
            cout << endl << "1st pair attempts: " << step[1].attempts << " - " << setprecision(3) << fixed << step[1].t.getTimeStamp() << "s";
            cout << endl << "2nd pair attempts: " << step[2].attempts << " - " << setprecision(3) << fixed << step[2].t.getTimeStamp() << "s";
            cout << endl << "3rd pair attempts: " << step[3].attempts << " - " << setprecision(3) << fixed << step[3].t.getTimeStamp() << "s";
            cout << endl << "Last pair attempts: " << step[4].attempts << " - " << setprecision(3) << fixed << step[4].t.getTimeStamp() << "s";
            cout << endl << "OLL attempts: " << step[5].attempts << " - " << setprecision(3) << fixed << step[5].t.getTimeStamp() << "s";
            cout << endl << "PLL attempts: " << step[6].attempts << " - " << setprecision(3) << fixed << step[6].t.getTimeStamp() << "s";
        }
        
        for (int i = 0; i < 7; i++)
            totalAttempts += step[i].attempts;
        
        if (numLayers == 2)
            cout << endl << "Total attempts: " << totalAttempts;
        cout << endl << "Total time elapsed: " << setprecision(3) << fixed << t.getTimeStamp() << "s";
        cout << endl << "Attempts per second: " << setprecision(0) << fixed << totalAttempts / t.getTimeStamp();
        cout << endl << "Moves to solution: " << moveCount << endl << endl;
    }
    else
    {
        c.display();        //display once
        cin.ignore(1000,'\n');
        
        makeMoves(&c);
    }
}
