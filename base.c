#include <stdio.h>
#include "base.h"

void print(void){
    #if defined(_WIN32)
        printf("Hello World, Windows \n");
    #elif defined(__linux__)
        printf("Hello World, Linux \n");
    #endif
}
