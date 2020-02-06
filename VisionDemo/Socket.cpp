#include "Socket.h"

Socket::Socket() : endpoint(asio::ip::address::from_string(address), port), socket(service) {
#ifndef NO_SOCKETS
	try {
		socket.connect(endpoint);
		isConnected = true;
	}
	catch (asio::system_error e) {
		std::cout << "Error: " << e.what() << std::endl;
		isConnected = false;
	}
#endif // !NO_SOCKETS
}

Socket::~Socket() {
#ifndef NO_SOCKET
	socket.close();
#endif // !NO_SOCKET
}

void Socket::send(std::vector<DetectedCard> cards) {
#ifndef NO_SOCKETS
	if (!isConnected) {
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
		std::cout << "Could not send data to server: " << e.what() << std::endl;
	}
#endif // !NO_SOCKETS
}

