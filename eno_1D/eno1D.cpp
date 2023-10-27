#include "eno1D.h"
#include "iostream"
double firstOrder(Point1D *p1, Func1D *f1, int i, int sign) // Rreturn first order
{
     if (sign == -1)
     {
          return (f1->f_old[i] - f1->f_old[i - 1]) / p1->dx;
     }
     else if (sign == 1)
     {
          return (f1->f_old[i + 1] - f1->f_old[i]) / p1->dx;
     }
     else
     {
          printf("Error: Invalid value for 'sign'\n");
          exit(1);
     }
}
double secondOrder(Point1D *p1, Func1D *f1, int i) // Rreturn second order
{
     return (f1->f_old[i + 1] - 2 * f1->f_old[i] + f1->f_old[i - 1]) / (2 * p1->dx * p1->dx);
}
double thirdOrder(Point1D *p1, Func1D *f1, int i, int sign) // Rreturn third order
{
     if (sign == -1)
     {
          return (f1->f_old[i + 1] - 3 * f1->f_old[i] + 3 * f1->f_old[i - 1] - f1->f_old[i - 2]) / (3 * p1->dx * p1->dx * p1->dx);
     }
     else if (sign == 1)
     {
          return (f1->f_old[i + 2] - 3 * f1->f_old[i + 1] + 3 * f1->f_old[i] - f1->f_old[i - 1]) / (3 * p1->dx * p1->dx * p1->dx);
     }
     else
     {
          printf("Error: Invalid value for 'sign'\n");
          exit(1);
     }
}
double c2(Point1D *p1, Func1D *f1, int k)
{
     double a1 = secondOrder(p1, f1, k);
     double a2 = secondOrder(p1, f1, k + 1);
     if (std::abs(a1) <= std::abs(a2))
     {
          return a1;
     }
     else
     {
          return a2;
     }
}
double c3(Point1D *p1, Func1D *f1, int k)
{
     int k1;
     double a1 = secondOrder(p1, f1, k);
     double a2 = secondOrder(p1, f1, k + 1);
     if (std::abs(a1) <= std::abs(a2))
     {
          k1 = k - 1;
     }
     else
     {
          k1 = k;
     }
     double b1 = thirdOrder(p1, f1, k1, 1);
     double b2 = thirdOrder(p1, f1, k1 + 1, 1);
     if (std::abs(b1) <= std::abs(b2))
     {
          return b1;
     }
     else
     {
          return b2;
     }
}

void eno1D(Point1D *p1, Func1D *f1, Velocity1D *v1, Timestamp *t1)
{
     int k;
     double q1, q2, q3;
     copy(f1->f.begin(), f1->f.end(), f1->f_old.begin());
     for (int i = 3; i < p1->nx - 3; i++)
     {
          if (v1->u > 0)
          {
               k = i - 1;
          }
          else
          {
               k = i;
          }
          q1 = firstOrder(p1, f1, k, 1);
          q2 = c2(p1, f1, k) * (2 * (i - k) - 1) * p1->dx;
          if (std::abs(secondOrder(p1, f1, k)) <= std::abs(secondOrder(p1, f1, k + 1)))
          {
               q3 = c3(p1, f1, k) * (3 * (i - k + 1) * (i - k + 1) - 6 * (i - k + 1) + 2) * p1->dx * p1->dx;
          }
          else
          {
               q3 = c3(p1, f1, k) * (3 * (i - k) * (i - k) - 6 * (i - k) + 2) * p1->dx * p1->dx;
          }
          f1->f[i] = f1->f_old[i] - t1->dt * v1->u * (q1 + q2 + q3);
     }
     periodicBoundary(p1, f1, v1, t1);
}