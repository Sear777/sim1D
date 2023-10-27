#include "../myinclude/init.h"
#include <cmath>
void eno1D(Point1D*, Func1D*, Velocity1D*, Timestamp*); // Caluculate grids in ENO method
void periodicBoundary(Point1D*, Func1D*, Velocity1D*, Timestamp*); // Caluculate grids near boundary