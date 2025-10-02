/*
See the LICENSE.txt file for this sample’s licensing information.

Abstract:
The C++ API.
*/

#pragma once
#include <cstddef>

#define _CXX_INTEROP_STRINGIFY(_x) #_x
#define SWIFT_SHARED_REFERENCE(_retain, _release)                                \
  __attribute__((swift_attr("import_reference")))                          \
  __attribute__((swift_attr(_CXX_INTEROP_STRINGIFY(retain:_retain))))      \
  __attribute__((swift_attr(_CXX_INTEROP_STRINGIFY(release:_release))))

class FibonacciCalculatorCplusplus {
public:
    FibonacciCalculatorCplusplus(bool printInvocation);
    double fibonacci(double value) const;
private:
    bool printInvocation;
};

class CppRefCounted {
public:
    static CppRefCounted* create(int p) __attribute__((swift_attr("returns_retained"))) { return new CppRefCounted(p); }
private:
    CppRefCounted(int p) : value(p), refCount(1) {}
    int value;
    int refCount;
    friend void refCppRefCounted(CppRefCounted* o);
    friend void derefCppRefCounted(CppRefCounted* o);
} SWIFT_SHARED_REFERENCE(refCppRefCounted, derefCppRefCounted);



inline void refCppRefCounted(CppRefCounted* o) {
    o->refCount++;
}
inline void derefCppRefCounted(CppRefCounted* o) {
    o->refCount--;
    if (o->refCount == 0) {
        delete o;
    }
}

template<typename T>
class SomeSmartPtr {
public:
    T* item;
};

inline SomeSmartPtr<CppRefCounted> makeSomeSmartPtr(CppRefCounted* item) {
    return SomeSmartPtr(item);
}

class CppContainer {
public:
    void reserveCapacity(size_t s) {}
    void append(SomeSmartPtr<CppRefCounted> item) {}
};

void printItems(CppContainer items);
