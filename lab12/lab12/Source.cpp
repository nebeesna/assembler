#include <iostream>
#include<cmath>
using namespace std;

const int n = 4; // кількість значень змінної
float c, d;
const float seven = 7, two = 2, one = 1;
float numerator, // чисельник
	  denominator, // знаменник
	  a[n],  // масив a
	  res[n]; // кінцеве значення виразу

void calculateASM() {
	_asm {
		// обрахунок чисельника
		lea esi, a // початок масиву a
		lea edi, res // початок кінцевого масиву
		mov ecx, n // записуємо розмір масиву
		finit // ініціалізація співпроцесора
			calc_numerator : // початок циклу для обрахунку чисельника
		fld d // додавання значення d в стек співпроцесора
		fdiv two // ділення d на 2
		fchs // змінення d/2 на -(d/2)
		fadd c // додавання значення c 
		fpatan // arctg(c - (d/2))
		mov	numerator, edi
		add esi, 4 // перехід до наступних елементів масиву
		add edi, 4
		loop calc_numerator // завершення циклу обрахунку чисельника
		//обрахунок знаменника
		lea esi, a
		lea edi, res
		mov ecx, n
			calc_denominator : // початок циклу для обрахунку знаменника
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
			calc_res : // обрахунок результату
		fld[esi]
		fdiv denominator
		fstp[edi] // запис результату в масив
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
const int n = 3;// кількість значень змінної х
const float neg4 = -4;
float d;
float x[n];// значення змінної
float res[n];// значення виразу
void calculateASM()
{
	__asm
	{// заповнення регістрів
		lea esi, x// адреса початку масиву х
		lea edi, res// адреса початку масиву res
		mov ecx, n// розмір масиву
		finit// ініціалізація співпроцесора
		iteration :// початок циклу
		fld[esi]// значення х в стек співпроцесора
			fadd d// x + d
			fsincos// sin(x+d) i cos(x+d) в стек
			fmul// sin(x+d)*cos(x+d)
			fld neg4// -4 в стек
			fdiv// sin(x+d)cos(x+d)/(-4)
			fstp[edi]// запис значення виразу в масив
			// перехід до наступних елементів масивів
			add esi, 4
			add edi, 4
			loop iteration // кінець циклу
	}
}
void enteringData()
{
	cout << " Введіть d : ";
	cin >> d;
	cout << " Введіть x[i] :" << endl;
	for (int i = 0; i < n; ++i)
	{
		cout << " x[" << i << "] = ";
		cin >> x[i];
	}
}
void printRes(string sym)
{
	cout << " Обчислено в " << sym << endl;
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