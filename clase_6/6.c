#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    struct in_addr ip;
    struct hostent *hp;

    if (argc != 2) {
        fprintf(stderr, "usage: %s ipaddr\n", argv[0]);
        return 1;
    }

    if (!inet_aton(argv[1], &ip)) {
        fprintf(stderr, "can't parse IP address %s\n", argv[1]);
        return 1;
    }

    if ((hp = gethostbyaddr((const void *)&ip, sizeof ip, AF_INET)) == NULL) {
        fprintf(stderr, "no reverse name associated with %s\n", argv[1]);
        return 1;
    }

    printf("reverse name associated with %s is %s\n", argv[1], hp->h_name);
    return 0;
}
