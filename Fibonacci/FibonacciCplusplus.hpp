/*
See the LICENSE.txt file for this sample’s licensing information.

Abstract:
The C++ API.
*/

#pragma once

#include <Fibonacci/Fibonacci-Swift.h>
#include <sstream>

class FibonacciCalculatorCplusplus {
public:
    FibonacciCalculatorCplusplus(bool printInvocation);
    double fibonacci(double value) const;
private:
    bool printInvocation;
};

inline swift::String makeSwiftStringFromChar(char whatever) {
    std::ostringstream os;
    os << "The char is " << whatever << "." << std::endl;
    return swift::String(os.str());
}
