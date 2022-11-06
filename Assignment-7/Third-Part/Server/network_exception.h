#ifndef _NETWORK_EXCEPTION_H
#define _NETWORK_EXCEPTION_H

class NetworkException {
public:
	NetworkException (std::string msg): message(msg) {}
	std::string get_message() { return message; } 
protected:	
	std::string message;
};

class SocketCreationException : public NetworkException {
public:
  SocketCreationException(std::string message) : NetworkException(message) {}
};

class SocketBindException : public NetworkException {
public:
  SocketBindException(std::string message) : NetworkException(message) {}
};

class SocketListenException : public NetworkException {
public:
  SocketListenException(std::string message) : NetworkException(message) {}
};

class SocketAcceptException : public NetworkException {
public:
  SocketAcceptException(std::string message) : NetworkException(message) {}
};

class SocketConnectException : public NetworkException {
public:
  SocketConnectException(std::string message) : NetworkException(message) {}
};

class ConnectionTerminationException : public NetworkException {
public:
  ConnectionTerminationException(std::string message) : NetworkException(message) {}
};

class ClientNotFoundException : public NetworkException {
public:
  ClientNotFoundException(std::string message) : NetworkException(message) {}
};

class SocketReceiveException : public NetworkException {
public:
  SocketReceiveException(std::string message) : NetworkException(message) {}
};

class SocketSendException : public NetworkException {
public:
  SocketSendException(std::string message) : NetworkException(message) {}
};

#endif
