#include "init_m.h"
#include <iostream>
void initcMatrix1D(int nx, double dx, double dt, CMatrix1D *m1) // Initialize coefficient matrix in 1D
{
    // 0 indicates the case of Cranc Nicolson
    int i = 0;
    double kappa = 0.01;
    double r = kappa * dt / pow(dx, 2);
    if (i == 0)
    {
        m1->a.resize(nx - 2, nx - 2);
        m1->b.resize(nx - 2, nx - 2);
        // Initialize A
        m1->a.setZero();
        m1->a.diagonal() = Eigen::VectorXd::Constant(nx - 2, 2 + 2 * r);
        m1->a.diagonal(1) = Eigen::VectorXd::Constant(nx - 3, -r);
        m1->a.diagonal(-1) = Eigen::VectorXd::Constant(nx - 3, -r);
        // Initialize B
        m1->b.setZero();
        m1->b.diagonal() = Eigen::VectorXd::Constant(nx - 2, 2 - 2 * r);
        m1->b.diagonal(1) = Eigen::VectorXd::Constant(nx - 3, r);
        m1->b.diagonal(-1) = Eigen::VectorXd::Constant(nx - 3, r);
        // initialize llt
        m1->llt.compute(m1->a);
    }
}