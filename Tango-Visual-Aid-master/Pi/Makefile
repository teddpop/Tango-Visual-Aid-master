CC = gcc
CFLAGS = -Wall -Werror

main: UdpServer

UdpServer:
	$(CC) udp_server.c $(CFLAGS) -o server -lwiringPi

clean:
	rm server
