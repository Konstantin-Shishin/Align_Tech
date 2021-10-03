#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
	std::ifstream in("test34.txt"); // окрываем файл для чтения
	if (in.is_open()) {
		vector <int> ivector;
		for (int n; in >> n; )
		{
			ivector.push_back(n);
		}

		if (in.bad())
			std::cout << "Ошибка ввода-вывода при чтении\n";
		else if (in.eof())
			std::cout << "end of file" << endl;
		else if (in.fail())
			std::cout << "Неверный формат данных\n";

		sort(ivector.begin(), ivector.end(), greater<int>());

		int counter = 0;
		int tmp;
		while (ivector.size() > 2) {
			ivector.at(ivector.size() - 1)--;
			tmp = ivector.at(0) + ivector.at(1);
			ivector.erase(ivector.begin());
			ivector.at(0) = tmp;
			counter++;
		}
		if (ivector.at(1) != 0) {
			counter++;
		}
		cout << "Count: " << counter << endl;
	}
}
