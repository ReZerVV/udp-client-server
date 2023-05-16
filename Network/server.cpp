#include "Server.h"

#pragma warning(disable: 4996)

namespace Net
{
	Server::Server(std::string ip_address, int32_t port)
		:
		wsa_data{ 0 },
		server_socket(INVALID_SOCKET),
		ip_address(ip_address),
		port(port),
		info{ 0 },
		info_length(sizeof(info)) {}

	Server::~Server()
	{
		WSACleanup();
		closesocket(server_socket);
	}
	
	void Server::initialize()
	{
		info.sin_family = AF_INET;
		info.sin_port = htons(port);
		// info.sin_addr.s_addr = inet_addr(ip_address.c_str());
		inet_pton(AF_INET, ip_address.c_str(), &info.sin_addr.s_addr);

		assert(!WSAStartup(MAKEWORD(2,2), &wsa_data));
		assert(!((server_socket = socket(AF_INET, SOCK_DGRAM, 0)) == SOCKET_ERROR));
		assert(!(bind(server_socket, (struct sockaddr*)&info, info_length)));
		
		printf("Initialization server success.\n");
		printf("Server start at:[%s:%d]\n", inet_ntoa(info.sin_addr), htons(port));
	}

	void Server::start()
	{
		initialize();

		for (;;)
		{
			receive();
			proccess();
			send();
		}
	}
	
	void Server::receive()
	{
		if ((recv_length = recvfrom(server_socket, buffer, SIZE, 0, (struct sockaddr*)&info, &info_length)) == SOCKET_ERROR)
		{
			printf("Error::%d\n", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
	}

	void Server::proccess()
	{
		printf("Packet from:[%s:%d]:\t", inet_ntoa(info.sin_addr), htons(port));
		for (unsigned i = 0; i < recv_length; ++i)
		{
			printf("%c", buffer[i]);
		}
		printf("\n");
	}

	void Server::send()
	{
		if ((sendto(server_socket, buffer, recv_length, 0, (struct  sockaddr*)&info, info_length)) == SOCKET_ERROR)
		{
			printf("Error::%d\n", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
	}
	
	void Server::stop() {}
}