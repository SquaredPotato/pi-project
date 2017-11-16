#include "connection.hpp"

using namespace boost::asio;

connection::pointer connection::create(io_service &io_service)
{
	return pointer(new connection(io_service));
}

ip::tcp::socket & connection::socket()
{
	return shared_from_this()->socket_;
}

void connection::start(objectHandler *handler_)
{
	streambuf sb;
	boost::system::error_code err;

	shared_from_this()->handler = handler_;

	std::cout << "Connection accepted\n" << std::endl;

	// Read header
	async_read(shared_from_this()->socket_,
	           shared_from_this()->strbuf,
	           boost::bind(&connection::handle_receive, shared_from_this()));

	async_write(shared_from_this()->socket_,
	            shared_from_this()->response_,
	            boost::bind(&connection::handle_write, shared_from_this()));
}

void connection::handle_write()
{
	std::cout << "write completed" << std::endl;
}

void connection::handle_receive()
{
	// Serialization object
	std::ostringstream ostr;
	boost::archive::text_oarchive oarch(ostr);

	std::string data;

	read(shared_from_this()->socket_,
	     shared_from_this()->strbuf);

	// Save first three bytes (opcode) as string to prevent repeated calls to make_string
	std::string opcode = shared_from_this()->make_string(&shared_from_this()->strbuf);

	std::cout << shared_from_this()->socket_.remote_endpoint().address() << std::endl;
}

void connection::write(std::string msg)
{
	async_write(shared_from_this()->socket_, buffer(msg, msg.size()),
	            boost::bind(&connection::handle_write, shared_from_this()));
}

std::string connection::make_string(streambuf *streambuf)
{
	return {boost::asio::buffers_begin(streambuf->data()),
	        boost::asio::buffers_end(streambuf->data())};
}
