#include "definitions.hpp"

int main(int argc, char* argv[])
{
	try
	{
		std::cout << "Welcome to PiProject!" << std::endl;

		std::cout << "Setting up" << std::endl;
		wiringPiSetup ();
		std::cout << "wiringPiSetup();\n" << std::endl;

		objectHandler handler = objectHandler(&stop);
		std::cout << "objectHandler\n" << std::endl;

		settings settings("config/nodes.xml");
//		std::cout << "settings\n" << std::endl;
//		if (handler.load_settings(&settings) == 0)
//		{
//			std::cout << "strings\n" << std::endl;
//			std::string ans, ip;
//			std::cout << "Loading settings failed, do you want to start the program anyway? [y/n]" << std::endl;
//			std::cin >> ans;
//			if (ans == "n") return 0;
//		}

		run_test(&handler, &settings);

		boost::thread poll(boost::bind(poll_loop, &handler));
		poll.join();
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}

void run_test(objectHandler* handler, settings* setting)
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

	handler->save_settings(setting);
	handler->delTrigger(tID);
	handler->delNode(nID);
	handler->delGroup(gID);
	handler->delGroup(sgID);

	std::cout << handler->getGroups().size() << std::endl;

	if (handler->load_settings(setting) == 0)
	{
		std::cerr << "loading settings failed" << std::endl;
	}

	std::cout << handler->getGroups().size() << std::endl;
}

// User interaction lol
void poll_loop(objectHandler *handler)
{
	std::cout << "Poll loop was activated!" << std::endl;
	while (stop == 0)
	{
		int ans;
		std::cout << strt;
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
			}
			case 4:
			{

			}
			default:
			{
				std::cout << "please enter 0 or 1" << std::endl;
			}
		}
	}
}
