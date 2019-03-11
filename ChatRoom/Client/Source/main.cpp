#include "ENetClient.h"

int main()
{
	ENetClient client;
	client.initialise();
	client.run();
	return 0;
}