#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <math.h>
#include <vector>
#include <time.h>

using namespace std;

double DoubleRand(double _max, double _min)
{
	return _min + double(rand()) / RAND_MAX * (_max - _min);
}

struct point {
	double x;
	double y;
	double r;
	double angle;
};

struct pred
{
	bool operator()(const point& dot1, const point& dot2)
	{
		return dot1.angle < dot2.angle;
	}
};

double raast(double x, double y) {
	return abs(80 - sqrt(x * x + y * y));
}

double angle(double x1, double y1, double x2, double y2) {
	return acos((x1 * x2 + y1 * y2) / (sqrt(x1 * x1 + y1 * y1) * sqrt(x2 * x2 + y2 * y2)));
}

const int N = 100;

int main()
{
	setlocale(LC_ALL, "Russian");
	double** points = new double* [N];
	for (int i = 0; i < N; ++i) {
		points[i] = new double[2];
	}

	srand(time(NULL));
	for (int i = 0; i < N; i++) {
		points[i][0] = DoubleRand(-100, 100);
		points[i][1] = DoubleRand(-100, 100);
	}

	// для теста закомментировать все, что выше, и раскомментировать все, что ниже закомментировано
	//double points[8][2] = { {-66,53}, {64.16, 28},{-48,30},{-91,32},{80,-20},{60,60}, {-64,37 }, {136,30} }; //1 рисунок
	//double points[10][2] = { {-39,11}, {-100,43},{-18,-72},{106,20},{40,12},{54,53},{-12,86},{-14,68},{20,-40},{-73,-12} }; // 2 рисунок
	//double points[10][2] = { {40,4}, {15,-99},{-76,17},{-60,-23},{-75,3},{17,-77},{-6,38},{46,-34},{-14,74},{14,99} }; // 3 рисунок

	point* arr = new point[N];
	for (int i = 0; i < N; i++) {
		arr[i].x = points[i][0];
		arr[i].y = points[i][1];
		arr[i].r = raast(arr[i].x, arr[i].y);
	}
	for (int i = 0; i < N; i++) {
		cout << "x:" << arr[i].x << " y:" << arr[i].y << endl;
	}
	std::vector <point> ivector;
	bool flag = false;
	double x0, y0;
	for (int i = 0; i < N; i++) {
		if (arr[i].r < 10) {
			if (flag == false) {
				x0 = arr[i].x;
				y0 = arr[i].y;
				arr[i].angle = 0;
				ivector.push_back(arr[i]);
				flag = true;
			}
			else {
				arr[i].angle = angle(x0, y0, arr[i].x, arr[i].y);
				ivector.push_back(arr[i]);
			}
		}
	}

	cout << "Исходные точки" << endl;
	for (int i = 0; i < N; i++) {
		cout << "x:" << arr[i].x << " y:" << arr[i].y << endl;
	}

	sort(ivector.begin(), ivector.end(), pred());

	cout << "Отсортированные точки, удовлетворяющие условию" << endl;
	for (unsigned int i = 0; i < ivector.size(); i++) {
		cout << "x:" << ivector.at(i).x << " y:" << ivector.at(i).y << endl;
	}
}

