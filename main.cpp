#include <iostream>
#include <fstream>
#include <sstream>

#include <math.h>
#include "Matriz3d.h"



using namespace std;

double CM = 1E+8;

int main()
{
    Matriz3d cerebro = Matriz3d(181,217,181);
    ifstream file ( "Cerebro.csv" ); // declare file stream: http://www.cplusplus.com/reference/iostream/ifstream/
    string value;
    while ( file.good() )
    {
         getline ( file, value, ',' ); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
         int x = atoi(value.c_str());

         getline ( file, value, ',' ); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
         int y = atoi(value.c_str());

         getline ( file, value, ',' ); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
         int z = atoi(value.c_str());

         getline ( file, value ); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
         int s = atoi(value.c_str());

         cerebro.setItem(x-1,y-1,z-1,s);

         //printf("<%u,%u,%u,%u>\n", x,y,z,s);
    }

for (int t = 1; t < 10000; t++){
    for (int x = 1; x < 181; x++){
      for (int y = 1; y < 217; y++){
        for (int z = 1; z < 181; z++){
          float val = cerebro.getItem(x,y,z);
          cerebro.setItem(x,y,z) =
            (D(cerebro.getItem(x+1,y,z)) - D(cerebro.getItem(x-1,y,z))  * (cerebro.getItem(x+1,y,z) - cerebro.getItem(x-1,y,z)) + D(val) * (cerebro.getItem(x+1,y,z) - 2* cerebro.getItem(x,y,z) +cerebro.getItem(x-1,y,z))) / (dx * dx)
            +
            (D(cerebro.getItem(x,y+1,z)) - D(cerebro.getItem(x,y-1,z))  * (cerebro.getItem(x,y+1,z) - cerebro.getItem(x,y-1,z)) + D(val) * (cerebro.getItem(x,y+1,z) - 2* cerebro.getItem(x,y,z) +cerebro.getItem(x,y-1,z))) / (dy * dy)
            +
            (D(cerebro.getItem(x,y,z+1)) - D(cerebro.getItem(x,y,z-1))  * (cerebro.getItem(x,y,z+1) - cerebro.getItem(x,y,z+1)) + D(val) * (cerebro.getItem(x,y,z+1) - 2* cerebro.getItem(x,y,z) +cerebro.getItem(x,y,z-1))) / (dz * dz)
            +
            RO(val) * val * log(CM / val) - R(val);

        }
      }
    }}


    return 0;


}
int calcular(){

    return 0;

}

double RO(double value){
    if ( value >= 55 && value < 255)
        return 0.107;
    else
        return 0;
}
double D(double value){
    if ( value >= 110 && value < 255)
        return 0.255;
    else if (value <= 110 && value >= 55)
        return 0.051;
    else
        return 0;
}
double R(double C){
    double alpha = 0.036;
    double beta = 0.0036;
    double dose = 1.8;
    double s = exp(-(alpha * dose) -(beta * dose*dose));
    return (1-s) * C * log(CM / C);
}
