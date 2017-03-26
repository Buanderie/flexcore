#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <thread>

#include <flexcore/extended/base_node.hpp>
#include <flexcore/extended/nodes/region_worker_node.hpp>
#include <flexcore/ports.hpp>
#include <flexcore/infrastructure.hpp>

#include <boost/scope_exit.hpp>

using namespace fc;

struct counter : fc::region_worker_node
{
	explicit counter(const fc::node_args& node)
		: region_worker_node(
				[this](){ ++count; },
				node)
	{
	}

	std::atomic<int> count{0};
};

int main()
{
	const auto nr_of_slow_cycles =  10000;
	infrastructure infra;

	auto fast_region = infra.add_region(
			"first_region",
			fc::thread::cycle_control::fast_tick);
	auto medium_region = infra.add_region(
			"second_region",
			fc::thread::cycle_control::medium_tick);
	auto slow_region = infra.add_region(
			"third_region",
			fc::thread::cycle_control::slow_tick);


	auto& child_a = infra.node_owner().
			make_child_named<counter>(fast_region, "a");
	auto& child_b = infra.node_owner().
			make_child_named<counter>(medium_region, "b");
	auto& child_c = infra.node_owner().
			make_child_named<counter>(slow_region, "c");

	infra.start_scheduler();
	while(!(child_a.count  >= nr_of_slow_cycles*100 &&
				child_b.count >= nr_of_slow_cycles*10 &&
				child_c.count >= nr_of_slow_cycles))
		{

		}
	infra.stop_scheduler();
	return 0;
}
