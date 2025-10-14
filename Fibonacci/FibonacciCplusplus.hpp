/*
See the LICENSE.txt file for this sample’s licensing information.

Abstract:
The C++ API.
*/

#pragma once
#include <swift/bridging>
#include <utility>


namespace API {
class Array {
public:
    static Array*_Nonnull create() { return new Array(); }
    int value;
    int* _Nullable value2;
private:
    Array() {}
} SWIFT_SHARED_REFERENCE(arrayRef, arrayDeref);

}

inline void arrayRef(API::Array* _Nonnull o) {}

inline void arrayDeref(API::Array* _Nonnull o) {}

template<typename T>
struct RawPtrTraits {
//    template<typename U> using RebindTraits = RawPtrTraits<U>;
//
    using StorageType = T*;

    template<typename U>
    static inline T* _Nonnull exchange(StorageType _Nonnull& ptr, U&& newValue) { return std::exchange(ptr, newValue); }
//
//    static ALWAYS_INLINE void swap(StorageType& a, StorageType& b) { std::swap(a, b); }
//    static ALWAYS_INLINE T* unwrap(const StorageType& ptr) { return ptr; }
//
//    static StorageType hashTableDeletedValue() { return std::bit_cast<StorageType>(static_cast<uintptr_t>(-1)); }
//    static ALWAYS_INLINE bool isHashTableDeletedValue(const StorageType& ptr) { return ptr == hashTableDeletedValue(); }
};


template<typename T> struct DefaultRefDerefTraits {
//    static inline T* refIfNotNull(T* ptr)
//    {
//        if (ptr) [[likely]]
//            ptr->ref();
//        return ptr;
//    }
//
//    static inline T& ref(T& ref)
//    {
//        ref.ref();
//        return ref;
//    }
//
//    static inline void derefIfNotNull(T* ptr)
//    {
//        if (ptr) [[likely]]
//            ptr->deref();
//    }
};


template<typename T, typename = RawPtrTraits<T>, typename = DefaultRefDerefTraits<T>> class Ref;


template<typename T, typename _PtrTraits, typename RefDerefTraits>
class SWIFT_ESCAPABLE_IF(T) Ref {
public:
    using PtrTraits = _PtrTraits;
    static constexpr bool isRef = true;

    ~Ref()
    {
    }

    Ref(T& object)
        : m_ptr(&object)
    {
    }

    Ref copyRef() && = delete;
    Ref copyRef() const & { return Ref(*m_ptr); }

    T& leakRef()
    {
        T& result = *PtrTraits::exchange(m_ptr, nullptr);
        return result;
    }

    T* _Nonnull take() const SWIFT_RETURNS_RETAINED SWIFT_RETURNS_INDEPENDENT_VALUE {
        return &copyRef().leakRef();
    }

private:
    enum AdoptTag { Adopt };
    Ref(T& object, AdoptTag)
        : m_ptr(&object)
    {
    }

    typename PtrTraits::StorageType m_ptr;
};

class FibonacciCalculatorCplusplus {
public:
    FibonacciCalculatorCplusplus(bool printInvocation);
    double fibonacci(double value) const;
    Ref<API::Array> getRef() const { return Ref(*API::Array::create()); }
private:
    bool printInvocation;
};
