#ifndef COLUMN_SERVER_HPP
#define COLUMN_SERVER_HPP

#include <boost/asio.hpp>
#include <iostream>

#include "../src/group.hpp"
#include "../src/node.hpp"
#include "../src/objectHandler.hpp"

using boost::asio::ip::tcp;

class server
{
public:
	explicit server (unsigned short port, objectHandler *handler);
	bool discoverMaster();
private:
	unsigned short port;
	objectHandler *handler;

	boost::asio::streambuf input_buffer;

	void start();
};


#endif //COLUMN_SERVER_HPP
