/*
See the LICENSE.txt file for this sample’s licensing information.

Abstract:
The C++ API.
*/

#pragma once

class FibonacciCalculatorCplusplus {
public:
    FibonacciCalculatorCplusplus(bool printInvocation);
    double fibonacci(double value) const;
private:
    bool printInvocation;
};

struct DefaultTraits;

template<typename T, typename Traits=DefaultTraits>
class Ref {
public:
    T* item;
};

struct Payload {
    int val;
};
