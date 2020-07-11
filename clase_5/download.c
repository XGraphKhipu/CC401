#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>

void me(const char *p ) {
	printf("%s failed (%d) \n", p, errno);
}
// http://es.tldp.org/Tutoriales/PROG-SOCKETS/prog-sockets.pdf
int main()
{
    int socket_desc;

    char server_reply[4096];
    char *filename = "file.pdf";
    int total_len = 0;
    
    FILE *file = NULL;

	struct addrinfo limitsocket;
	struct addrinfo *addr_serv;
	
	memset(&limitsocket, 0, sizeof(limitsocket));
	
	limitsocket.ai_socktype = SOCK_STREAM;
	
	if (getaddrinfo("es.tldp.org", "80", &limitsocket, &addr_serv)) {
		me("getaddrinfo()");
		return 1;
	}
    /**/
    //Create socket
    socket_desc = socket(addr_serv->ai_family, addr_serv->ai_socktype, addr_serv->ai_protocol);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    
    //Connect to remote server
    int conn = connect(socket_desc, addr_serv->ai_addr, addr_serv->ai_addrlen);
    
    if (conn < 0)
    {
        puts("connect error");
        return 1;
    }

    puts("Connected\n");

    //Send request
    char message[] = "GET /Tutoriales/PROG-SOCKETS/prog-sockets.pdf HTTP/1.1\r\nHost: es.tldp.org\r\n\r\n Connection: keep-alive\r\n\r\n Keep-Alive: 300\r\n";
    
    if( send(socket_desc , message , strlen(message) , 0) < 0)
    {
        puts("Send failed");
        return 1;
    }

    puts("Data Send\n"); 

    remove(filename);
    file = fopen(filename, "ab");

    if(file == NULL){
        printf("File could not opened");
    }   

    while(1)
    {
        int received_len = recv(socket_desc, server_reply , sizeof server_reply , 0);

        if( received_len < 0 ) {
            puts("recv failed");
            break;
        } else if (received_len == 0) {
            puts("\nserver close the connection!\n");
            break;
        }
        total_len += received_len;
        
        fwrite(server_reply , received_len , 1, file);

        printf("\nReceived byte size = %d\nTotal lenght = %d", received_len, total_len);
    }

    puts("Reply received\n");

    fclose(file);

    return 0;
}
