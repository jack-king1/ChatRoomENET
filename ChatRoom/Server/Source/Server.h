#pragma once
#include <enetpp/server.h>

struct server_client
{
    unsigned int _uid;
    unsigned int get_id() const { return _uid; }
};

class Server
{
public:
	Server();
	~Server();

	void initialise();
	void run();

    enetpp::server<server_client> network_server;
    unsigned int next_uid = 0;
	
private:

};