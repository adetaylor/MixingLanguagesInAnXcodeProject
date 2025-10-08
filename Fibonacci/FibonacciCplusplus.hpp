/*
See the LICENSE.txt file for this sample’s licensing information.

Abstract:
The C++ API.
*/

#pragma once
#include <optional>

class FibonacciCalculatorCplusplus {
public:
    FibonacciCalculatorCplusplus(bool printInvocation);
    double fibonacci(double value) const;
    std::optional<double> meaningOfLife;
private:
    bool printInvocation;
};
