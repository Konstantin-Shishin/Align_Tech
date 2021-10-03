#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

struct point {
	int x;
	int y;
};

inline int area(point a, point b, point c) { // вычисляет ориентированную площадь
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

inline bool intersect_1(int a, int b, int c, int d) {
	if (a > b)  swap(a, b);
	if (c > d)  swap(c, d);
	return max(a, c) <= min(b, d);
}

bool intersect(point a, point b, point c, point d) { //определяет, пересекаются ли отрезки ab и cd
	return intersect_1(a.x, b.x, c.x, d.x)
		&& intersect_1(a.y, b.y, c.y, d.y)
		&& area(a, b, c) * area(a, b, d) <= 0
		&& area(c, d, a) * area(c, d, b) <= 0;
}

bool pointper(point* p, int N, point p0) {
	point c = p0; // тестируемая точка, которую бросаем на плоскость
	point d; // cd -  горизонтальный отрезок, с началом в тестируемой точке и концом за пределами контура.
	d.y = c.y;
	int max = p[0].x;
	for (int n = 1; n < N; n++) { // самая правая точка по оси x
		if (p[n].x >= max)
			max = p[n].x;
	}
	d.x = max + 100;
	int counterper = 0; //количество пересечений отрезка cd и ab
	for (int n = 0; n < N - 1; n++) { // проверяем отрезки контурв на пересечение с cd		
		if (intersect(p[n], p[n + 1], c, d))
			counterper++;
	}
	if (counterper % 2 == 0) { // если отрезок cd пересекает четное количество ребер, то точка вне контура. Иначе в контуре
		return false;
	}
	else {
		return true;
	}
}

int main() {
	int n;
	int m;
	int temp;
	point* p;
	point* p0;

	std::ifstream in("test13.txt");
	if (in.is_open())
	{
		in >> n; // количество отрезков
		in >> m; // количество тестируемых точек

		p = new point[n + 1]; // координаты концов отрезков
		p0 = new point[m]; // массив из m точек (бросаем на плоскость)
		for (int i = 0; i < 2 * n - 1; i++) {
			if (i % 2 == 0) {//Считываем вершины фигуры без повторений
				in >> p[i / 2].x;
				in >> p[i / 2].y;
			}
			else
			{
				in >> temp;
				in >> temp;
			}
		}

		//Считываем замыкающую точку
		in >> p[n].x;
		in >> p[n].y;
		for (int j = 0; j < m; j++) {
			in >> p0[j].x;
			in >> p0[j].y;
		}

		int counter = 0;
		for (int i = 0; i < m; i++) {
			if (pointper(p, n + 1, p0[i])) {
				counter++;
			}
		}
		cout << counter;
		in.close();
	}
	return 0;
}

