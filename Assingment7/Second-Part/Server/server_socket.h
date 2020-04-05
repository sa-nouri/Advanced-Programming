#ifndef _SERVER_SOCKET_H
#define _SERVER_SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>

#include "tools.h"
#include "network_exception.h"

#define CONNECTION_BACKLOG 10
#define MAX_BUFFER_SIZE 2048


class NetworkEvent {
public:
  enum Type { NEWCONNECTION, NEWMESSAGE };
  NetworkEvent(int id, Type t) : identifier(id), type(t) {}
  int identifier;
  Type type;
};

class ServerSocket {
public:
	ServerSocket(int port);
  NetworkEvent interrupt(int fd);
  std::vector<int> file_descriptors();
  bool has_client(int fd);
  void terminate_client(int fd);
  int send(int fd, std::string message);
  std::string receive(int fd);
  ~ServerSocket();
private:
  void batchsend(int fd, std::string message);
  std::string batchreceive(int fd, int partcount);
private:
  int sockfd;
  struct sockaddr_in address;
  std::vector<int> clients;
};

#endif
