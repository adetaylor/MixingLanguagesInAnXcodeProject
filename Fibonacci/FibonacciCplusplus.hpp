/*
See the LICENSE.txt file for this sample’s licensing information.

Abstract:
The C++ API.
*/

#pragma once
#include <cstddef>
#include <stdlib.h>
#include <limits>
#include <utility>
#include <algorithm>
#include <span>

#define _CXX_INTEROP_STRINGIFY(_x) #_x
#define SWIFT_SHARED_REFERENCE(_retain, _release)                                \
  __attribute__((swift_attr("import_reference")))                          \
  __attribute__((swift_attr(_CXX_INTEROP_STRINGIFY(retain:_retain))))      \
  __attribute__((swift_attr(_CXX_INTEROP_STRINGIFY(release:_release))))

#define LIFETIME_BOUND [[clang::lifetimebound]]

class FibonacciCalculatorCplusplus {
public:
    FibonacciCalculatorCplusplus(bool printInvocation);
    double fibonacci(double value) const;
private:
    bool printInvocation;
};

class FrameState {
public:
private:
    int v;
} SWIFT_SHARED_REFERENCE(refFrameState, derefFrameState);

inline void refFrameState(FrameState* o) {
}

inline void derefFrameState(FrameState* o) {
}

template<typename T>
class Ref {
public:
    T* thingy;
};


template<typename T>
class Vector {
public:
    Vector() {}
    const T& getElem(size_t i) const LIFETIME_BOUND
    {
        return m_buffer[i];
    }
    Vector(Vector<T>&& other)
    {
    }

protected:
    T* m_buffer;
};

using VecRefFrameState = Vector<Ref<FrameState>>;
using RefFrameState = Ref<FrameState>;
