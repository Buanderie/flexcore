/*
 * assert.hpp
 *
 *  Created on: Jan 7, 2017
 *      Author: ckielwein
 */

#ifndef FLEXCORE_UTILS_ASSERT_HPP_
#define FLEXCORE_UTILS_ASSERT_HPP_

/**
 * Custom Assert Macros
 *
 * These macros and classes are used inside flexcore,
 * but they can also be used without it, as they carry no dependencies.
 *
 * The general idea is heavily inspired by bloombergs assert library bsl_assert.
 * The bloomberg assert library was designed by John Lakos and can be found here:
 * https://github.com/bloomberg/bde
 */

#ifndef ASSERT_LEVEL
	#define ASSERT_LEVEL ASSERT_LEVEL_DEFAULT
#endif

#define ASSERT_LEVEL_SAFE 1
#define ASSERT_LEVEL_DEFAULT 2
#define ASSERT_LEVEL_OPT 3
#define ASSERT_LEVEL_OFF 4

extern void fc_assert_fail (const char* assertion,
		const char* file,
		unsigned int line,
		const char* function)
     __attribute__ ((__noreturn__));

#define ASSERT_IMPL(expr) ((expr)				\
	? static_cast<void>(0)						\
	: fc_assert_fail(#expr, __FILE__, __LINE__, __PRETTY_FUNCTION__))

#if ASSERT_LEVEL >= ASSERT_LEVEL_SAFE
	#define ASSERT_SAFE(expr) ASSERT_IMPL(expr)
#else
	#define ASSERT_SAFE(expr) (static_cast<void>(0))
#endif

#if ASSERT_LEVEL >= ASSERT_LEVEL_DEFAULT
	#define ASSERT(expr) ASSERT_IMPL(expr)
#else
	#define ASSERT(expr) (static_cast<void>(0))
#endif

#if ASSERT_LEVEL >= ASSERT_LEVEL_OPT
	#define ASSERT_OPT(expr) ASSERT_IMPL(expr)
#else
	#define ASSERT_OPT(expr) (static_cast<void>(0))
#endif

#define ASSUME(expr) \
		do { if (!(expr)) __builtin_unreachable(); } while (0)

#if ASSERT_LEVEL >= ASSERT_LEVEL_DEFAULT
	#define ASSERT_ASSUME(expr) ASSERT_IMPL(expr)
#else
	#define ASSERT_ASSUME(expr) ASSUME(expr)
#endif

#undef ASSERT_IMPL

namespace fc
{

class assert
{
public:
	typedef void (*handler_t)(const char*, const char*, int);

	static void set_failure_handler(handler_t h);
	static handler_t failure_handler();

	// out of the box handlers

	///The default handler, prints a "Assertion failed" message and aborts.
	// static void fail_abort()

	///Prints a stack trace leading to the assert and aborts.
	// static void fail_stack_trace()

	/**
	 * \brief throws a assert_failure exception, useful to negative-test asserts.
	 *
	 * We recommend, not to use this outside of unit_tests.
	 * Handling the exception might lead to undefined behavior.
	 */
	//static void fail_throw()

private:
	static handler_t handler;
};

}

#endif /* FLEXCORE_UTILS_ASSERT_HPP_ */
