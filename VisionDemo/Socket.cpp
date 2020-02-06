#include "Socket.h"

Socket::Socket() : endpoint(asio::ip::address::from_string(address), port), socket(service) {
	lastConnectionAttempt = std::chrono::steady_clock::now();
	isConnected = connectToServer();
}

Socket::~Socket() {
#ifndef NO_SOCKET
	socket.close();
#endif // !NO_SOCKET
}

bool Socket::connectToServer() {
#ifndef NO_SOCKETS
	try {
		socket.connect(endpoint);
		return true;
	}
	catch (asio::system_error e) {
		std::cout << "Error: " << e.what() << std::endl;
		lastConnectionAttempt = std::chrono::steady_clock::now();

		return false;
	}
#endif // !NO_SOCKETS

	return false;
}

#ifndef NO_SOCKETS
void Socket::tryReconnect() {
	auto timeNow = std::chrono::steady_clock::now();
	auto timeBetweenLastConnect = std::chrono::duration_cast<std::chrono::seconds>(timeNow - lastConnectionAttempt).count();

	if (timeBetweenLastConnect >= reconnectionDelay) {
		if (socket.is_open()) {
			socket.close();
		}

		isConnected = connectToServer();
	}
}
#endif // !NO_SOCKETS

void Socket::send(std::vector<DetectedCard> cards) {
#ifndef NO_SOCKETS
	if (!isConnected) {
		tryReconnect(); 
		return;
	}

	std::stringstream ss;
	for (auto card : cards) {
		ss << "Found Card:\n";
		ss << "\tLocation X: " << card.center.x << " Y: " << card.center.y << "\n";
		ss << "\tColour: " << (card.colour == Colour::RED ? "Red" : "Black") << "\n\n";
	}

	std::string message = ss.str();

	try {
		socket.write_some(asio::buffer(message.data(), message.size()));
	}
	catch(asio::system_error e) {
		isConnected = false;
		std::cout << "Could not send data to server: " << e.what() << std::endl;
	}
#endif // !NO_SOCKETS
}

