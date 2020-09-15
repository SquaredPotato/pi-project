#include "definitions.hpp"
#include "globals.hpp"

std::atomic<bool> STOP;

int main(int argc, char* argv[])
{
	try
	{
		STOP = false;

		std::cout << "Welcome to PiProject!" << std::endl;
		std::cout << "C++ version: " << __cplusplus << std::endl;

		std::cout << "Setting up" << std::endl;
		wiringPiSetup ();
		std::cout << "wiringPiSetup();\n" << std::endl;

		objectHandler handler = objectHandler();
		handler.init(&STOP);
		std::cout << "objectHandler\n" << std::endl;

		settings settings("config/config.xml");

//		run_test(&handler, &settings);

//		boost::thread poll(boost::bind(poll_loop, &handler, &settings));
		std::thread poll(poll_loop, &handler, &settings);

		poll.join();
	}
	catch (std::exception &e)
	{   std::cerr << e.what() << std::endl; }

	return 0;
}

int run_test(objectHandler* handler, settings* setting)
{
	std::cerr << "running test: single node, in/out-puts, groups, triggers, saving, loading";

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

	std::cerr << "Added in/out puts" << std::endl;

	unsigned int gID = (unsigned int) handler->createGroup("testgroup", INPUT);
	unsigned int sgID = (unsigned int) handler->createGroup("testgroup2", INPUT);
	handler->getGroup(sgID)->addPin(0, nID);
	handler->getGroup(gID)->addPin(1, nID);

	std::cerr << "Created groups" << std::endl;

	unsigned int tID = (unsigned int) handler->createTrigger("testtrigger");
	handler->getTrigger(tID)->addPin(7, nID);
	handler->getTrigger(tID)->addGroup(gID);
	handler->getTrigger(tID)->addGroup(sgID);

	handler->getTrigger(tID)->setGCond(1, AND);

	std::cerr << "Created triggers" << std::endl;

	if (!setting->save(*handler))
		std::cerr << "saving settings failed" << std::endl;

	std::cerr << "Saved settings" << std::endl;
	std::cout << handler->getTriggers().size() << std::endl;

	if (!setting->load(*handler, &STOP))
		std::cerr << "loading settings failed" << std::endl;

	std::cerr << "Loaded settings" << std::endl;

	std::cerr << "main.cpp: " << handler->getTriggers().size() << std::endl;

	handler->getTrigger(tID)->delPin(7, nID);
	handler->getTrigger(tID)->delGroup(gID);

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
	while (STOP == 0)
	{
		int ans;

		ask(strt, &ans);

		switch (ans)
		{
			case 0: // Stop
			{
				STOP = 1;
				sleep(1);
				break;
			}
			case 1: // Add node
			{
				std::string name, address;

				ask(eNam, &name);
				ask("Enter IP address: \n", &address);

				std::cout << "Node id: " << handler->createNode(name, address) << std::endl;
				break;
			}
			case 2: // Add input to node
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
			case 3: // Add output to node
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
			case 4: // Save settings
			{
				if (!setting->save(*handler))
					std::cerr << "saving settings failed" << std::endl;
				break;
			}
			case 5: // Load settings
			{
				try
				{
					if (!setting->load(*handler, &STOP))
						std::cerr << "loading settings failed" << std::endl;
				} catch (boost::archive::archive_exception &e)
				{
					std::cerr << "Error: loading settings failed: " << e.what() << std::endl;
				}

				break;
			}
			case 6: // Add group
			{
				std::string name;
				int mode;

				ask(eNam, &name);
				ask(eMod, &mode);

				handler->createGroup(name, mode);
				break;
			}
			case 7: // Add trigger
			{
				std::string name;

				ask(eNam, &name);

				try
				{
					std::cout << "Trigger ID: " << handler->createTrigger(name) << std::endl;
				}
				catch(std::exception &e)
				{
					std::cerr << "Error while creating trigger: " << e.what();
				}



				break;
			}
			case 8: // Add pin to trigger
			{
				int wpi;
				unsigned int nodeID, triggerID;

				ask(wiPi, &wpi);
				ask(nID, &nodeID);
				ask(tID, &triggerID);

				handler->getTrigger(triggerID)->addPin(wpi, nodeID);
				break;
			}
			case 99: // run test
			{
				run_test(handler, setting);
				break;
			}
			default:
			{
				std::cout << "please enter a number from 0 to 8" << std::endl;
				break;
			}
		}
	}
}

