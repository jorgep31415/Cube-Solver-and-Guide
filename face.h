#ifndef face_h
#define face_h

class Face
{
public:
    Face(int dim, int ID);
    ~Face();
    
    //Accessors
    char getArrElem(int i) const;
    
    //Mutators
    void changeArrElem(int i, char c);
    void rotate(int dir);
    
    
private:
    char* m_arr;
    int m_id;
    int m_d;
};

#endif /* face_h */
