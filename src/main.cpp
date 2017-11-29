#include "definitions.hpp"

int main(int argc, char* argv[])
{
	try
	{
		std::cout << "Welcome to PiProject!" << std::endl;

		std::cout << "Setting up" << std::endl;
		wiringPiSetup ();
		std::cout << "wiringPiSetup();\n" << std::endl;

		objectHandler handler = objectHandler();
		handler.init(&stop);
		std::cout << "objectHandler\n" << std::endl;

		settings settings("config/config.xml");

		boost::thread poll(boost::bind(poll_loop, &handler, &settings));
		poll.join();
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}

int run_test(objectHandler* handler, settings* setting)
{
//	std::string host = "192.168.2.2";
//	std::cout << "running test\n" << std::endl;
//
//	boost::asio::io_service io;
//	boost::asio::io_service::work work(io);
//
//	server server(io, TCP_PORT, handler);
//	client client(io, host, TCP_PORT);
//
//	boost::thread th(boost::bind(&boost::asio::io_service::run, &io));

	unsigned int nID = (unsigned int) handler->createNode("test", "localhost");

	handler->getNode(nID)->add_input(1, INT_EDGE_BOTH, PUD_OFF, "dist");
	handler->getNode(nID)->add_input(0, INT_EDGE_BOTH, PUD_DOWN, "DIP");
	handler->getNode(nID)->add_output(7, 0, "LED");

	unsigned int gID = (unsigned int) handler->createGroup("testgroup", INPUT);
	unsigned int sgID = (unsigned int) handler->createGroup("testgroup2", INPUT);
	handler->getGroup(sgID)->addPin(0, nID);
	handler->getGroup(gID)->addPin(1, nID);

	unsigned int tID = (unsigned int) handler->createTrigger("testtrigger");
	handler->getTrigger(tID)->addPin(7, nID);
	handler->getTrigger(tID)->addGroup(gID);
	handler->getTrigger(tID)->addGroup(sgID);

	handler->getTrigger(tID)->setGCond(1, AND);

	if (!setting->save(*handler))
		std::cerr << "saving settings failed" << std::endl;

	if (!setting->load(handler))
		std::cerr << "loading settings failed" << std::endl;

	std::cout << "test completed" << std::endl;
	return 1;
}

// User interaction lol
void poll_loop(objectHandler *handler, settings* setting)
{
	std::cout << "Poll loop was activated!" << std::endl;
	while (stop == 0)
	{
		int ans;
		std::cout << strt << std::endl;
		std::cin >> ans;
		switch (ans)
		{
			case 0:
			{
				stop = 1;
				sleep(1);
				break;
			}
			case 1:
			{
				std::string name, address;
				std::cout << eNam;
				std::cin >> name;
				std::cout << "Enter IP address: " << std::endl;
				std::cin >> address;
				handler->createNode(name, address);
				break;
			}
			case 2:
			{
				int wpi, pud, edge;
				unsigned int node;
				std::string name;
				std::cout << nID;
				std::cin >> node;
				std::cout << wiPi;
				std::cin >> wpi;
				std::cout << pupd;
				std::cin >> pud;
				std::cout << iedg;
				std::cin >> edge;
				std::cout << eNam;
				std::cin >> name;

				handler->getNode(node)->add_input(wpi, edge, pud, name);
				break;
			}
			case 3:
			{
				int wpi, state;
				unsigned int node;
				std::string name;
				std::cout << nID;
				std::cin >> node;
				std::cout << wiPi;
				std::cin >> wpi;
				std::cout << "Enter initial state: (low: 0, high: 1)" << std::endl;
				std::cin >> state;
				std::cout << eNam;
				std::cin >> name;

				handler->getNode(node)->add_output(wpi, state, name);
				break;
			}
			case 4:
			{
				if (!setting->save(*handler))
					std::cerr << "saving settings failed" << std::endl;
				break;
			}
			case 5:
			{
				if (!setting->load(handler))
					std::cerr << "loading settings failed" << std::endl;
				break;
			}
			default:
			{
				std::cout << "please enter 0 or 1" << std::endl;
			}
		}
	}
}

