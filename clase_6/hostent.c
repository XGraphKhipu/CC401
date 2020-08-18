#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <error.h>
#include <arpa/inet.h>

//~ const char *Inet_ntop(int family, const void *addrptr, char *strptr, size_t len)
//~ {
	//~ const char	*ptr;

	//~ if (strptr == NULL)		/* check for old code */
		//~ puts("NULL 3rd argument to inet_ntop");
	//~ if ( (ptr = inet_ntop(family, addrptr, strptr, len)) == NULL)
		//~ puts("inet_ntop error");		/* sets errno */
	//~ return(ptr);
//~ }
int main(int argc, char **argv) {
    char   *ptr, **pptr;
    char    str[INET_ADDRSTRLEN];
    struct hostent *hptr;
    
    
    while (--argc > 0) {
        ptr = *++argv;
        struct sockaddr_in myaddr;
        int s;
        //~ struct addrinfo {
               //~ int              ai_flags;
               //~ int              ai_family;
               //~ int              ai_socktype;
               //~ int              ai_protocol;
               //~ socklen_t        ai_addrlen;
               //~ struct sockaddr *ai_addr;
               //~ char            *ai_canonname;
               //~ struct addrinfo *ai_next;
           //~ };
        //~ struct sockaddr {
           //~ sa_family_t sa_family;
           //~ char        sa_data[14];
       //~ }
        //~ struct hostent {
               //~ char  *h_name;            /* official name of host */
               //~ char **h_aliases;         /* alias list */
               //~ int    h_addrtype;        /* host address type */
               //~ int    h_length;          /* length of address */
               //~ char **h_addr_list;       /* list of addresses */
           //~ }
        //~ struct sockaddr_in {
            //~ short            sin_family;   // e.g. AF_INET
            //~ unsigned short   sin_port;     // e.g. htons(3490)
            //~ struct in_addr   sin_addr;     // see struct in_addr, below
            //~ char             sin_zero[8];  // zero this if you want to
        //~ };
            //~ struct sockaddr {
               //~ sa_family_t sa_family;
               //~ char        sa_data[14];
           //~ }
        //~ struct in_addr {
            //~ in_addr_t s_addr;  // in_addr_t is a 32-bit integer.
        //~ };
        myaddr.sin_family = AF_INET;
        myaddr.sin_port = htons(3490);
        //~ int inet_aton(const char *cp, struct in_addr *inp);
        inet_aton("63.161.169.137", &myaddr.sin_addr);
        //~ const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);
        inet_ntop(myaddr.sin_family, &myaddr.sin_addr, str, sizeof(str));
        ///////////////////////
        //~ struct in_addr *ad1;
        //~ inet_aton("135.84.35.167", ad1);
        //~ printf("%i\n", ad1->s_addr);
        //~ struct hostent *pht = gethostbyaddr(ad1, 4, AF_INET);
        //~ printf("cname = %s\n", pht->h_name);
        ///////////////////////
        printf("== %s\n", str);
        if ((hptr = gethostbyname(ptr)) == NULL) {
            printf("gethostbyname error for host: %s: %s",
                    ptr, hstrerror(h_errno));
            continue;
        }
        printf("official hostname: %s\n", hptr->h_name);

        for (pptr = hptr->h_aliases; *pptr != NULL; pptr++)
            printf("\talias: %s\n", *pptr);

        switch (hptr->h_addrtype) {
        case AF_INET:
            pptr = hptr->h_addr_list;
            for (; *pptr != NULL; pptr++)
                printf("\taddress: %s\n",
                       inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str)));
            break;

        default:
            puts("unknown address type");
            break;
        }
    }
    return 0;
}
