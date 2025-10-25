#include "math.h"
#include "itmo.h"
// #include <iostream>
#include <stdio.h>



#define __DEBUG__


#ifdef __DEBUG__
    #define error_log(format, ...) printf("[ERROR] (%s:%d) " format "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
    #define error_log(format, ...)
#endif

#define MAX(x,y) (x > y ? x : y)
#define ITMO

int main(int, char**) {

///    int x = nextYear(2025);

    error_log("some error %d\n", 1);

    return 0;
}
