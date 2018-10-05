#include "cube.h"
#include "utilities.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
using namespace std;

Cube::Cube(int dim)
{
    m_dim = dim;
    m_stickersPerFace = m_dim * m_dim;
    for (int i = 0; i < FACES; i++)
        m_face[i] = new Face(dim,i);
}

Cube::~Cube()
{
    for (int i = 0; i < FACES; i++)
        delete m_face[i];
}

int Cube::dim() const
{
    return m_dim;
}

void Cube::display() const
{
    int R = dim();
    int C = dim();
    int hBlocks = FACES / 3;
    int vBlocks = FACES / 4;
    int r, c, h, v;
    string spaces, dashes;
    
    for (int i = 0; i < m_dim; i++)
    {
        dashes += "-";
        spaces += " ";
    }
    
    cout << " " << spaces << " " << dashes << endl;
    for (v = 0; v < vBlocks; v++)       //3 big (3-down) rows
    {
        for (r = 0; r < R; r++)
        {
            for (h = 0; h < hBlocks; h++)      //4 big (3-wide) columns
            {
                int f = (v * 4) + h;
                
                if (f == 4)
                    cout << "|";
                else if (f == 0 || f == 8)
                    cout << " ";
                
                for (c = 0; c < C; c++)
                {
                    cout << m_face[f]->getArrElem((r*C)+c);
                }
                
                if (!(f == 2 | f == 3 | f == 10 | f == 11))
                    cout << "|";
                else
                    cout << " ";
            }
            cout << endl;
        }
        if (v != 2)
        {
            for (int i = 0; i < 4; i++)
                cout << " " << dashes;
            cout << endl;
        }
        else
            cout << " " << spaces << " " << dashes << endl;
    }
    
}

bool Cube::move(string s)
{
    int reps = 1;
    bool w = false;
    bool has3 = false;
    char sig = s[0];
    if (m_dim >= 6 && s[0] == '3')
    {
        sig = s[1];
        has3 = true;
        w = true;
    }
    
    if (s.size() != 1 && s[1] == 'w')
        w = true;
    
    if (s.size() != 1)
    {
        if (s[s.size()-1] == '2')    reps = 2;
        else if (s[s.size()-1] == '\'')  reps = 3;
        else if (s[s.size()-1] != 'w' || s[s.size()-2] != sig || (sig == s[0] && sig == s[1]) || (m_dim < 3 && w))
        {
            cout << "Not a valid move. Try again."; cout << endl;
            reps = 0;
            return false;
        }
    }
    
    for (int i = 0; i < reps; i++)
        switch(sig)
    {
        case 'F':  F(0); if (w) F(1); if (has3) F(2); break;    //1-3
        case 'B':  B(0); if (w) B(1); if (has3) B(2); break;    //10-12
        case 'L':  L(0); if (w) L(1); if (has3) L(2); break;    //13-15
        case 'R':  R(0); if (w) R(1); if (has3) R(2); break;    //4-6
        case 'D':  D(0); if (w) D(1); if (has3) D(2); break;    //16-18
        case 'U':  U(0); if (w) U(1); if (has3) U(2); break;    //7-9
        case 'M':  if (m_dim % 2 != 0) L((m_dim - 1)/2);  break;
        case 'E':  if (m_dim % 2 != 0) F((m_dim - 1)/2);  break;
        case 'S':  if (m_dim % 2 != 0) D((m_dim - 1)/2);  break;
        case 'x':  for (int i = 0; i < m_dim; i++) R(i);  break;
        case 'y':  for (int i = 0; i < m_dim; i++) U(i);  break;
        case 'z':  for (int i = 0; i < m_dim; i++) F(i);  break;
        case 'f':  if (m_dim > 2 && !has3 && !w){ F(0); F(1);  break;}
        case 'b':  if (m_dim > 2 && !has3 && !w){ B(0); B(1);  break;}
        case 'l':  if (m_dim > 2 && !has3 && !w){ L(0); L(1);  break;}
        case 'r':  if (m_dim > 2 && !has3 && !w){ R(0); R(1);  break;}
        case 'd':  if (m_dim > 2 && !has3 && !w){ D(0); D(1);  break;}
        case 'u':  if (m_dim > 2 && !has3 && !w){ U(0); U(1);  break;}
        default: cout << "Not a valid move. Try again."; cout << endl; reps = 0; return false;
    }
    return true;
}

void Cube::scramble(int show)
{
    int moves = 0, randMax = 0;
    switch(m_dim)
    {
        case 2: moves = 10; randMax = 9; break;
        case 3: moves = 25; randMax = 18; break;
        case 4: moves = 40; randMax = 27; break;
        case 5: moves = 60; randMax = 36; break;
        case 6: moves = 80; randMax = 45; break;
        case 7: moves = 100; randMax = 54; break;
    }
    
    string turn;
    int cur, prev = 57;
    for (int i = 0; i < moves; i++)
    {
        do{
            cur = randInt(0,randMax-1);
        } while(cur / 3 == prev / 3);
        
        prev = cur;
        turn = intToTurn(cur);
        move(turn);
        
        if (show)
            cout << turn << " ";
    }
    if (show)
        cout << endl;
}

void Cube::buildYourCube()
{
    string stickers, temp;
    
    do
    {
        cout << "Enter one face at a time, as listed below, sticker-letter by sticker-letter, in order from left to right, top row to bottom row. No spaces and all caps. (characters allowed: W,O,G,R,B,Y to represent each color)" << endl << endl;
        
        cout << "Enter UP face: ";
        cin >> stickers;
        cout << "Enter LEFT face: ";
        cin >> temp;
        stickers += temp;
        cout << "Enter FRONT face: ";
        cin >> temp;
        stickers += temp;
        cout << "Enter RIGHT face: ";
        cin >> temp;
        stickers += temp;
        cout << "Enter BACK face: ";
        cin >> temp;
        stickers += temp;
        cout << "Enter DOWN face: ";
        cin >> temp;
        stickers += temp;
        
    } while (!isValidState(stickers));
    
    for (int i = 0; i < m_stickersPerFace; i++)
    {
        m_face[UP]->changeArrElem(i,stickers[i]);
        m_face[LEFT]->changeArrElem(i,stickers[i + m_stickersPerFace]);
        m_face[FRONT]->changeArrElem(i,stickers[i + (2 * m_stickersPerFace)]);
        m_face[RIGHT]->changeArrElem(i,stickers[i + (3 * m_stickersPerFace)]);
        m_face[BACK]->changeArrElem(i,stickers[i + (4 * m_stickersPerFace)]);
        m_face[DOWN]->changeArrElem(i,stickers[i + (5 * m_stickersPerFace)]);
    }
}

///////////////////////////////////////////////////////////////////////////
//  Cube Movement functions
///////////////////////////////////////////////////////////////////////////

void Cube::F(int l)
{
    char temp[m_dim];
    for (int i = 0; i < m_dim; i++)
    {
        int posL = ((m_dim * m_dim) - 1) - (m_dim * i) - l;
        int posU = ((m_dim - 1) * m_dim) + i - (m_dim * l);
        int posR = i * m_dim + l;
        int posD = m_dim - i - 1 + (m_dim * l);
        temp[i] = m_face[DOWN]->getArrElem(posD);                          //save 9
        m_face[DOWN]->changeArrElem(posD,m_face[RIGHT]->getArrElem(posR));     //6 to 9, red to yellow
        m_face[RIGHT]->changeArrElem(posR,m_face[UP]->getArrElem(posU));     //1 to 6, white to red
        m_face[UP]->changeArrElem(posU,m_face[LEFT]->getArrElem(posL));     //4 to 1, orange to white
        m_face[LEFT]->changeArrElem(posL,temp[i]);                         //9 to 4, yellow to orange
    }
    if (l == 0)
        m_face[FRONT]->rotate(CW);
    else if (l == m_dim - 1)
        m_face[BACK]->rotate(CCW);
}

