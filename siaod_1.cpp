#include <iostream>
#include <bitset>
#include <Windows.h>
#include <time.h>
#include <vector>
#include <fstream>

using namespace std;

int f_a(unsigned char x) { //установка 5-го бита числа в 0 - уменьшенное на 16 значение числа или то же самое число
	unsigned char maska = 1;
	x = x & (~(maska << 4));
	return x;
}

int f_b(unsigned char x) { //установка 7-го бита числа в 1 - увеличенное на 64 значение числа или то же самое число
	unsigned char maska = 1;
	x = x | (maska << 6);
	return x;
}

void f_c() { //реализация кода листинга
	unsigned int x = 25;
	const int n = sizeof(x) * 8; //количество битов числа - 32
	unsigned maska = (1 << (n - 1)); //установка 1 в старший разряд разрядного числа
	cout << "Начальный вид маски: " << bitset<n>(maska) << endl; //создание объекта класса bitset - инициализация битов соответствующего числа
	cout << "Результат: ";
	for (int i = 1; i <= n; i++) {
		cout << ((x & maska) >> (n - i)); //вывод битов переменной x слева направо
		maska = maska >> 1; //сдвиг 1 в маске влево на бит
	}
	cout << endl;
}

void s_a() {
	unsigned char a = 0;
	unsigned char maska = 1;
	float x;
	int i = 0;
	cout << "Введите до 8 целых чисел от 0 до 7: " << endl;
	cout << "Чтобы прекратить ввод, введите -1" << endl;
	while (i < 8) {
		cin >> x;
		if (x == -1)
			break;
		while (x > 8 || x < 0 || (x - (int)x) > 0) {
			cout << "Введите до 8 целых чисел от 0 до 7: " << endl;
			cout << "Чтобы прекратить ввод, введите -1" << endl;
			cin >> x;
		}
		a = a | (maska << (8 - (int)x - 1));
		maska = 1;
		i++;
	}
	maska = maska << 7;
	cout << "Отсортированная последовательность: " << endl;
	for (int i = 1; i <= 8; i++) {
		if (((a & maska) >> (8 - i)) == 1) {
			cout << i - 1 << " ";
		}
		maska = maska >> 1;
	}
	cout << endl << "Битовый массив: " << bitset<8>(a) << endl;
}

void s_b() {
	unsigned long long a = 0;
	unsigned long long maska = 1;
	float x;
	int n;
	srand(time(NULL));
	cout << "Введите до 64 целых чисел от 0 до 63: " << endl;
	cout << "Ввести числа вручную - 1, случайные числа - 2" << endl;
	cout << "Чтобы прекратить ввод, введите -1" << endl;
	cin >> n;
	for (int i = 0; i < 64; i++) {
		switch (n) {
		case 1:
			cin >> x;
			if (x == -1)
				break;
			while (x < 0 || x > 63 || (x - (int)x) > 0) {
				cout << "Введите до 64 целых чисел от 0 до 63: " << endl;
				cout << "Чтобы прекратить ввод, введите -1" << endl;
				cin >> x;
			}
			break;
		case 2:
			x = rand() % 64;
			break;
		}
		if (x == -1)
			break;
		a = a | (maska << (64 - (int)x - 1));
		maska = 1;
	}
	maska = maska << 63;
	cout << "Отсортированная последовательность: ";
	for (int i = 1; i <= 64; i++) {
		if (((a & maska) >> (64 - i)) == 1) {
			cout << i - 1 << " ";
		}
		maska = maska >> 1;
	}
	cout << endl << "Битовый массив: " << bitset<64>(a) << endl;
}

void s_c() {
	vector<unsigned char> mas = { 0 };
	int x;
	cout << "Введите целые числа: " << endl;
	cout << "Чтобы прекратить ввод, введите -1" << endl;
	cin >> x;
	while (x != -1) {
		while (mas.size() - 1 < (x / 8)) {
			mas.push_back(0);
		}
		mas[x / 8] = mas[x / 8] | (1 << (8 - (x % 8) - 1));
		cin >> x;
	}
	cout << "Отсортированный массив чисел: " << endl;
	for (int i = 0; i < mas.size(); i++) {
		for (int j = 0; j <= 7; j++) {
			if (((mas[i] & (1 << (8 - j - 1))) >> (8 - j - 1)) == 1) {
				cout << i * 8 + j << " ";
			}
		}
	}
	cout << endl;
}

void t() {
	vector<unsigned char> mas(1250000);
	int x;
	clock_t start = clock();
	ifstream fin("num.txt");
	ofstream fout("num_sort.txt");
	while (!fin.eof()) {
		fin >> x;
		x--;
		mas[x / 8] = mas[x / 8] | (1 << (8 - (x % 8) - 1));
	}
	for (int i = 0; i < mas.size(); i++) {
		for (int j = 0; j <= 7; j++) {
			if (((mas[i] & (1 << (8 - j - 1))) >> (8 - j - 1)) == 1) {
				fout << i * 8 + j + 1 << " ";
			}
		}
	}
	fin.close(); siaod
		fout.close();
	clock_t end = clock();
	double seconds = (double)(end - start) / CLK_TCK;
	cout << "Время работы программы: " << seconds << " секунд" << endl;
	cout << "Объем оперативной памяти, занимаемой битовым массивом: " << sizeof(mas) / (1024.0 * 1024.0) << " MB" << endl;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int n;
	char x;
	float k;
	cout << "Выберите задание: 1 2 3" << endl;
	cout << "Для выхода из меню введите 0" << endl;
	cin >> n;
	while (n != 0) {
		switch (n) {
		case 1:
			cout << "Выберите подзадание: a b c" << endl;
			cin >> x;
			switch (x) {
			case 'a':
				cout << "Введите неотрицательное целое число до 255: " << endl;
				cin >> k;
				while (k > 255 || k < 0 || (k - (int)k) > 0) {
					cout << "Введите неотрицательное целое число до 255: " << endl;
					cin >> k;
				}
				cout << "Число с 5-м нулевым битом: " << endl;
				cout << f_a((unsigned char)k) << endl;
				break;
			case 'b':
				cout << "Введите неотрицательное целое число до 255: " << endl;
				cin >> k;
				while (k > 255 || k < 0 || (k - (int)k) > 0) {
					cout << "Введите неотрицательное целое число до 255: " << endl;
					cin >> k;
				}
				cout << "Число с 7-м единичным битом: " << endl;
				cout << f_b((unsigned char)k) << endl;
				break;
			case 'c':
				f_c();
				break;
			}
			break;
		case 2:
			cout << "Выберите подзадание: a b c" << endl;
			cin >> x;
			switch (x) {
			case 'a':
				s_a();
				break;
			case 'b':
				s_b();
				break;
			case 'c':
				s_c();
				break;
			}
			break;
		case 3:
			t();
			break;
		}
		cout << "Выберите задание: 1 2 3" << endl;
		cout << "Для выхода из меню введите 0" << endl;
		cin >> n;
	}
	return 0;
}