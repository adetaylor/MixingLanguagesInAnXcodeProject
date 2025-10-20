/*
See the LICENSE.txt file for this sample’s licensing information.

Abstract:
The C++ API.
*/

#pragma once
#include <span>

class FibonacciCalculatorCplusplus {
public:
    FibonacciCalculatorCplusplus(bool printInvocation);
    double fibonacci(double value) const;
private:
    bool printInvocation;
};


using SpanConstChar = std::span<const char>;

inline void takeSpan(const SpanConstChar& data) {}

inline void makeSpan() {
    const char data[] = {'a', 'b'};
    SpanConstChar dataSpan{data, 2};
    takeSpan(dataSpan);
}
