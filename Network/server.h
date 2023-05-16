#pragma once

#include <winsock2.h>
#include <WinSock2.h>
#include <Ws2tcpip.h>
#include <stddef.h>
#include <string>
#include <cassert>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")


#define SIZE 1024
namespace Net
{

	class Server
	{
	private:
		WSADATA		wsa_data;
		SOCKET		server_socket;
		std::string ip_address;
		int32_t		port;
		char		buffer[SIZE];
		sockaddr_in info;
		int			info_length;
		int			recv_length;
	public:
		Server(std::string ip_address, int32_t port);
		~Server();
	public:
		void start();
		void stop();
	private:
		void initialize();
		void receive();
		void proccess();
		void send();
	};

}
