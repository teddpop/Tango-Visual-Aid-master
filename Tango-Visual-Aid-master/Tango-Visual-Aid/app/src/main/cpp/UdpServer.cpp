#include "UdpServer.h"

UdpServer::UdpServer() {
}

// TODO do something lol
UdpServer::~UdpServer() {
  close(socket_fd);
}

// used to setup and connect to server
// returns 0 on success
int UdpServer::connectSocket(const char* ip, int port) {

  int status; // used to check status returns

  // SOCK_DGRAM for UDP
  socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (socket_fd < 0) { LOGE("UDP: socket() ERROR: %d", socket_fd); return 1; }

  server_addr.sin_addr.s_addr = inet_addr(ip); // sets IP of server
  server_addr.sin_family = AF_INET; // uses internet address domain
  server_addr.sin_port = htons(port); // sets PORT on server

  LOGI("UDP: end connect, %d", status);
  return 0;
}

void UdpServer::closeSocket() {
  close(socket_fd);
}

// sends message to all other users online
// returns 0 on success
int UdpServer::send(char** message, int message_size) {
  int status;

  // WARNING: Can't send message size greater then MaxBuffer
  // No reason to check since these should be small packets
  status = sendto(socket_fd, *message, message_size, 0, (struct sockaddr*) &server_addr, sizeof(server_addr));
  if (status < 0) {
    LOGE("UDP: sendto() ERROR: %d", status); return 1;
  }

//  status = recv(socket_fd, message_recv, strlen(message_recv), 0);
//  if (status < 0) {
//    LOGE("UDP: recv() ERROR"); return 1;
//  } else {
//    LOGI("Reply received: %s", message_recv);
//  }

  return 0;
}
