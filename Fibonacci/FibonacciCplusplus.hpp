/*
See the LICENSE.txt file for this sample’s licensing information.

Abstract:
The C++ API.
*/

#pragma once
#include <utility>
#include <memory>

class FibonacciCalculatorCplusplus {
public:
    FibonacciCalculatorCplusplus(bool printInvocation);
    double fibonacci(double value) const;
private:
    bool printInvocation;
};

template<typename> class Function;


namespace Detail {

template<typename Out, typename... In>
class CallableWrapperBase {
public:
    virtual ~CallableWrapperBase() { }
    virtual Out call(In...) = 0;
};

template<typename, typename, typename...> class CallableWrapper;

template<typename CallableType, typename Out, typename... In>
class CallableWrapper : public CallableWrapperBase<Out, In...> {
public:
    explicit CallableWrapper(CallableType&& callable)
        : m_callable(std::move(callable)) { }
    CallableWrapper(const CallableWrapper&) = delete;
    CallableWrapper& operator=(const CallableWrapper&) = delete;
    Out call(In... in) final { return m_callable(std::forward<In>(in)...); }
private:
    CallableType m_callable;
};

} // namespace Detail

template<typename Out, typename... In> Function<Out(In...)> adopt(Detail::CallableWrapperBase<Out, In...>*);

template <typename Out, typename... In>
class Function<Out(In...)> {

public:
    using Impl = Detail::CallableWrapperBase<Out, In...>;

    Function() = default;
    Function(std::nullptr_t) { }

    template<typename CallableType, class = typename std::enable_if<!(std::is_pointer<CallableType>::value && std::is_function<typename std::remove_pointer<CallableType>::type>::value) && std::is_rvalue_reference<CallableType&&>::value>::type>
    Function(CallableType&& callable)
        : m_callableWrapper(std::make_unique<Detail::CallableWrapper<CallableType, Out, In...>>(std::forward<CallableType>(callable))) { }

    template<typename FunctionType, class = typename std::enable_if<std::is_pointer<FunctionType>::value && std::is_function<typename std::remove_pointer<FunctionType>::type>::value>::type>
    Function(FunctionType f)
        : m_callableWrapper(std::make_unique<Detail::CallableWrapper<FunctionType, Out, In...>>(std::forward<FunctionType>(f))) { }

    Out operator()(In... in) const
    {
        return m_callableWrapper->call(std::forward<In>(in)...);
    }

    explicit operator bool() const { return !!m_callableWrapper; }

    template<typename CallableType, class = typename std::enable_if<!(std::is_pointer<CallableType>::value && std::is_function<typename std::remove_pointer<CallableType>::type>::value) && std::is_rvalue_reference<CallableType&&>::value>::type>
    Function& operator=(CallableType&& callable)
    {
        m_callableWrapper = makeUnique<Detail::CallableWrapper<CallableType, Out, In...>>(std::forward<CallableType>(callable));
        return *this;
    }

    template<typename FunctionType, class = typename std::enable_if<std::is_pointer<FunctionType>::value && std::is_function<typename std::remove_pointer<FunctionType>::type>::value>::type>
    Function& operator=(FunctionType f)
    {
        m_callableWrapper = makeUnique<Detail::CallableWrapper<FunctionType, Out, In...>>(std::forward<FunctionType>(f));
        return *this;
    }

    Function& operator=(std::nullptr_t)
    {
        m_callableWrapper = nullptr;
        return *this;
    }

    Impl* leak()
    {
        return m_callableWrapper.release();
    }

private:
    enum AdoptTag { Adopt };
    Function(Impl* impl, AdoptTag)
        : m_callableWrapper(impl)
    {
    }

    friend Function adopt<Out, In...>(Impl*);

    std::unique_ptr<Impl> m_callableWrapper;
};

#define SWIFT_ESCAPABLE \
  __attribute__((swift_attr("Escapable")))

#define _CXX_INTEROP_STRINGIFY(_x) #_x

#define SWIFT_SHARED_REFERENCE(_retain, _release)                                \
  __attribute__((swift_attr("import_reference")))                          \
  __attribute__((swift_attr(_CXX_INTEROP_STRINGIFY(retain:_retain))))      \
  __attribute__((swift_attr(_CXX_INTEROP_STRINGIFY(release:_release))))

// Workaround for rdar://162361370
// (storing a WTF::Function inside a copyable, in this case ref-counted, type)
template<typename> class SWIFT_ESCAPABLE FunctionContainer;

template <typename Out, typename... In>
class SWIFT_ESCAPABLE FunctionContainer<Out(In...)> {
public:
    static FunctionContainer<Out(In...)>* create(Function<Out(In...)>&& fn) {
        return new FunctionContainer(std::move(fn));
    }

    Out call(In... in) const
    {
        return m_fn(std::forward<In>(in)...);
    }
    void ref() {  }
    void deref() {  }

private:
    FunctionContainer(Function<Out(In...)>&& fn) : m_fn(std::move(fn)) {}
    Function<Out(In...)> m_fn;
    // The following line requires rdar://160696723, so if it doesn't build,
    // you're probably not using a sufficiently recent swiftc.
} SWIFT_SHARED_REFERENCE(.ref, .deref);

struct WebBackForwardListCounts {
    uint32_t backCount { 0 };
    uint32_t forwardCount { 0 };
};


using CountsCompletionHandler = FunctionContainer<void(WebBackForwardListCounts&&)>;

