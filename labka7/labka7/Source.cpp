#include <iostream>
using namespace std;
char FORMAT[] = "%s %s %s\n";
char DESIGN[] = "Desing by";
char NAME[] = "Anastasiia Dovha";
char YEAR[] = "2021";
int main() {
    __asm { // ������� ������������ ����
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
        // �������� ����� ��� ���������� ���������� ��������� main
        pop  ebx
        pop  ebx
        pop  ebx
        pop  ebx
    } // ����� ������������ ����
    system("pause");
    return 0;
}
