#include "../myinclude/data_writer.h"
#include "../myinclude/graph.h"
#include "../myinclude/sleepMilliseconds.h"
#include "../myinclude/transf.h"
#include "wendroff1D.h"
int main()
{
    Point1D p1;
    Func1D f1;
    Velocity1D v1;
    Timestamp t1;
    FILE *g1;
    init1D(&p1, &f1, &v1, &t1);
    transf(&(f1.f), &(f1.f_x), p1.nx);
    launchPlot(&g1, 0);
    for (int i = 0; i <= int(t1.tlim / t1.dt); i++)
    {
        wendroff1D(&p1, &f1, &v1, &t1);
        if (i % 10 == 0)
        {
            untransf(&(f1.f), &(f1.f_x), p1.nx);
            data_writer_1D(p1.x, p1.nx, f1.f, t1.t);
            Plot2D(p1.xlim, 2.0, t1.t, g1);
            transf(&(f1.f), &(f1.f_x), p1.nx);
            sleepMilliseconds(100);
        }
        t1.t += t1.dt;
    }
    endPlot(g1);
    return 0;
}