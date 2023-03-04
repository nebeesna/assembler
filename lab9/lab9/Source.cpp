#include <iostream>
using namespace std;

const int a = -2;
int y, y2, x; // x є [-4;0]
int values[5];
int main() {
	__asm {
		mov eax, offset values
		push eax // заштовхуємо у стек адресу початку масиву
		mov cx, 5 // кількість проходів циклу 
		start: //початок циклу
		mov ax, 1 // для обчислення x = 1 - сх 
			sub ax, cx // отримуємо значення x = -1 - сх 
			cwde // розширюємо ax до eax
			mov ebx, eax // записуємо x в ebx
			mov eax, a // стала а

			cmp ebx, eax // порівнюємо х з сталою a
			je equals // якщо х = a, переходимо до мітки equals
			jne not_equals // якщо х != a, переходимо до мітки not_equals

			equals :
			mov edx, 3 //записуємо у edx 3 
			add edx, ebx //для розрахунку  y1 = x + 3
			mov y, edx //записуємо значення y1
			jmp calc_y2 //переходимо до мітки y2

			not_equals :
			mov edx, eax //записуємо у edx сталу а
			sub edx, ebx //для розрахунку  y1 = a - x
			mov y, edx //записуємо значення y1
			jmp calc_y2 //переходимо до мітки y2

			calc_y2 :
			cmp ebx, eax // порівнюємо х з сталою a
			jg more // якщо х > a, переходимо до мітки more
			jle equals_less // якщо х <= a, переходимо до мітки equals_less

			more :
			mov edx, eax //записуємо у edx сталу а
			imul edx, -1 //розрахунок y2 = |a|
			mov y2, edx //записуємо значення y2
			jmp result

			equals_less :
			mov edx, eax //записуємо у edx сталу а
			imul edx, -1 //розрахунок |a| для |a| - x
			sub edx, ebx //y2 = |a| - x
			mov y2, edx //записуємо значення y2
			jmp result

			result :
			mov eax, y //для обрахунку у записуємо у1 в еах
			mov ebx, y2 //для обрахунку у записуємо у2 в ebx
			imul ebx // у = у1 * у2
			pop ebx // виштовхуємо зі стеку адресу масиву
			mov[ebx], eax // записуємо результат за поточною адресою
			add ebx, 4 // зсуваємо вказівник масиву
			push ebx // заштовхуємо в стек нову адресу
			loop start // кінець циклу
	}
	for (int i = 0; i < 5; i++) {
		cout << values[i] << endl;
	}
	return 0;
}
/*
const int a = -4;
int y1, y2, y, x; // x є [-6,-2]
int values[5];
int main(){
	__asm() {
		mov eax, offset values
		push eax // заштовхуємо у стек адресу початку масиву
		mov cx, 5 // кількість проходів циклу
			start: //початок циклу
		mov ax, -1 // для обчислення x = -1 - сх
		sub ax, cx // отримуємо значення x = -1 - сх
		cwde // розширюємо ax до eax
		mov ebx, eax // записуємо x в ebx
		mov eax, a // стала а

		cmp ebx, eax // порівнюємо х з сталою a
		je equals // якщо х = a, переходимо до мітки equals
		jne not_equals // якщо х != a, переходимо до мітки not_equals

			equals:
		mov edx, 3 //записуємо у edx 3
		add edx, ebx //для розрахунку  y1 = x + 3
		jmp y2 //переходимо до мітки y2

			not_equals:
		mov edx, eax //записуємо у edx сталу а
		sub edx, ebx //для розрахунку  y1 = a - x
		jmp y2 //переходимо до мітки y2

			y2:
		cmp ebx, eax // порівнюємо х з сталою a
		jg more // якщо х > a, переходимо до мітки more
		jle equals_less // якщо х <= a, переходимо до мітки equals_less

			more:
		mov edx, eax //записуємо у edx сталу а
		imul edx, -1 //розрахунок y2 = |a|
		jmp result

			equals_less:
		mov edx, eax //записуємо у edx сталу а
		imul edx, -1 //розрахунок |a| для |a| - x
		sub edx, ebx //y2 = |a| - x
		jmp result

			result:
		pop ebx // виштовхуємо зі стеку адресу масиву
		mov [ebx], eax // записуємо результат за поточною адресою
		add ebx, 4 // зсуваємо вказівник масиву
		push ebx // заштовхуємо в стек нову адресу
		loop start // кінець циклу
	}
	for (int i = 0; i < 5; i++) {
		cout << values[i] << endl;
	}
	return 0;
}
*/
