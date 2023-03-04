#include <iostream>
using namespace std;

const int a = -2;
int y, y2, x; // x � [-4;0]
int values[5];
int main() {
	__asm {
		mov eax, offset values
		push eax // ���������� � ���� ������ ������� ������
		mov cx, 5 // ������� ������� ����� 
		start: //������� �����
		mov ax, 1 // ��� ���������� x = 1 - �� 
			sub ax, cx // �������� �������� x = -1 - �� 
			cwde // ���������� ax �� eax
			mov ebx, eax // �������� x � ebx
			mov eax, a // ����� �

			cmp ebx, eax // ��������� � � ������ a
			je equals // ���� � = a, ���������� �� ���� equals
			jne not_equals // ���� � != a, ���������� �� ���� not_equals

			equals :
			mov edx, 3 //�������� � edx 3 
			add edx, ebx //��� ����������  y1 = x + 3
			mov y, edx //�������� �������� y1
			jmp calc_y2 //���������� �� ���� y2

			not_equals :
			mov edx, eax //�������� � edx ����� �
			sub edx, ebx //��� ����������  y1 = a - x
			mov y, edx //�������� �������� y1
			jmp calc_y2 //���������� �� ���� y2

			calc_y2 :
			cmp ebx, eax // ��������� � � ������ a
			jg more // ���� � > a, ���������� �� ���� more
			jle equals_less // ���� � <= a, ���������� �� ���� equals_less

			more :
			mov edx, eax //�������� � edx ����� �
			imul edx, -1 //���������� y2 = |a|
			mov y2, edx //�������� �������� y2
			jmp result

			equals_less :
			mov edx, eax //�������� � edx ����� �
			imul edx, -1 //���������� |a| ��� |a| - x
			sub edx, ebx //y2 = |a| - x
			mov y2, edx //�������� �������� y2
			jmp result

			result :
			mov eax, y //��� ��������� � �������� �1 � ���
			mov ebx, y2 //��� ��������� � �������� �2 � ebx
			imul ebx // � = �1 * �2
			pop ebx // ���������� � ����� ������ ������
			mov[ebx], eax // �������� ��������� �� �������� �������
			add ebx, 4 // ������� �������� ������
			push ebx // ���������� � ���� ���� ������
			loop start // ����� �����
	}
	for (int i = 0; i < 5; i++) {
		cout << values[i] << endl;
	}
	return 0;
}
/*
const int a = -4;
int y1, y2, y, x; // x � [-6,-2]
int values[5];
int main(){
	__asm() {
		mov eax, offset values
		push eax // ���������� � ���� ������ ������� ������
		mov cx, 5 // ������� ������� �����
			start: //������� �����
		mov ax, -1 // ��� ���������� x = -1 - ��
		sub ax, cx // �������� �������� x = -1 - ��
		cwde // ���������� ax �� eax
		mov ebx, eax // �������� x � ebx
		mov eax, a // ����� �

		cmp ebx, eax // ��������� � � ������ a
		je equals // ���� � = a, ���������� �� ���� equals
		jne not_equals // ���� � != a, ���������� �� ���� not_equals

			equals:
		mov edx, 3 //�������� � edx 3
		add edx, ebx //��� ����������  y1 = x + 3
		jmp y2 //���������� �� ���� y2

			not_equals:
		mov edx, eax //�������� � edx ����� �
		sub edx, ebx //��� ����������  y1 = a - x
		jmp y2 //���������� �� ���� y2

			y2:
		cmp ebx, eax // ��������� � � ������ a
		jg more // ���� � > a, ���������� �� ���� more
		jle equals_less // ���� � <= a, ���������� �� ���� equals_less

			more:
		mov edx, eax //�������� � edx ����� �
		imul edx, -1 //���������� y2 = |a|
		jmp result

			equals_less:
		mov edx, eax //�������� � edx ����� �
		imul edx, -1 //���������� |a| ��� |a| - x
		sub edx, ebx //y2 = |a| - x
		jmp result

			result:
		pop ebx // ���������� � ����� ������ ������
		mov [ebx], eax // �������� ��������� �� �������� �������
		add ebx, 4 // ������� �������� ������
		push ebx // ���������� � ���� ���� ������
		loop start // ����� �����
	}
	for (int i = 0; i < 5; i++) {
		cout << values[i] << endl;
	}
	return 0;
}
*/
