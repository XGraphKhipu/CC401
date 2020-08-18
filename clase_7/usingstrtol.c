/* strtol example */
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* strtol */
#define p(a) printf("%s\n", a)
#define pd(a) printf("%d\n", a)
#define pi(a) printf("%i\n", a)
#define pli(a) printf("%li\n", a)
int main ()
{
  char szNumbers[] = "2001 60c0c0 -1101110100110100100000 0x6fffff";
  char * pEnd;
  long int li1, li2, li3, li4;
  li1 = strtol (szNumbers,&pEnd,10);
  li2 = strtol (pEnd,&pEnd,16);
  li3 = strtol (pEnd,&pEnd,2);
  li4 = strtol (pEnd,NULL,0);
  printf ("The decimal equivalents are: %ld, %ld, %ld and %ld.\n", li1, li2, li3, li4);
  
  return 0;
}
//~ https://www.google.com/search?q=http+header+proxy+squid&oq=http+header+proxy+squid&aqs=chrome..69i57.3320j0j1&sourceid=chrome&ie=UTF-8
