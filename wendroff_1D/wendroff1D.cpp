#include "wendroff1D.h"
void periodicBoundary(Point1D *p1, Func1D *f1, Velocity1D *v1, Timestamp *t1){
     f1->f[0] = f1->f_old[0] - v1->u * t1->dt / (2 * p1->dx) * (f1->f_old[1] - f1->f_old[p1->nx-1]) + v1->u * v1->u * t1->dt * t1->dt / (2 * p1->dx * p1->dx) * (f1->f_old[1] - 2 * f1->f_old[0] + f1->f_old[p1->nx-1]);
     f1->f[p1->nx-1] = f1->f_old[p1->nx-1] - v1->u * t1->dt / (2 * p1->dx) * (f1->f_old[0] - f1->f_old[p1->nx-2]) + v1->u * v1->u * t1->dt * t1->dt / (2 * p1->dx * p1->dx) * (f1->f_old[0] - 2 * f1->f_old[p1->nx-1] + f1->f_old[p1->nx-2]);
}
void wendroff1D(Point1D *p1, Func1D *f1, Velocity1D *v1, Timestamp *t1)
{
     copy(f1->f.begin(), f1->f.end(), f1->f_old.begin());
     for (int i = 1; i < p1->nx-1; i++)
     {
          f1->f[i] = f1->f_old[i] - v1->u * t1->dt / (2 * p1->dx) * (f1->f_old[i + 1] - f1->f_old[i - 1]) + v1->u * v1->u * t1->dt * t1->dt / (2 * p1->dx * p1->dx) * (f1->f_old[i + 1] - 2 * f1->f_old[i] + f1->f_old[i - 1]);
     }
     periodicBoundary(p1, f1, v1, t1);
}