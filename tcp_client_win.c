
#include <stdio.h>
#include <winsock2.h>


#define PORT 8090
#define DEFAULT_BUFLEN 512

int main(int argc , char *argv[])
{
	WSADATA wsa;
	SOCKET s,s_new;
	struct sockaddr_in server;
	int addrlen = sizeof(server);
	char *msg_sent="Hello from Morocco";
	long msg_recv;
	 char recvbuf[DEFAULT_BUFLEN];
     int recvbuflen = DEFAULT_BUFLEN;


					/* 	Initialise Winsock   */
					
	
	printf("\nInitialising Winsock...");

	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
		return 1;
	}
	
	printf("Initialised. \n");


					  /*	Create a TCP socket   */

	if((s = socket(AF_INET , SOCK_STREAM , IPPROTO_TCP )) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d" , WSAGetLastError());
		return 1;
	}

	printf("\nSocket created.\n");


						/*  Name the socket    */

	/*if(inet_pton(AF_INET, "127.0.0.1", &server.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return 1;
    }*/
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons( PORT );
	


	//connect(ConnectSocket, (SOCKADDR *) & clientService, sizeof (clientService));

	if (connect(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
    {
        printf("Connection Failed : %d" , WSAGetLastError());
		return 1;
    }


    printf("\nConnected to server.\n\n");


    //printf("Send a message : ");
    //scanf("%ld", &msg_sent);

    //send(s , msg_sent , strlen(msg_sent) , 0);
    

    if (send( s, msg_sent, (int)strlen(msg_sent), 0 ) == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return 1;
    }
    printf("\n Your message has sent \n");

    msg_recv =recv(s, recvbuf, recvbuflen, 0);
    printf("\n Message recieved : %s\n",recvbuf );

	//closesocket(s);
	WSACleanup();
	return 0;




	
}