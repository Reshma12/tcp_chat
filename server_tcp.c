#include "sys/socket.h"
#include "netinet/in.h"
#include "arpa/inet.h"
#include "unistd.h"
#include "pthread.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
char buf[100];
int main()
{
  int k,sock_desc,temp,listenfd;
  socklen_t len;

  //Creation and allocation  
  struct sockaddr_in server,client;
  memset(&server,0,sizeof(server));
  memset(&client,0,sizeof(client));

  //Socket creation and assigning of structure sockaddr_in
  sock_desc=socket(AF_INET,SOCK_STREAM,0);
  if(sock_desc<0)
  {
    printf("\nError in socket creation.");
  }
  server.sin_family=AF_INET;
  server.sin_addr.s_addr=inet_addr("127.0.0.1");
  server.sin_port=htons(3000);

  //Binding and listening
  k=bind((sock_desc),(struct sockaddr*)&server,sizeof(server));
  if(k<0)
  {
    printf("\nError in binding.");
  }
  listenfd=listen(sock_desc,20);
  if(listenfd<0)
  {
    printf("\nError in listening.");
  }

  //Creating a live server and transmission of data
  while(1)
 {
  len=sizeof(client);

  //temporary socket creation to accept values from client
  temp=accept(sock_desc,(struct sockaddr*)&client,(socklen_t*)&len);
  if(temp<0)
  {
    printf("\nError in temporary socket creation.");
  }
  recv(temp,buf,sizeof(buf),0);
  printf("Received from client %s\n",buf);
  printf("\nEnter the data to be send,type end for stop:\n");
  gets(buf);
  if(strcmp(buf,"exit")!=0)
  send(temp,buf,sizeof(buf),0);
  else
  break;
 }

//closing of sockets
close(temp);
close(sock_desc);
return 0;
}

