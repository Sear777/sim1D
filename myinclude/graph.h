#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <thread>
void Plot2D(double, double, double, FILE *);         // Plot data in 2D
void Plot3D(double, double, double, double, FILE *); // Plot data in 3D
void launchPlot(FILE **, int);                       // Launch Gnuplot
void endPlot(FILE *);                                // End Gnuplot