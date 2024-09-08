#include "coordConversion.h"

Matrix cart2Sph(const Matrix& cartesian) //[x y z] -> [az el r], radian
{
    Matrix spherical;
    int colVector = (cartesian.colCount == 1 && cartesian.rowCount == 3) ? 1 : 0;
    int rowVector = (cartesian.colCount == 3 && cartesian.rowCount == 1) ? 1 : 0;

    if (cartesian.element == nullptr || !(rowVector || colVector)) //invalid incoming vector
    {
        spherical = MatrixRect(1, 3, std::numeric_limits<float>::quiet_NaN()); //return a row vector filled with NAN
        return spherical;
    }
    spherical = MatrixRect(cartesian.rowCount, cartesian.colCount);

    float x = cartesian.element[0][0];
    float y = cartesian.element[1 * colVector][1 * rowVector];
    float z = cartesian.element[2 * colVector][2 * rowVector];

    if (std::isnan(x) || std::isnan(y) || std::isnan(z))
    {
        spherical.element[0][0] = std::numeric_limits<float>::quiet_NaN();
        spherical.element[1 * colVector][1 * rowVector] = std::numeric_limits<float>::quiet_NaN();
        spherical.element[2 * colVector][2 * rowVector] = std::numeric_limits<float>::quiet_NaN();
        return spherical;
    }
    float r, elevation, azimuth;

    double hypotxy = pow(pow(x, 2) + pow(y, 2), 0.5);
    //radius portion
    r = pow(pow(hypotxy, 2) + pow(z, 2), 0.5);

    //elevation portion / phi
    if (z == 0 && hypotxy == 0)
        elevation = std::numeric_limits<float>::quiet_NaN(); //"Vector has no magnitude, therefore theta is undefined."
    else
        elevation = atan2(z, hypotxy);

    //azimuth portion / theta
    if (x == 0 && y == 0)
        azimuth = std::numeric_limits<float>::quiet_NaN(); //"Vector has no magnitude, therefore theta is undefined."
    else
        azimuth = atan2(y, x);

    spherical.element[0][0] = azimuth;
    spherical.element[1 * colVector][1 * rowVector] = elevation;
    spherical.element[2 * colVector][2 * rowVector] = r;
    return spherical;
}

Matrix cart2SphD(const Matrix& cartesian) //[x y z] -> [az el r], degree
{
    Matrix spherical;
    int colVector = (cartesian.colCount == 1 && cartesian.rowCount == 3) ? 1 : 0;
    int rowVector = (cartesian.colCount == 3 && cartesian.rowCount == 1) ? 1 : 0;

    if (cartesian.element == nullptr || !(rowVector || colVector)) //invalid incoming vector
    {
        spherical = MatrixRect(1, 3, std::numeric_limits<float>::quiet_NaN()); //return a row vector filled with NAN
        return spherical;
    }
    spherical = MatrixRect(cartesian.rowCount, cartesian.colCount);

    float x = cartesian.element[0][0];
    float y = cartesian.element[1 * colVector][1 * rowVector];
    float z = cartesian.element[2 * colVector][2 * rowVector];

    if (std::isnan(x) || std::isnan(y) || std::isnan(z))
    {
        spherical.element[0][0] = std::numeric_limits<float>::quiet_NaN();
        spherical.element[1 * colVector][1 * rowVector] = std::numeric_limits<float>::quiet_NaN();
        spherical.element[2 * colVector][2 * rowVector] = std::numeric_limits<float>::quiet_NaN();
        return spherical;
    }
    float r, elevation, azimuth;

    double hypotxy = pow(pow(x, 2) + pow(y, 2), 0.5);
    //radius portion
    r = pow(pow(hypotxy, 2) + pow(z, 2), 0.5);

    //elevation portion / phi
    if (z == 0 && hypotxy == 0)
        elevation = std::numeric_limits<float>::quiet_NaN(); //"Vector has no magnitude, therefore theta is undefined."
    else
        elevation = atan2(z, hypotxy);

    //azimuth portion / theta
    if (x == 0 && y == 0)
        azimuth = std::numeric_limits<float>::quiet_NaN(); //"Vector has no magnitude, therefore theta is undefined."
    else
        azimuth = atan2(y, x);

    spherical.element[0][0] = azimuth * ((180.0f) / M_PI);
    spherical.element[1 * colVector][1 * rowVector] = elevation * ((180.0f) / M_PI);
    spherical.element[2 * colVector][2 * rowVector] = r;
    return spherical;
}

