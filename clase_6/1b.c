#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <error.h>
#include <arpa/inet.h>

int main() {
    char   **pptr;
    char ptr[] = "uni.edu.pe";
    char  str[INET_ADDRSTRLEN];
    struct hostent *hptr;

    if ((hptr = gethostbyname(ptr)) == NULL) {
        printf("gethostbyname error for host: %s: %s",
                ptr, hstrerror(h_errno));
    }
    printf("official hostname: %s\n", hptr->h_name);

    for (pptr = hptr->h_aliases; *pptr != NULL; pptr++)
        printf("\talias: %s\n", *pptr);

    return 0;
}
