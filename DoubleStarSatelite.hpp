#include "RungeKutta.h"
#include <cmath>
#include <vector>

#ifndef DoubleStarSateliteCls
#define DoubleStarSateliteCls

class DoubleStarSatelite : public RungeKutta
{
private:
    const double G = 6.6740E-17; // м3 с-3 кг-2 Гравитационная постоянная

    double M1, M2, m;   // Массы первой звезды, второй и спутника соотв.
    double x1, x2, L;   // Расстояния от начала координат до первой звезды, до второй звезды и между звездами
    double w;           // Угловая скорость вращения системы звезд
    double x, y;        // Координаты спутника
    double Vx, Vy;      // Скорость спутника
public:
    DoubleStarSatelite(double M1, double M2, double m, double L, double x0, double y0, double Vx0, double Vy0);
    ~DoubleStarSatelite();

    virtual std::vector<double> F(double t, std::vector<double> &Y);
    double Step(int interval);

    double get_x() { return Y[0]; }
    double get_y() { return Y[1]; }
    double get_Vx() { return Y[2]; }
    double get_Vy() { return Y[3]; }
    double get_V() { return sqrt(Y[2] * Y[2] + Y[3] * Y[3]); }
};

#endif
