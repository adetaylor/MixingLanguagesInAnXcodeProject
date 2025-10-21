/*
See the LICENSE.txt file for this sample’s licensing information.

Abstract:
The C++ API.
*/

#pragma once

#include <memory>
#include <swift/bridging>

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
    std::unique_ptr<Fibonacci::FibonacciCalculator> m_swiftCalculator;
} SWIFT_SHARED_REFERENCE(ref, release);

inline void ref(FibonacciCalculatorCplusplus* _Nonnull o) {}


inline void release(FibonacciCalculatorCplusplus* _Nonnull o) {}
