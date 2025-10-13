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

using IntSpan = std::span<const int>;
inline void takeSpan(std::span<const int> x [[clang::noescape]]);

inline void takeSpanChar(std::span<char> data [[clang::noescape]]) {}
inline void takeSpanConstChar(std::span<const char> data [[clang::noescape]]) {}
inline void takeSpanUChar(std::span<const unsigned int> data [[clang::noescape]]) {}
