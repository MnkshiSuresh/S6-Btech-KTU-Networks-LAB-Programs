server.c:

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
struct sockaddr_in server, client;
if (argc != 2)
printf("Input format not correct!\n");
int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
if (sockfd == -1)
printf("Error in socket creation!\n");
server.sin_family = AF_INET;
server.sin_addr.s_addr = INADDR_ANY;
server.sin_port = htons(atoi(argv[1]));
if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0)
printf("Error in bind()!\n");
char buffer[100];
socklen_t server_len = sizeof(server);
printf("Server waiting...\n");
if (recvfrom(sockfd, buffer, 100, 0, (struct sockaddr *)&server,
&server_len)< 0)
printf("Error in receiving!\n");
printf("Got a datagram: %s", buffer);
return 0;
}

client.c:

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
struct sockaddr_in server, client;
if (argc != 3)
printf("Input format not correct!\n");
int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
if (sockfd == -1)
printf("Error in socket creation!\n");
server.sin_family = AF_INET;
server.sin_addr.s_addr = INADDR_ANY;
server.sin_port = htons(atoi(argv[2]));
char buffer[100];
printf("Enter a message to sent to server: ");
fgets(buffer, 100, stdin);
if (sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&server,
sizeof(server)) < 0)
printf("Error in sending!\n");
return 0;
}
