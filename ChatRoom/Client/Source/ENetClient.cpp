#include "ENetClient.h"
#include <iostream>
#include <Printer.h>

ENetClient::~ENetClient()
{
	enetpp::global_state::get().deinitialize();
}

void ENetClient::initialise()
{
    Printer() <<
              "Welcome to the coolest chatroom evz. Fo Sho!\n" <<
              "Please enter your tag, in'it\n";
    std::getline(std::cin, username);

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

        while (msg_queue.size())
        {
            std::lock_guard<std::mutex>lock(msg_queue_mtx);
            const auto& msg = msg_queue.front();
            assert(sizeof(char) == sizeof(enet_uint8));
            unsigned int msg_length = 0;
            auto msg_data = msg.data(msg_length);
            msg_queue.pop();
            client.send_packet(0,
                               reinterpret_cast<const enet_uint8*>(msg_data),
                               msg_length, ENET_PACKET_FLAG_RELIABLE);
        }
	}

	exiting = true;
}

void ENetClient::input() {

	while (!exiting) {
		std::string txt;
		std::getline(std::cin, txt);
		std::time_t result = std::time(nullptr);
		std::string time_stamp = std::asctime(std::localtime(&result));
		ChatMsg msg(username, txt, result);
		std::lock_guard<std::mutex>lock(msg_queue_mtx);
		msg_queue.push(std::move(msg));
	}
}

void ENetClient::connection()
{
	Printer() << "Connected!\n";
}

void ENetClient::disconnection()
{
	Printer() << "Disconnected!\n";
}

void ENetClient::data(const enet_uint8* data, size_t data_size)
{
	ChatMsg msg(reinterpret_cast<const char*>(data));
	std::string time_stamp = std::asctime(std::localtime(&msg.getStamp()));
	Printer() << "(" + time_stamp + ")" + msg.getUsername() + ": " + msg.getMsg();
}
