/*
 * test_types.cpp
 *
 *  Created on: Jan 23, 2017
 *      Author: ckielwein
 */

#include <boost/test/unit_test.hpp>

#include <flexcore/test_types.hpp>

BOOST_AUTO_TEST_SUITE(testing_types)

BOOST_AUTO_TEST_CASE(test_integrals)
{
	fc::int_value a{1};
	fc::int_value b{a};
	fc::int_value c;

	a = b;

	BOOST_CHECK(a==b);
	BOOST_CHECK(sizeof(a) == sizeof(int));

	c = std::move(b);
	BOOST_CHECK(a==c);
}

BOOST_AUTO_TEST_SUITE_END()
