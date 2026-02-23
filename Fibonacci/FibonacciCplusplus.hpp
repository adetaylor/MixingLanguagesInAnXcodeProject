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

inline bool find_if_asan_is_enabled_inline() {
#if __has_feature(address_sanitizer)
    return true;
#else
    return false;
#endif
}

bool find_if_asan_is_enabled_non_inline();

