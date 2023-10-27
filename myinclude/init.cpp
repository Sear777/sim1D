#include "init.h"
void initFunc1D(Point1D *p1, Func1D *f1) // Initialize Function in 1D
{
    f1->f.resize(p1->nx);
    f1->f_x.resize(p1->nx);
    f1->f_old.resize(p1->nx);
    f1->f_x_old.resize(p1->nx);
    /*
    for (int i = 0; i < p1->nx; i++) // sin
    {
        f1->f[i] = sin(p1->x[i] * M_PI);
        f1->f_old[i] = sin(p1->x[i] * M_PI);
        f1->f_x[i] = cos(p1->x[i] * M_PI) * M_PI;
        f1->f_x_old[i] = cos(p1->x[i] * M_PI) * M_PI;
    }
    */
    /*
    for (int i = 6; i < 20; i++) // rectangle
    {
        f1->f_x[i] = 0;
        f1->f_x_old[i] = 0;
        if (i < int(p1->nx / 2))
        {
            f1->f[i] = 1;
            f1->f_old[i] = 1;
        }
        else
        {
            f1->f[i] = 0;
            f1->f_old[i] = 0;
        }
    }
    */
    for (int i = 0; i < p1->nx; i++) // rectangle2
    {
        f1->f_x[i] = 0;
        f1->f_x_old[i] = 0;
        if (i >= int(7 * p1->nx / 16) && i <= int(9 * p1->nx / 16))
        {
            f1->f[i] = 1;
            f1->f_old[i] = 1;
        }
        else
        {
            f1->f[i] = 0;
            f1->f_old[i] = 0;
        }
    }
}
void initPoint1D(Point1D *p1) // Initialize Point in 1D
{
    p1->nx = 100;
    p1->xlim = 1;
    p1->dx = p1->xlim / double(p1->nx - 1);
    p1->x.resize(p1->nx);
    double x = 0.0;
    for (int i = 0; i < p1->nx; i++)
    {
        p1->x[i] = x;
        x += p1->dx;
    }
}
void initVelocity1D(Velocity1D *v1) // Initialize velocity in 1D
{
    v1->u = 1.0;
}
void initFunc2D(Point2D *p1, Func2D *f1) // Initialize Function in 2D
{
    f1->f.resize(p1->nx, std::vector<double>(p1->ny));
    f1->f_x.resize(p1->nx, std::vector<double>(p1->ny));
    f1->f_old.resize(p1->nx, std::vector<double>(p1->ny));
    f1->f_x_old.resize(p1->nx, std::vector<double>(p1->ny));
    for (int i = 0; i < p1->nx; i++)
    {
        for (int j = 0; j < p1->ny; j++)
        {
            if (1.0 - ((p1->x[i] - 1) * (p1->x[i] - 1) + (p1->y[j] - 1) * (p1->y[j] - 1)) >= 0)
            {
                f1->f[i][j] = sqrt(1.0 - ((p1->x[i] - 1) * (p1->x[i] - 1) + (p1->y[j] - 1) * (p1->y[j] - 1)));
            }
            else
            {
                f1->f[i][j] = 0;
            }
        }
    }
}
void initPoint2D(Point2D *p1) // Initialize Point in 2D
{
    p1->nx = 50;
    p1->ny = 50;
    p1->xlim = 2;
    p1->ylim = 2;
    p1->dx = p1->xlim / double(p1->nx - 1);
    p1->dy = p1->ylim / double(p1->ny - 1);
    double x = 0.0;
    double y = 0.0;
    for (int i = 0; i < p1->nx; i++)
    {
        p1->x.push_back(x);
        x += p1->dx;
    }
    for (int i = 0; i < p1->nx; i++)
    {
        p1->y.push_back(y);
        y += p1->dy;
    }
}
void initVelocity2D(Velocity2D *v1)
{
    v1->u = 1.0;
    v1->v = 1.0;
}
void initTime(Timestamp *t1) // Initialize time in the simulation
{
    t1->t = 0;
    t1->dt = 0.001;
    t1->tlim = 1;
}
// main function
void init1D(Point1D *p1, Func1D *f1, Velocity1D *v1, Timestamp *t1)
{
    initPoint1D(p1);
    initFunc1D(p1, f1);
    initVelocity1D(v1);
    initTime(t1);
}
void init2D(Point2D *p1, Func2D *f1, Velocity2D *v1, Timestamp *t1)
{
    initPoint2D(p1);
    initFunc2D(p1, f1);
    initVelocity2D(v1);
    initTime(t1);
}