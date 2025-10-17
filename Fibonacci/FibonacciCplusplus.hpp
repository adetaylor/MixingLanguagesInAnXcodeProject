/*
See the LICENSE.txt file for this sample’s licensing information.

Abstract:
The C++ API.
*/

#pragma once
#include <memory>
#include <swift/bridging>

// #include <Fibonacci/Fibonacci-Swift.h> // not OK

namespace Fibonacci {
class FibonacciCalculator;
}

class FibonacciCalculatorCplusplus {
public:
    FibonacciCalculatorCplusplus(bool printInvocation);
    FibonacciCalculatorCplusplus(FibonacciCalculatorCplusplus&&) = default;
    double fibonacci(double value) const;
    ~FibonacciCalculatorCplusplus();
private:
    std::unique_ptr<Fibonacci::FibonacciCalculator> m_swiftCalculator;
} SWIFT_ESCAPABLE;
