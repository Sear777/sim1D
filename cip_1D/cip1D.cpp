#include "cip1D.h"
void periodicBoundary(Point1D *p1, Func1D *f1, Velocity1D *v1, Timestamp *t1) // Caluculate vicinity of boundary
{
     double a, b, xi;
     xi = -v1->u * t1->dt;
     if (int(copysign(1.0, v1->u)) == 1) // case i_m = i - 1
     {
          // Caluculate x[0]
          a = (f1->f_x_old[p1->nx - 1] + f1->f_x_old[0]) / (pow(p1->dx, 2)) - 2 * (f1->f_old[0] - f1->f_old[p1->nx - 1]) / (pow(p1->dx, 3) * copysign(1.0, v1->u));
          b = (f1->f_x_old[p1->nx - 1] + 2 * f1->f_x_old[0]) * copysign(1.0, v1->u) / p1->dx + 3 * (f1->f_old[p1->nx - 1] - f1->f_old[0]) / pow(p1->dx, 2);
          f1->f[0] = a * pow(xi, 3) + b * pow(xi, 2) + f1->f_x_old[0] * xi + f1->f_old[0];
          f1->f_x[0] = 3 * a * pow(xi, 2) + 2 * b * xi + f1->f_x_old[0];
          // Caluculate x[p1->nx-1]
          a = (f1->f_x_old[p1->nx - 2] + f1->f_x_old[p1->nx - 1]) / (pow(p1->dx, 2)) - 2 * (f1->f_old[p1->nx - 1] - f1->f_old[p1->nx - 2]) / (pow(p1->dx, 3) * copysign(1.0, v1->u));
          b = (f1->f_x_old[p1->nx - 2] + 2 * f1->f_x_old[p1->nx - 1]) * copysign(1.0, v1->u) / p1->dx + 3 * (f1->f_old[p1->nx - 2] - f1->f_old[p1->nx - 1]) / pow(p1->dx, 2);
          f1->f[p1->nx - 1] = a * pow(xi, 3) + b * pow(xi, 2) + f1->f_x_old[p1->nx - 1] * xi + f1->f_old[p1->nx - 1];
          f1->f_x[p1->nx - 1] = 3 * a * pow(xi, 2) + 2 * b * xi + f1->f_x_old[p1->nx - 1];
     }
     else // // case i_m = i + 1
     {
          // Caluculate x[0]
          a = (f1->f_x_old[1] + f1->f_x_old[0]) / (pow(p1->dx, 2)) - 2 * (f1->f_old[0] - f1->f_old[1]) / (pow(p1->dx, 3) * copysign(1.0, v1->u));
          b = (f1->f_x_old[1] + 2 * f1->f_x_old[0]) * copysign(1.0, v1->u) / p1->dx + 3 * (f1->f_old[1] - f1->f_old[0]) / pow(p1->dx, 2);
          f1->f[p1->nx - 1] = a * pow(xi, 3) + b * pow(xi, 2) + f1->f_x_old[p1->nx - 1] * xi + f1->f_old[p1->nx - 1];
          f1->f_x[p1->nx - 1] = 3 * a * pow(xi, 2) + 2 * b * xi + f1->f_x_old[p1->nx - 1];
          // Caluculate x[p1->nx-1]
          a = (f1->f_x_old[0] + f1->f_x_old[p1->nx - 1]) / (pow(p1->dx, 2)) - 2 * (f1->f_old[p1->nx - 1] - f1->f_old[0]) / (pow(p1->dx, 3) * copysign(1.0, v1->u));
          b = (f1->f_x_old[0] + 2 * f1->f_x_old[p1->nx - 1]) * copysign(1.0, v1->u) / p1->dx + 3 * (f1->f_old[0] - f1->f_old[p1->nx - 1]) / pow(p1->dx, 2);
          f1->f[p1->nx - 1] = a * pow(xi, 3) + b * pow(xi, 2) + f1->f_x_old[p1->nx - 1] * xi + f1->f_old[p1->nx - 1];
          f1->f_x[p1->nx - 1] = 3 * a * pow(xi, 2) + 2 * b * xi + f1->f_x_old[p1->nx - 1];
     }
}
void cip1D(Point1D *p1, Func1D *f1, Velocity1D *v1, Timestamp *t1)
{
     int i_m;
     double a, b, xi;
     xi = -v1->u * t1->dt;
     copy(f1->f.begin(), f1->f.end(), f1->f_old.begin());
     copy(f1->f_x.begin(), f1->f_x.end(), f1->f_x_old.begin());

     for (int i = 1; i < p1->nx - 1; i++)
     {
          i_m = i - int(copysign(1.0, v1->u));
          a = (f1->f_x_old[i_m] + f1->f_x_old[i]) / (pow(p1->dx, 2)) - 2 * (f1->f_old[i] - f1->f_old[i_m]) / (pow(p1->dx, 3) * copysign(1.0, v1->u));
          b = (f1->f_x_old[i_m] + 2 * f1->f_x_old[i]) * copysign(1.0, v1->u) / p1->dx + 3 * (f1->f_old[i_m] - f1->f_old[i]) / pow(p1->dx, 2);
          f1->f[i] = a * pow(xi, 3) + b * pow(xi, 2) + f1->f_x_old[i] * xi + f1->f_old[i];
          f1->f_x[i] = 3 * a * pow(xi, 2) + 2 * b * xi + f1->f_x_old[i];
     }
     periodicBoundary(p1, f1, v1, t1);
}