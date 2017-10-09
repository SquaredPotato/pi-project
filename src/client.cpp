#include <iostream>
#include <boost/asio.hpp>
#include "client.hpp"

void client::start()
{
	std::cout << "Endpoint address: " << this->endpoint_.address() << "\n Enpoint port: " << this->endpoint_.port();

	try {
		this->socket_.connect(this->endpoint_);

		std::string msg = "test";
		this->socket_.write_some(boost::asio::buffer(msg, msg.size()));

		boost::asio::streambuf sb;
		boost::system::error_code err;

		boost::asio::read(this->socket_, sb);

		std::string response_ = {boost::asio::buffers_begin(sb.data()),
		                         boost::asio::buffers_end(sb.data())};

		std::cout << response_ << std::endl;

		msg = "close";
		this->socket_.write_some(boost::asio::buffer(msg, msg.size()));
		this->socket_.close();
		std::cout << "closed connection" << std::endl;
	} catch (std::exception &ex)
	{
		std::cerr << "An error has occured: " << ex.what() << std::endl;
	}

}