/*
See the LICENSE.txt file for this sample’s licensing information.

Abstract:
The C++ API.
*/

#pragma once

namespace Fibonacci {
class FibonacciCalculator;
};

class FibonacciCalculatorCplusplus {
public:
    FibonacciCalculatorCplusplus(bool printInvocation, Fibonacci::FibonacciCalculator* _Nonnull swiftCalculator);
    double fibonacci(double value) const;
private:
    bool printInvocation;
};
