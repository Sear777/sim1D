#include <fstream>
#include <vector>
#include <math.h>
struct point1D
{
    std::vector<double> x;
    std::vector<double> x_old;
    int nx;
    double xlim;
    double dx;
};
struct func1D
{
    std::vector<double> f;
    std::vector<double> f_old;
    std::vector<double> f_x;
    std::vector<double> f_x_old;
    int nx;
};
struct velocity1D
{
    double u;
};
struct point2D
{
    std::vector<double> x;
    std::vector<double> y;
    std::vector<double> x_old;
    std::vector<double> y_old;
    int nx;
    int ny;
    double xlim;
    double ylim;
    double dx;
    double dy;
};
struct func2D
{
    std::vector<std::vector<double>> f;
    std::vector<std::vector<double>> f_old;
    std::vector<std::vector<double>> f_x;
    std::vector<std::vector<double>> f_x_old;
    int nx;
    int ny;
};
struct velocity2D
{
    double u;
    double v;
};
struct timestamp
{
    double t;
    double dt;
    double tlim;
};
typedef point1D Point1D;
typedef func1D Func1D;
typedef velocity1D Velocity1D;
typedef point2D Point2D;
typedef func2D Func2D;
typedef velocity2D Velocity2D;
typedef timestamp Timestamp;
void init1D(Point1D *, Func1D *, Velocity1D *, Timestamp *t1); // Set parameter in1D
void init2D(Point2D *, Func2D *, Velocity2D *, Timestamp *t1); // Set parameter in 2D
