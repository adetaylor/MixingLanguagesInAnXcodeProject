/*
See the LICENSE.txt file for this sample’s licensing information.

Abstract:
The C++ API.
*/

#pragma once
#import <memory>
#import <utility>

class FibonacciCalculatorCplusplus {
public:
    FibonacciCalculatorCplusplus(bool printInvocation);
    double fibonacci(double value) const;
private:
    bool printInvocation;
};

class Noncopyable {
public:
    Noncopyable(int a) : value(a) {}
    Noncopyable(const Noncopyable&) = delete;
    Noncopyable(Noncopyable&& other) {
    }
    int value;
};
