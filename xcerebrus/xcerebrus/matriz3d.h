#ifndef MATRIZ3D_H
#define MATRIZ3D_H
#include <vector>


class Matriz3d
{
    public:
        Matriz3d(int dimx, int dimy, int dimz);
        virtual ~Matriz3d();
        double getItem(int, int, int);
        void setItem(int, int, int,int);
        int dimx, dimy, dimz;
        std::vector<double> data;
    protected:
    private:


};

#endif // MATRIZ3D_H
