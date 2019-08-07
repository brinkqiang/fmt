#pragma once
#include <iostream>
#include <typeinfo>

#include "dmformat.h"

// the type holding sequences
template <int... Ns>
struct sequence {};

// First define the template signature
template <int... Ns>
struct seq_gen;

// forward extend recursively
template <int I, int... Ns>
struct seq_gen<I, Ns...> {
    // Take front most number of sequence,
    // decrement it, and prepend it twice.
    // First I - 1 goes into the counter,
    // Second I - 1 goes into the sequence.
    using type = typename seq_gen<I - 1, I - 1, Ns...>::type;
};

// Recursion abort
template <int... Ns>
struct seq_gen<0, Ns...> {
    using type = sequence<Ns...>;
};

template <int N>
using sequence_t = typename seq_gen<N>::type;



//////////////////////////////////////////////////////////////////////////

template <typename... Args>
struct STuple{

    //virtual void print() = 0;
};

template <>
struct STuple<>{
    virtual void print() = 0;
};

//template <typename First, typename... Rest>
//struct STuple<First, Rest...>
//    :public STuple<Rest...>
//{
//    STuple() :value() {}
//    STuple(First&& first, Rest&&... rest)
//        :value(std::forward<First>(first)),
//        STuple<Rest...>(std::forward<Rest>(rest)...) {}
//    First value;
//};

template <typename First, typename... Rest>
struct STuple<First, Rest...>
    :public STuple<Rest...>
{
    STuple() :value() {}
    STuple(First&& first, Rest&&... rest)
        :value(std::forward<First>(first)),
        STuple<Rest...>(std::forward<Rest>(rest)...) {}

    //virtual void print()
    //{
    //    //print_impl(*this, std::make_index_sequence<sizeof...(Rest) + 1>());
    //    //invoke_impl([](const auto&... args) {
    //    //    fmt::print(args...);
    //    //}, *this, std::make_index_sequence<sizeof...(Rest) + 1>());
    //}

    size_t size() { return sizeof...(Rest); }

    typename std::enable_if<std::is_arithmetic<First>::value, First>::type value;
};

template <typename... Rest>
struct STuple<std::string, Rest...>
    :public STuple<Rest...>
{
    STuple() :value(0) {}
    STuple(const std::string& str, Rest&&... rest)
        :STuple<Rest...>(std::forward<Rest>(rest)...)
    {
        value = new char[str.length() + 1];
        memcpy(value, str.c_str(), str.length());
        value[str.length()] = 0;
    }

    virtual void print()
    {
        //print_impl(*this, std::make_index_sequence<sizeof...(Rest) + 1>());
        print_impl_ex(*this, sequence_t<sizeof...(Rest) + 1>());
    }

    size_t size() { return sizeof...(Rest); }
    char* value;
};

template <size_t N, typename STP> struct STupleElement;

template <typename T, typename... Rest>
struct STupleElement<0, STuple<T, Rest...>>
{
    typedef T type;
    typedef STuple<T, Rest...> STPType;
};

template <typename... Rest>
struct STupleElement<0, STuple<std::string, Rest...>>
{
    typedef char* type;
    typedef STuple<std::string, Rest...> STPType;
};

template <size_t N, typename T, typename... Rest>
struct STupleElement<N, STuple<T, Rest...>>
    :public STupleElement<N-1, STuple<Rest...>>{};

template <size_t N, typename... Rest>
typename STupleElement<N, STuple<Rest...>>::type& get(STuple<Rest...> &stp) {
    typedef typename STupleElement<N, STuple<Rest...>>::STPType type;
    return ((type &)stp).value;
}

//template<typename... Rest, size_t... I>
//void print_impl(STuple<Rest...> &stp, std::index_sequence<I...>)
//{
//    fmt::print(get<I>(stp)...);
//}


template<typename... Rest, int... I>
void print_impl_ex(STuple<Rest...> &stp, sequence<I...>)
{
    fmt::print(get<I>(stp)...);
}

//template<typename F, typename T, size_t... I>
//void invoke_impl(F f, T& t, std::index_sequence<I...>)
//{
//    f(get<I>(t)...);
//}


//auto print_message = [](const auto&... args) {
//    fmt::print(args...);
//};

//template <typename... Rest>
//void test_format(STuple<Rest...> &stp)
//{
//    invoke_impl([](const auto&... args) {
//    }, stp, std::make_index_sequence<sizeof...(Rest)>());
//}
