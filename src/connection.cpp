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

void connection::start(objectHandler &handler)
{
	shared_from_this()->handler = handler;
	streambuf sb;
	boost::system::error_code err;

	std::cout << "Connection accepted\n" << std::endl;

	// Read header
	async_read(shared_from_this()->socket_,
	           shared_from_this()->opcode_,
				boost::bind(&connection::handle_receive, shared_from_this));

	async_write(shared_from_this()->socket_, shared_from_this()->response_,
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

	// Save first three bytes (opcode) as string to prevent repeated calls to make_string
	std::string opcode = shared_from_this()->make_string(shared_from_this()->opcode_);

	read(shared_from_this()->socket_,
	     shared_from_this()->specifier_);

	read(shared_from_this()->socket_,
		 shared_from_this()->subspecifier_);

	std::string specifier = shared_from_this()->make_string(shared_from_this()->specifier_);
	std::string subspecifier = shared_from_this()->make_string(shared_from_this()->subspecifier_);

	if (opcode == "cls")
	{
		shared_from_this()->socket_.close();
	}
	else if (opcode == "get")
	{
		if (specifier == "all")
		{
			oarch << shared_from_this()->handler.getGroups() << shared_from_this()->handler.getNodes();
			data = ostr.str();

			shared_from_this()->response = "setall000000" + data;
		}
		else if (specifier == "nod")
		{
			int nID = stoi(subspecifier);

			oarch << shared_from_this()->handler.getNode(nID);
			data = ostr.str();

			shared_from_this()->response = "setnde" + nID + data;
		}
		else if (specifier == "grp")
		{
			int gID = stoi(subspecifier);

			oarch << shared_from_this()->handler.getGroup(gID);
			data = ostr.str();

			shared_from_this()->response = "setgrp";
		}
		else if (specifier == "fID")
		{
			if (subspecifier == "nID")
			{
				// Get first available nodeID
				std::string id = std::to_string(shared_from_this()->handler.getFreeNID());

				shared_from_this()->response = "setlID000000" + id;
			}
			else;
		}
		else
		{
			// Invalid request
			shared_from_this()->response = "err003" + opcode + specifier + subspecifier;
		}
	}
	else if (opcode == "set")
	{
		int wpi = std::stoi(specifier);
		int nID = std::stoi(subspecifier);

		// TODO: Support this message, like local and non-local nodes to keep track and figure out group states.
		// TODO: This will likely require a change or addition in the protocol
		// TODO: Perhaps accept a custom message for this opcode
		shared_from_this()->response = "err004" + opcode + specifier + subspecifier;
		//shared_from_this()->handler.getNode(nID)->set_output_state(0);
	}
	else
	{
		// Invalid request
		shared_from_this()->response = "err003" + opcode + specifier + subspecifier;
	}

	std::cout << shared_from_this()->socket_.remote_endpoint().address() << std::endl;
}

void connection::write(std::string msg)
{
	async_write(shared_from_this()->socket_, buffer(msg, msg.size()),
	            boost::bind(&connection::handle_write, shared_from_this()));
}

std::string connection::make_string(boost::asio::streambuf& streambuf)
{
	return {boost::asio::buffers_begin(streambuf.data()),
	        boost::asio::buffers_end(streambuf.data())};
}