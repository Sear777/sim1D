#include "udm1D.h"
void periodicBoundary(Point1D *p1, Func1D *f1, Velocity1D *v1, Timestamp *t1) // Caluculate vicinity of boundary
{
     double kappa = v1->u * t1->dt / p1->dx;
     if (v1->u > 0)
     {
          f1->f[0] = f1->f_old[0] - copysign(1.0, v1->u) * kappa * (f1->f_old[0] - f1->f_old[p1->nx - 1]);
          f1->f[p1->nx - 1] = f1->f_old[p1->nx - 1] - copysign(1.0, v1->u) * kappa * (f1->f_old[p1->nx - 1] - f1->f_old[p1->nx - 2]);
     }
     else
     {
          f1->f[0] = f1->f_old[0] - copysign(1.0, v1->u) * kappa * (f1->f_old[0] - f1->f_old[1]);
          f1->f[p1->nx - 1] = f1->f_old[p1->nx - 1] - copysign(1.0, v1->u) * kappa * (f1->f_old[p1->nx - 1] - f1->f_old[0]);
     }
}
void udm1D(Point1D *p1, Func1D *f1, Velocity1D *v1, Timestamp *t1)
{
     double kappa = v1->u * t1->dt / p1->dx;
     int i_m;
     copy(f1->f.begin(), f1->f.end(), f1->f_old.begin());
     for (int i = 1; i < p1->nx - 1; i++)
     {
          i_m = i - int(copysign(1.0, v1->u));
          f1->f[i] = f1->f_old[i] - copysign(1.0, v1->u) * kappa * (f1->f_old[i] - f1->f_old[i_m]);
     }
     periodicBoundary(p1, f1, v1, t1);
}
