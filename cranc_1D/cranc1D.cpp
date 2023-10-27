#include "cranc1D.h"
void periodicBoundary(Point1D *p1, Func1D *f1, Velocity1D *v1, Timestamp *t1) // Caluculate vicinity of boundary
{
     
}
void cranc1D(Point1D *p1, Func1D *f1, Velocity1D *v1, Timestamp *t1, CMatrix1D m1)
{
     std::vector<double> vec(f1->f.size());
     std::copy(f1->f.begin(), f1->f.end(), vec.begin());
     std::vector<double> subset(vec.begin() + 1, vec.end() - 1);
     Eigen::Map<Eigen::VectorXd> ev(subset.data(), subset.size());
     ev = m1.llt.solve(m1.b * ev);
     std::copy(ev.data(), ev.data() + ev.size(), f1->f.begin() + 1);
}