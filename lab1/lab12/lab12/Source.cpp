#include <iostream>
#include <functional>
#include "find_min.h"

using namespace std;

double sqr(double x) {
	return x * x;
}

double f1(PointN p) {
	return 100 * sqr(p[1] - sqr(p[0])) + sqr(1 - p[0]);
}

double f2(PointN p) {
	return sqr(p[0] - 5) + sqr(p[1] - 20);
}

PointN df2(PointN p) {
	return PointN({ 2 * (p[0] - 5), 2 * (p[1] - 20) });
}

double f3(PointN p) {
	return sqr(p[1] - p[0]) + 100 * sqr(1 - p[0]);
}

PointN gradf3(PointN p) {
	return -2 * (p[1] - p[0]) - 200 * (1 - p[0]);
}

int main() {
	vector<PointN> v(20, PointN({}));
	for (int i = 0; i < 20; i++)
		v[i] = PointN({ (double)(rand() % 500), (double)(rand() % 500) });
	freopen("ans.txt", "w", stdout);
	for (int i = 0; i < 5; i++) {
		double cureps = pow(10, -3 - i);
		cout << "eps = " << cureps << '\n';
		for (int j = 0; j < 20; j++)
			min_incline(f3, v[j], cureps);
			//cout << min_incline(f3, PointN({ (double)(rand() % 500), (double)(rand() % 500) }), cureps) << '\n';
		cout << "avg iters " << sum / 10 << '\n';
		sum = 0;
	}
}