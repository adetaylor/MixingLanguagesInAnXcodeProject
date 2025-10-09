/*
See the LICENSE.txt file for this sample’s licensing information.

Abstract:
The C++ API.
*/

#pragma once
#include <swift/bridging>
#include <optional>

class FibonacciCalculatorCplusplus {
public:
    FibonacciCalculatorCplusplus(bool printInvocation);
    double fibonacci(double value, int bonus=0) const;
private:
    bool printInvocation;
};

struct FrameState{};

struct WebPageProxyIdentifier{};

struct FrameIdentifier {};

class BrowsingContextGroup {};

template<typename T>
class Ref {
public:
    T item;
};

class WebBackForwardListItem {
public:
    static Ref<WebBackForwardListItem> create(Ref<FrameState>&&, WebPageProxyIdentifier, std::optional<FrameIdentifier>, BrowsingContextGroup* _Nullable = nullptr);
}  SWIFT_SHARED_REFERENCE(refBackForwardListItem, derefBackForwardListItem);


inline void refBackForwardListItem(WebBackForwardListItem* _Nonnull obj)
{
    
}

inline void derefBackForwardListItem(WebBackForwardListItem* _Nonnull obj)
{
    
}

using RefFrameState = Ref<FrameState>;
