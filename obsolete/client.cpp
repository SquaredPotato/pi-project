#include <boost/asio.hpp>
#include <iostream>
#include "client.hpp"

using namespace boost::asio;

client::client(unsigned short port)
{
	this->port = port;
}

void client::send(const std::string &msg, const std::string &ip)
{
	int exc = 0;
	while (exc < 5)
	{
		try
		{
			io_service io;
			ip::tcp::endpoint end(ip::address::from_string(ip), this->port);
			ip::tcp::socket socket(io);

			socket.connect(end);

			boost::system::error_code er;

			// Prepare for sending by copying message into buffer
			std::array<char, msg.size()> buf{};
			std::copy(msg.begin(), msg.end(), buf.begin());

			socket.write_some(boost::asio::buffer(buf, msg.size()), er);
			socket.close();
			break;
		}
		catch (std::exception &e)
		{
			std::cerr << "Something went wrong in the client class: " << e.what() << std::endl;
			std::cout << "trying to resend message for " << 4 - exc << "more times" << std::endl;
			exc ++;
		}
	}
}