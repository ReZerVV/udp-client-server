#include "client.h"

#pragma warning(disable: 4996)

namespace Net
{
	Client::Client(std::string ip_address, int32_t port)
		:
		wsa_data{ 0 },
		client_socket(INVALID_SOCKET),
		ip_address(ip_address),
		port(port),
		info{ 0 },
		info_length(sizeof(info)) {}

	Client::~Client()
	{
		WSACleanup();
		closesocket(client_socket);
	}

	void Client::initialize()
	{
		info.sin_family = AF_INET;
		info.sin_port = htons(port);
		// info.sin_addr.s_addr = inet_addr(ip_address.c_str());
		inet_pton(AF_INET, ip_address.c_str(), &info.sin_addr.s_addr);

		assert(!WSAStartup(MAKEWORD(2, 2), &wsa_data));
		assert(!((client_socket = socket(AF_INET, SOCK_DGRAM, 0)) == SOCKET_ERROR));

		printf("Initialization Client success.\n");
	}

	void Client::connect()
	{
		initialize();

		for (;;)
		{
			send();
			receive();
			proccess();
		}
	}

	void Client::send()
	{
		printf("Enter a message:");
		std::getline(std::cin, message);
		if ((sendto(client_socket, message.c_str(), message.size(), 0, (struct  sockaddr*)&info, info_length)) == SOCKET_ERROR)
		{
			printf("Error::%d\n", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
	}

	void Client::receive()
	{
		if ((recv_length = recvfrom(client_socket, buffer, SIZE, 0, (struct sockaddr*)&info, &info_length)) == SOCKET_ERROR)
		{
			printf("Error::%d\n", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
	}

	void Client::proccess()
	{
		printf("Packet from:[%s:%d]\n", inet_ntoa(info.sin_addr), htons(port));
		for (unsigned i = 0; i < recv_length; ++i)
		{
			printf("%c", buffer[i]);
		}
		printf("\n");
	}
}