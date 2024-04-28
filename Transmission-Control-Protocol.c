server.c  :

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
char buf[100];
int k;
socklen_t len;
int sock_desc, temp_sock_desc;
struct sockaddr_in server, client;
sock_desc = socket(AF_INET, SOCK_STREAM, 0);
if (sock_desc == -1)
printf("Error in socketcreation");
server.sin_family = AF_INET;
server.sin_addr.s_addr = INADDR_ANY;
server.sin_port = 3003;
client.sin_family = AF_INET;
client.sin_addr.s_addr = INADDR_ANY;
client.sin_port = 3003;
k = bind(sock_desc, (struct sockaddr *)&server, sizeof(server));
if (k == -1)
printf("Error in binding");
k = listen(sock_desc, 5);
if (k == -1)
printf("Error in listening");
len = sizeof(client);
temp_sock_desc = accept(sock_desc, (struct sockaddr *)&client,&len);
if (temp_sock_desc == -1)
printf("Error in temporary socket creation");
k = recv(temp_sock_desc, buf, 100, 0);
if (k == -1)
printf("Error in receiving");
printf("Message got from client: %s", buf);
close(temp_sock_desc);
return 0;
}




client.c :


#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
char buf[100];
int k;
int sock_desc;
struct sockaddr_in client;
sock_desc = socket(AF_INET, SOCK_STREAM, 0);
if (sock_desc == -1)
printf("Error in socket creation!");
client.sin_family = AF_INET;
client.sin_addr.s_addr = INADDR_ANY;
client.sin_port = 3003;
k = connect(sock_desc, (struct sockaddr *)&client, sizeof(client));
if (k == -1)
printf("Error in connecting to server!");
printf("\nEnter data to be send: ");
fgets(buf, 100, stdin);
k = send(sock_desc, buf, 100, 0);
if (k == -1)
printf("Error in sending!");
close(sock_desc);
return 0;
}
