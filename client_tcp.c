#include "sys/socket.h"
#include "netinet/in.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
int main()
{
  char buf[100];
  int k=1,sock_desc,temp_sock_desc,connectfd;
  socklen_t len;

  //creation of socket
  struct sockaddr_in client;
  memset(&client,0,sizeof(client));
  sock_desc=socket(AF_INET,SOCK_STREAM,0);
  if(sock_desc==-1)
  {
    printf("\nUnsuccessful creation......\n");
  }

  //Assigning of structure sockaddr_in 
  client.sin_family=AF_INET;
  client.sin_addr.s_addr=INADDR_ANY;
  client.sin_port=htons(3000);
 
  //Request to the server for connection
  connectfd=connect(sock_desc,(struct sockaddr*)&client,sizeof(client));
  if(connectfd<0)
  {
    printf("\nError in connection.");
  }

  //Entering the data from client side
  printf("\nEnter the data to be send:");
  gets(buf);
  k=send(sock_desc,buf,100,0);
  if(k<0)
  {
    printf("\nError in sending.");
  }

  //Receiving from server
  k=recv(sock_desc,buf,sizeof(buf),0);
  printf("Received from server: %s\n",buf);
  if(k<0)
  {
    printf("\nError in receiving.");
  } 
  //closing the socket connections
  close(connectfd);
  close(sock_desc);
}
