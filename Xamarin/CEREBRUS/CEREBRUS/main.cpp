#include <iostream>
#include <fstream>
#include <sstream>

#include <math.h>
#include "Matriz3d.h"



using namespace std;

double CM = 1E+8;

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

int main()
{
    Matriz3d cerebro = Matriz3d(181,217,181);
    Matriz3d difusion = Matriz3d(181,217,181);

    ifstream file ( "Cerebro.csv" ); // declare file stream: http://www.cplusplus.com/reference/iostream/ifstream/
    string value;
    int limite = 181 * 217 * 181;
    //while ( file.good() )
getline ( file, value, ',' );
getline ( file, value, ',' );
getline ( file, value, ',' );
getline ( file, value, ',' );

    for (int i = 1; i < limite; i++)
    {



        //printf ("aa\n");
         getline ( file, value, ',' ); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
         int x = atoi(value.c_str());

         getline ( file, value, ',' ); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
         int y = atoi(value.c_str());

         getline ( file, value, ',' ); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
         int z = atoi(value.c_str());

         getline ( file, value ); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
         int s = atoi(value.c_str());

         difusion.setItem(x-1,y-1,z-1,s);
           //printf ("bb\n");
    }

printf ("Salio\n");

// Inicializacion Cerebro
for (int x = 1; x < 180; x++)
  for (int y = 1; y < 216; y++)
    for (int z = 1; z < 180; z++){
      // Inserción del tumor, 3x3x3mm, al centro
      if (89 <= x && x <= 91 && 72 <= y && y <= 74 && 89 <= z && z <= 91)
        cerebro.setItem(x,y,z,1E8);
      else
        cerebro.setItem(x,y,z,0);

    }

float dx = 1;float dy=1;float dz=1;
float dt0 = ((0.4) * (dx*dx)) / 0.255;
float dt1 = ((0.4) * (dx*dx)) / 0.051;
float dt = min(dt0, dt1);

for (int t = 1; t < 10; t++){
    for (int x = 1; x < 180; x++){
      for (int y = 1; y < 216; y++){
        for (int z = 1; z < 180; z++){
          float val = difusion.getItem(x,y,z);
          cerebro.setItem(x,y,z,
            (D(difusion.getItem(x+1,y,z)) - D(difusion.getItem(x-1,y,z))  * (cerebro.getItem(x+1,y,z) - cerebro.getItem(x-1,y,z)) + D(val) * (cerebro.getItem(x+1,y,z) - 2* cerebro.getItem(x,y,z) +cerebro.getItem(x-1,y,z))) / (dx * dx)
            +
            (D(difusion.getItem(x,y+1,z)) - D(difusion.getItem(x,y-1,z))  * (cerebro.getItem(x,y+1,z) - cerebro.getItem(x,y-1,z)) + D(val) * (cerebro.getItem(x,y+1,z) - 2* cerebro.getItem(x,y,z) +cerebro.getItem(x,y-1,z))) / (dy * dy)
            +
            (D(difusion.getItem(x,y,z+1)) - D(difusion.getItem(x,y,z-1))  * (cerebro.getItem(x,y,z+1) - cerebro.getItem(x,y,z+1)) + D(val) * (cerebro.getItem(x,y,z+1) - 2* cerebro.getItem(x,y,z) +cerebro.getItem(x,y,z-1))) / (dz * dz)
            +
            RO(cerebro.getItem(x,y,z)) * cerebro.getItem(x,y,z) * log(CM / val) - R(cerebro.getItem(x,y,z)));

        }
      }
    }}
    for (int x = 1; x < 180; x++)
      for (int y = 1; y < 216; y++)
        for (int z = 1; z < 180; z++)
                printf("<%u,%u,%u,%f>\n", x,y,z,cerebro.getItem(x,y,z));

    return 0;
}
