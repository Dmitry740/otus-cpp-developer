// OTUS C++ basic course
// Recursive fibinacci numbers

#include "fib.h"
#include <iostream>
#include <cstdlib>
#include <fstream>

// void PrintInFile(unsigned long res) {
//     std::fstream fso;git
//     fso.open("fib_file.txt", std::fstream::app);
//     fso << res << std::endl;
//     fso.close();
// }

// unsigned long fib(unsigned long n) {
//     unsigned long result = 0;
//     long first = 1;
//     long second = 1;
//     if(n == 0) {
//         return 0;
//     }
//     if(n == 1 || n == 2) {
//         result = 1;
//     }
//     for(unsigned long i = 3; i <= n; ++i) {
//             result = first + second;
//             second = result;
//             first = second - first;
//         }        
//     return result;
//    }

int main(int argc, char *argv[]) {
    unsigned long n = 100;
    if (argc == 2) {
        long temp =std::atol(argv[1]);
        if (temp < 0) {
            std::cerr << "Only positive number allowed" << std::endl;
            return 1;
        }
        n = temp;
    }
    for(unsigned long i = 1; i < n; ++i) {
    std::cout << fib(i) << std::endl;
    PrintInFile(fib(i));
    }
    return 0;
}

// Eval nth fibanicci number
// unsigned long fib(unsigned long n) {
//     if (n < 2) {
//         return n;
//     }
//     return fib(n - 1) + fib(n - 2);
// }

// int main(int argc, char *argv[]) {
//     unsigned long n = 100;
//     if (argc == 2) {
//         long tmp = std::atol(argv[1]);
//         if (tmp < 0) {
//             std::cerr << "Only non-negative number allowed\n";
//             return 1;
//         }
//         n = tmp;
//     }
//     for (unsigned long i = 0; i < n; ++i) {
//         std::cout << fib(i) << "\n";
//     }
//     return 0;
// }