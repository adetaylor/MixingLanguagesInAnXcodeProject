/*
See the LICENSE.txt file for this sample’s licensing information.

Abstract:
The C++ API.
*/

#pragma once

#import <iostream>


#define _CXX_INTEROP_STRINGIFY(_x) #_x
#define SWIFT_SHARED_REFERENCE(_retain, _release)                                \
  __attribute__((swift_attr("import_reference")))                          \
  __attribute__((swift_attr(_CXX_INTEROP_STRINGIFY(retain:_retain))))      \
  __attribute__((swift_attr(_CXX_INTEROP_STRINGIFY(release:_release))))

#define SWIFT_RETURNS_UNRETAINED                                               \
  __attribute__((swift_attr("returns_unretained")))

class FibonacciCalculatorCplusplus {
public:
    FibonacciCalculatorCplusplus(bool printInvocation);
    double fibonacci(double value) const;
private:
    bool printInvocation;
};

template<class T>
class Ref {
public:
    T* ptr() const __attribute__((returns_nonnull)) { return ref; }
    T* ref;
};

template<class T>
class RefCounted {
public:
    RefCounted() : refCount(0) {}
    void ref() { refCount++; std::cout << "Referenced; refCount " << refCount << std::endl; }
    void deref() { refCount--; std::cout << "Dereferenced; refCount " << refCount << std::endl; if (refCount == 0) { delete this; }}
    virtual ~RefCounted() {}
private:
    int refCount;
};

template<class T>
Ref<T> adoptRef(T& thingy) {
    thingy.ref();
    Ref<T> ref;
    ref.ref = &thingy;
    return ref;
};

class Payload;

inline void payloadRef(Payload* p);
inline void payloadDeref(Payload* p);

class Payload final : public RefCounted<Payload> {
public:
    static Ref<Payload> create(int value) { return adoptRef(*new Payload(value)); }

    ~Payload() { std::cout << "Destroying Payload with value " << m_value << std::endl; }

    int value() const { return m_value; }
    void setValue(int value) { m_value = value; }

private:
    explicit Payload(int value) : m_value(value) { std::cout << "Creating Payload with value " << value << std::endl; }
    int m_value;
} SWIFT_SHARED_REFERENCE(payloadRef, payloadDeref);

inline Ref<Payload> getPayloadRef(int value) {
    return Payload::create(value);
}

inline void payloadRef(Payload* p) { std::cout << "Swift referencing Payload with value " << p->value() << std::endl; p->ref(); }
inline void payloadDeref(Payload* p) { std::cout << "Swift dereferencing Payload with value " << p->value() << std::endl;  p->deref(); }

