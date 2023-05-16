#include "server.h"

int main(int argc, char** argv)
{
	Net::Server server("127.0.0.1", 8888);
	server.start();
	return 0;
}