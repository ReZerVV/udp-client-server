#include "client.h"

int main(int argc, char** argv)
{
	Net::Client client("127.0.0.1", 8888);
	client.connect();
	return 0;
}