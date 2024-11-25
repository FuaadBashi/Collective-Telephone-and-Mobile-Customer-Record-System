#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include "record.c"



int main(){
    bool done = false;

    while(!done){
        int option = Menu();
        done = initOptions(option);

    }

}       