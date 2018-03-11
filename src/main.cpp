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
	{   std::cerr << e.what() << std::endl; }

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

	if (!setting->load(handler, &stop))
		std::cerr << "loading settings failed" << std::endl;

	std::cout << "test completed" << std::endl;
	return 1;
}

template <class T>
void ask(const std::string &question, T* response)
{
	std::cout << question << std::endl;
	std::cin >> *response;
}

// User interaction lol
void poll_loop(objectHandler *handler, settings* setting)
{
	std::cout << "Poll loop was activated!" << std::endl;
	while (stop == 0)
	{
		int ans;

		ask(strt, &ans);

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

				ask(eNam, &name);
				ask("Enter IP address: \n", &address);

				std::cout << "Node id: " << handler->createNode(name, address) << std::endl;
				break;
			}
			case 2:
			{
				int wpi, pud, edge;
				unsigned int node;
				std::string name;

				ask(nID, &node);
				ask(wiPi, &wpi);
				ask(pupd, &pud);
				ask(iedg, &edge);
				ask(eNam, &name);

				handler->getNode(node)->add_input(wpi, edge, pud, name);
				break;
			}
			case 3:
			{
				int wpi, state;
				unsigned int node;
				std::string name;

				ask(nID, &node);
				ask(wiPi, &wpi);
				ask("Enter initial state: (low: 0, high: 1)\n", &state);
				ask(eNam, &name);

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
				if (!setting->load(handler, &stop))
					std::cerr << "loading settings failed" << std::endl;
				break;
			}
			case 6:
			{
				std::string name;
				int mode;

				ask(eNam, &name);
				ask(eMod, &mode);

				handler->createGroup(name, mode);
				break;
			}
			case 7:
			{
				std::string name;

				ask(eNam, &name);

				std::cout << "Trigger ID: " << handler->createTrigger(name) << std::endl;
				break;
			}
			case 8:
			{
				int wpi;
				unsigned int nodeID, triggerID;

				ask(wiPi, &wpi);
				ask(nID, &nodeID);
				ask(tID, &triggerID);

				handler->getTrigger(triggerID)->addPin(wpi, nodeID);
				break;
			}
			default:
			{
				std::cout << "please enter 0 or 1" << std::endl;
				break;
			}
		}
	}
}

