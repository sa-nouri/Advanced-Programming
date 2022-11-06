#ifndef _CLIENT_SOCKET_H
#define _CLIENT_SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "tools.h"
#include "network_exception.h"

#define MAX_BUFFER_SIZE 2048


class ClientSocket {
public:
	ClientSocket(std::string address, int port);
  void send(std::string message);
  std::string receive();
  void status();
  ~ClientSocket();
private:
  void batchsend(std::string message);
  std::string batchreceive(int partcount);
private:
  int sockfd;
  int sentbytes;
  int receivedbytes;
};

#endif
