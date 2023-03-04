#include <iostream>
#include<cmath>
using namespace std;

const int n = 4; // ������� ������� �����
float c, d;
const float seven = 7, two = 2, one = 1;
float numerator, // ���������
	  denominator, // ���������
	  a[n],  // ����� a
	  res[n]; // ������ �������� ������

void calculateASM() {
	_asm {
		// ��������� ����������
		lea esi, a // ������� ������ a
		lea edi, res // ������� �������� ������
		mov ecx, n // �������� ����� ������
		finit // ����������� ������������
			calc_numerator : // ������� ����� ��� ��������� ����������
		fld d // ��������� �������� d � ���� ������������
		fdiv two // ������ d �� 2
		fchs // ������� d/2 �� -(d/2)
		fadd c // ��������� �������� c 
		fpatan // arctg(c - (d/2))
		mov	numerator, edi
		add esi, 4 // ������� �� ��������� �������� ������
		add edi, 4
		loop calc_numerator // ���������� ����� ��������� ����������
		//��������� ����������
		lea esi, a
		lea edi, res
		mov ecx, n
			calc_denominator : // ������� ����� ��� ��������� ����������
		fld[esi]
		fmul seven
		fsub one
		mov denominator, edi
		add esi, 4
		add edi, 4
		loop calc_denominator
		lea esi, numerator
		lea esi, a
		lea edi, res
		mov ecx, n
			calc_res : // ��������� ����������
		fld[esi]
		fdiv denominator
		fstp[edi] // ����� ���������� � �����
		add esi, 4
		add edi, 4
		loop calc_res
	}
}

void calculateC() {
	for (int i = 0; i < n; i++)
	{
		res[i] = (atan(c - (d / 2))) / (7 * a[i] - 1);
	}
	cout << "\nCalculated on C++\n" ;
	for (int i = 0; i < n; i++)
	{
		cout << "res[" << i << "] = " << res[i] << endl;
	}

}

void input() {
	cout << " c > d\n" ;
	cout << "Enter c: " ;
	cin >> c;
	cout << "Enter d:";
	cin >> d;
	cout << "Initialise array a:\n";
	for (int i = 0; i < n; i++) {
		cout << "a[" << i << "] = ";
		cin >> a[i];
	}
}

void print_asm() {
	cout << "\nCalculated on ASM\n";
	for (int i = 0; i < n; i++)
		cout << "res[" << i << "] = " << res[i] << endl;
}

int main() {
	input();
	calculateASM();
	calculateC();
	print_asm();

	return 0;
}


/*
#include<windows.h>
using namespace std;
const int n = 3;// ������� ������� ����� �
const float neg4 = -4;
float d;
float x[n];// �������� �����
float res[n];// �������� ������
void calculateASM()
{
	__asm
	{// ���������� �������
		lea esi, x// ������ ������� ������ �
		lea edi, res// ������ ������� ������ res
		mov ecx, n// ����� ������
		finit// ����������� ������������
		iteration :// ������� �����
		fld[esi]// �������� � � ���� ������������
			fadd d// x + d
			fsincos// sin(x+d) i cos(x+d) � ����
			fmul// sin(x+d)*cos(x+d)
			fld neg4// -4 � ����
			fdiv// sin(x+d)cos(x+d)/(-4)
			fstp[edi]// ����� �������� ������ � �����
			// ������� �� ��������� �������� ������
			add esi, 4
			add edi, 4
			loop iteration // ����� �����
	}
}
void enteringData()
{
	cout << " ������ d : ";
	cin >> d;
	cout << " ������ x[i] :" << endl;
	for (int i = 0; i < n; ++i)
	{
		cout << " x[" << i << "] = ";
		cin >> x[i];
	}
}
void printRes(string sym)
{
	cout << " ��������� � " << sym << endl;
	for (int i = 0; i < n; ++i)
	{
		cout << " result: [" << i + 1 << "] = " << res[i] << endl;
	}
}
void calculateCpp()
{
	for (int i = 0; i < n; i++)
	{
		res[i] = -0.125 * sin(2 * (d + x[i]));
	}
}
int main()
{
	SetConsoleOutputCP(1251);
	enteringData();
	calculateASM();
	printRes("ASM");
	calculateCpp();
	printRes("C++");
	system("pause");
	return 0;
}
*/