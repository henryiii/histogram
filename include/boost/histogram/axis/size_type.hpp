// Copyright 2018 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_AXIS_SIZE_TYPE_HPP
#define BOOST_HISTOGRAM_AXIS_SIZE_TYPE_HPP

#include <type_traits>

namespace boost {
namespace histogram {
namespace detail {
template <typename T, typename = std::enable_if_t<std::is_unsigned<T>::value>>
struct requires_unsigned {};
} // namespace detail
namespace axis {
class size_type {
public:
  constexpr explicit size_type(int v) noexcept : value(v) {}
  constexpr operator int() const noexcept { return value; }

  template <typename T, typename = detail::requires_unsigned<T>>
  constexpr friend bool operator<(size_type a, T b) noexcept {
    return a.value < 0 || static_cast<unsigned>(a.value) < b;
  }

  template <typename T, typename = detail::requires_unsigned<T>>
  constexpr friend bool operator>(size_type a, T b) noexcept {
    return a.value > 0 && static_cast<unsigned>(a.value) > b;
  }

  template <typename T, typename = detail::requires_unsigned<T>>
  constexpr friend bool operator<=(size_type a, T b) noexcept {
    return !(a > b);
  }

  template <typename T, typename = detail::requires_unsigned<T>>
  constexpr friend bool operator>=(size_type a, T b) noexcept {
    return !(a < b);
  }

  template <typename T, typename = detail::requires_unsigned<T>>
  constexpr friend bool operator==(size_type a, T b) noexcept {
    return a.value >= 0 && static_cast<unsigned>(a.value) == b;
  }

  template <typename T, typename = detail::requires_unsigned<T>>
  constexpr friend bool operator!=(size_type a, T b) noexcept {
    return !(a == b);
  }

private:
  int value;
};
} // namespace axis
} // namespace histogram
} // namespace boost
#endif
