#include "utilities.h"
#include "face.h"

Face::Face(int dim, int ID)
{
    m_arr = new char[dim * dim];
    m_id = ID;
    m_d = dim;
    
    char insChar;
    switch (ID)
    {
        case UP: insChar = 'W'; break;
        case LEFT: insChar = 'O'; break;
        case FRONT: insChar = 'G'; break;
        case RIGHT: insChar = 'R'; break;
        case BACK: insChar = 'B'; break;
        case DOWN: insChar = 'Y'; break;
        default: insChar = ' ';
    }
    
    for (int i = 0; i < (dim*dim); i++)
        m_arr[i] = insChar;
};

Face::~Face()
{
    delete [] m_arr;
}

char Face::getArrElem(int i) const
{
    return m_arr[i];
}

void Face::changeArrElem(int i, char c)
{
    m_arr[i] = c;
}

void Face::rotate(int dir)
{
    int size = m_d * m_d;
    char temp[size];
    for (int i = 0; i < size; i++)
        temp[i] = m_arr[i];
    
    int a = m_d, k = 0;
    
    if (dir == CW)
        while (k < size)
        {
            for (int j = a - 1; j < size; j += m_d)
            {
                m_arr[j] = temp[k];
                k++;
            }
            a--;
        }
    else if (dir == CCW)
        while (k < size)
        {
            for (int j = a - 1; j < size; j += m_d)
            {
                m_arr[k] = temp[j];
                k++;
            }
            a--;
        }
}
