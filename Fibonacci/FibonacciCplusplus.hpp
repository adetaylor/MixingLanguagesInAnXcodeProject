/*
See the LICENSE.txt file for this sample’s licensing information.

Abstract:
The C++ API.
*/

#pragma once

#include <memory>


namespace Fibonacci {
class FibonacciCalculator;
};

class FibonacciCalculatorCplusplus {
public:
    FibonacciCalculatorCplusplus(bool printInvocation, Fibonacci::FibonacciCalculator* _Nonnull swiftCalculator);
    ~FibonacciCalculatorCplusplus(); // necessary to avoid incomplete type problems
    double fibonacci(double value) const;
private:
    bool printInvocation;
//    std::unique_ptr<Fibonacci::FibonacciCalculator> m_swiftCalculator;
    Fibonacci::FibonacciCalculator* _Nonnull m_swiftCalculator;
};
