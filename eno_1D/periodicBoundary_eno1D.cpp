#include "eno1D.h"
#include <iostream>
double firstOrder_p(Point1D *p1, Func1D *f1, int i, int sign) // Rreturn first order
{
     if (sign == -1)
     {
          return (f1->f_old[(i + p1->nx) % p1->nx] - f1->f_old[(i - 1 + p1->nx) % p1->nx]) / p1->dx;
     }
     else if (sign == 1)
     {
          return (f1->f_old[(i + 1 + p1->nx) % p1->nx] - f1->f_old[(i + p1->nx) % p1->nx]) / p1->dx;
     }
     else
     {
          printf("Error: Invalid value for 'sign'\n");
          exit(1);
     }
}
double secondOrder_p(Point1D *p1, Func1D *f1, int i) // Rreturn second order
{
     return (f1->f_old[(i + 1 + p1->nx) % p1->nx] - 2 * f1->f_old[(i + p1->nx) % p1->nx] + f1->f_old[(i - 1 + p1->nx) % p1->nx]) / (2 * p1->dx * p1->dx);
}
double thirdOrder_p(Point1D *p1, Func1D *f1, int i, int sign) // Rreturn third order
{
     if (sign == -1)
     {
          return (f1->f_old[(i + 1 + p1->nx) % p1->nx] - 3 * f1->f_old[(i + p1->nx) % p1->nx] + 3 * f1->f_old[(i - 1 + p1->nx) % p1->nx] - f1->f_old[(i - 2 + p1->nx) % p1->nx]) / (3 * p1->dx * p1->dx * p1->dx);
     }
     else if (sign == 1)
     {
          return (f1->f_old[(i + 2 + p1->nx) % p1->nx] - 3 * f1->f_old[(i + 1 + p1->nx) % p1->nx] + 3 * f1->f_old[(i + p1->nx) % p1->nx] - f1->f_old[(i - 1 + p1->nx) % p1->nx]) / (3 * p1->dx * p1->dx * p1->dx);
     }
     else
     {
          printf("Error: Invalid value for 'sign'\n");
          exit(1);
     }
}
double c2_p(Point1D *p1, Func1D *f1, int k)
{
     double a1 = secondOrder_p(p1, f1, k);
     double a2 = secondOrder_p(p1, f1, k + 1);
     if (std::abs(a1) <= std::abs(a2))
     {
          return a1;
     }
     else
     {
          return a2;
     }
}
double c3_p(Point1D *p1, Func1D *f1, int k)
{
     int k1;
     double a1 = secondOrder_p(p1, f1, k);
     double a2 = secondOrder_p(p1, f1, k + 1);
     if (std::abs(a1) <= std::abs(a2))
     {
          k1 = k - 1;
     }
     else
     {
          k1 = k;
     }
     double b1 = thirdOrder_p(p1, f1, k1, 1);
     double b2 = thirdOrder_p(p1, f1, k1 + 1, 1);
     if (std::abs(b1) <= std::abs(b2))
     {
          return b1;
     }
     else
     {
          return b2;
     }
}
void periodicBoundary(Point1D *p1, Func1D *f1, Velocity1D *v1, Timestamp *t1) // Calucurate vicinity of boundary in periodic condition
{
     int k;
     double q1, q2, q3;
     for (int i = 0; i < 3; i++)
     {
          if (v1->u > 0)
          {
               k = i - 1;
          }
          else
          {
               k = i;
          }
          q1 = firstOrder_p(p1, f1, k, 1);
          q2 = c2_p(p1, f1, k) * (2 * (i - k) - 1) * p1->dx;
          if (std::abs(secondOrder_p(p1, f1, k)) <= std::abs(secondOrder_p(p1, f1, k + 1)))
          {
               q3 = c3_p(p1, f1, k) * (3 * (i - k + 1) * (i - k + 1) - 6 * (i - k + 1) + 2) * p1->dx * p1->dx;
          }
          else
          {
               q3 = c3_p(p1, f1, k) * (3 * (i - k) * (i - k) - 6 * (i - k) + 2) * p1->dx * p1->dx;
          }
          f1->f[i] = f1->f_old[i] - t1->dt * v1->u * (q1 + q2 + q3);
     }
     for (int i = p1->nx - 3; i < p1->nx; i++)
     {
          if (v1->u > 0)
          {
               k = i - 1;
          }
          else
          {
               k = i;
          }
          q1 = firstOrder_p(p1, f1, k, 1);
          q2 = c2_p(p1, f1, k) * (2 * (i - k) - 1) * p1->dx;
          if (std::abs(secondOrder_p(p1, f1, k)) <= std::abs(secondOrder_p(p1, f1, k + 1)))
          {
               q3 = c3_p(p1, f1, k) * (3 * (i - k + 1) * (i - k + 1) - 6 * (i - k + 1) + 2) * p1->dx * p1->dx;
          }
          else
          {
               q3 = c3_p(p1, f1, k) * (3 * (i - k) * (i - k) - 6 * (i - k) + 2) * p1->dx * p1->dx;
          }
          f1->f[i] = f1->f_old[i] - t1->dt * v1->u * (q1 + q2 + q3);
     }
}