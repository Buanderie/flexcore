#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(stream_ports)

namespace {
class test_node {
public:
	void process() {


	}

	stream_sink<int> input;
	stream_source<int> output;
};
}

// This test shows how to send events between nodes in flexcore.
BOOST_AUTO_TEST_CASE(test_basic_node) {

}

BOOST_AUTO_TEST_SUITE_END()
