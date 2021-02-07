#ifndef TANGO_VISUAL_AID_UDPSERVER_H
#define TANGO_VISUAL_AID_UDPSERVER_H

#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#include "Util.h"

class UdpServer {

 public:
  // Constructor and destructor
  UdpServer();
  ~UdpServer();

  // used to setup and connect to server
  // returns 0 on success
  int connectSocket(const char* ip, int port);

  void closeSocket();

  // sends message to all other users online
  // returns 0 on success
  int send(char** message, int message_size);

 private:

  struct sockaddr_in server_addr; // socket struct object
  int socket_fd;                  // holds socket file discriptor

  char message_recv[128];
};

#endif //TANGO_VISUAL_AID_UDPSERVER_H
