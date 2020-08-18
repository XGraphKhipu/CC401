#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc, char * argv[]) {

  struct addrinfo * _addrinfo;
  struct addrinfo * _res;
  char _address[INET6_ADDRSTRLEN];
  int errcode = 0;

  if(argc < 2) {
    printf("Usage: %s [host]\n", argv[0]);
    return EXIT_FAILURE;
  }

  errcode = getaddrinfo(argv[1], NULL, NULL, &_addrinfo);
  if(errcode != 0) {
    printf("getaddrinfo: %s\n", gai_strerror(errcode));
    return EXIT_FAILURE;
  }

  for(_res = _addrinfo; _res != NULL; _res = _res->ai_next) {

    if(_res->ai_family == AF_INET) {

      if( NULL == inet_ntop( AF_INET,
        &((struct sockaddr_in *)_res->ai_addr)->sin_addr,
        _address,
        sizeof(_address) )
      ) {
        perror("inet_ntop");
        return EXIT_FAILURE;
      }

      printf("%s\n", _address);
    }
  }
}
