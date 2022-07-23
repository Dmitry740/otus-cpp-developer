#include "fib.h"
#include <cstdlib>
#include <fstream>
#include <iostream>

void PrintInFile(unsigned long res) {
    std::fstream fso;
    fso.open("fib_file.txt", std::fstream::app);
    fso << res << std::endl;
    fso.close();
}

unsigned long fib(unsigned long n) {
    unsigned long result = 0;
    long first = 1;
    long second = 1;
    if(n == 0) {
        return 0;
    }
    if(n == 1 || n == 2) {
        result = 1;
    }
    for(unsigned long i = 3; i <= n; ++i) {
            result = first + second;
            second = result;
            first = second - first;
        }        
    return result;
   }