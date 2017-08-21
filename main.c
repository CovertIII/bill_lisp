#include <stdlib.h>
#include <stdio.h>
#include "parse.h"

int main(int argc, char * argv[]){
  if ( argc != 2 ) {
    /* We print argv[0] assuming it is the program name */
    printf( "usage: %s filename", argv[0] );
  } else {
    parseFile(argv[1]);
  }
}
