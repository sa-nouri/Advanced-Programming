#include "client_socket.h"

using namespace std;


ClientSocket::ClientSocket(string address, int port)
{
  // initialize sent and received bytes to zero, only for statistical purposes
  sentbytes = 0;
  receivedbytes = 0;
  
  // creates an endpoint for communication and returns a file descriptor that refers to that endpoint
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    throw SocketCreationException(string(strerror(errno)));
  
  // setup server address and port number
  struct sockaddr_in servaddr;
  servaddr.sin_addr.s_addr = inet_addr(address.c_str());
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(port);
  
  // connect the socket referred to by the file descriptor 'sockfd' to the address specified by 'servaddr'
  if (connect(sockfd, (struct sockaddr*) &servaddr , sizeof(servaddr)) < 0)
    throw SocketConnectException(string(strerror(errno)));
}


void ClientSocket::send(string message)
{
  int size = message.size();
  
  // transmit a single message over the socket, if and only if message length is smaller than maximum buffer size
  if (size <= MAX_BUFFER_SIZE) {
    int bytecount = ::send(sockfd, message.c_str(), size + 1, 0);
    if (bytecount < 0)
      throw SocketSendException("failed to send a message to the server.");
    sentbytes += bytecount;
    return;
  }
  
  batchsend(message);
}


void ClientSocket::batchsend(string message)
{
  int size = message.size();
  
  // a header message determining number of transmissions required will be dispatced to the server
  ostringstream oss;
  oss << "[-[BATCH/" << Tools::itos(size / MAX_BUFFER_SIZE + (size % MAX_BUFFER_SIZE ? 1 : 0)) << "]-]";
  string header = oss.str();
  header += string (MAX_BUFFER_SIZE - header.length(), '/');
  send(header);
  
  // divide the original message to small tokens and send them individually
  for(int i = 0; (size - i) > 0; i += MAX_BUFFER_SIZE) {
    string part = message.substr(i, min(MAX_BUFFER_SIZE, size - i));
    send(part);
  }
  
  sentbytes -= header.length();
}


string ClientSocket::receive()
{
  char buffer[MAX_BUFFER_SIZE + 1];
  
  // receive a single message initially
  int bytecount = ::recv(sockfd, buffer, MAX_BUFFER_SIZE + 1, 0);
  if (bytecount < 0)
    throw SocketReceiveException("failed to receive a message from the server.");
  string message = string(buffer);
  
  // match the received message againts control commands
  if (message.substr(0, 3) == "[-[") {
    int pivot = message.find("]-]") + 3;
    string command = message.substr(3, pivot - 6);
    if (command == "DC") {
      close(sockfd);
      throw ConnectionTerminationException("connection terminated by client.");
    }
    else if (command.substr(0, 5) == "BATCH") {
      int partcount = Tools::mystoi(command.substr(6));
      message = batchreceive(partcount);
    }
  }
  
  receivedbytes += message.size() + 1;
  return message;
}


string ClientSocket::batchreceive(int partcount)
{
  string message = "";
  while (partcount--)
    message += receive();
  receivedbytes -= message.size();
  return message;
}


void ClientSocket::status()
{
  cout << Tools::decorate_text("=> Connection", 15, RIGHT) << Tools::decorate_text((sockfd < 0 ? "DOWN" : "UP"), 20, LEFT) << endl;
  cout << Tools::decorate_text("=> Sent", 15, RIGHT) << Tools::decorate_text(Tools::itos(sentbytes), 20, LEFT) << endl;
  cout << Tools::decorate_text("=> Received", 15, RIGHT) << Tools::decorate_text(Tools::itos(receivedbytes), 20, LEFT) << endl;
}


ClientSocket::~ClientSocket()
{
  send("[-[DC]-]");
  close(sockfd);
}
