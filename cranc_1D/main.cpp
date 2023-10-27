#include "../myinclude/data_writer.h"
#include "../myinclude/graph.h"
#include "../myinclude/sleepMilliseconds.h"
#include "cranc1D.h"
int main()
{
    Point1D p1;
    Func1D f1;
    Velocity1D v1;
    Timestamp t1;
    CMatrix1D m1;
    FILE *g1;
    init1D(&p1, &f1, &v1, &t1);
    initcMatrix1D(p1.nx, p1.dx, t1.dt, &m1);
    launchPlot(&g1, 0);
    for (int i = 0; i <= int(t1.tlim / t1.dt); i++)
    {
        cranc1D(&p1, &f1, &v1, &t1, m1);
        if (i % 10 == 0)
        {
            data_writer_1D(p1.x, p1.nx, f1.f, t1.t);
            Plot2D(p1.xlim, 2.0, t1.t, g1);
            sleepMilliseconds(100);
        }
        t1.t += t1.dt;
    }
    endPlot(g1);
    return 0;
}