/*
See the LICENSE.txt file for this sample’s licensing information.

Abstract:
Implements the C++ API.
*/

#include "FibonacciCplusplus.hpp"
#include <Fibonacci/Fibonacci-Swift.h>
#include <iostream>

FibonacciCalculatorCplusplus::FibonacciCalculatorCplusplus(bool printInvocation) : printInvocation(printInvocation) {}

double FibonacciCalculatorCplusplus::fibonacci(double value) const {
    // Print the value if applicable.
    if (printInvocation)
        std::cout << "[c++] fibonacci(" << value << ")\n";
    
    // Handle the base case of the recursion.
    if (value <= 1.0)
        return 1.0;
    
    // Create the Swift `FibonacciCalculator` structure and invoke its `fibonacci` method.
    auto swiftCalculator = Fibonacci::FibonacciCalculator::init(printInvocation);
    return swiftCalculator.fibonacci(value - 1.0) + swiftCalculator.fibonacci(value - 2.0);
}

bool find_if_asan_is_enabled_non_inline() {
#if __has_feature(address_sanitizer)
    return true;
#else
    return false;
#endif
}
