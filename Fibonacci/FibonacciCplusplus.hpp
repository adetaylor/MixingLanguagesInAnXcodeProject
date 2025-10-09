/*
See the LICENSE.txt file for this sample’s licensing information.

Abstract:
The C++ API.
*/

#pragma once
#import <swift/bridging>

class FibonacciCalculatorCplusplus {
public:
    FibonacciCalculatorCplusplus(bool printInvocation);
    double fibonacci(double value) const;
private:
    bool printInvocation;
} SWIFT_SHARED_REFERENCE(ref, deref);

inline void ref(FibonacciCalculatorCplusplus* o) {};
inline void deref(FibonacciCalculatorCplusplus* o) {};
