/*
See the LICENSE.txt file for this sample’s licensing information.

Abstract:
The C++ API.
*/

#pragma once
#include <cstdint>
#include <limits>
#include <algorithm>

class FibonacciCalculatorCplusplus {
public:
    FibonacciCalculatorCplusplus(bool printInvocation);
    double fibonacci(double value) const;
private:
    bool printInvocation;
};

struct WebPageProxyIdentifierType;

template<typename T>
class ObjectIdentifierGeneric {
public:
    explicit constexpr ObjectIdentifierGeneric(uint64_t identifier)
        : m_identifier(identifier)
    {
    }
    using RawValue = uint64_t;

    RawValue toRawValue() const { return m_identifier; }

private:
    RawValue m_identifier { 0 };

};

template<typename T> using ObjectIdentifier = ObjectIdentifierGeneric<T>;

using WebPageProxyIdentifier = ObjectIdentifier<WebPageProxyIdentifierType>;

inline WebPageProxyIdentifier getWPPI() { return WebPageProxyIdentifier(3); }

// operator== A

template<typename T>
bool operator==(const ObjectIdentifierGeneric<T>& a, const ObjectIdentifierGeneric<T>& b)
{
    return a.toRawValue() == b.toRawValue();
}

// operator== B

//inline bool operator==(const WebPageProxyIdentifier& a, const WebPageProxyIdentifier& b) {
//    return a.toRawValue() == b.toRawValue();
//}

inline bool wppisMatch(const WebPageProxyIdentifier& a, const WebPageProxyIdentifier& b) {
    return a == b;
}
