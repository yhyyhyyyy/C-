#include "MathFunctions.h"
#include <cmath>
#include <iostream>
#include <limits>

double mysqrt(double x)
{
    if (x < 0) return std::numeric_limits<double>::quiet_NaN();
    if (x == 0) return 0;
#if defined(HAVE_LOG) && defined(HAVE_EXP)
    std::cout << "Computing with detected log and exp\n";
    return std::exp(std::log(x) * 0.5);
#else
    // Scale the input so Newton iteration also handles very small/large values.
    int exponent = 0;
    double scaled = std::frexp(x, &exponent);
    if (exponent % 2 != 0) { scaled *= 2; --exponent; }
    double result = 1;
    for (int i = 0; i < 12; ++i) result = 0.5 * (result + scaled / result);
    return std::ldexp(result, exponent / 2);
#endif
}
