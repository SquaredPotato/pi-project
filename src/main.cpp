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
		std::cout << "objectHandler\n" << std::endl;

		settings settings("/home/pi/projects/pi-project/config/groups.cfg", "/home/pi/projects/pi-project/config/nodes.cfg");
		std::cout << "settings\n" << std::endl;
		if (handler.load_settings(&settings) == 0)
		{
			std::cout << "strings\n" << std::endl;
			std::string ans, ip;
			std::cout << "Loading settings failed, do you want to start the program anyway? [y/n]" << std::endl;
			std::cin >> ans;
			if (ans == "n") return 0;
		}

		boost::thread t(run_test);

		std::cout << "test" << std::endl;

		sleep(300);
		t.join();
//		poll_loop(handler);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}

void run_test(/*const std::string &host*/)
{
	std::string host = "192.168.2.2";
	std::cout << "running test\n" << std::endl;

	boost::asio::io_service io;
	boost::asio::io_service::work work(io);

	server server(io, 13370, );
//	client client(io, host, 13370);
	io.run();
}

void poll_loop(objectHandler &handler)
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
				break;
			}
			case 1:
			{
				std::string name, address;
				std::cout << eNam;
				std::cin >> name;
				std::cout << "Enter IP address: " << std::endl;
				std::cin >> address;
				handler.createNode(name, address);
			}
			case 2:
			{
				int wpi, pud, edge, node;
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

				handler.getNode(node)->add_input((unsigned long) wpi, edge, pud, name);
			}
			case 3:
			{
				int wpi, state, node;
				std::string name;
				std::cout << nID;
				std::cin >> node;
				std::cout << wiPi;
				std::cin >> wpi;
				std::cout << "Enter initial state: (low: 0, high: 1)" << std::endl;
				std::cin >> state;
				std::cout << eNam;
				std::cin >> name;

				handler.getNode(node)->add_output(wpi, state, name);
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
