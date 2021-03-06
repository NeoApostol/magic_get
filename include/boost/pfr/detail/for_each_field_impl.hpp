// Copyright (c) 2016 Antony Polukhin
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PFR_DETAIL_FOR_EACH_FIELD_IMPL_HPP
#define BOOST_PFR_DETAIL_FOR_EACH_FIELD_IMPL_HPP

#include <utility>      // metaprogramming stuff

#include <boost/pfr/detail/sequence_tuple.hpp>

namespace boost { namespace pfr { namespace detail {

template <class T, class F, class I, class = decltype(std::declval<F>()(std::declval<T>(), I{}))>
void for_each_field_impl(T&& v, F&& f, I i, long) {
    std::forward<F>(f)(std::forward<T>(v), i);
}

template <class T, class F, class I>
void for_each_field_impl(T&& v, F&& f, I /*i*/, int) {
    std::forward<F>(f)(std::forward<T>(v));
}

template <class T, class F, std::size_t... I>
void for_each_field_impl(T&& t, F&& f, std::index_sequence<I...>) {
     const int v[] = {(
         for_each_field_impl(sequence_tuple::get<I>(t), std::forward<F>(f), size_t_<I>{}, 1L),
         0
     )...};
     (void)v;
}

}}} // namespace boost::pfr::detail


#endif // BOOST_PFR_DETAIL_FOR_EACH_FIELD_IMPL_HPP
