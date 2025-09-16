/*
See the LICENSE.txt file for this sample’s licensing information.

Abstract:
The C++ API.
*/

#pragma once


#include <swift/bridging>

class FibonacciCalculatorCplusplus {
public:
    FibonacciCalculatorCplusplus(bool printInvocation);
    double fibonacci(double value) const;
private:
    bool printInvocation;
};



class RefCountedBase {
public:

    void ref() const
    {
        ++m_refCount;
    }

protected:
    RefCountedBase()
        : m_refCount(1)
    {
    }

    ~RefCountedBase() {}

    bool derefBase() const
    {
        unsigned tempRefCount = m_refCount - 1;
        if (!tempRefCount) {
            return true;
        }
        m_refCount = tempRefCount;
        return false;
    }

private:
    mutable unsigned m_refCount;
};

template<typename T> class RefCounted : public RefCountedBase {
public:
    void deref() const
    {
        if (derefBase())
            delete const_cast<T*>(static_cast<const T*>(this));
    }

protected:
    RefCounted() { }
    ~RefCounted()
    {
    }
} SWIFT_SHARED_REFERENCE(refRef, derefRef);

template<typename T>
inline void ref(T* obj)
{
    obj->ref();
}

template<typename T>
inline void deref(T* obj)
{
    obj->deref();
}

//===================== End of namespace

template<typename T>
inline void refRef(T* obj)
{
    ref(obj);
}

template<typename T>
inline void derefRef(T* obj)
{
    deref(obj);
}

//=====================


class SomeThingy: RefCounted<SomeThingy> {
public:
    SomeThingy(int value) : m_value(value) {};
    int value() { return m_value; }
private:
    int m_value;
};
