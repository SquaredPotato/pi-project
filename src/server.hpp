#ifndef COLUMN_SERVER_HPP
#define COLUMN_SERVER_HPP

#include <boost/asio.hpp>
#include "connection.hpp"
#include "objectHandler.hpp"

using namespace boost::asio;

class server
{
public:
	explicit server(io_service& io, unsigned short port, objectHandler &handler) :
		acceptor_(io, ip::tcp::endpoint(ip::tcp::v4(), port))
	{
		handler_ = &handler;
		start_accept();
	};

	/*void stop();*/
private:
	void start_accept();
	void handle_accept(connection::pointer new_connection, const boost::system::error_code& error);

	objectHandler* handler_;

	ip::tcp::acceptor acceptor_;
};


#endif //COLUMN_SERVER_HPP
