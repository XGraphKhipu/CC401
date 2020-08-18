#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <stdio.h>

int main(void) {
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int s;
    char host[256];

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;

    s = getaddrinfo("google.com", NULL, &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }
    //~ int getnameinfo(const struct sockaddr *addr, socklen_t addrlen,
                       //~ char *host, socklen_t hostlen,
                       //~ char *serv, socklen_t servlen, int flags);
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        getnameinfo(rp->ai_addr, rp->ai_addrlen, host, sizeof(host), NULL, 0, NI_NUMERICHOST);
        printf("%s\n", host);
    }
    freeaddrinfo(result);
}
