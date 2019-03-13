#include <Printer.h>
#include "Server.h"
#include <ChatMsg.h>

Server::Server()
{
	// constructor
	enetpp::global_state::get().initialize();
}

Server::~Server()
{
	// destructor
	network_server.stop_listening();
	enetpp::global_state::get().deinitialize();
}

void Server::initialise()
{
	auto init_client_func =
			[&](server_client& client, const char* ip)
			{
				client._uid = next_uid;
				next_uid++;
			};

	// set the server running
	network_server.start_listening(
			enetpp::server_listen_params<server_client>()
					.set_max_client_count(20)
					.set_channel_count(1)
					.set_listen_port(8888)
					.set_initialize_client_function(init_client_func));
}

void Server::run()
{
	auto on_connect = ([&](server_client& client)
	{
		Printer() << "client " <<
				  std::to_string(client.get_uid()) <<
				  ": has connected" << std::endl;
	});

	auto on_disconnect = ([&](unsigned int client_uid)
	{
		Printer() << "client " <<
				  std::to_string(client_uid) << ": has disconnected\n";
	});

    auto on_data = ([&](server_client& client,
                        const enet_uint8* data, size_t data_size)
    {
        ChatMsg msg(reinterpret_cast<const char*>(data));
        Printer()
                << "client "
                << std::to_string(client.get_uid())
                << ": "
                << msg.getUsername()
                << "=> "
                << msg.getMsg();
        Printer() << std::endl;
        Printer() << "forwarding msg to all clients\n";
        network_server.send_packet_to_all_if(
                0,
                data, data_size, ENET_PACKET_FLAG_RELIABLE,
                [&](const server_client& destination) {
                    return destination.get_uid() != client.get_uid();
                });
    });

	// while server should not terminate
	static bool terminate = false;
	while (!terminate)
	{
		network_server.consume_events(
				on_connect, on_disconnect, on_data);
		std::this_thread::sleep_for(
				std::chrono::milliseconds(1000));
	}
}