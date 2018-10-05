#ifndef cube_h
#define cube_h

#include "utilities.h"
#include "face.h"
#include <string>

class Cube
{
public:
    Cube(int dim);
    ~Cube();
    
    //Accessors
    int dim() const;
    void display() const;
    
    //Mutators
    bool move(std::string s);
    void scramble(int show);
    void buildYourCube();
    std::vector<Move> findSolution(Stamp* step);
    
    //Solution checks
    bool checkSolved();
    bool checkFace();
    bool checkSide();
    bool checkDomino();
    bool checkCross(int& face);
    bool checkXCross(int& num, int& face, Pair* done);
    bool checkNewPair(Pair* done, int num);
    bool checkTopCross();
    bool checkTopFace();
    bool checkTopSide();
    
private:
    int m_dim;
    int m_stickersPerFace;
    Face* m_face[FACES];
    
    void F(int l);
    void B(int l);
    void L(int l);
    void R(int l);
    void D(int l);
    void U(int l);
    void M();
    void E();
    void S();
    
    bool isValidState(std::string stickers) const;
    bool centers(std::string stickers) const;
    bool centerType(int typeOffset, int* counters, std::string stickers) const;
    bool edges(std::string stickers) const;
    bool edgeType(int* off, int* counters, std::string stickers) const;
    bool corners(std::string stickers) const;
    
    void solver2x2(int prev, int randMax, std::vector<Move>& moves, bool& found);
    void findCross(int prev, int randMax, std::vector<Move>& moves, bool& found);
    void doNewPair(int prev, int randMax, std::vector<Move>& moves, bool& found, int movesIn, Pair* done, int num);
    void doLastPair(std::vector<Move>& moves, int& movesIn, Pair* done, Stamp* step);
    void doLastLayer(std::vector<Move>& moves, int& movesIn, Stamp* step);
    bool doAlgSet(std::string filename, std::vector<Move>& moves, int movesIn, Stamp* step, Pair* done);
    
    bool searchKocDomino(int top, int bottom, char sig);
};


#endif /* cube_h */