void Cube::B(int l)
{
    char temp[m_dim];
    for (int i = 0; i < m_dim; i++)
    {
        int posR = ((m_dim * m_dim) - 1) - (m_dim * i) - l;
        int posD = ((m_dim - 1) * m_dim) + i  - (m_dim * l);
        int posL = i * m_dim + l;
        int posU = m_dim - i - 1 + (m_dim * l);
        temp[i] = m_face[DOWN]->getArrElem(posD);                          //save 9
        m_face[DOWN]->changeArrElem(posD,m_face[LEFT]->getArrElem(posL));     //4 to 9
        m_face[LEFT]->changeArrElem(posL,m_face[UP]->getArrElem(posU));     //1 to 4
        m_face[UP]->changeArrElem(posU,m_face[RIGHT]->getArrElem(posR));     //6 to 1
        m_face[RIGHT]->changeArrElem(posR,temp[i]);                         //9 to 6
    }
    if (l == 0)
        m_face[BACK]->rotate(CW);
    else if (l == m_dim - 1)
        m_face[FRONT]->rotate(CCW);
}

void Cube::L(int l)
{
    char temp[m_dim];
    for (int i = 0; i < m_dim; i++)
    {
        int posB = (m_dim - 1) + (m_dim * i) - l;
        int posUFD = ((m_dim - 1) * m_dim) - (m_dim * i) + l;
        temp[i] = m_face[DOWN]->getArrElem(posUFD);                        //save 9
        m_face[DOWN]->changeArrElem(posUFD,m_face[FRONT]->getArrElem(posUFD));   //5 to 9
        m_face[FRONT]->changeArrElem(posUFD,m_face[UP]->getArrElem(posUFD));   //1 to 5
        m_face[UP]->changeArrElem(posUFD,m_face[BACK]->getArrElem(posB)); //7 to 1
        m_face[BACK]->changeArrElem(posB,temp[i]);                       //9 to 7
    }
    if (l == 0)
        m_face[LEFT]->rotate(CW);
    else if (l == m_dim - 1)
        m_face[RIGHT]->rotate(CCW);
}

void Cube::R(int l)
{
    char temp[m_dim];
    for (int i = 0; i < m_dim; i++)
    {
        int posUFD = (m_dim - 1) + (m_dim * i) - l;
        int posB = ((m_dim - 1) * m_dim) - (m_dim * i) + l;
        temp[i] = m_face[DOWN]->getArrElem(posUFD);                        //save 9
        m_face[DOWN]->changeArrElem(posUFD,m_face[BACK]->getArrElem(posB));   //7 to 9
        m_face[BACK]->changeArrElem(posB,m_face[UP]->getArrElem(posUFD));   //1 to 7
        m_face[UP]->changeArrElem(posUFD,m_face[FRONT]->getArrElem(posUFD)); //5 to 1
        m_face[FRONT]->changeArrElem(posUFD,temp[i]);                       //9 to 5
    }
    if (l == 0)
        m_face[RIGHT]->rotate(CW);
    else if (l == m_dim - 1)
        m_face[LEFT]->rotate(CCW);
}

void Cube::D(int l)
{
    char temp[m_dim];
    for (int i = 0; i < m_dim; i++)
    {
        int pos = ((m_dim - 1) * m_dim) + i - (l * m_dim);
        temp[i] = m_face[BACK]->getArrElem(pos);                        //save 7
        m_face[BACK]->changeArrElem(pos,m_face[RIGHT]->getArrElem(pos));      //6 to 7
        m_face[RIGHT]->changeArrElem(pos,m_face[FRONT]->getArrElem(pos));      //5 to 6
        m_face[FRONT]->changeArrElem(pos,m_face[LEFT]->getArrElem(pos));      //4 to 5
        m_face[LEFT]->changeArrElem(pos,temp[i]);                         //7 to 4
    }
    if (l == 0)
        m_face[DOWN]->rotate(CW);
    else if (l == m_dim - 1)
        m_face[UP]->rotate(CCW);
}

void Cube::U(int l)
{
    char temp[m_dim];
    for (int i = 0; i < m_dim; i++)
    {
        int pos = i + (l * m_dim);
        temp[i] = m_face[BACK]->getArrElem(pos);                        //save 7
        m_face[BACK]->changeArrElem(pos,m_face[LEFT]->getArrElem(pos));      //4 to 7
        m_face[LEFT]->changeArrElem(pos,m_face[FRONT]->getArrElem(pos));      //5 to 4
        m_face[FRONT]->changeArrElem(pos,m_face[RIGHT]->getArrElem(pos));      //6 to 5
        m_face[RIGHT]->changeArrElem(pos,temp[i]);                         //7 to 6
    }
    if (l == 0)
        m_face[UP]->rotate(CW);
    else if (l == m_dim - 1)
        m_face[DOWN]->rotate(CCW);
}

void Cube::M()
{
    char temp[m_dim];
    for (int i = 0; i < m_dim; i++)
    {
        int posB = ((m_dim * m_dim) - ((m_dim + 1)/2)) - (m_dim * i);
        int posUFD = ((m_dim - 1)/2) + (m_dim * i);
        temp[i] = m_face[DOWN]->getArrElem(posUFD);                        //save 9
        m_face[DOWN]->changeArrElem(posUFD,m_face[FRONT]->getArrElem(posUFD));   //5 to 9
        m_face[FRONT]->changeArrElem(posUFD,m_face[UP]->getArrElem(posUFD));   //1 to 5
        m_face[UP]->changeArrElem(posUFD,m_face[BACK]->getArrElem(posB)); //7 to 1
        m_face[BACK]->changeArrElem(posB,temp[i]);                       //9 to 7
    }
}

void Cube::E()
{
    char temp[m_dim];
    for (int i = 0; i < m_dim; i++)
    {
        int pos = (m_dim * ((m_dim - 1)/2)) + i;
        temp[i] = m_face[BACK]->getArrElem(pos);                        //save 7
        m_face[BACK]->changeArrElem(pos,m_face[RIGHT]->getArrElem(pos));      //6 to 7
        m_face[RIGHT]->changeArrElem(pos,m_face[FRONT]->getArrElem(pos));      //5 to 6
        m_face[FRONT]->changeArrElem(pos,m_face[LEFT]->getArrElem(pos));      //4 to 5
        m_face[LEFT]->changeArrElem(pos,temp[i]);                         //7 to 4
    }
}

void Cube::S()
{
    char temp[m_dim];
    for (int i = 0; i < m_dim; i++)
    {
        int posL = ((m_dim - 1)/2) + (m_dim * (2 - i));
        int posU = (m_dim * ((m_dim - 1)/2)) + i;
        int posR = ((m_dim - 1)/2) + (m_dim * i);
        int posD = (m_dim * ((m_dim - 1)/2)) + (m_dim - 1 - i);
        temp[i] = m_face[DOWN]->getArrElem(posD);                          //save 9
        m_face[DOWN]->changeArrElem(posD,m_face[RIGHT]->getArrElem(posR));     //6 to 9, red to yellow
        m_face[RIGHT]->changeArrElem(posR,m_face[UP]->getArrElem(posU));     //1 to 6, white to red
        m_face[UP]->changeArrElem(posU,m_face[LEFT]->getArrElem(posL));     //4 to 1, orange to white
        m_face[LEFT]->changeArrElem(posL,temp[i]);                         //9 to 4, yellow to orange
    }
}

///////////////////////////////////////////////////////////////////////////
//  CUBE-CHECKING FUNCTIONS
///////////////////////////////////////////////////////////////////////////

bool Cube::isValidState(string stickers) const
{
    bool corner = true, center = true, edge = true;
    
    if (stickers.size() != m_stickersPerFace * 6)
        return false;
    
    center = centers(stickers);
    edge = edges(stickers);
    corner = corners(stickers);
    
    cout << endl;
    if (!center)
        cout << "Center input invalid. ";
    if (!edge)
        cout << "Edge input invalid. ";
    if (!corner)
        cout << "Corner input invalid. ";
    
    if (!corner || !center || !edge)
    {
        cout << "Try again." << endl << endl;
        return false;
    }
    
    return true;
}

///////////////////////////////////////////////////////////////////////////
//  Center-Checking functions
///////////////////////////////////////////////////////////////////////////

