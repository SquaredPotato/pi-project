
#include "connection.hpp"

using namespace boost::asio;

connection::pointer connection::create(io_service &io_service)
{   return pointer(new connection(io_service)); }

ip::tcp::socket & connection::socket()
{   return shared_from_this()->socket_; }

void connection::start(objectHandler *handler_)
{
	streambuf sb;
	boost::system::error_code err;

	shared_from_this()->handler = handler_;

	std::cout << "Connection accepted\n" << std::endl;

	// Read request
	async_read(shared_from_this()->socket_,
	           shared_from_this()->strbuf,
	           boost::bind(&connection::handle_receive, shared_from_this()));

	async_write(shared_from_this()->socket_,
	            shared_from_this()->response_,
	            boost::bind(&connection::handle_write, shared_from_this()));
}

void connection::handle_write()
{   std::cout << "write completed" << std::endl;    }

void connection::handle_receive()
{
	// Serialization object
	std::ostringstream ostr;
	boost::archive::text_oarchive oarch(ostr);

	// Put payload in buffer
	read(shared_from_this()->socket_,
	     shared_from_this()->strbuf);

	// Place payload in string
	std::string packet = shared_from_this()->make_string(&shared_from_this()->strbuf),
				empty = "///";

	// Unpack header and data
	std::string opcode          = packet.substr(0, 2),
				specifier       = packet.substr(3, 5),
				subSpecifier    = packet.substr(6, 8),
				detail          = packet.substr(9, 11),
				data;

	// If it comes with data, load that in too
	if (packet.length() > 11)
	{   data = packet.substr(12, packet.length() - 1);  }

	std::cout << shared_from_this()->socket_.remote_endpoint().address() << std::endl;

	if (opcode == "cls")
	{   this->socket_.close();  }
	else if (opcode == "err")
	{
		// TODO: Implement error handling
	}
	else if (opcode == "set")
	{
		if (!data.empty())
		{
			std::istringstream istr(data);
			boost::archive::text_iarchive iarch(istr);

			if (specifier == "lID")
			{   shared_from_this()->handler->lID = std::stoi(data, nullptr);    }
			else if (specifier == "nod")
			{
				// TODO: Deserialize node and add it to handler
			}
		}
	}
	else if (opcode == "get")
	{
		//! All responses to a get MUST be a set
		opcode = "set";

		// TODO: Error handling when getting non-existing emelements

		if (specifier == "all")
		{
			oarch << shared_from_this()->handler->getGroups()
			      << shared_from_this()->handler->getNodes()
			      << shared_from_this()->handler->getTriggers();

			subSpecifier = empty;
			detail = empty;
		}
		else if (specifier == "nod")
		{
			if (subSpecifier == empty)
			{   oarch << shared_from_this()->handler->getNodes();   }
			else
			{   oarch << shared_from_this()->handler->getNode((unsigned int)strtol(subSpecifier.c_str(), nullptr, 0));  }
		}
		else if (specifier == "grp")
		{
			if (subSpecifier == empty)
			{   oarch << shared_from_this()->handler->getGroups();  }
			else
			{   oarch << shared_from_this()->handler->getGroup((unsigned int)strtol(subSpecifier.c_str(), nullptr, 0)); }
		}
		else if (specifier == "trg")
		{
			if (subSpecifier == empty)
			{   oarch << shared_from_this()->handler->getTriggers();    }
			else
			{   oarch << shared_from_this()->handler->getTrigger((unsigned int)strtol(subSpecifier.c_str(), nullptr, 0));   }
		}
		else if (specifier == "pin")
		{
			if (subSpecifier == empty)
			{   oarch << shared_from_this()->handler->getNode(shared_from_this()->handler->getlId())->}
		}

		data = ostr.str();
	}


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
