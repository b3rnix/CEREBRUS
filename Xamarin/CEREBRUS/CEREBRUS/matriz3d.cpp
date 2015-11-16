#include "matriz3d.h"
#include <vector>

Matriz3d::Matriz3d(int dimx, int dimy, int dimz)
{
    int dimVector = dimx * dimy * dimz;
    this->dimx = dimx;
    this->dimy = dimy;
    this->dimz = dimz;
    this->data = std::vector<double>(dimVector);
    for (unsigned int i = 0; i < this->data.size(); i++)
        this->data[i] = 0;

}

Matriz3d::~Matriz3d()
{
    //delete this->data;
}

double Matriz3d::getItem(int x, int y, int z){
        int offset = z * (dimx * dimy) + y * dimx + x;
        return data[offset];
}


void Matriz3d::setItem(int x, int y, int z, int val){
        int offset = z * (dimx * dimy) + y * dimx + x;
        data[offset] = val;
}
