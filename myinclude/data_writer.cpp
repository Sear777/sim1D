#include "data_writer.h"
void data_writer_1D(std::vector<double> x, int nx, std::vector<double> f, double t)
{
    char filename[100];
    std::sprintf(filename, "src/example1D_%.4f.dat", t);
    std::ofstream outfile(filename);
    if (!outfile)
    {
        std::cerr << "Error: could not open file " << filename << std::endl;
        return;
    }
    for (int i = 0; i < nx; i++)
    {
        outfile << x[i] << " " << f[i] << std::endl;
    }
    outfile.close();
}

void data_writer_2D(std::vector<double> x, int nx, std::vector<double> y, int ny, std::vector<std::vector<double>> f)
{
    std::ofstream outfile;
    outfile.open("src/example2D.dat", std::ios::out | std::ios::trunc);
    for (int i = 0; i < nx; i++)
    {
        for (int j = 0; j < ny; j++)
        {
            outfile << x[i] << "  " << y[j] << "  " << f[i][j] << std::endl;
        }
        outfile << std::endl;
    }
    outfile.close();
}