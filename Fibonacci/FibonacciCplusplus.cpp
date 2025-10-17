/*
See the LICENSE.txt file for this sample’s licensing information.

Abstract:
Implements the C++ API.
*/

#include "FibonacciCplusplus.hpp"
#include <Fibonacci/Fibonacci-Swift.h>
#include <iostream>

FibonacciCalculatorCplusplus::FibonacciCalculatorCplusplus(bool printInvocation) : m_swiftCalculator(std::make_unique<Fibonacci::FibonacciCalculator>(Fibonacci::FibonacciCalculator::init(printInvocation))) {}

double FibonacciCalculatorCplusplus::fibonacci(double value) const {
    // Handle the base case of the recursion.
    if (value <= 1.0)
        return 1.0;

    return m_swiftCalculator->fibonacci(value - 1.0) + m_swiftCalculator->fibonacci(value - 2.0);
}

FibonacciCalculatorCplusplus::~FibonacciCalculatorCplusplus() {}
