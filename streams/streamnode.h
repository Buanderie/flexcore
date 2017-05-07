/*
 * streamnode.h
 *
 *  Created on: May 6, 2017
 *      Author: ckielwein
 */

#ifndef STREAMS_STREAMNODE_H_
#define STREAMS_STREAMNODE_H_

namespace fc {
namespace streams {

class stream_node {
public:
	virtual ~stream_node() = default;

	virtual void Process() noexcept = 0;
private:

};

} /* namespace streams */
} /* namespace fc */

#endif /* STREAMS_STREAMNODE_H_ */
