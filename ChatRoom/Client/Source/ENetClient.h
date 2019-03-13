#pragma once

#include <atomic>
#include <queue>
#include <enetpp/client.h>
#include <ChatMsg.h>

class ENetClient
{
public: 
	ENetClient() = default;
	~ENetClient();
	void initialise();
	void run();
	void input();

	void connection();
	void disconnection();
	void data(const enet_uint8* data, size_t data_size);

private:
	enetpp::client client;
	std::atomic<bool> exiting = false;
	//std::queue<std::string> msg_queue;
    std::queue<ChatMsg> msg_queue;
	std::mutex msg_queue_mtx;
	std::string username;
};

