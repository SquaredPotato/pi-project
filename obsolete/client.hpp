#ifndef COLUMN_CLIENT_HPP
#define COLUMN_CLIENT_HPP

#include <string>

class client
{
public:
	explicit client(unsigned short port);
	void send(const std::string &msg, const std::string &ip);

private:
	unsigned short port;

};

#endif //COLUMN_CLIENT_HPP
