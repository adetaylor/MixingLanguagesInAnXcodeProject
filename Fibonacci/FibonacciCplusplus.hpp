/*
See the LICENSE.txt file for this sample’s licensing information.

Abstract:
The C++ API.
*/

#pragma once
#import <memory>
#import <utility>
#import <swift/bridging>

class FibonacciCalculatorCplusplus {
public:
    FibonacciCalculatorCplusplus(bool printInvocation);
    double fibonacci(double value) const;
private:
    bool printInvocation;
};


template<typename, typename, typename...> class CallableWrapper;

template<typename CallableType, typename Out, typename... In>
class CallableWrapper {
public:
    explicit CallableWrapper(CallableType&& callable)
        : m_callable(WTFMove(callable)) { }
    CallableWrapper(const CallableWrapper&) = delete;
    virtual ~CallableWrapper() { }
private:
    CallableType m_callable;
};

template<typename> class Function;

template <typename Out, typename... In>
class Function<Out(In...)> {
public:
    using Impl = CallableWrapper<Out, In...>;

    template<typename FunctionType, class = typename std::enable_if<std::is_pointer<FunctionType>::value && std::is_function<typename std::remove_pointer<FunctionType>::type>::value>::type>
    Function(FunctionType f)
        : m_callableWrapper(makeUnique<CallableWrapper<FunctionType, Out, In...>>(std::forward<FunctionType>(f))) { }

private:
    Function(Impl* _Nonnull impl)
        : m_callableWrapper(impl)
    {
    }

    std::unique_ptr<Impl> m_callableWrapper;
};

struct SomeInput {
    int value;
};

using InputTest = Function<bool (SomeInput&)>;

inline void callFunctionyThing(InputTest&& test) {
    
}

// Workaround for rdar://162361370
// (storing a WTF::Function inside a copyable, in this case ref-counted, type)
template<typename> class FunctionContainer;

template <typename Out, typename... In>
class FunctionContainer<Out(In...)>  {
public:
    FunctionContainer(Function<Out(In...)>&& fn) : m_fn(fn) {}

    Out call(In... in) const
    {
        return m_fn(std::forward<In>(in)...);
    }

private:
    Function<Out(In...)> m_fn;
} SWIFT_SHARED_REFERENCE(funcContainerRetain, funcContainerRelease);

template <typename Out, typename... In>
inline void funcContainerRetain(FunctionContainer<Out(In...)>* _Nonnull o) {
    
}

template <typename Out, typename... In>
inline void funcContainerRelease(FunctionContainer<Out(In...)>* _Nonnull o) {
    
}

using InputTestContainer = FunctionContainer<bool (SomeInput&)>;

