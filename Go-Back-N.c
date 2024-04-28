server.c:

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
int main()
{
int s_sock, c_sock;
s_sock = socket(AF_INET, SOCK_STREAM, 0);
struct sockaddr_in server, other;
memset(&server, 0, sizeof(server));
memset(&other, 0, sizeof(other));
server.sin_family = AF_INET;
server.sin_port = htons(9009);
server.sin_addr.s_addr = INADDR_ANY;
socklen_t add;
if (bind(s_sock, (struct sockaddr *)&server, sizeof(server)) == -1){
printf("Binding failed\n");
return 0;
}
printf("\tServer Up\n Go back n (n=3) used to send 10 messages \n\n");
listen(s_sock, 10);
add = sizeof(other);
c_sock = accept(s_sock, (struct sockaddr *)&other, &add);
time_t t1, t2;
char msg[50] = "server message :";
char buff[50];
int flag = 0;
fd_set set1, set2, set3;
struct timeval timeout1, timeout2, timeout3;
int rv1, rv2, rv3;
int i = -1;
qq:
i = i + 1;
bzero(buff, sizeof(buff));
char buff2[60];
bzero(buff2, sizeof(buff2));
strcpy(buff2, "server message :");
buff2[strlen(buff2)] = i + '0';
buff2[strlen(buff2)] = '\0';
printf("Message sent to client :%s \n", buff2);
write(c_sock, buff2, sizeof(buff2));
usleep(1000);
i = i + 1;
bzero(buff2, sizeof(buff2));
strcpy(buff2, msg);
buff2[strlen(msg)] = i + '0';
printf("Message sent to client :%s \n", buff2);
write(c_sock, buff2, sizeof(buff2));
i = i + 1;
usleep(1000);
qqq:
bzero(buff2, sizeof(buff2));
strcpy(buff2, msg);
buff2[strlen(msg)] = i + '0';
printf("Message sent to client :%s \n", buff2);
write(c_sock, buff2, sizeof(buff2));
FD_ZERO(&set1);
FD_SET(c_sock, &set1);
timeout1.tv_sec = 2;
timeout1.tv_usec = 0;
rv1 = select(c_sock + 1, &set1, NULL, NULL, &timeout1);
if (rv1 == -1)
perror("select error ");
else if (rv1 == 0){
printf("Going back from %d:timeout \n", i);
i = i - 3;
goto qq;
}
else{
}
qq2:
read(c_sock, buff, sizeof(buff));
printf("Message from Client: %s\n", buff);
i++;
if (i <= 9)
goto qqq;
FD_ZERO(&set2);
FD_SET(c_sock, &set2);
timeout2.tv_sec = 3;
timeout2.tv_usec = 0;
rv2 = select(c_sock + 1, &set2, NULL, NULL, &timeout2);
if (rv2 == -1)
perror("select error "); // an error accured
else if (rv2 == 0){
printf("Going back from %d:timeout on last 2\n", i - 1);
i = i - 2;
bzero(buff2, sizeof(buff2));
strcpy(buff2, msg);
buff2[strlen(buff2)] = i + '0';
write(c_sock, buff2, sizeof(buff2));
usleep(1000);
bzero(buff2, sizeof(buff2));
i++;
strcpy(buff2, msg);
buff2[strlen(buff2)] = i + '0';
write(c_sock, buff2, sizeof(buff2));
goto qq2;
} // a timeout occured
else{
read(c_sock, buff, sizeof(buff));
printf("Message from Client: %s\n", buff);
bzero(buff, sizeof(buff));
read(c_sock, buff, sizeof(buff));
printf("Message from Client: %s\n", buff);
}
close(c_sock);
close(s_sock);
return 0;
}


client.c:

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
int main(){
int c_sock;
c_sock = socket(AF_INET, SOCK_STREAM, 0);
struct sockaddr_in client;
memset(&client, 0, sizeof(client));
client.sin_family = AF_INET;
client.sin_port = htons(9009);
client.sin_addr.s_addr = inet_addr("127.0.0.1");
if(connect(c_sock, (struct sockaddr *)&client, sizeof(client))==-1){
printf("Connection failed");
return 0;
}
printf("\n\tClient -with individual acknowledgement scheme\n\n");
char msg1[50] = "acknowledgement of :";
char msg2[50];
char buff[100];
int flag = 1, flg = 1;
for (int i = 0; i <= 9; i++){
flg = 1;
bzero(buff, sizeof(buff));
bzero(msg2, sizeof(msg2));
if (i == 8 && flag == 1){
printf("here\n"); // simulating loss
flag = 0;
read(c_sock, buff, sizeof(buff));
}
int n = read(c_sock, buff, sizeof(buff));
if (buff[strlen(buff) - 1] != i + '0'){ // out of order
printf("Discarded as out of order \n");
i--;
}else{
}
}
printf("Message received from server:%s \t%d\n",buff, i);
printf("Acknowledgement sent for message \n");
strcpy(msg2, msg1);
msg2[strlen(msg2)] = i + '0';
write(c_sock, msg2, sizeof(msg2));
close(c_sock);
return 0;
}
