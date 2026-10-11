#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include "TutorialConfig.h"

#ifdef USE_MYMATH
#include "MathFunctions.h"
#endif

int main(int argc, char* argv[])
{
    std::cout << "Tutorial Version " << Tutorial_VERSION_MAJOR << "."
              << Tutorial_VERSION_MINOR << '\n';

    // Preserve the original no-argument debugging example.
    double value = 9.0;
    if (argc > 2) {
        std::cerr << "Usage: " << argv[0] << " [number]\n";
        return 1;
    }
    if (argc == 2) {
        try {
            std::size_t consumed = 0;
            const std::string input(argv[1]);
            value = std::stod(input, &consumed);
            if (consumed != input.size() || !std::isfinite(value)) {
                throw std::invalid_argument("Expected a finite number");
            }
        } catch (const std::exception&) {
            std::cerr << "Invalid number. Usage: " << argv[0] << " [number]\n";
            return 1;
        }
    }

#ifdef USE_MYMATH
    std::cout << "Implementation: MathFunctions\n";
    const double result = mysqrt(value);
#else
    std::cout << "Implementation: std::sqrt\n";
    const double result = std::sqrt(value);
#endif

    std::cout << "sqrt(" << value << ")=" << result << '\n';
    return 0;
}
