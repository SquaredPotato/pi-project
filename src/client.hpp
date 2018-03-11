#ifndef COLUMN_CLIENT_HPP
#define COLUMN_CLIENT_HPP

#include <boost/asio/ip/tcp.hpp>

using namespace boost::asio;

class client
{
public:
	client(io_service& io, const std::string& host, unsigned short port) :
		socket_(io),
		endpoint_(ip::address::from_string(host), port)
	{
		start();
	}


private:
	void start();

	ip::tcp::endpoint endpoint_;
	ip::tcp::socket socket_;
};


#endif //COLUMN_CLIENT_HPP
