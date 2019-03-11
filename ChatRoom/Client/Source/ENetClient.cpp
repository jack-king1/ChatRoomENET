#include "ENetClient.h"
#include <iostream>
#include <Printer.h>

ENetClient::~ENetClient()
{
	enetpp::global_state::get().deinitialize();
}

void ENetClient::initialise()
{
    enetpp::global_state::get().initialize();
    client.connect(enetpp::client_connect_params()
                           .set_channel_count(1)
                           .set_server_host_name_and_port("localhost"
                                   , 8888));
}

void ENetClient::run()
{
    std::thread th(&ENetClient::input, this);
    th.detach();
	while (client.is_connecting_or_connected())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
        using namespace std::placeholders;
        client.consume_events(
                std::bind(&ENetClient::connection, this),
                std::bind(&ENetClient::disconnection, this),
                std::bind(&ENetClient::data, this, _1, _2));
    }

	exiting = true;
}

void ENetClient::input()
{
  while (!exiting)
  {
      std::string txt;
      std::getline(std::cin, txt);
  }
}

void ENetClient::connection()
{
    Printer() << "client has CONNECTED.";
}

void ENetClient::disconnection()
{
    Printer() << "client has DISCONNECTED.";
}

void ENetClient::data(const enet_uint8 *data, size_t data_size)
{

}

