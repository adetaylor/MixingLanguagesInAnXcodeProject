/*
See the LICENSE.txt file for this sample’s licensing information.

Abstract:
The C++ API.
*/

#pragma once
#import <memory>
#import <utility>

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
    
    template<typename CallableType, class = typename std::enable_if<!(std::is_pointer<CallableType>::value && std::is_function<typename std::remove_pointer<CallableType>::type>::value) && std::is_rvalue_reference<CallableType&&>::value>::type>
    Function(CallableType&& callable)
        : m_callableWrapper(makeUnique<CallableWrapper<CallableType, Out, In...>>(std::forward<CallableType>(callable))) { }

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

template <typename Out, typename... In>
class FunctionContainer  {
public:
    
    template<typename CallableType, class = typename std::enable_if<!(std::is_pointer<CallableType>::value && std::is_function<typename std::remove_pointer<CallableType>::type>::value) && std::is_rvalue_reference<CallableType&&>::value>::type>
    FunctionContainer(CallableType&& callable)
        : m_fn(Function(std::forward<CallableType>(callable))) { }

    Out call(In... in) const
    {
        return m_fn(std::forward<In>(in)...);
    }
    void ref() {
    }
    void deref() {}

private:
    Function<Out(In...)> m_fn;
} SWIFT_SHARED_REFERENCE(.ref, .deref);


using InputTestContainer = FunctionContainer<bool,SomeInput&>;
