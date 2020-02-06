#pragma once
#ifndef NO_SOCKETS
#include <asio.hpp>
#include <sstream>
#endif // !NO_SOCKETS
#include "Detector.h"
#include <iostream>

class Socket
{
//Properties
private:
	std::string address = "127.0.0.1";
	unsigned short port = 8080;

#ifndef NO_SOCKETS
	asio::io_service service;
	asio::ip::tcp::socket socket;
	asio::ip::tcp::endpoint endpoint;
	bool isConnected;
#endif // !NO_SOCKETS

// Methods
public:
	Socket();
	~Socket();

	void send(std::vector<DetectedCard> cards);
};

