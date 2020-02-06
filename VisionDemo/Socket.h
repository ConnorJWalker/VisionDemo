#pragma once
#ifndef NO_SOCKETS
#include <chrono>
#include <sstream>
#include <asio.hpp>
#endif // !NO_SOCKETS
#include "Detector.h"
#include <iostream>

class Socket
{
//Properties
private:
	std::string address = "127.0.0.1";
	unsigned short port = 8080;
	bool isConnected;

#ifndef NO_SOCKETS
	asio::io_service service;
	asio::ip::tcp::socket socket;
	asio::ip::tcp::endpoint endpoint;

	const int reconnectionDelay = 5;
	std::chrono::steady_clock::time_point lastConnectionAttempt;
#endif // !NO_SOCKETS

// Methods
private:
	bool connectToServer();

#ifndef NO_SOCKETS
	void tryReconnect();
#endif // !NO_SOCKETS


public:
	Socket();
	~Socket();

	void send(std::vector<DetectedCard> cards);
};

