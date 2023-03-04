#include<iostream>
#include<ctime>
using namespace std;
//13. Задані квадратні матриці  A та  B порядку  n.Отримати матрицю
//A(B  – E) + C, де  E - одинична матриця порядку  n, а елементи
//матриці С обчислюються за формулою : Сij = 1 / (i + j); i, j = 1, 2, ..., n.

int main() {
	srand(time(NULL));
	// ФОРМУВАННЯ МАТРИЦІ
	int n;
	cout << "Enter size of matrix: ";
	cin >> n;
	int** a = new int* [n];// матриця А
	int** b = new int* [n];// матриця В
	int** e = new int* [n];// матриця E
	int** c = new int* [n];// матриця C
	int** res = new int* [n];// результуюча матриця
	int** temp = new int* [n];// допоміжна матриця
	for (int i = 0; i < n; i++)
	{
		a[i] = new int[n];
		b[i] = new int[n];
		e[i] = new int[n];
		c[i] = new int[n];
		res[i] = new int[n];
		temp[i] = new int[n];
		for (int j = 0; j < n; j++)
		{
			a[i][j] = rand() % 10; //заповнення рандомними числами
			b[i][j]	= rand() % 10; // в проміжку [ 0 ; 9 ]
			e[i][j] = 1; // одинична матриця
			c[i][j] = (10 / (i + j + 1)); // формула змінена 
			//щоб матриця не була нульовою і всі масиви були однакового типу іnt
			res[i][j] = 0;
			temp[i][j] = 0;
		}
	}
	// ВІЗУАЛІЗАЦІЯ СФОРМОВАНИХ МАТРИЦЬ
	cout << "\n  A: \n" ;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	cout << "\n  B: \n";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << b[i][j] << " ";
		}
		cout << endl;
	}
	cout << "\n  C: \n";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << c[i][j] << " ";
		}
		cout << endl;
	}
	cout << "\n  E: \n";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << e[i][j] << " ";
		}
		cout << endl;
	}
	// АСЕМБЛЕРНА ВСТАВКА (B  – E)
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			__asm 
			{
				mov edx, res // edx = res
				mov esi, i
				imul esi, 4 //множення на 4, бо розмір int = 4
				add edx, esi // edx = &res[i]
				push[edx]
				pop edx // edx = res[i]
				mov esi, j
				imul esi, 4
				add edx, esi // edx = &res[i][j]
				push edx
				xor esi, esi // обнулення регістру

				mov eax, b
				mov ebx, e

				mov edx, i
				mov eax, [eax + 4 * edx] // eax = b[i]
				mov edx, j
				mov eax, [eax + 4 * edx] // eax = b[i][j]

				mov edx, i
				mov ebx, [ebx + 4 * edx] // ebx = e[i]
				mov edx, j
				mov ebx, [ebx + 4 * edx] // ebx = e[i][j]

				pop edx
				sub eax, ebx // eax = b[i][j] - e[i][j]
				add[edx], eax
				push edx
				pop edx
			}
		}
	}
	cout << "\n  (B - E) \n";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << res[i][j] << " ";
		}
		cout << endl;
	}
	// АСЕМБЛЕРНА ВСТАВКА A(B  – E)
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			__asm
			{
				mov edx, temp// edx = res
				mov esi, i
				imul esi, 4
				add edx, esi// edx = &res[i]
				push[edx]
				pop edx// edx = res[i]
				mov esi, j
				imul esi, 4
				add edx, esi// edx = &res[i][j]
				push edx
				xor esi, esi
				mov ecx, n
					start :
				mov eax, a
				mov ebx, res
					a_to_eax :
				mov edx, i
				mov eax, [eax + 4 * edx] // eax = a[i]
				mov edx, esi
				mov eax, [eax + 4 * edx] // eax = a[i][esi]
					res_to_ebx :
				mov edx, esi
				mov ebx, [ebx + 4 * edx] // ebx = res[esi]
				mov edx, j
				mov ebx, [ebx + 4 * edx] // ebx = res[esi][j]
					end :
				pop edx
				imul eax, ebx// eax = a[i][esi]*b[esi][j]
				add[edx], eax
				push edx
				inc esi
				loop start
				pop edx
			}
		}
	}
	cout << "\n  A(B - E) \n";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << temp[i][j] << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			res[i][j] = 0; // обнуляємо матрицю res для виконання A(B  – E) + C
		}
	}
	// АСЕМБЛЕРНА ВСТАВКА A(B  – E) + C
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			__asm
			{
				mov edx, res // edx = res
				mov esi, i
				imul esi, 4 //множення на 4, бо розмір int = 4
				add edx, esi // edx = &res[i]
				push[edx]
				pop edx // edx = res[i]
				mov esi, j
				imul esi, 4
				add edx, esi // edx = &res[i][j]
				push edx
				xor esi, esi // обнулення регістру

				mov eax, temp
				mov ebx, c

				mov edx, i
				mov eax, [eax + 4 * edx] // eax = temp[i]
				mov edx, j
				mov eax, [eax + 4 * edx] // eax = temp[i][j]

				mov edx, i
				mov ebx, [ebx + 4 * edx] // ebx = c[i]
				mov edx, j
				mov ebx, [ebx + 4 * edx] // ebx = c[i][j]

				pop edx
				add eax, ebx // eax = temp[i][j] + c[i][j]
				add[edx], eax
				push edx
				pop edx
			}
		}
	}
	// ВИВЕДЕННЯ РЕЗУЛЬТАТУ
	cout << "\n  A(B - E) + C ";
	cout << "\n  Result matrix: \n";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << res[i][j] << " ";
		}
		cout << endl;
	}
	cout << **res << endl;

	for (int i = 0; i < n; i++) { // звільнення пам’яті
		delete[] res[i];
		delete[] temp[i];
		delete[] a[i];
		delete[] b[i];
		delete[] e[i];
		delete[] c[i];
	}
	delete[] res;
	delete[] temp;
	delete[] a;
	delete[] b;
	delete[] e;
	delete[] c;
	return 0;
}
