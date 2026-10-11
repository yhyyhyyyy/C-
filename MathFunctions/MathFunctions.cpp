#include "MathFunctions.h"
#include "Table.h"
#include <cmath>
#include <iostream>
#include <limits>

double mysqrt(double x)
{
    if (x < 0) return std::numeric_limits<double>::quiet_NaN();
    if (x == 0 || !std::isfinite(x)) return x;
    double result;
    if (x >= 1 && x < 10) {
        std::cout << "Using generated Table.h\n";
        result = sqrtTable[static_cast<int>(x)];
        for (int i = 0; i < 12; ++i) result = 0.5 * (result + x / result);
        return result;
    }
    // Normalize before Newton iteration to avoid overflow and slow convergence.
    int exponent = 0;
    double scaled = std::frexp(x, &exponent);
    if (exponent % 2 != 0) { scaled *= 2; --exponent; }
    result = 1;
    for (int i = 0; i < 12; ++i) result = 0.5 * (result + scaled / result);
    return std::ldexp(result, exponent / 2);
}
