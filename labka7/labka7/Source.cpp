#include <iostream>
using namespace std;
char FORMAT[] = "%s %s %s\n";
char DESIGN[] = "Desing by";
char NAME[] = "Anastasiia Dovha";
char YEAR[] = "2021";
int main() {
    __asm { // початок асемблерного коду
        mov  eax, offset YEAR
        push eax
        mov  eax, offset NAME
        push eax
        mov  eax, offset DESIGN
        push eax
        mov  eax, offset FORMAT
        push eax
        mov edi, printf
        call edi
        // Очищення стеку для коректного завершення процедури main
        pop  ebx
        pop  ebx
        pop  ebx
        pop  ebx
    } // кінець асемблерного коду
    system("pause");
    return 0;
}
