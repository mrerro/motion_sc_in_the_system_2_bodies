#include "DoubleStarSatelite.hpp"

DoubleStarSatelite::DoubleStarSatelite(double M1, double M2, double m, double L, double x0, double y0, double Vx0, double Vy0) : RungeKutta (4)
{
    this->M1 = M1;
    this->M2 = M2;
    this->m = m;

    this->L = L;
    this->x1 = L * M2 / (M1+M2);
    this->x2 = L - x1;

    this->w = std::sqrt(G*(M1+M2)/std::pow(L, 3));

    std::vector<double> Y0(4);
    Y0[0] = x0;
    Y0[1] = y0;
    Y0[2] = Vx0;
    Y0[3] = Vy0;
    SetInit (0, Y0);
}

std::vector<double> DoubleStarSatelite::F(double time, std::vector<double> &coordinates) {
    // x'=Vx - FY[0] = Y[2]
    // y'=Vy - FY[1] = Y[3] 
    // Vx'=... FY[2] =  
    // Vy'=... FY[3] =  

    FY[0] = Y[2];
    FY[1] = Y[3];
    FY[2] = G*M1*(Y[0]-x1) / std::pow(std::pow(Y[0]-x1,2.) + std::pow(Y[1],2.), 3./2.) 
          + G*M2*(Y[0]-x2) / std::pow(std::pow(Y[0]-x2,2.) + std::pow(Y[1],2.), 3./2.) 
          + w*w*Y[0] + 2*Y[3]*w;
    FY[3] = G*M1*Y[1] / std::pow(std::pow(Y[0]-x1,2.)+ std::pow(Y[1],2.), 3./2.) 
          + G*M2*Y[1] / std::pow(std::pow(Y[0]-x2,2.)+ std::pow(Y[1],2.), 3./2.) 
          + w*w*Y[1] - 2*Y[2]*w;
    return FY;
}

DoubleStarSatelite::~DoubleStarSatelite()
{
}
