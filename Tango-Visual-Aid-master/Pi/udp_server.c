/*
 * Simple UDP Socket server
 * Author: Spencer Fricke
 *
 * To compile:
 *     gcc udp_server.c -o server
 *
 * To run
 *     ./server <optional_port_number>
 */

#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>
#include <wiringPi.h>

#define DEFAULT_PORT 5000
#define MSG_SIZE 512

// wrapper for throwing error
void error(const char *msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]) {

  char receiveMsg[MSG_SIZE]; // message buffer
//  char returnMsg[] = "message received\n";
  int msgSize; // used to store incoming message size
  int status; // used to check status of c functions return values
  int port;

  struct sockaddr_in dest; // socket info about the machine connecting to us
  struct sockaddr_in serv; // socket info about our server
  int mySocket;            // socket used to listen for incoming connections
  socklen_t socksize = sizeof(struct sockaddr_in);

  // sets up servo control
  wiringPiSetupGpio();
  //softPwmCreate(18,0,500);
  pinMode(18,PWM_OUTPUT);
  pwmSetMode(PWM_MODE_MS);
  pwmSetClock(192);
  pwmSetRange(2000);

  // see if passed port in argument
  if (argc == 2) {
    port = atoi(argv[1]);
  } else {
    port = DEFAULT_PORT;
  }

  memset(&serv, 0, sizeof(serv)); // zero the struct before filling the fields
  serv.sin_family = AF_INET; // set to use Internet address family
  serv.sin_addr.s_addr = INADDR_ANY; // sets our local IP address
  serv.sin_port = htons(port); // sets the server port number

  // creates the socket
  // AF_INET refers to the Internet Domain
  // SOCK_DGRAM sets to datagrams
  // 0 will have the OS pick UDP for SOCK_DGRAM
  mySocket = socket(AF_INET, SOCK_DGRAM, 0);
  if (mySocket < 0) { error("ERROR: Opening socket\n"); }
  else { printf("UDP Socket Created! \n"); }

  // binds the serv object to the mySocket object
  status = bind(mySocket, (struct sockaddr *)&serv, sizeof(struct sockaddr)); 
  if (status < 0) { error("ERROR binding socket \n"); }
  else { printf("Socket Binded on port %d\n", port); }

  int motor = 150;
  int lastMotor = 0;

  for (;;) { // keeps daemon running forever

    // used to get message of size MSG_SIZE
    msgSize = recvfrom(mySocket, receiveMsg, MSG_SIZE, 0, (struct sockaddr *)&dest, &socksize);
    if (msgSize < 0) { error("ERROR: on recvfrom\n"); }

   // normalizes receiveMsg to 50-250
    motor = atoi(receiveMsg);
    motor = (int)((motor/1.275)+50);

    printf("%s  --- %d --- (%d)\n", receiveMsg, motor, lastMotor);

    //writes to servo
    if (lastMotor != motor) {
         lastMotor = motor;
         pwmWrite(18,motor);
    }

    // clears receive message buffer
    memset(receiveMsg, 0, MSG_SIZE);

    // sends back message to sender
    //  status = sendto(mySocket, returnMsg, strlen(returnMsg), 0, (struct sockaddr *)&dest, socksize);
    //  if (status < 0) { error("ERROR: on send\n"); }

  } // end forever loop

  return 0;
}