Matrix cart2Pol(const Matrix& cartesian) //[x y] -> [az r] radian
{
    Matrix polar;
    int colVector = (cartesian.colCount == 1 && cartesian.rowCount == 2) ? 1 : 0;
    int rowVector = (cartesian.colCount == 2 && cartesian.rowCount == 1) ? 1 : 0;

    if (cartesian.element == nullptr || !(rowVector || colVector)) //invalid incoming vector
    {
        polar = MatrixRect(1, 3, std::numeric_limits<float>::quiet_NaN()); //return a row vector filled with NAN
        return polar;
    }
    polar = MatrixRect(cartesian.rowCount, cartesian.colCount);

    float x = cartesian.element[0][0];
    float y = cartesian.element[1 * colVector][1 * rowVector];

    if (std::isnan(x) || std::isnan(y))
    {
        polar.element[0][0] = std::numeric_limits<float>::quiet_NaN();
        polar.element[1 * colVector][1 * rowVector] = std::numeric_limits<float>::quiet_NaN();
        return polar;
    }
    float r, azimuth;

    //radius portion
    r = pow(pow(x, 2) + pow(y, 2), 0.5);;

    //azimuth portion / theta
    if (x == 0 && y == 0)
        azimuth = std::numeric_limits<float>::quiet_NaN(); //"Vector has no magnitude, therefore theta is undefined."
    else
        azimuth = atan2(y, x);

    polar.element[0][0] = azimuth;
    polar.element[1 * colVector][1 * rowVector] = r;
    return polar;
}

Matrix cart2PolD(const Matrix& cartesian) //[x y] -> [az r] degree
{
    Matrix polar;
    int colVector = (cartesian.colCount == 1 && cartesian.rowCount == 2) ? 1 : 0;
    int rowVector = (cartesian.colCount == 2 && cartesian.rowCount == 1) ? 1 : 0;

    if (cartesian.element == nullptr || !(rowVector || colVector)) //invalid incoming vector
    {
        polar = MatrixRect(1, 3, std::numeric_limits<float>::quiet_NaN()); //return a row vector filled with NAN
        return polar;
    }
    polar = MatrixRect(cartesian.rowCount, cartesian.colCount);

    float x = cartesian.element[0][0];
    float y = cartesian.element[1 * colVector][1 * rowVector];

    if (std::isnan(x) || std::isnan(y))
    {
        polar.element[0][0] = std::numeric_limits<float>::quiet_NaN();
        polar.element[1 * colVector][1 * rowVector] = std::numeric_limits<float>::quiet_NaN();
        return polar;
    }
    float r, azimuth;

    //radius portion
    r = pow(pow(x, 2) + pow(y, 2), 0.5);;

    //azimuth portion / theta
    if (x == 0 && y == 0)
        azimuth = std::numeric_limits<float>::quiet_NaN(); //"Vector has no magnitude, therefore theta is undefined."
    else
        azimuth = atan2(y, x);

    polar.element[0][0] = azimuth * ((180.0f) / M_PI);
    polar.element[1 * colVector][1 * rowVector] = r;
    return polar;
}

Matrix sphRad2Deg(const Matrix& radian) //degree [az el r]
{
    Matrix degree;
    int colVector = (radian.colCount == 1 && radian.rowCount == 3) ? 1 : 0;
    int rowVector = (radian.colCount == 3 && radian.rowCount == 1) ? 1 : 0;

    if (radian.element == nullptr || !(rowVector || colVector)) //invalid incoming vector
    {
        degree = MatrixRect(1, 3, std::numeric_limits<float>::quiet_NaN()); //return a row vector filled with NAN
        return degree;
    }
    degree = MatrixRect(radian.rowCount, radian.colCount);
    degree.element[0][0] = radian.element[0][0] * ((180.0f) / M_PI);
    degree.element[1 * colVector][1 * rowVector] = radian.element[1 * colVector][1 * rowVector] * ((180.0f) / M_PI);
    degree.element[2 * colVector][2 * rowVector] = radian.element[2 * colVector][2 * rowVector];
    return degree;
}

Matrix polRad2Deg(const Matrix& radian) //[az r] radian -> [az r] degree
{
    Matrix degree;
    int colVector = (radian.colCount == 1 && radian.rowCount == 2) ? 1 : 0;
    int rowVector = (radian.colCount == 2 && radian.rowCount == 1) ? 1 : 0;

    if (radian.element == nullptr || !(rowVector || colVector)) //invalid incoming vector
    {
        degree = MatrixRect(1, 3, std::numeric_limits<float>::quiet_NaN()); //return a row vector filled with NAN
        return degree;
    }
    degree = MatrixRect(radian.rowCount, radian.colCount);
    degree.element[0][0] = radian.element[0][0] * ((180.0f) / M_PI);
    degree.element[1 * colVector][1 * rowVector] = radian.element[1 * colVector][1 * rowVector];
    return degree;
}
