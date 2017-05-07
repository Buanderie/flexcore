/*
 * stream_port.hpp
 *
 *  Created on: May 5, 2017
 *      Author: ckielwein
 */

#ifndef STREAMS_STREAMPORT_HPP_
#define STREAMS_STREAMPORT_HPP_

/**
 * Concepts:
 *
 * * stream_buffer is a (circular) buffer, which holds the stream
 * sole owner of all data.
 * * one source can be connected to multiple sinks (mpsc)
 * * the connection is stored in the source
 * * idea: buffer can be transfered / shared inside nodes
 * to minimize memory consumption
 *
 */

using size_type = int;

template<class T>
class stream_buffer {

public:

	//write access
	class iterator {

	};

	void consumed(iterator cursor);

	//read access
	class const_iterator {

	};

private:

	boost::circular_buffer<T> buffer;
};

template<class T>
class stream_source {
	//write interface for inside nodes

	auto begin();
	auto end();

	//read interface for outside connection

private:
	stream_buffer<T>& stream;
};

template<class T>
class stream_sink {
public:
	//read interface for inside the nodes
	struct reader {

		using iterator = typename stream_buffer<T>::const_iterator;

		explicit reader(stream_buffer<T>& s) noexcept
		: stream(s)
		{
		}

		iterator begin() noexcept {return cursor;}
		iterator end() const noexcept {return end_avail;}

		bool empty() const noexcept {
			return (end_avail - cursor) == 0;
		}

		~reader() noexcept {
			//tell buffer how many tokens we consumed
			stream.consumed(cursor);
		}

	private:
		stream_buffer<T>& stream;
		const iterator begin_avail;
		const iterator end_avail;
		iterator cursor {begin_avail};
	};

	reader read() noexcept;

	//write interface outside connections

private:
	stream_buffer<T>* stream;
}
;

#endif /* STREAMS_STREAMPORT_HPP_ */
