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

	class Client
	{
	private:
		WSADATA		wsa_data;
		SOCKET		client_socket;
		std::string ip_address;
		std::string message;
		int32_t		port;
		char		buffer[SIZE];
		sockaddr_in info;
		int			info_length;
		int			recv_length;
	public:
		Client(std::string ip_address, int32_t port);
		~Client();
	public:
		void connect();
	private:
		void initialize();
		void receive();
		void proccess();
		void send();
	};

}