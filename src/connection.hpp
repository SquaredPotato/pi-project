#ifndef COLUMN_CONNECTION_HPP
#define COLUMN_CONNECTION_HPP

#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/archive_exception.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/string.hpp>
#include <iostream>
#include <string>
#include "objectHandler.hpp"

using namespace boost::asio;

class connection : public boost::enable_shared_from_this<connection>
{
public:
	typedef boost::shared_ptr<connection> pointer;

	static pointer create(io_service& io_service);
	ip::tcp::socket& socket();

	void start(objectHandler *handler);

private:
	explicit connection(io_service& io_service_) :
			 socket_(io_service_) {};

	ip::tcp::socket socket_;

	streambuf strbuf;

	streambuf response_;

	objectHandler *handler;

	std::string make_string(streambuf *streambuf), response;

	void write(std::string msg);

	void handle_write();
	void handle_receive();
};


#endif //COLUMN_CONNECTION_HPP
