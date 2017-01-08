/*
 * assert.cpp
 *
 *  Created on: Jan 8, 2017
 *      Author: ckielwein
 */

#include "assert.hpp"

namespace fc
{
void assert::set_failure_handler(assert::handler_t h)
{
	assert::handler = h;
}

assert::handler_t failure_handler()
{
	return assert::handler;
}
assert::handler = &assert::fail_abort;

}
