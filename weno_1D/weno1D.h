#include "../myinclude/init.h"
#include <cmath>
void weno1D(Point1D *, Func1D *, Velocity1D *, Timestamp *);           // Caluculate grids in WENO method
void periodicBoundary(Point1D *, Func1D *, Velocity1D *, Timestamp *); // Caluculate grids near boundary