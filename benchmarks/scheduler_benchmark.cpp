#include <benchmark/benchmark.h>

#include <flexcore/scheduler/cyclecontrol.hpp>
#include <flexcore/scheduler/parallelregion.hpp>
#include <flexcore/extended/nodes/region_worker_node.hpp>
#include <flexcore/infrastructure.hpp>
#include "benchmarkfunctions.h"

#include <random>
#include <iostream>

// benchmnark of flexcore scheduler

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

void cyclecontrol(benchmark::State& state) {
	std::random_device rd;
	std::mt19937 gen(rd());

	fc::infrastructure infrastructure;

	auto fast_region = infrastructure.add_region(
			"first_region",
			fc::thread::cycle_control::fast_tick);
	auto medium_region = infrastructure.add_region(
			"second_region",
			fc::thread::cycle_control::medium_tick);
	auto slow_region = infrastructure.add_region(
			"third_region",
			fc::thread::cycle_control::slow_tick);


	auto& child_a = infrastructure.node_owner().
			make_child_named<counter>(fast_region, "a");
	auto& child_b = infrastructure.node_owner().
			make_child_named<counter>(medium_region, "b");
	auto& child_c = infrastructure.node_owner().
			make_child_named<counter>(slow_region, "c");

	while (state.KeepRunning()) {

		infrastructure.start_scheduler();
		while(true){
			const auto nr_of_slow_cycles = state.range(0) * 1000;
			if(child_a.count  >= nr_of_slow_cycles*100 &&
					child_b.count >= nr_of_slow_cycles*10 &&
					child_c.count >= nr_of_slow_cycles){

				infrastructure.stop_scheduler();
				break;
			}
		}
	}
}


BENCHMARK(cyclecontrol)
	->RangeMultiplier(2)->Range(1, 8)->UseRealTime();
BENCHMARK_MAIN()

