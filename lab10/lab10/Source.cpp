#include <iostream>
using namespace std;
//13. ������  �����  �  3  ����.�����������  ����, 
//��  �����  �  24  ��, ���������� ������� 
//��������� ������� � ������� ����.ʳ����
//����������� ���������� �� ����.
#include <iostream>
using namespace std;

int main() {
	char arr[3] = { 2 , 4 , 6 }; //	2 = 0010 4 = 0100 6 = 0110
	int res = 0;			//  ��������� 2

	_asm {
		mov ecx, 3	// ������� ������� �����
		mov al, 1	// �����
		xor dl, dl	// ��������� 
		xor dh, dh
		xor bl, bl
		start_outer :
			mov bh, 8 // ������� ������� ����������� �����
		start_in :
			mov ah, arr[ecx - 1]
			and ah, al // ���������� �����
			jnz go_next  // ���� ��������� == 0
			cmp dh, 0 // ��������� ��������
			jne go_next  // ���� dh != 0 
			cmp bl, 0 // ��������� ��������
			je go_next  // ���� bl == 0 
			inc res // �������� �������� ���� �����  ��������
		go_next :
			mov bl, dl  
			mov dl, dh 
			mov dh, ah 
			shl al, 1 // ���� �� 1 ��
			dec bh // ������� �-��� �������
			test bh, bh // �������� �� �������� 8 ��� ��������
			jnz start_in // ���� � �� ���������
		loop start_outer // ��������� ���������� �����
	}
	cout << res << endl;

	return 0;
}
	
/*
int main() {
	__int32 arr = 848843586; // (0011 0010 1001 1000
						     // 0101 0011 0100 0010)
	__int32 res = 0;
	__asm {
		mov cx, 8 // ������� ������� �����
		mov eax, 1 // �����
		start_outer: // ������� ���������� ����� (�� ������)
		mov bx, 4 // ������� ������� ����������� ����� 
		xor di, di // ��������� ��������� �������
		start_inner:// ������� ���������� ����� (�� ����)
		mov edx, arr 
		and edx, eax // ���������� �����
		jz go_next// ���� ��������� � 0
		inc di// ���� ��������� � 1, �������� ��������
		go_next:
		shl eax, 1// �������� ���� ���� �� 1 ��
		dec bx// �������� �������� ������� �� 1
		test bx, bx// ���������� ����� ���������� �����
		jnz start_inner// ���������� ����, ���� ��������� �� 0
		and di, 1// �������� �� �������
		jnz end_// ���� �������
		inc res// ���� �����, �������� �������� 
		end_:
		loop start_outer// ��������� ���������� �����
	}
	cout << res << endl;
	return 0;
}
*/

