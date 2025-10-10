/*
See the LICENSE.txt file for this sample’s licensing information.

Abstract:
The C++ API.
*/

#pragma once
#import <memory>
#import <utility>

class FibonacciCalculatorCplusplus {
public:
    FibonacciCalculatorCplusplus(bool printInvocation);
    double fibonacci(double value) const;
private:
    bool printInvocation;
};


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
        : m_callable(WTFMove(callable)) { }
    CallableWrapper(const CallableWrapper&) = delete;
    CallableWrapper& operator=(const CallableWrapper&) = delete;
    Out call(In... in) final { return m_callable(std::forward<In>(in)...); }
private:
    CallableType m_callable;
};


template<typename> class Function;

template<typename Out, typename... In> Function<Out(In...)> adopt(CallableWrapperBase<Out, In...>*);

template <typename Out, typename... In>
class Function<Out(In...)> {
public:
    using Impl = CallableWrapperBase<Out, In...>;

    Function() = default;
    Function(std::nullptr_t) { }

    template<typename CallableType, class = typename std::enable_if<!(std::is_pointer<CallableType>::value && std::is_function<typename std::remove_pointer<CallableType>::type>::value) && std::is_rvalue_reference<CallableType&&>::value>::type>
    Function(CallableType&& callable)
        : m_callableWrapper(makeUnique<CallableWrapper<CallableType, Out, In...>>(std::forward<CallableType>(callable))) { }

    template<typename FunctionType, class = typename std::enable_if<std::is_pointer<FunctionType>::value && std::is_function<typename std::remove_pointer<FunctionType>::type>::value>::type>
    Function(FunctionType f)
        : m_callableWrapper(makeUnique<CallableWrapper<FunctionType, Out, In...>>(std::forward<FunctionType>(f))) { }

    Out operator()(In... in) const
    {
        ASSERT(m_callableWrapper);
        return m_callableWrapper->call(std::forward<In>(in)...);
    }

    explicit operator bool() const { return !!m_callableWrapper; }

    template<typename CallableType, class = typename std::enable_if<!(std::is_pointer<CallableType>::value && std::is_function<typename std::remove_pointer<CallableType>::type>::value) && std::is_rvalue_reference<CallableType&&>::value>::type>
    Function& operator=(CallableType&& callable)
    {
        m_callableWrapper = makeUnique<CallableWrapper<CallableType, Out, In...>>(std::forward<CallableType>(callable));
        return *this;
    }

    template<typename FunctionType, class = typename std::enable_if<std::is_pointer<FunctionType>::value && std::is_function<typename std::remove_pointer<FunctionType>::type>::value>::type>
    Function& operator=(FunctionType f)
    {
        m_callableWrapper = makeUnique<CallableWrapper<FunctionType, Out, In...>>(std::forward<FunctionType>(f));
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

template<typename Out, typename... In> Function<Out(In...)> adopt(CallableWrapperBase<Out, In...>* impl)
{
    return Function<Out(In...)>(impl, Function<Out(In...)>::Adopt);
}

struct SomeInput {
    int value;
};

using InputTest = Function<bool (SomeInput&)>;
