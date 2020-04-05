#include "server.h"

using namespace std;


Server::Server(int port)
{
  socket = new ServerSocket(port);
  active = true;
}


void Server::run()
{
  while(active)
  {
    FD_ZERO(&fds);
    FD_SET(STDIN, &fds);
    int maxfd = STDIN;
    vector<int> sfds = socket->file_descriptors();
    for (int i = 0 ; i < sfds.size(); i++) {
      FD_SET(sfds[i], &fds);
      maxfd = max(maxfd, sfds[i]);
    }

    // monitor multiple file descriptors and block until one or more of the fds become ready for some class of I/O operation
    int activity = select(maxfd + 1, &fds, NULL, NULL, NULL);
    if (activity < 0 && errno != EINTR)
      throw InternalServerError("'select' procedure crashed unexpectedly.");
    
    if (FD_ISSET(STDIN, &fds))
    {
      string line;
      getline(cin, line);
      on_standard_input(line);
    }
    else
    {
      for (int i = 0 ; i < sfds.size(); i++) {
        if (FD_ISSET(sfds[i], &fds)) {
          NetworkEvent event = socket->interrupt(sfds[i]);
          if(event.type == NetworkEvent::NEWCONNECTION) {
            on_new_connection(event.identifier);
          }
          else if (event.type == NetworkEvent::NEWMESSAGE) {
            try {
              string message = receive(event.identifier);
              on_new_message(event.identifier, message);
            }
            catch(ConnectionTerminationException ex) {
              on_terminated_connection(event.identifier);
            }
          }
        }
      }
    }    
  }
}


void Server::stop()
{
  if (!active)
    throw InternalServerError("server is already stopped.");
  active = false;
}


void Server::send(int identifier, string message)
{
  socket->send(identifier, message);
}


string Server::receive(int identifier)
{
  return socket->receive(identifier);
}


Server::~Server()
{
  delete(socket);
}
