#ifndef menu_h
#define menu_h

#include <iostream>
#include "utilities.h"
#include "cube.h"

void menuProc(int& numLayers, int& option, int& show);
void askQuestion(std::string question, int& selection, int bRange, int tRange);
void makeMoves(Cube* c);

#endif /* menu_h */