bool Cube::centers(string stickers) const
{
    int counters[6] = {0,0,0,0,0,0}; // 0 - W, 1 - O, 2 - G, 3 - R, 4 - B, 5 - Y
    
    if (m_dim % 2 == 1)         //3x3+
        if (!centerType(m_stickersPerFace / 2, counters, stickers) || !counterCheck(counters, 6, 1))
            return false;
    
    for (int i = 1; i < m_dim / 2; i++) //all corner centers, 4x4+
    {
        resetCounters(counters, 6);
        if (!centerType((m_dim * i) + i, counters, stickers) || !centerType((m_dim * (i+1)) - (i+1), counters, stickers) || !centerType(m_stickersPerFace - (m_dim * (i+1)) + i, counters, stickers) || !centerType(m_stickersPerFace - (m_dim * i) - (i+1), counters, stickers) || !counterCheck(counters, 6, 4))
            return false;
    }
    
    if (m_dim % 2 == 1)
        for (int i = 1; i < (m_dim - 1) / 2; i++) //all edge centers, 5x5+
        {
            resetCounters(counters, 6);
            if (!centerType(m_dim * (0.5 + i), counters, stickers) || !centerType(m_dim * (m_dim / 2) + i, counters, stickers) || !centerType(m_stickersPerFace - (m_dim * (m_dim / 2) + 1) - i, counters, stickers) || !centerType(m_stickersPerFace - (m_dim * (0.5 + i)) - 0.5, counters, stickers) || !counterCheck(counters, 6, 4))
                return false;
        }
    
    for (int i = 1; i < (m_dim - 2) / 2; i++) //all edge center pairs, 6x6+
    {
        for (int j = 0; j < i; j++) //only affects 8x8+
        {
            resetCounters(counters, 6);
            if (!centerType((m_dim * (j + 1)) + 1 + i, counters, stickers) || !centerType((m_dim * (j + 2)) - 2 - i, counters, stickers) || !centerType((m_dim * (i + 1)) + 1 + j, counters, stickers) || !centerType((m_dim * (i + 2)) - 2 - j, counters, stickers) || !centerType(m_stickersPerFace - (m_dim * (i + 2)) + 1 + j, counters, stickers) || !centerType(m_stickersPerFace - (m_dim * (i + 1)) - 2 - j, counters, stickers) || !centerType(m_stickersPerFace - (m_dim * (j + 2)) + i + 1, counters, stickers) || !centerType(m_stickersPerFace - (m_dim * (j + 1)) - 2 - i, counters, stickers) || !counterCheck(counters, 6, 8))
                return false;
        }
    }
    return true;
}

