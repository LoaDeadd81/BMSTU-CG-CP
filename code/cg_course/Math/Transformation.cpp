#include "Transformation.h"

double to_radians(double degree)
{
    return degree * (M_PI / 180);
}

Matix4x4d getMoveMatrix(double dx, double dy, double dz)
{
    Matix4x4d res;
    res[0][0] = 1;
    res[1][1] = 1;
    res[2][2] = 1;
    res[3][0] = dx;
    res[3][1] = dy;
    res[3][2] = dz;
    res[3][3] = 1;
    return res;
}

Matix4x4d getScaleMatrix(double dx, double dy, double dz)
{
    Matix4x4d res;
    res[0][0] = dx;
    res[1][1] = dy;
    res[2][2] = dz;
    res[3][3] = 1;
    return res;
}

Matix4x4d getRotateMatrix(double dx, double dy, double dz)
{
    Matix4x4d resx, resy, resz, res;
    double rx = to_radians(std::fmod(dx, 360.0)),
            ry = to_radians(std::fmod(dy, 360.0)),
            rz = to_radians(std::fmod(dz, 360.0));

    double cosx = std::cos(rx), sinx = std::sin(rx);
    double cosy = std::cos(ry), siny = std::sin(ry);
    double cosz = std::cos(rz), sinz = std::sin(rz);

    resx[0][0] = resx[3][3] = 1;
    resx[2][2] = resx[1][1] = (abs(cosx) < TREPS) ? 0 : cosx;
    resx[1][2] = (abs(sinx) < TREPS) ? 0 : sinx;
    resx[2][1] = -resx[1][2];

    resy[1][1] = resy[3][3] = 1;
    resy[0][0] = resy[2][2] = (abs(cosy) < TREPS) ? 0 : cosy;
    resy[2][0] = (abs(siny) < TREPS) ? 0 : siny;
    resy[0][2] = -resy[2][0];

    resz[2][2] = resz[3][3] = 1;
    resz[0][0] = resz[1][1] = (abs(cosz) < TREPS) ? 0 : cosz;
    resz[0][1] = (abs(sinz) < TREPS) ? 0 : sinz;
    resz[1][0] = -resz[0][1];

    res = resx * resy;
    res = res * resz;

    return res;
}

Vec4d operator*(Vec4d &v, Matix4x4d &mtr)
{
    Vec4d res;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            res[i] += mtr[j][i] * v[j];
        }
    }

    return res;
}