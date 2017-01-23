/*
 * test_types.hpp
 *
 *  Created on: Jan 23, 2017
 *      Author: ckielwein
 */

#ifndef FLEXCORE_TEST_TYPES_HPP_
#define FLEXCORE_TEST_TYPES_HPP_

#include <boost/operators.hpp>

template<bool, bool noexcept_move>
struct no_copy
{
	no_copy() = default;

	no_copy(const no_copy&) = delete;
	no_copy& operator=(const no_copy&) = delete;

	no_copy(no_copy&&) noexcept(noexcept_move) = default;
	no_copy& operator=(no_copy&&) noexcept(noexcept_move) = default;

};

template<bool noexept_copy, bool noexcept_move>
struct copy_move
{
	copy_move() = default;

	copy_move(const copy_move&) noexcept(noexept_copy) = default;
	copy_move& operator=(const copy_move&)  noexcept(noexept_copy) = default;

	copy_move(copy_move&&) noexcept(noexcept_move) = default;
	copy_move& operator=(copy_move&&) noexcept(noexcept_move) = default;
};

template<bool noexept_copy, bool noexcept_move>
struct no_assign
{
	no_assign() = default;

	no_assign(const no_assign&) noexcept(noexept_copy) = default;
	no_assign& operator=(const no_assign&) = delete;

	no_assign(no_assign&&) noexcept(noexcept_move) = default;
	no_assign& operator=(no_assign&&) = delete;
};

template<class T>
struct default_constructor : T
{
	explicit default_constructor(typename T::value_t v) : T(v) {}
	default_constructor() = default;
};

template<class T>
struct no_default_constructor : T
{
	explicit no_default_constructor(typename T::value_t v) : T(v) {}
	no_default_constructor() = delete;
};

namespace detail
{

int constexpr clipped_minus(int subtrahend, int subtrand)
{
	const int tmp = subtrahend - subtrand;
	if (tmp < 0)
		return 0;
	else return tmp;
}

template<int size>
struct padding_t
{
	char pad[size] = {0};
};

template<>
struct padding_t<0>
{
	//empty to allow empty base optimization in value::storage_t
};

} // detail namespace

template<class T, int size = sizeof(T)>
struct value : boost::ordered_euclidean_ring_operators<value<T>>
{
	explicit value(T t) : val(t) {}
	value() = default;

	using value_t = T;

	bool operator==(const value& o) const { return val.v == o.val.v; }
	bool operator<(const value& o) const { return val.v < o.val.v; }
	value& operator+=(const value& o)
	{
		val.v += o.val.v;
		return *this;
	}

	template<class padding>
	struct storage_t : padding
	{
		explicit storage_t(T v) : v(v) {}
		storage_t() : v() {}
		T v;
	};

	using storage = storage_t<
			detail::padding_t<detail::clipped_minus(size, sizeof(T))>>;

	storage val;
};

using small_value = value<char>;

template<class has_copy_constructor,
	template<class> class has_default_constructor,
	class value_t>
struct constructed :has_default_constructor<value_t>, has_copy_constructor
{
	using has_default_constructor<value_t>::has_default_constructor;
};

using integer = constructed<
		copy_move<true,true>,
		default_constructor,
		value<int>
		>;


#endif /* FLEXCORE_TEST_TYPES_HPP_ */
