// Copyright 2015-2017 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/core/lightweight_test.hpp>
#include <boost/histogram/axis/size_type.hpp>
#include <limits>

using namespace boost::histogram::axis;

int main() {
  size_type s(0);
  BOOST_TEST_LT(s, 1);
  BOOST_TEST_LT(s, 1u);
  BOOST_TEST_GT(s, -1);
  BOOST_TEST_EQ(s, 0);
  BOOST_TEST_EQ(s, 0u);
  return boost::report_errors();
}
