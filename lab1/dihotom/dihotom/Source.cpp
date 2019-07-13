#include <iostream>
#include <cmath>
#include <functional>
#include <vector>
using namespace std;

const double GS = 1.61803398875;

vector<int> fib(2, 1);
double f1(double x) {
	return (x - 2) * (x - 2);
}

double find_min(double(*_f)(double), double l, double r, double eps, function<bool(double, double)> _pred = less<double>()) {
	//int O = log((r - l) / eps) / log(GS);

	int i = 1;
	while (r - l > eps) {
		double m1 = l + (r - l) * fib[i] / fib[i + 2];
		double m2 = l + (r - l) * fib[i + 1] / fib[i + 2];
		//double m1 = r - (r - l) * (GS - 1);
		//double m2 = l + (r - l) * (GS - 1);
		//double m1 = (r + l) / 2 - eps / 3;
		//double m2 = (r + l) / 2 + eps / 3;
		printf("it #%2d: l = %11lf; m1 = %13lf; m2 = %15lf; r = %15lf\n", i, l, m1, m2, r);
		printf("it #%2d: f(l) = %8lf; f(m1) = %10lf; f(m2) = %12lf; f(r) = %12lf\n", i, _f(l), _f(m1), _f(m2), _f(r));
		i++;
		if (_pred(_f(m1), _f(m2)))
			r = m2;
		else
			l = m1;
	}
	return (l + r) / 2 ;
}

pair<double, double> find_interval(double(*_f)(double), double x0, double k, function<bool(double, double)> _pred = less<double>()) {
	while (_pred(_f(x0 - k), _f(x0)) && _pred(_f(x0), _f(x0 + k))) {
		x0 -= k;
	}
	while (_pred(_f(x0), _f(x0 - k)) && _pred(_f(x0 + k), _f(x0))) {
		x0 += k;
	}
	return{ x0 - k, x0 + k };
}

int main() {
	
	for (int i = 2; fib[i - 1] < 2000 / 0.02; i++)
		fib.push_back(fib[i - 1] + fib[i - 2]);

	auto interv = find_interval(f1, 0, 1000);
	//cout << interv.first << ' ' << interv.second << '\n';
	double p = find_min(f1, interv.first, interv.second, 0.02);
	cout << "ans = " << p << '\n';
}