/*
See the LICENSE.txt file for this sample’s licensing information.

Abstract:
The C++ API.
*/

#pragma once
#include <swift/bridging>
#include <span>

class FibonacciCalculatorCplusplus {
public:
    FibonacciCalculatorCplusplus(bool printInvocation);
    double fibonacci(double value) const;
private:
    bool printInvocation;
};

class StringImpl {
    char* bobbins;
};

template<typename T>
class SWIFT_ESCAPABLE RefPtr {
public:
    T* val;
};

class SWIFT_ESCAPABLE String final {
public:
    String() = default;
    String(const String&) = default;

    RefPtr<StringImpl> m_impl;
} SWIFT_ESCAPABLE;

class Thingy {
public:
    const String& getString() const [[clang::lifetimebound]];
private:
    String interior;
} SWIFT_SHARED_REFERENCE(thingyRef, thingyDeref);

inline void thingyRef(Thingy*) {}
inline void thingyDeref(Thingy*) {}
