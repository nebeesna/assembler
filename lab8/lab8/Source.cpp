#include <iostream>
using namespace std;
//13. Визначити, чи  дорівнює  сума  двох  перших  цифр  заданого
//чотирицифрового числа сумі двох його останніх цифр.
int main() {
	int num = 0, sum1, sum2, ten = 10, hundred = 100;
	cout << "enter number:  ";
	cin >> num;
	sum1 = num;
	__asm {
		mov eax, num
		cdq

		div hundred // eax / 100   в edx записується остача
		mov sum2, edx
		mov sum1, eax //результат sum1 = eax
		cdq

		div ten // eax / 10  в edx записується остача
		mov sum1, eax
		add sum1, edx // sum1 = eax + edx ~~

		mov eax, sum2
		cdq
		div ten // eax / 10 в edx записується остача sum2=eax
		mov sum2, eax
		add sum2, edx // sum2 = sum2 + edx ~~
	}


	if (sum1 == sum2)
		cout << "sum of two first and two last numbers is equal.\n"
		<< sum1 << " and " << sum2;
	else cout << "sum of two first and two last numbers isn't equal.\n"
		<< sum1 << " and " << sum2;

	return 0;
}


/*
#include <iostream>
using namespace std;
int main() {
	int year, leap;
	cin >> year;
	__asm {
		mov ebx, 0
		mov ecx, 400
		mov eax, year
		cdq
		div ecx
		test edx, edx
		jz is_leap
		mov eax, year
		cdq
		mov ecx, 4
		div ecx
		test edx, edx
		jz maybe_leap
		jmp result
		is_leap :
		mov ebx, 1
			jmp result
			maybe_leap :
		mov eax, year
			cdq
			mov ecx, 100
			div ecx
			test edx, edx
			jz result
			jmp is_leap
			result :
		mov leap, ebx
			if (leap > 0) { cout << "Yes" << endl; }
			else { cout << "No" << endl; }
		return 0;
	}
	*/