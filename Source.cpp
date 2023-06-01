#include <iostream>
#include <ctime>
#include <cmath>

using namespace std;

int* generator(size_t length) {
	int* array = new int[length];
	srand(time(0));
	for (size_t i = 0; i < length; i++) {
		array[i] = rand() % 2;
	}
	return array;
}

double same_bits(int* array, size_t length) {
	double x = 0;
	for (size_t i = 0; i < length; i++) x += array[i];
	x /= length;
	if (!(abs(x - 0.5) < (2 / sqrt(length)))) return 0;
	double y = 0;
	for (size_t i = 0; i < length - 1; i++) y += (array[i] = array[i + 1] ? 0 : 1);
	return erfc(abs((y - 2 * length * x * (1 - x)) / (2 * sqrt(2 * length) * x * (1 - x))));
}

double bits_periodicity(int* array, size_t length) {
	double sum = 0;
	for (size_t i = 0; i < length; i++) sum += array[i] ? 1 : -1;
	sum /= sqrt(length);
	return erfc(sum / sqrt(2));
}

double longest_seq(int* array, size_t length) {
	int x1 = 0, x2 = 0, x3 = 0, x4 = 0, x_max = 0, count = 0;
	for (size_t i = 0; i <= 120; i += 8) {
		x_max = 0;
		count = 0;
		for (size_t j = 0; j < 7; j++) {
			if (count > x_max) x_max = count;
			if (array[j + 1] == 1 && array[j + i + 1] == 1) count++;
			else count = 0;
		}
		if (count > x_max) x_max = count;
		x_max++;
		if (x_max <= 1) x1++;
		else if (x_max == 2) x2++;
		else if (x_max == 3) x3++;
		else if (x_max == 4) x4++;
	}
	double x = (((x1 - 16 * 0.2148) * (x1 - 16 * 0.2148)) / 16 * 0.2148) + (((x2 - 16 * 0.3672) * (x2 - 16 * 0.3672)) / 16 * 0.3672) + (((x3 - 16 * 0.2305) * (x3 - 16 * 0.2305)) / 16 * 0.2305) + (((x4 - 16 * 0.1875) * (x4 - 16 * 0.1875)) / 16 * 0.1875);
	return x;
}

int main() {
	setlocale(LC_ALL, "Russian");
	int* array = generator(128);
	for (size_t i = 0; i < 128; i++) cout << array[i];
	cout << endl;
	cout << "Частотный побитовый тест Р = " << bits_periodicity(array, 128) << endl;
	cout << "Одинаковые подряд идущие биты Р = " << same_bits(array, 128) << endl;
	cout << "Тест на самую дллинную последовательность единиц в блоке x = " << longest_seq(array, 128) << endl;
	return 0;
}