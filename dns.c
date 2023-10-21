#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argn, char* args[]){

  if(argn != 2){
    printf("must insert an address\n");
    exit(1);
  }

  struct addrinfo* address_out;
  int ai_res = 0;
  char addr_str[NI_MAXHOST];
  
  // gets address info from the specified domain name, 
  // querying from dns at name args[1] port 80
  ai_res = getaddrinfo(args[1], "80", NULL, &address_out);

  if(ai_res != 0){
    printf("address resolution failed: %d\n", ai_res);
    exit(1);
  }

  for(struct addrinfo* ai_tmp = address_out; ai_tmp != NULL; ai_tmp = ai_tmp->ai_next){
    
    // gets every address present in address_out
    int err = getnameinfo(ai_tmp->ai_addr, ai_tmp->ai_addrlen, addr_str, NI_MAXHOST, 
              NULL, 0, NI_NUMERICHOST);

    if(err != 0){
      printf("getnameinfo failed: %d\n", err);
      exit(1);
    }

    printf("ADDRESS: %s\n", addr_str);

  }
  exit(0);
}
