#ifndef _SERVER_H
#define _SERVER_H

#include <sys/select.h>
#include <iostream>

#include "server_socket.h"

#define STDIN 1


class InternalServerError {
public:
	InternalServerError (std::string msg): message(msg) {}
	std::string get_message() { return message; } 
protected:
	std::string message;
};

class Server {
public:
  Server(int port);
  virtual void run();
  virtual void stop();
  virtual void send(int identifier, std::string message);
  virtual std::string receive(int identifier);
  virtual void on_standard_input(std::string line) = 0;
  virtual void on_new_connection(int identifier) = 0;
  virtual void on_terminated_connection(int identifier) = 0;
  virtual void on_new_message(int identifier, std::string message) = 0;
  ~Server();
protected:
  bool active;
  fd_set fds;
  ServerSocket* socket;
};

#endif
