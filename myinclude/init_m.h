#include <Eigen/Dense>
struct cMatrix1D
{
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> a;
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> b;
    Eigen::LDLT<Eigen::MatrixXd> llt;
};
typedef cMatrix1D CMatrix1D;
void initcMatrix1D(int, double, double, CMatrix1D *); // Initialize coefficient matrix in 1D