
#include <stdio.h>
#include <winsock2.h>

//#pragma comment(lib,"ws2_32.lib") //Winsock Library


#define PORT 8090
#define DEFAULT_BUFLEN 512

int main(int argc , char *argv[])
{
	WSADATA wsa;
	SOCKET s,s_new;
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	char *msg_sent = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
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

	address.sin_addr.s_addr = INADDR_ANY;;
	address.sin_family = AF_INET;
	address.sin_port = htons(PORT);
	memset(address.sin_zero, '\0', sizeof address.sin_zero);

	 if (bind(s, (struct sockaddr *)&address, sizeof(address))==SOCKET_ERROR)
    {
        printf("Error in Binding: %d" , WSAGetLastError());
        closesocket(s);
	    WSACleanup();
	    return 1;
    
    }

    printf("\n Socket binded.\n");


     if (listen(s, 10)==SOCKET_ERROR)
    {
        printf("Error in Listening: %d" , WSAGetLastError());
        closesocket(s);
	    WSACleanup();
	    return 1;
       
    }


    				/*+++++++ Waiting for new connection +++++++*/

    while(1){
    	 printf("\n\n+++++++ Waiting for new connection ++++++++\n\n");
    	 if ((s_new = accept(s, NULL, NULL))==INVALID_SOCKET)
        {
            printf("accept failed with error: %d", WSAGetLastError());
	        closesocket(s);
	        WSACleanup();
	        return 1;
        }

        printf("\nClient conencted !\n");
        
      
        msg_recv =recv(s_new, recvbuf, recvbuflen, 0);
        printf("\n Message recieved : %s\n",recvbuf );


        if (send(s_new, msg_sent, (int)strlen(msg_sent), 0 ) == SOCKET_ERROR) {
	        printf("send failed with error: %d\n", WSAGetLastError());
	        closesocket(s);
	        WSACleanup();
	        return 1;
	    }
	    printf("\n Your message has sent \n");
        //send(s_new , hello , strlen(hello) , 0);
       // printf("\n Hello message sent \n");
        closesocket(s_new);

    }




	return 0;

	
}