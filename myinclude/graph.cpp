#include "graph.h"
void Plot2D(double xlim, double ylim, double t, FILE *gnuplotPipe)
{
    // Set 2Dplot
    fprintf(gnuplotPipe, "set xrange [0:%3f]\n", xlim);
    fprintf(gnuplotPipe, "set yrange [-1:%3f]\n", ylim);
    char filename[50];
    std::sprintf(filename, "src/example1D_%.4f.dat", t);
    fprintf(gnuplotPipe, "plot '%s' with line title 't = %.2f'\n", filename, t);
    fflush(gnuplotPipe);
}
void Plot3D(double xlim, double ylim, double zlim, double t, FILE *gnuplotPipe)
{
    // Set 3Dplot
    fprintf(gnuplotPipe, "set xrange [0:%3f]\n", xlim);
    fprintf(gnuplotPipe, "set yrange [0:%3f]\n", ylim);
    fprintf(gnuplotPipe, "set zrange [0:%3f]\n", xlim);
    fprintf(gnuplotPipe, "set palette defined ( 0 '#000090',1 '#000fff',2 '#0090ff',3 '#0fffee',4 '#90ff70',5 '#ffee00',6 '#ff7000',7 '#ee0000',8 '#7f0000')\n");
    fprintf(gnuplotPipe, "splot 'src/example2D.dat' with line lc palette title 't = %3f'\n", t);
    fflush(gnuplotPipe);
}
void launchPlot(FILE **gnuplotPipe, int i)
{
    // Launch Gnuplot
    *gnuplotPipe = popen("gnuplot", "w");
    if (i == 0)
    {
        // make gif
        fprintf(*gnuplotPipe, "set term gif animate\n");
        fprintf(*gnuplotPipe, "set output 'test.gif'\n");
    }
}
void endPlot(FILE *gnuplotPipe)
{
    // End Gnuplot
    fprintf(gnuplotPipe, "exit");
    fflush(gnuplotPipe);
    pclose(gnuplotPipe);
}
