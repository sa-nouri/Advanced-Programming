#include "server_socket.h"
using namespace std;


ServerSocket::ServerSocket(int port)
{
  // creates an endpoint for communication and returns a file descriptor that refers to that endpoint
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    throw SocketCreationException(string(strerror(errno)));
  
  // allow reuse of local addresses
  int optval = 1;
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
    throw SocketCreationException(string(strerror(errno)));
  
  // assigns the address specified by 'address' to the socket referred to by the file descriptor 'sockfd'
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);
  if (bind(sockfd, (struct sockaddr *) &address, sizeof(address)) < 0)
    throw SocketBindException(string(strerror(errno)));
  
  // marks the socket as a socket that will be used to accept incoming connection
  if (listen(sockfd, CONNECTION_BACKLOG) < 0)
    throw SocketListenException(string(strerror(errno)));
}


NetworkEvent ServerSocket::interrupt(int fd)
{
  if (fd == sockfd) {
    struct sockaddr_in newaddr;
    socklen_t newaddrsize = sizeof(struct sockaddr_in);
    
    // extracts the first connection request on the queue of pending connections for the listening socket
    int newsockfd = accept(sockfd, (struct sockaddr*) &newaddr, (socklen_t*) &newaddrsize);
    if (newsockfd < 0)
      throw SocketAcceptException(string(strerror(errno)));
    clients.push_back(newsockfd);
    return NetworkEvent(newsockfd, NetworkEvent::NEWCONNECTION);
  }

  if (!has_client(fd))
    throw ClientNotFoundException("unable to locate the client in active connection pool.");
  
  return NetworkEvent(fd, NetworkEvent::NEWMESSAGE);
}


vector<int> ServerSocket::file_descriptors()
{
  vector<int> descriptors;
  descriptors.push_back(sockfd);
  for (int i = 0; i < clients.size(); i++)
    descriptors.push_back(clients[i]);
  return descriptors;
}


bool ServerSocket::has_client(int fd)
{
  return (find (clients.begin(), clients.end(), fd) != clients.end()); 
}


void ServerSocket::terminate_client(int fd)
{
  if (!has_client(fd))
    throw ClientNotFoundException("unable to locate the client in active connection pool.");
  
  vector<int>::iterator it = find (clients.begin(), clients.end(), fd);
  close(*it);
	clients.erase(it);
}


int ServerSocket::send(int fd, string message)
{
  if (!has_client(fd))
    throw ClientNotFoundException("unable to locate the client in active connection pool.");
  
  // transmit a single message over the socket, if and only if message length is smaller than maximum buffer size
  int size = message.size();
  if (size <= MAX_BUFFER_SIZE) {
    int bytecount = ::send(fd, message.c_str(), size + 1, 0);
    if (bytecount < 0)
      throw SocketSendException("failed to send a message to the server.");
    return bytecount;
  }
  
  batchsend(fd, message);
  return message.size();
}

void ServerSocket::batchsend(int fd, string message)
{
  int size = message.size();
  
  // a header message determining number of transmissions required will be dispatced to the client
  ostringstream oss;
  oss << "[-[BATCH/" << Tools::itos(size / MAX_BUFFER_SIZE + (size % MAX_BUFFER_SIZE ? 1 : 0)) << "]-]";
  string header = oss.str();
  header += string (MAX_BUFFER_SIZE - header.length(), '/');
  send(fd, header);
  
  // divide the original message to small tokens and send them individually
  for(int i = 0; (size - i) > 0; i += MAX_BUFFER_SIZE) {
    string part = message.substr(i, min(MAX_BUFFER_SIZE, size - i));
    send(fd, part);
  }
}


string ServerSocket::receive(int fd)
{
  if (!has_client(fd))
    throw ClientNotFoundException("unable to locate the client in active connection pool.");

  // receive a single message initially
  char buffer[MAX_BUFFER_SIZE + 1];
  int bytecount = ::recv(fd, buffer, MAX_BUFFER_SIZE + 1, 0);
  if (bytecount < 0)
    throw SocketReceiveException("failed to receive a message from the client.");
  
  // in case of ctrl+c on client side (SIGINT)
  if (bytecount == 0) {
    terminate_client(fd);
    throw ConnectionTerminationException("connection terminated by client.");
  }
      
  // match the received message againts control commands
  string message = string(buffer);
  if (message.substr(0, 3) == "[-[") {
    int pivot = message.find("]-]") + 3;
    string command = message.substr(3, pivot - 6);
    if (command == "DC") {
      terminate_client(fd);
      throw ConnectionTerminationException("connection terminated by client.");
    }
    else if (command.substr(0, 5) == "BATCH") {
      int partcount = Tools::mystoi(command.substr(6));
      message = batchreceive(fd, partcount);
    }
  }
  
  return message;
}


string ServerSocket::batchreceive(int fd, int partcount)
{
  string message = "";
  while (partcount--)
    message += receive(fd);
  return message;
}


ServerSocket::~ServerSocket()
{
  for (int i = 0; i < clients.size(); i++) {
    send(clients[i], "[-[DC]-]");
    close(clients[i]);
  }
  close(sockfd);
}
