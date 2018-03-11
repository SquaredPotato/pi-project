#include <boost/bind.hpp>
#include "server.hpp"

using namespace boost::asio;

void server::start_accept()
{
	connection::pointer new_connection = connection::create(this->acceptor_.get_io_service());

	this->acceptor_.async_accept(new_connection->socket(),
	                             boost::bind(&server::handle_accept, this, new_connection,
	                             boost::asio::placeholders::error));

	std::cout << "start accept done\n" << std::endl;
}

void server::handle_accept(connection::pointer new_connection, const boost::system::error_code &error)
{
	std::cout << "handle_accept\n" << std::endl;

	if (!error)
	{   new_connection->start(this->handler_);  }

	this->start_accept();
}





/*void server::stop ()
{
	this->work.reset();
}*/