bool Cube::centerType(int typeOffset, int* counters, string stickers) const
{
    for (int i = typeOffset; i < (m_stickersPerFace * 6); i += m_stickersPerFace) //center centers
    {
        switch(stickers[i])
        {
            case 'W': counters[0]++; break;
            case 'O': counters[1]++; break;
            case 'G': counters[2]++; break;
            case 'R': counters[3]++; break;
            case 'B': counters[4]++; break;
            case 'Y': counters[5]++; break;
            default: return false;
        }
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////
//  Edge-Checking functions
///////////////////////////////////////////////////////////////////////////

bool Cube::edges(string stickers) const
{
    int off[8] = {0,0,0,0,0,0,0,0}, counters[12] = {0,0,0,0,0,0,0,0,0,0,0,0}; // 0 - WO, 1 - WR, 2 - WG, 3 - WB, 4 - YO, 5 - YR, 6 - YG, 7 - YB, 8 - OG, 9 - OB, 10 - RG, 11 - RB
    
    if (m_dim % 2 == 1)     //center edges
    {
        off[0] = (m_dim - 1)/2;
        off[1] = m_dim * off[0];
        off[2] = m_stickersPerFace - off[1] - 1;
        off[3] = m_stickersPerFace - off[0] - 1;
        if (!edgeType(off, counters, stickers) || !counterCheck(counters, 12, 1))
            return false;
    }
    
    for (int i = 1; i < m_dim / 2; i++)     //edge edge pairs
    {
        resetCounters(counters, 12);
        off[0] = i;
        off[1] = m_dim - i - 1;
        off[2] = m_dim * i;
        off[3] = off[0] + off[1] + off[2];
        off[4] = m_stickersPerFace - off[3] - 1;
        off[5] = m_stickersPerFace - off[2] - 1;
        off[6] = m_stickersPerFace - off[1] - 1;
        off[7] = m_stickersPerFace - i - 1;
        if (!edgeType(off, counters, stickers) || !counterCheck(counters, 12, 2))
            return false;
    }
    return true;
}

bool Cube::edgeType(int* off, int* counters, string stickers) const
{
    int u = 0, l = m_stickersPerFace, f = m_stickersPerFace * 2, r = m_stickersPerFace * 3, b = m_stickersPerFace * 4, d = m_stickersPerFace * 5; //sticker on that side
    
    
    int edgeNo = 24;
    char edges[24][2] = {{stickers[u + off[0]], stickers[b + off[1]]},
        {stickers[u + off[1]], stickers[b + off[0]]},
        {stickers[u + off[2]], stickers[l + off[0]]},
        {stickers[u + off[3]], stickers[r + off[1]]},
        {stickers[d + off[0]], stickers[f + off[6]]},
        {stickers[d + off[1]], stickers[f + off[7]]},
        {stickers[d + off[2]], stickers[l + off[7]]},
        {stickers[d + off[3]], stickers[r + off[6]]},
        {stickers[u + off[4]], stickers[l + off[1]]},
        {stickers[u + off[5]], stickers[r + off[0]]},
        {stickers[u + off[6]], stickers[f + off[0]]},
        {stickers[u + off[7]], stickers[f + off[1]]},
        {stickers[d + off[4]], stickers[l + off[6]]},
        {stickers[d + off[5]], stickers[r + off[7]]},
        {stickers[d + off[6]], stickers[b + off[7]]},
        {stickers[d + off[7]], stickers[b + off[6]]},
        {stickers[l + off[2]], stickers[b + off[3]]},
        {stickers[l + off[4]], stickers[b + off[5]]},
        {stickers[l + off[3]], stickers[f + off[2]]},
        {stickers[l + off[5]], stickers[f + off[4]]},
        {stickers[r + off[2]], stickers[f + off[3]]},
        {stickers[r + off[4]], stickers[f + off[5]]},
        {stickers[r + off[3]], stickers[b + off[2]]},
        {stickers[r + off[5]], stickers[b + off[4]]}};
    
    
    if (off[4] == 0)    //if the last four offsets are unused - means center edges
    {
        edgeNo = 12;
        
        edges[0][1] = stickers[b + off[0]];
        edges[1][1] = stickers[l + off[0]];
        edges[2][1] = stickers[r + off[0]];
        edges[3][1] = stickers[f + off[0]];
        edges[4][1] = stickers[f + off[3]];
        edges[5][1] = stickers[l + off[3]];
        edges[6][1] = stickers[r + off[3]];
        edges[7][1] = stickers[b + off[3]];
        
        edges[8][0] = stickers[l + off[1]];
        edges[8][1] = stickers[b + off[2]];
        edges[9][0] = stickers[l + off[2]];
        edges[9][1] = stickers[f + off[1]];
        edges[10][0] = stickers[r + off[1]];
        edges[10][1] = stickers[f + off[2]];
        edges[11][0] = stickers[r + off[2]];
        edges[11][1] = stickers[b + off[1]];
    }
    
    for (int i = 0; i < edgeNo; i++)
    {
        bool w = false, o = false, g = false, r = false, b = false, y = false;
        for (int j = 0; j < 2; j++)
        {
            switch (edges[i][j])
            {
                case 'W': w = true; break;
                case 'O': o = true; break;
                case 'G': g = true; break;
                case 'R': r = true; break;
                case 'B': b = true; break;
                case 'Y': y = true; break;
                default: return false;
            }
        }
        
        if (w == true && o == true) counters[0]++;
        else if (w == true && r == true) counters[1]++;
        else if (w == true && g == true) counters[2]++;
        else if (w == true && b == true) counters[3]++;
        else if (y == true && o == true) counters[4]++;
        else if (y == true && r == true) counters[5]++;
        else if (y == true && g == true) counters[6]++;
        else if (y == true && b == true) counters[7]++;
        else if (o == true && g == true) counters[8]++;
        else if (o == true && b == true) counters[9]++;
        else if (r == true && g == true) counters[10]++;
        else if (r == true && b == true) counters[11]++;
        else
            return false;
    }
    
    return true;
}

///////////////////////////////////////////////////////////////////////////
//  Corner-Checking functions
///////////////////////////////////////////////////////////////////////////

bool Cube::corners(string stickers) const
{
    int u = 0, l = m_stickersPerFace, f = m_stickersPerFace * 2, r = m_stickersPerFace * 3, b = m_stickersPerFace * 4, d = m_stickersPerFace * 5; //sticker on that side
    int off2 = m_dim - 1, off3 = m_stickersPerFace - m_dim, off4 = m_stickersPerFace - 1;   //face offsets for each corner
    
    char corners[8][3] = {{stickers[u], stickers[l], stickers[b + off2]},               //U1,L1,B2 0,9,38
        {stickers[u + off2], stickers[r + off2], stickers[b]},        //U2,R2,B1 2,29,36
        {stickers[u + off3], stickers[l + off2], stickers[f]},        //U3,L2,F1 6,11,18
        {stickers[u + off4], stickers[f + off2], stickers[r]},        //U4,F2,R1 8,20,27
        {stickers[l + off3], stickers[b + off4], stickers[d + off3]}, //L3,B4,D3 15,44,51
        {stickers[l + off4], stickers[f + off3], stickers[d]},        //L4,F3,D1 17,24,45
        {stickers[f + off4], stickers[r + off3], stickers[d + off2]}, //F4,R3,D2 26,33,47
        {stickers[r + off4], stickers[b + off3], stickers[d + off4]}};//R4,B3,D4 35,42,53
    
    int WOB = 0, WRG = 0, WOG = 0, WRB = 0, YOB = 0, YOG = 0, YRG = 0, YRB = 0;
    
    for (int i = 0; i < 8; i++)
    {
        bool w = false, o = false, g = false, r = false, b = false, y = false;
        for (int j = 0; j < 3; j++)
        {
            switch (corners[i][j])
            {
                case 'W': w = true; break;
                case 'O': o = true; break;
                case 'G': g = true; break;
                case 'R': r = true; break;
                case 'B': b = true; break;
                case 'Y': y = true; break;
                default: return false;
            }
        }
        
        if (w == true && o == true && b == true) WOB++;
        else if (w == true && o == true && g == true) WOG++;
        else if (w == true && r == true && b == true) WRB++;
        else if (w == true && r == true && g == true) WRG++;
        else if (y == true && o == true && b == true) YOB++;
        else if (y == true && o == true && g == true) YOG++;
        else if (y == true && r == true && b == true) YRB++;
        else if (y == true && r == true && g == true) YRG++;
        else
            return false;
    }
    
    if (WOB != 1 || WRG != 1 || WOG != 1 || WRB != 1 || YOB != 1 || YOG != 1 || YRG != 1 || YRB != 1)
        return false;
    
    return true;
}

///////////////////////////////////////////////////////////////////////////
//  State-checking functions
///////////////////////////////////////////////////////////////////////////

bool Cube::checkSolved()
{
    int st = 0;
    char u = m_face[UP]->getArrElem(st);
    char l = m_face[LEFT]->getArrElem(st);
    char f = m_face[FRONT]->getArrElem(st);
    char r = m_face[RIGHT]->getArrElem(st);
    char b = m_face[BACK]->getArrElem(st);
    
    for (int i = 1; i < m_stickersPerFace; i++)
    {
        if (!(u == m_face[UP]->getArrElem(i) &&
              l == m_face[LEFT]->getArrElem(i) &&
              f == m_face[FRONT]->getArrElem(i) &&
              r == m_face[RIGHT]->getArrElem(i) &&
              b == m_face[BACK]->getArrElem(i)))
            return false;
    }
    return true;
}

bool Cube::checkFace()
{
    int st = 0;
    char u = m_face[UP]->getArrElem(st);
    char l = m_face[LEFT]->getArrElem(st);
    char f = m_face[FRONT]->getArrElem(st);
    char r = m_face[RIGHT]->getArrElem(st);
    char b = m_face[BACK]->getArrElem(st);
    char d = m_face[DOWN]->getArrElem(st);
    bool matches[6] = {true, true, true, true, true, true};
    
    for (int i = 1; i < m_stickersPerFace; i++)
    {
        if (matches[0] && (u != m_face[UP]->getArrElem(i))) matches[0] = false;
        if (matches[1] && (l != m_face[LEFT]->getArrElem(i))) matches[1] = false;
        if (matches[2] && (f != m_face[FRONT]->getArrElem(i))) matches[2] = false;
        if (matches[3] && (r != m_face[RIGHT]->getArrElem(i))) matches[3] = false;
        if (matches[4] && (b != m_face[BACK]->getArrElem(i))) matches[4] = false;
        if (matches[5] && (d != m_face[DOWN]->getArrElem(i))) matches[5] = false;
    }
    if (!(matches[0] || matches[1] || matches[2] || matches[3] || matches[4] || matches[5]))
        return false;
    
    return true;
}

bool Cube::checkSide()
{
    int st = 0;
    char u = m_face[UP]->getArrElem(st);
    char l = m_face[LEFT]->getArrElem(st);
    char f = m_face[FRONT]->getArrElem(st);
    char r = m_face[RIGHT]->getArrElem(st);
    char b = m_face[BACK]->getArrElem(st);
    char d = m_face[DOWN]->getArrElem(st);
    bool matches[6] = {true, true, true, true, true, true};
    
    for (int i = 1; i < m_stickersPerFace; i++)
    {
        if (matches[0] && (u != m_face[UP]->getArrElem(i))) matches[0] = false;
        if (matches[1] && (l != m_face[LEFT]->getArrElem(i))) matches[1] = false;
        if (matches[2] && (f != m_face[FRONT]->getArrElem(i))) matches[2] = false;
        if (matches[3] && (r != m_face[RIGHT]->getArrElem(i))) matches[3] = false;
        if (matches[4] && (b != m_face[BACK]->getArrElem(i))) matches[4] = false;
        if (matches[5] && (d != m_face[DOWN]->getArrElem(i))) matches[5] = false;
    }
    if (matches[0])
    {
        for (int j = 1; j < m_dim; j++)
            if (!(l == m_face[LEFT]->getArrElem(j) &&
                  f == m_face[FRONT]->getArrElem(j) &&
                  r == m_face[RIGHT]->getArrElem(j)))
                return false;
    }
    else if (matches[1])
    {
        for (int j = m_dim; j < m_stickersPerFace; j+=3)
            if (!(u == m_face[UP]->getArrElem(j) &&
                  f == m_face[FRONT]->getArrElem(j) &&
                  d == m_face[DOWN]->getArrElem(j)))
                return false;
    }
    else if (matches[2])
    {
        int offset = m_stickersPerFace - m_dim;
        int u6 = m_face[UP]->getArrElem(offset);
        for (int j = 1; j < m_dim; j++)
            if (!(u6 == m_face[UP]->getArrElem(j+offset) &&
                  d == m_face[DOWN]->getArrElem(j) &&
                  r == m_face[RIGHT]->getArrElem(j*m_dim)))
                return false;
    }
    else if (matches[3])
    {
        int offset = m_dim - 1;
        int u2 = m_face[UP]->getArrElem(offset);
        int f2 = m_face[FRONT]->getArrElem(offset);
        int d2 = m_face[DOWN]->getArrElem(offset);
        for (int j = m_dim + offset; j < m_stickersPerFace; j+=m_dim)
            if (!(u2 == m_face[UP]->getArrElem(j+offset) &&
                  f2 == m_face[FRONT]->getArrElem(j+offset) &&
                  d2 == m_face[DOWN]->getArrElem(j+offset)))
                return false;
    }
    else if (matches[4])
    {
        int offset = m_stickersPerFace - m_dim;
        int d6 = m_face[DOWN]->getArrElem(offset);
        for (int j = 1; j < m_dim; j++)
            if (!(l == m_face[LEFT]->getArrElem(j) &&
                  u == m_face[UP]->getArrElem(j) &&
                  d6 == m_face[DOWN]->getArrElem(j+offset)))
                return false;
    }
    else if (matches[5])
    {
        int offset = m_stickersPerFace - m_dim;
        int l6 = m_face[LEFT]->getArrElem(offset);
        int f6 = m_face[FRONT]->getArrElem(offset);
        int r6 = m_face[RIGHT]->getArrElem(offset);
        for (int j = 7; j < m_stickersPerFace; j++)
            if (!(l6 == m_face[LEFT]->getArrElem(j) &&
                  f6 == m_face[FRONT]->getArrElem(j) &&
                  r6 == m_face[RIGHT]->getArrElem(j)))
                return false;
    }
    else
        return false;
    
    return true;
}

bool Cube::checkDomino()
{
    int st = 0;
    char u = m_face[UP]->getArrElem(st);
    char l = m_face[LEFT]->getArrElem(st);
    char f = m_face[FRONT]->getArrElem(st);
    char r = m_face[RIGHT]->getArrElem(st);
    char b = m_face[BACK]->getArrElem(st);
    char d = m_face[DOWN]->getArrElem(st);
    
    if (((u == 'W' || u == 'Y') && (d == 'W' || d == 'Y')) || ((u == 'O' || u == 'R') && (d == 'O' || d == 'R')) || ((u == 'G' || u == 'B') && (d == 'G' || d == 'B')))
    {if (searchKocDomino(UP,DOWN,u)) return true;}
    if (((l == 'W' || l == 'Y') && (r == 'W' || r == 'Y')) || ((l == 'O' || l == 'R') && (r == 'O' || r == 'R')) || ((l == 'G' || l == 'B') && (r == 'G' || r == 'B')))
    {if (searchKocDomino(LEFT,RIGHT,l)) return true;}
    if (((f == 'W' || f == 'Y') && (b == 'W' || b == 'Y')) || ((f == 'O' || f == 'R') && (b == 'O' || b == 'R')) || ((f == 'G' || f == 'B') && (b == 'G' || b == 'B')))
    {if (searchKocDomino(FRONT,BACK,f)) return true;}
    return false;
}

bool Cube::searchKocDomino(int top, int bottom, char sig)
{
    char to, bo, sig2 = 0;
    if (top != 0)
    {
        sig2 = opp(sig);
        for (int i = 1; i < m_stickersPerFace; i++)
        {
            to = m_face[top]->getArrElem(i);
            bo = m_face[bottom]->getArrElem(i);
            if (!((to == sig || to == sig2) &&
                  (bo == sig || bo == sig2)))
                return false;
        }
        return true;
    }
    
    return false;
}

bool Cube::checkCross(int& face)
{
    int st = 4;
    char u = m_face[UP]->getArrElem(st);
    char l = m_face[LEFT]->getArrElem(st);
    char f = m_face[FRONT]->getArrElem(st);
    char r = m_face[RIGHT]->getArrElem(st);
    char b = m_face[BACK]->getArrElem(st);
    char d = m_face[DOWN]->getArrElem(st);
    bool matches[6] = {true, true, true, true, true, true};
    
    for (int i = 1; i < m_stickersPerFace; i+=2)
    {
        if (matches[0] && (u != m_face[UP]->getArrElem(i))) matches[0] = false;
        if (matches[1] && (l != m_face[LEFT]->getArrElem(i))) matches[1] = false;
        if (matches[2] && (f != m_face[FRONT]->getArrElem(i))) matches[2] = false;
        if (matches[3] && (r != m_face[RIGHT]->getArrElem(i))) matches[3] = false;
        if (matches[4] && (b != m_face[BACK]->getArrElem(i))) matches[4] = false;
        if (matches[5] && (d != m_face[DOWN]->getArrElem(i))) matches[5] = false;
    }
    if (matches[0] && l == m_face[LEFT]->getArrElem(1) &&
        f == m_face[FRONT]->getArrElem(1) &&
        r == m_face[RIGHT]->getArrElem(1))
    {
        face = UP;
        return true;
    }
    else if (matches[1] && u == m_face[UP]->getArrElem(3) &&
             f == m_face[FRONT]->getArrElem(3) &&
             d == m_face[DOWN]->getArrElem(3))
    {
        face = LEFT;
        return true;
    }
    else if (matches[2] && u == m_face[UP]->getArrElem(7) &&
             d == m_face[DOWN]->getArrElem(1) &&
             r == m_face[RIGHT]->getArrElem(3))
    {
        face = FRONT;
        return true;
    }
    else if (matches[3] && u == m_face[UP]->getArrElem(5) &&
             f == m_face[FRONT]->getArrElem(5) &&
             d == m_face[DOWN]->getArrElem(5))
    {
        face = RIGHT;
        return true;
    }
    else if (matches[4] && l == m_face[LEFT]->getArrElem(3) &&
             u == m_face[UP]->getArrElem(1) &&
             d == m_face[DOWN]->getArrElem(7))
    {
        face = BACK;
        return true;
    }
    else if (matches[5] && l == m_face[LEFT]->getArrElem(7) &&
             f == m_face[FRONT]->getArrElem(7) &&
             r == m_face[RIGHT]->getArrElem(7))
    {
        face = DOWN;
        return true;
    }
    
    return false;
}

bool Cube::checkXCross(int& num, int& face, Pair* done)
{
    int st = 4;
    char u = m_face[UP]->getArrElem(st);
    char l = m_face[LEFT]->getArrElem(st);
    char f = m_face[FRONT]->getArrElem(st);
    char r = m_face[RIGHT]->getArrElem(st);
    char b = m_face[BACK]->getArrElem(st);
    char d = m_face[DOWN]->getArrElem(st);
    bool matches[6] = {true, true, true, true, true, true};
    
    for (int i = 1; i < m_stickersPerFace; i+=2)
    {
        if (matches[0] && (u != m_face[UP]->getArrElem(i))) matches[0] = false;
        if (matches[1] && (l != m_face[LEFT]->getArrElem(i))) matches[1] = false;
        if (matches[2] && (f != m_face[FRONT]->getArrElem(i))) matches[2] = false;
        if (matches[3] && (r != m_face[RIGHT]->getArrElem(i))) matches[3] = false;
        if (matches[4] && (b != m_face[BACK]->getArrElem(i))) matches[4] = false;
        if (matches[5] && (d != m_face[DOWN]->getArrElem(i))) matches[5] = false;
    }
    if (matches[0])
    {
        if (l == m_face[LEFT]->getArrElem(1) &&
            f == m_face[FRONT]->getArrElem(1) &&
            r == m_face[RIGHT]->getArrElem(1))
        {
            num++;
            if (u == m_face[UP]->getArrElem(0) &&
                l == m_face[LEFT]->getArrElem(0) && l == m_face[LEFT]->getArrElem(3) &&
                b == m_face[BACK]->getArrElem(2) && b == m_face[BACK]->getArrElem(5))
            {face = UP; done->pos = 0; done->c[0] = u; done->c[1] = l; done->c[2] = b; return true;}
            else if (u == m_face[UP]->getArrElem(2) &&
                     r == m_face[RIGHT]->getArrElem(2) && r == m_face[RIGHT]->getArrElem(5) &&
                     b == m_face[BACK]->getArrElem(0) && b == m_face[BACK]->getArrElem(3))
            {face = UP; done->pos = 1; done->c[0] = u; done->c[1] = r; done->c[2] = b; return true;}
            else if (u == m_face[UP]->getArrElem(6) &&
                     l == m_face[LEFT]->getArrElem(2) && l == m_face[LEFT]->getArrElem(5) &&
                     f == m_face[FRONT]->getArrElem(0) && f == m_face[FRONT]->getArrElem(3))
            {face = UP; done->pos = 2; done->c[0] = u; done->c[1] = l; done->c[2] = f; return true;}
            else if (u == m_face[UP]->getArrElem(8) &&
                     r == m_face[RIGHT]->getArrElem(0) && r == m_face[RIGHT]->getArrElem(3) &&
                     f == m_face[FRONT]->getArrElem(2) && f == m_face[FRONT]->getArrElem(5))
            {face = UP; done->pos = 3; done->c[0] = u; done->c[1] = r; done->c[2] = f; return true;}
        }
    }
    if (matches[1])
    {
        if (u == m_face[UP]->getArrElem(3) &&
            f == m_face[FRONT]->getArrElem(3) &&
            d == m_face[DOWN]->getArrElem(3))
        {
            num++;
            if (l == m_face[LEFT]->getArrElem(0) &&
                u == m_face[UP]->getArrElem(0) && u == m_face[UP]->getArrElem(1) &&
                b == m_face[BACK]->getArrElem(1) && b == m_face[BACK]->getArrElem(2))
            {face = LEFT; done->pos = 2; done->c[0] = l; done->c[1] = u; done->c[2] = b; return true;}
            else if (l == m_face[LEFT]->getArrElem(2) &&
                     u == m_face[UP]->getArrElem(6) && u == m_face[UP]->getArrElem(7) &&
                     f == m_face[FRONT]->getArrElem(0) && f == m_face[FRONT]->getArrElem(1))
            {face = LEFT; done->pos = 0; done->c[0] = l; done->c[1] = u; done->c[2] = f; return true;}
            else if (l == m_face[LEFT]->getArrElem(6) &&
                     d == m_face[DOWN]->getArrElem(6) && d == m_face[DOWN]->getArrElem(7) &&
                     b == m_face[BACK]->getArrElem(7) && b == m_face[BACK]->getArrElem(8))
            {face = LEFT; done->pos = 3; done->c[0] = l; done->c[1] = d; done->c[2] = b; return true;}
            else if (l == m_face[LEFT]->getArrElem(8) &&
                     f == m_face[FRONT]->getArrElem(6) && f == m_face[FRONT]->getArrElem(7) &&
                     d == m_face[DOWN]->getArrElem(0) && d == m_face[DOWN]->getArrElem(1))
            {face = LEFT; done->pos = 1; done->c[0] = l; done->c[1] = d; done->c[2] = f; return true;}
        }
    }
    if (matches[2])
    {
        if (u == m_face[UP]->getArrElem(7) &&
            d == m_face[DOWN]->getArrElem(1) &&
            r == m_face[RIGHT]->getArrElem(3))
        {
            num++;
            if (f == m_face[FRONT]->getArrElem(0) &&
                l == m_face[LEFT]->getArrElem(1) && l == m_face[LEFT]->getArrElem(2) &&
                u == m_face[UP]->getArrElem(3) && u == m_face[UP]->getArrElem(6))
            {face = FRONT; done->pos = 0; done->c[0] = f; done->c[1] = l; done->c[2] = u; return true;}
            else if (f == m_face[FRONT]->getArrElem(2) &&
                     u == m_face[UP]->getArrElem(5) && u == m_face[UP]->getArrElem(8) &&
                     r == m_face[RIGHT]->getArrElem(0) && r == m_face[RIGHT]->getArrElem(1))
            {face = FRONT; done->pos = 1; done->c[0] = f; done->c[1] = r; done->c[2] = u; return true;}
            else if (f == m_face[FRONT]->getArrElem(6) &&
                     l == m_face[LEFT]->getArrElem(7) && l == m_face[LEFT]->getArrElem(8) &&
                     d == m_face[DOWN]->getArrElem(0) && d == m_face[DOWN]->getArrElem(3))
            {face = FRONT; done->pos = 2; done->c[0] = f; done->c[1] = l; done->c[2] = d; return true;}
            else if (f == m_face[FRONT]->getArrElem(8) &&
                     r == m_face[RIGHT]->getArrElem(6) && r == m_face[RIGHT]->getArrElem(7) &&
                     d == m_face[DOWN]->getArrElem(2) && d == m_face[DOWN]->getArrElem(5))
            {face = FRONT; done->pos = 3; done->c[0] = f; done->c[1] = r; done->c[2] = d; return true;}
        }
    }
    if (matches[3])
    {
        if (u == m_face[UP]->getArrElem(5) &&
            f == m_face[FRONT]->getArrElem(5) &&
            d == m_face[DOWN]->getArrElem(5))
        {
            num++;
            if (r == m_face[RIGHT]->getArrElem(0) &&
                u == m_face[UP]->getArrElem(7) && u == m_face[UP]->getArrElem(8) &&
                f == m_face[FRONT]->getArrElem(1) && f == m_face[FRONT]->getArrElem(2))
            {face = RIGHT; done->pos = 1; done->c[0] = r; done->c[1] = u; done->c[2] = f; return true;}
            else if (r == m_face[RIGHT]->getArrElem(2) &&
                     u == m_face[UP]->getArrElem(1) && u == m_face[UP]->getArrElem(2) &&
                     b == m_face[BACK]->getArrElem(0) && b == m_face[BACK]->getArrElem(1))
            {face = RIGHT; done->pos = 3; done->c[0] = r; done->c[1] = u; done->c[2] = b; return true;}
            else if (r == m_face[RIGHT]->getArrElem(6) &&
                     f == m_face[FRONT]->getArrElem(7) && f == m_face[FRONT]->getArrElem(8) &&
                     d == m_face[DOWN]->getArrElem(1) && d == m_face[DOWN]->getArrElem(2))
            {face = RIGHT; done->pos = 0; done->c[0] = r; done->c[1] = d; done->c[2] = f; return true;}
            else if (r == m_face[RIGHT]->getArrElem(8) &&
                     d == m_face[DOWN]->getArrElem(7) && d == m_face[DOWN]->getArrElem(8) &&
                     b == m_face[BACK]->getArrElem(6) && b == m_face[BACK]->getArrElem(7))
            {face = RIGHT; done->pos = 2; done->c[0] = r; done->c[1] = d; done->c[2] = b; return true;}
        }
    }
    if (matches[4])
    {
        if (l == m_face[LEFT]->getArrElem(3) &&
            u == m_face[UP]->getArrElem(1) &&
            d == m_face[DOWN]->getArrElem(7))
        {
            num++;
            if (b == m_face[BACK]->getArrElem(0) &&
                u == m_face[UP]->getArrElem(2) && u == m_face[UP]->getArrElem(5) &&
                r == m_face[RIGHT]->getArrElem(1) && r == m_face[RIGHT]->getArrElem(2))
            {face = BACK; done->pos = 3; done->c[0] = b; done->c[1] = r; done->c[2] = u; return true;}
            else if (b == m_face[BACK]->getArrElem(2) &&
                     l == m_face[LEFT]->getArrElem(0) && l == m_face[LEFT]->getArrElem(1) &&
                     u == m_face[UP]->getArrElem(0) && u == m_face[UP]->getArrElem(3))
            {face = BACK; done->pos = 2; done->c[0] = b; done->c[1] = l; done->c[2] = u; return true;}
            else if (b == m_face[BACK]->getArrElem(6) &&
                     r == m_face[RIGHT]->getArrElem(7) && r == m_face[RIGHT]->getArrElem(8) &&
                     d == m_face[DOWN]->getArrElem(5) && d == m_face[DOWN]->getArrElem(8))
            {face = BACK; done->pos = 1; done->c[0] = b; done->c[1] = r; done->c[2] = d; return true;}
            else if (b == m_face[BACK]->getArrElem(8) &&
                     l == m_face[LEFT]->getArrElem(6) && l == m_face[LEFT]->getArrElem(7) &&
                     d == m_face[DOWN]->getArrElem(3) && d == m_face[DOWN]->getArrElem(6))
            {face = BACK; done->pos = 0; done->c[0] = b; done->c[1] = l; done->c[2] = d; return true;}
        }
    }
    if (matches[5])
    {
        if (l == m_face[LEFT]->getArrElem(7) &&
            f == m_face[FRONT]->getArrElem(7) &&
            r == m_face[RIGHT]->getArrElem(7))
        {
            num++;
            if (d == m_face[DOWN]->getArrElem(0) &&
                l == m_face[LEFT]->getArrElem(5) && l == m_face[LEFT]->getArrElem(8) &&
                f == m_face[FRONT]->getArrElem(3) && f == m_face[FRONT]->getArrElem(6))
            {face = DOWN; done->pos = 0; done->c[0] = d; done->c[1] = l; done->c[2] = f; return true;}
            else if (d == m_face[DOWN]->getArrElem(2) &&
                     r == m_face[RIGHT]->getArrElem(3) && r == m_face[RIGHT]->getArrElem(6) &&
                     f == m_face[FRONT]->getArrElem(5) && f == m_face[FRONT]->getArrElem(8))
            {face = DOWN; done->pos = 1; done->c[0] = d; done->c[1] = r; done->c[2] = f; return true;}
            else if (d == m_face[DOWN]->getArrElem(6) &&
                     l == m_face[LEFT]->getArrElem(3) && l == m_face[LEFT]->getArrElem(6) &&
                     b == m_face[BACK]->getArrElem(5) && b == m_face[BACK]->getArrElem(8))
            {face = DOWN; done->pos = 2; done->c[0] = d; done->c[1] = l; done->c[2] = b; return true;}
            else if (d == m_face[DOWN]->getArrElem(8) &&
                     r == m_face[RIGHT]->getArrElem(5) && r == m_face[RIGHT]->getArrElem(8) &&
                     b == m_face[BACK]->getArrElem(3) && b == m_face[BACK]->getArrElem(6))
            {face = DOWN; done->pos = 3; done->c[0] = d; done->c[1] = r; done->c[2] = b; return true;}
        }
    }
    return false;
}

bool Cube::checkNewPair(Pair* done, int num)
{
    int st = 4;
    char l = m_face[LEFT]->getArrElem(st);
    char f = m_face[FRONT]->getArrElem(st);
    char r = m_face[RIGHT]->getArrElem(st);
    char b = m_face[BACK]->getArrElem(st);
    char d = m_face[DOWN]->getArrElem(st);
    
    for (int i = 1; i < m_stickersPerFace; i+=2)    //cross
        if (d != m_face[DOWN]->getArrElem(i)) return false;
    
    if (!(l == m_face[LEFT]->getArrElem(7) &&       //cross sides
          f == m_face[FRONT]->getArrElem(7) &&
          r == m_face[RIGHT]->getArrElem(7))) return false;
    
    int pairsComplete = 0, newPairPos = 0;
    
    if (d == m_face[DOWN]->getArrElem(0) &&
        l == m_face[LEFT]->getArrElem(5) && l == m_face[LEFT]->getArrElem(8) &&
        f == m_face[FRONT]->getArrElem(3) && f == m_face[FRONT]->getArrElem(6))
    {
        bool taken = false;
        pairsComplete++;
        for (int i = 0; i < num-1; i++)
        {
            if (done[i].pos == 0)
                taken = true;
        }
        if (!taken)
            newPairPos = 0;
    }
    if (d == m_face[DOWN]->getArrElem(2) &&
        r == m_face[RIGHT]->getArrElem(3) && r == m_face[RIGHT]->getArrElem(6) &&
        f == m_face[FRONT]->getArrElem(5) && f == m_face[FRONT]->getArrElem(8))
    {
        bool taken = false;
        pairsComplete++;
        for (int i = 0; i < num-1; i++)
        {
            if (done[i].pos == 1)
                taken = true;
        }
        if (!taken)
            newPairPos = 1;
    }
    if (d == m_face[DOWN]->getArrElem(6) &&
        l == m_face[LEFT]->getArrElem(3) && l == m_face[LEFT]->getArrElem(6) &&
        b == m_face[BACK]->getArrElem(5) && b == m_face[BACK]->getArrElem(8))
    {
        bool taken = false;
        pairsComplete++;
        for (int i = 0; i < num-1; i++)
        {
            if (done[i].pos == 2)
                taken = true;
        }
        if (!taken)
            newPairPos = 2;
    }
    if (d == m_face[DOWN]->getArrElem(8) &&
        r == m_face[RIGHT]->getArrElem(5) && r == m_face[RIGHT]->getArrElem(8) &&
        b == m_face[BACK]->getArrElem(3) && b == m_face[BACK]->getArrElem(6))
    {
        bool taken = false;
        pairsComplete++;
        for (int i = 0; i < num-1; i++)
        {
            if (done[i].pos == 3)
                taken = true;
        }
        if (!taken)
            newPairPos = 3;
    }
    
    if (pairsComplete >= num)
    {
        done[num-1].pos = newPairPos;
        return true;
    }
    return false;
}

bool Cube::checkTopCross()
{
    int st = 4;
    char u = m_face[UP]->getArrElem(st);
    
    for (int i = 1; i < m_stickersPerFace; i+=2)
        if (u != m_face[UP]->getArrElem(i)) return false;
    return true;
}

bool Cube::checkTopFace()
{
    int st = 0;
    char u = m_face[UP]->getArrElem(st);
    
    for (int i = 1; i < m_stickersPerFace; i++)
        if (u != m_face[UP]->getArrElem(i)) return false;
    return true;
}

bool Cube::checkTopSide()
{
    int st = 0;
    char l = m_face[LEFT]->getArrElem(st);
    char f = m_face[FRONT]->getArrElem(st);
    char r = m_face[RIGHT]->getArrElem(st);
    
    for (int i = 1; i < m_dim; i++)
        if (l != m_face[LEFT]->getArrElem(i) ||
            f != m_face[FRONT]->getArrElem(i) ||
            r != m_face[RIGHT]->getArrElem(i))
            return false;
    
    return true;
}


///////////////////////////////////////////////////////////////////////////
//  Solution-finding functions
///////////////////////////////////////////////////////////////////////////

vector<Move> Cube::findSolution(Stamp* step)
{
    vector<Move> moves;
    bool found = false;
    int randMax = (m_dim - 1) * 9;
    int curSize = 0;
    Pair* done = new Pair[4];
    
    if (m_dim == 2)
        while(moves.empty())
        {
            solver2x2(57, randMax, moves, found);
            step[0].attempts++;
        }
    else if (m_dim == 3)
    {
        step[0].t.start();
        while(moves.empty())
        {
            findCross(57, randMax, moves, found);    //finds the x-cross and rotates it to the bottom
            step[0].attempts++;
        }
        step[0].t.saveTimeStamp();
        step[0].moveCountAfter = static_cast<int>(moves.size());
        
        for (int i = 1; i < 4; i++)     //F2L
        {
            found = false;
            curSize = static_cast<int>(moves.size());
            step[i].t.start();
            while (moves.size() == curSize && !checkNewPair(done, i))
            {
                doNewPair(57, 15, moves, found, curSize, done, i);
                step[i].attempts++;
            }
            step[i].t.saveTimeStamp();
            step[i].moveCountAfter = static_cast<int>(moves.size());
        }
        
        curSize = static_cast<int>(moves.size());
        step[4].t.start();
        doLastPair(moves, curSize, done, step);
        
        curSize = static_cast<int>(moves.size());
        doLastLayer(moves, curSize, step);
        
    }
    return moves;
}

void Cube::solver2x2(int prev, int randMax, vector<Move>& moves, bool& found)
{
    int cur;
    Move m;
    
    if (checkSolved())
    {
        found = true;
        return;
    }
    
    do{                                 //finds new move to do
        cur = randInt(0,randMax-1);
    } while(cur / 3 == prev / 3);
    m.turn = intToTurn(cur);
    move(m.turn);                         //does the move
    prev = cur;
    
    
    moves.push_back(m);
    
    if (moves.size() < 14)          //put number of moves in max it will go to
        solver2x2(prev, randMax, moves, found);
    
    if (found)
        return;
    
    string recent = moves.back().turn, undo = recent;    //to undo move
    moves.pop_back();
    if (recent.size() == 1)
        undo = recent + "'";
    else if (recent[1] == '\'')
        undo = recent[0];
    
    move(undo);
    
}

void Cube::findCross(int prev, int randMax, vector<Move>& moves, bool& found)
{
    int cur;
    int face;
    Move m;
    
    if (checkCross(face))
    {
        found = true;
        Move m2;
        m2.counts = false;
        switch(face)
        {
            case UP: move("x2"); m2.turn = "x2"; moves.push_back(m2); break;
            case LEFT: move("z'"); m2.turn = "z'"; moves.push_back(m2); break;
            case FRONT: move("x'"); m2.turn = "x'"; moves.push_back(m2); break;
            case RIGHT: move("z"); m2.turn = "z"; moves.push_back(m2); break;
            case BACK: move("x"); m2.turn = "x"; moves.push_back(m2); break;
        }
        return;
    }
    
    
    do{                                 //finds new move to do
        cur = randInt(0,randMax-1);
    } while(cur / 3 == prev / 3);
    m.turn = intToTurn(cur);
    move(m.turn);                         //does the move
    prev = cur;
    
    moves.push_back(m);
    
    if (moves.size() < 6)          //depth of number of moves
        findCross(prev, randMax, moves, found);
    
    if (found)
        return;
    
    
    string recent = moves.back().turn, undo = recent;    //to undo move
    moves.pop_back();
    if (recent.size() == 1)
        undo = recent + "'";
    else if (recent[1] == '\'')
        undo = recent[0];
    
    move(undo);
}

void Cube::doNewPair(int prev, int randMax, vector<Move>& moves, bool& found, int movesIn, Pair* done, int num)
{
    int cur, min = 0;
    Move m;
    
    if (checkNewPair(done, num))
    {
        found = true;
        return;
    }
    
    do{                                 //finds new move to do
        cur = randInt(min,randMax-1);
    } while((cur / 3 == prev / 3) || !restrct(cur, done, num-1));
    m.turn = intToTurn(cur);
    move(m.turn);                         //does the move
    prev = cur;
    
    moves.push_back(m);
    
    if (moves.size() < movesIn + num + 5)          //depth of number of moves
        doNewPair(prev, randMax, moves, found, movesIn, done, num);
    
    if (found)
        return;
    
    
    string recent = moves.back().turn, undo = recent;    //to undo move
    moves.pop_back();
    if (recent.size() == 1)
        undo = recent + "'";
    else if (recent[1] == '\'')
        undo = recent[0];
    
    move(undo);
}

void Cube::doLastPair(std::vector<Move>& moves, int& movesIn, Pair* done, Stamp* step)
{
    if (checkNewPair(done, 4))
    {
        step[4].t.saveTimeStamp();
        step[4].moveCountAfter = static_cast<int>(moves.size());
        return;
    }
    for (int j = 0; j < 4; j++)
    {
        Move m1;
        m1.counts = false;
        switch(j)
        {
            case 0: break;
            case 1: m1.turn = "y"; break;
            case 2: m1.turn = "y'"; break;
            case 3: m1.turn = "y2"; break;
        }
        
        if (j != 0)
        {
            move(m1.turn);
            moves.push_back(m1);
            movesIn++;
        }
        
        for (int i = 0; i < 7; i++)
        {
            Move m2;
            switch(i)
            {
                case 0: break;
                case 1: m2.turn = "U"; break;
                case 2: m2.turn = "U2"; break;
                case 3: m2.turn = "U'"; break;
                case 4: m2.turn = "d"; break;
                case 5: m2.turn = "d2"; break;
                case 6: m2.turn = "d'"; break;
            }
            if (i != 0)
            {
                move(m2.turn);
                moves.push_back(m2);
                movesIn++;
            }
            
            if (doAlgSet(F2L, moves, movesIn, step+4, done))
            {
                step[4].t.saveTimeStamp();
                step[4].moveCountAfter = static_cast<int>(moves.size());
                return;
            }
            
            else if (i != 0)
            {
                string recent = moves.back().turn, undo = recent;    //to undo move
                moves.pop_back();
                if (recent.size() == 1)
                    undo = recent + "'";
                else if (recent[1] == '\'')
                    undo = recent[0];
                move(undo);
                movesIn--;
            }
        }
        
        if (j != 0)
        {
            string recent = moves.back().turn, undo = recent;    //to undo move
            moves.pop_back();
            if (recent.size() == 1)
                undo = recent + "'";
            else if (recent[1] == '\'')
                undo = recent[0];
            move(undo);
            movesIn--;
        }
    }
}

void Cube::doLastLayer(vector<Move>& moves, int& movesIn, Stamp* step)
{
    bool OLLcomp = false, PLLcomp = false;
    
    step[5].t.start();
    if (checkTopFace())
    {
        step[5].t.saveTimeStamp();
        step[5].moveCountAfter = static_cast<int>(moves.size());
        step[5].info = "OLL skip";
        OLLcomp = true;
    }
    for (int i = 0; i < 4 && !OLLcomp; i++)
    {
        Move m;
        switch(i)
        {
            case 0: break;
            case 1: m.turn = "U"; break;
            case 2: m.turn = "U2"; break;
            case 3: m.turn = "U'"; break;
        }
        if (i != 0)
        {
            move(m.turn);
            moves.push_back(m);
            movesIn++;
        }
        
        if (doAlgSet(OLL, moves, movesIn, step+5, nullptr))
        {
            OLLcomp = true;
            step[5].t.saveTimeStamp();
            step[5].moveCountAfter = static_cast<int>(moves.size());
        }
        
        else if (i != 0)
        {
            string recent = moves.back().turn, undo = recent;    //to undo move
            moves.pop_back();
            if (recent.size() == 1)
                undo = recent + "'";
            else if (recent[1] == '\'')
                undo = recent[0];
            move(undo);
            movesIn--;
        }
    }
    
    movesIn = static_cast<int>(moves.size());
    
    step[6].t.start();
    if (checkTopSide())
    {
        step[6].t.saveTimeStamp();
        step[6].moveCountAfter = static_cast<int>(moves.size());
        step[6].info = "PLL skip";
        PLLcomp = true;
    }
    for (int i = 0; i < 4 && !PLLcomp; i++)
    {
        Move m;
        switch(i)
        {
            case 0: break;
            case 1: m.turn = "U"; break;
            case 2: m.turn = "U2"; break;
            case 3: m.turn = "U'"; break;
        }
        if (i != 0)
        {
            move(m.turn);
            moves.push_back(m);
            movesIn++;
        }
        
        if (doAlgSet(PLL, moves, movesIn, step+6, nullptr))
        {
            PLLcomp = true;
            step[6].t.saveTimeStamp();
            step[6].moveCountAfter = static_cast<int>(moves.size());
        }
        
        else if (i != 0)
        {
            string recent = moves.back().turn, undo = recent;    //to undo move
            moves.pop_back();
            if (recent.size() == 1)
                undo = recent + "'";
            else if (recent[1] == '\'')
                undo = recent[0];
            move(undo);
            movesIn--;
        }
    }
    
    if (checkSolved())
        return;
    for (int i = 0; i < 3; i++)         //AUF
    {
        Move m;
        switch(i)
        {
            case 0: m.turn = "U"; break;
            case 1: m.turn = "U2"; break;
            case 2: m.turn = "U'"; break;
        }
        
        move(m.turn);
        moves.push_back(m);
        movesIn++;
        
        if (checkSolved())
            return;
        
        string recent = moves.back().turn, undo = recent;    //to undo move
        moves.pop_back();
        if (recent.size() == 1)
            undo = recent + "'";
        else if (recent[1] == '\'')
            undo = recent[0];
        move(undo);
    }
}

bool Cube::doAlgSet(string filename, vector<Move>& moves, int movesIn, Stamp* step, Pair* done)
{
    ifstream infile(filename);
    if (!infile)
        return false;
    
    string algorithm, turn;
    int cases = 0;
    while(getline(infile, algorithm))
    {
        cases++;
        step[0].attempts++;
        for (int i = 0; i < algorithm.size(); i++)
        {
            if (!(algorithm[i] == ' '))        //if not a space yet
                turn += algorithm[i];         //goes into this one turn
            else if (!turn.empty())
            {
                Move m;
                m.turn = turn;
                move(m.turn);
                for (int j = 0; j < m.turn.size(); j++)
                    if (m.turn[j] == 'x' || m.turn[j] == 'y' || m.turn[j] == 'z')
                        m.counts = false;
                moves.push_back(m);
                turn = "";
            }
        }
        if (!turn.empty())      //if you have a turn going on at the very end w/o space
        {
            Move m;
            m.turn = turn;
            move(m.turn);
            for (int j = 0; j < m.turn.size(); j++)
                if (m.turn[j] == 'x' || m.turn[j] == 'y' || m.turn[j] == 'z')
                    m.counts = false;
            moves.push_back(m);
            turn = "";
        }
        
        if (filename == F2L && checkNewPair(done, 4))
            return true;
        
        else if (filename == OLL && checkTopFace())
        {
            step[0].info = "OLL ";
            step[0].info += OLLindex(cases);
            return true;
        }
        
        else if (filename == PLL && checkTopSide())
        {
            step[0].info = PLLindex(cases);
            if (step[0].info != "PLL skip")
                step[0].info += " perm";
            return true;
        }
        
        else
        {
            while(moves.size() != movesIn)
            {
                string recent = moves.back().turn, undo = recent;    //to undo move
                moves.pop_back();
                if (recent.size() == 1)
                    undo = recent + "'";
                else if (recent[1] == '\'')
                    undo = recent[0];
                move(undo);
            }
        }
    }
    return false;
}
