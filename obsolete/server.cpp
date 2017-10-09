#include <ifaddrs.h>
#include "server.hpp"
#include "../src/definitions.hpp"
#include <ifaddrs.h>

using namespace boost::asio;

server::server(unsigned short port, objectHandler *handler)
{
	this->port = port;
	this->handler = handler;
}

bool server::discoverMaster()
{
	// Get lan ip range
	struct ifaddrs *ifaddr, *ifa;
	int n, s, family;
	bool masterDetected = false;
	std::array<std::string, 255> clients;
	std::string ip;
	char host[NI_MAXHOST];

	if (getifaddrs(&ifaddr) == -1)
	{
		std::cerr << "This machine doesn't seem to support the iffaddr() function" << std::endl;
	}

	for (ifa = ifaddr, n = 0; ifa != nullptr; ifa = ifa->ifa_next, n ++)
	{
		if (ifa->ifa_addr == nullptr)
			continue;

		family = ifa->ifa_addr->sa_family;

		// Extract ip address
		if (family == AF_INET || family == AF_INET6)
		{
			s = getnameinfo(ifa->ifa_addr, (family == AF_INET) ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6), host, NI_MAXHOST, nullptr, 0, NI_NUMERICHOST);
		}
		if (s != 0)
		{
			std::cerr << "getnameinfo() failed: " << gai_strerror(s) << std::endl;
		}
		if ((ifa->ifa_name == "wlan0" || ifa->ifa_name == "eth0") && family == AF_INET)
		{
			// Change last 3 numbers of local ip to 0
			int dotCount = 0;
			for (int i = 0; host[i] != NULL; i ++)
			{
				if (dotCount == 3) host[i] = '0';
				if (host[i] == '.') dotCount ++;
			}
		}
	}

	io_service io;
	ip::tcp::socket socket(io);

	for (int i = 0; i < 255; i ++)
	{

		ip::tcp::endpoint end(ip::address::from_string(host), this->port);
	}
}

void server::start()
{
	int exc = 0;
	do
	{
		try
		{
			io_service io;
			ip::tcp::endpoint end(ip::tcp::v4(), this->port);
			ip::tcp::acceptor acc (io, ip::tcp::endpoint(ip::tcp::v4(), this->port));

			ip::tcp::socket socket(io);
			std::cout << "Waiting for connect" << std::endl;
			acc.accept(socket);

			std::cout << "Connection accepted from " << socket.remote_endpoint().address().to_string() << std::endl;

			streambuf sb;
			boost::system::error_code err;

			read(socket, sb, err);

			streambuf::const_buffers_type bufs = sb.data();
			std::string s(buffers_begin(bufs), buffers_begin(bufs) + sb.size());

			std::cout << "received: " << s << std::endl;
			if (s == "master")
			{
				boost::system::error_code er;
				std::string msg = this->handler->master ? "true" : "false";

				std::array<char, msg.size()> buf;
				socket.write_some(boost::asio::buffer(buf, msg.size()), er);
			}
			break;
		}
		catch (std::exception &e)
		{
			std::cerr << "Something went wrong in the server class: " << e.what() << std::endl;
			std::cout << "trying to restart the server for " << 5 - exc << "more times" << std::endl;
			exc ++;
		}
	} while (exc < 5);
}
