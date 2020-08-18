#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <error.h>
#include <arpa/inet.h>

//~ inet_aton
//~ gethostbyaddr
int main(int argc, char **argv) {

    struct in_addr *ad1;
    inet_aton("157.240.197.35", ad1);
    //~ printf("%i\n", ad1->s_addr);
    struct hostent *pht = gethostbyaddr(ad1, 4, AF_INET);
    printf("name = %s\n", pht->h_name);
    
    return 0;
}
