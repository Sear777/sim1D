#include "transf.h"
void transf(std::vector<double> *f, std::vector<double> *fx, int size)
{
     for (int i = 0; i < size; i++)
     {
          (*f)[i] = tan(0.9999*M_PI * ((*f)[i] - 0.5));
          (*fx)[i] = tan(0.9999*M_PI * ((*fx)[i] - 0.5));
     }
}
void untransf(std::vector<double> *f, std::vector<double> *fx, int size)
{
     for (int i = 0; i < size; i++)
     {
          (*f)[i] = atan((*f)[i])/(M_PI*0.9999)+0.5;
          (*fx)[i] = atan((*fx)[i])/(M_PI*0.9999)+0.5;
     }
}