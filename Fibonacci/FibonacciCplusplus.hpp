/*
See the LICENSE.txt file for this sample’s licensing information.

Abstract:
The C++ API.
*/

#pragma once

#include <type_traits>
#include <utility>

class FibonacciCalculatorCplusplus {
public:
    FibonacciCalculatorCplusplus(bool printInvocation);
    double fibonacci(double value) const;
private:
    bool printInvocation;
};

template<typename T>
class RefPtr {
public:
    RefPtr(T* val) : m_ptr(val) {}
    T* m_ptr;
};

template<typename T>
inline RefPtr<T> ptrise(T* source) {
    return RefPtr(source);
}

class AuxiliaryProcessProxy {
    
};

inline AuxiliaryProcessProxy* getAPP() {
    return new AuxiliaryProcessProxy();
}

inline RefPtr<AuxiliaryProcessProxy> ptriseAPP(AuxiliaryProcessProxy* app) {
    return ptrise(app);
}
