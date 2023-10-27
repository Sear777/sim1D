#include "weno1D.h"
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
void periodicBoundary(Point1D *p1, Func1D *f1, Velocity1D *v1, Timestamp *t1) // Calucurate vicinity of boundary in periodic condition
{
     double fx1, fx2, fx3;
     double w1, w2, w3;
     double s1, s2, s3;
     double a1, a2, a3;
     double eps = pow(10, -6);
     for (int i = 0; i < 3; i++)
     {
          fx1 = firstOrder_p(p1, f1, i - 2, -1) / 3 - 7 * firstOrder_p(p1, f1, i - 1, -1) / 6 + 11 * firstOrder_p(p1, f1, i, -1) / 6;
          fx2 = -firstOrder_p(p1, f1, i - 1, -1) / 6 + 5 * firstOrder_p(p1, f1, i, -1) / 6 + firstOrder_p(p1, f1, i + 1, -1) / 3;
          fx3 = firstOrder_p(p1, f1, i, -1) / 3 + 5 * firstOrder_p(p1, f1, i + 1, -1) / 6 - firstOrder_p(p1, f1, i + 2, -1) / 6;
          s1 = 13 * pow((firstOrder_p(p1, f1, i - 2, -1) - 2 * firstOrder_p(p1, f1, i - 1, -1) + firstOrder_p(p1, f1, i, -1)), 2.0) / 12 + pow((firstOrder_p(p1, f1, i - 2, -1) - 4 * firstOrder_p(p1, f1, i - 1, -1) + 3 * firstOrder_p(p1, f1, i, -1)), 2.0) / 4;
          s2 = 13 * pow((firstOrder_p(p1, f1, i - 1, -1) - 2 * firstOrder_p(p1, f1, i, -1) + firstOrder_p(p1, f1, i + 1, -1)), 2.0) / 12 + pow((firstOrder_p(p1, f1, i - 1, -1) - firstOrder_p(p1, f1, i + 1, -1)), 2.0) / 4;
          s3 = 13 * pow((firstOrder_p(p1, f1, i, -1) - 2 * firstOrder_p(p1, f1, i + 1, -1) + firstOrder_p(p1, f1, i + 2, -1)), 2.0) / 12 + pow(3 * (firstOrder_p(p1, f1, i, -1) - 4 * firstOrder_p(p1, f1, i + 1, -1) + firstOrder_p(p1, f1, i + 2, -1)), 2.0) / 4;
          a1 = 0.1 / pow((s1 + eps), 2.0);
          a2 = 0.6 / pow((s2 + eps), 2.0);
          a3 = 0.3 / pow((s3 + eps), 2.0);
          w1 = a1 / (a1 + a2 + a3);
          w2 = a2 / (a1 + a2 + a3);
          w3 = a3 / (a1 + a2 + a3);
          f1->f[i] = f1->f_old[i] - t1->dt * v1->u * (w1 * fx1 + w2 * fx2 + w3 * fx3);
     }
     for (int i = p1->nx - 3; i < p1->nx; i++)
     {
          fx1 = firstOrder_p(p1, f1, i - 2, -1) / 3 - 7 * firstOrder_p(p1, f1, i - 1, -1) / 6 + 11 * firstOrder_p(p1, f1, i, -1) / 6;
          fx2 = -firstOrder_p(p1, f1, i - 1, -1) / 6 + 5 * firstOrder_p(p1, f1, i, -1) / 6 + firstOrder_p(p1, f1, i + 1, -1) / 3;
          fx3 = firstOrder_p(p1, f1, i, -1) / 3 + 5 * firstOrder_p(p1, f1, i + 1, -1) / 6 - firstOrder_p(p1, f1, i + 2, -1) / 6;
          s1 = 13 * pow((firstOrder_p(p1, f1, i - 2, -1) - 2 * firstOrder_p(p1, f1, i - 1, -1) + firstOrder_p(p1, f1, i, -1)), 2.0) / 12 + pow((firstOrder_p(p1, f1, i - 2, -1) - 4 * firstOrder_p(p1, f1, i - 1, -1) + 3 * firstOrder_p(p1, f1, i, -1)), 2.0) / 4;
          s2 = 13 * pow((firstOrder_p(p1, f1, i - 1, -1) - 2 * firstOrder_p(p1, f1, i, -1) + firstOrder_p(p1, f1, i + 1, -1)), 2.0) / 12 + pow((firstOrder_p(p1, f1, i - 1, -1) - firstOrder_p(p1, f1, i + 1, -1)), 2.0) / 4;
          s3 = 13 * pow((firstOrder_p(p1, f1, i, -1) - 2 * firstOrder_p(p1, f1, i + 1, -1) + firstOrder_p(p1, f1, i + 2, -1)), 2.0) / 12 + pow(3 * (firstOrder_p(p1, f1, i, -1) - 4 * firstOrder_p(p1, f1, i + 1, -1) + firstOrder_p(p1, f1, i + 2, -1)), 2.0) / 4;
          a1 = 0.1 / pow((s1 + eps), 2.0);
          a2 = 0.6 / pow((s2 + eps), 2.0);
          a3 = 0.3 / pow((s3 + eps), 2.0);
          w1 = a1 / (a1 + a2 + a3);
          w2 = a2 / (a1 + a2 + a3);
          w3 = a3 / (a1 + a2 + a3);
          f1->f[i] = f1->f_old[i] - t1->dt * v1->u * (w1 * fx1 + w2 * fx2 + w3 * fx3);
     }
}