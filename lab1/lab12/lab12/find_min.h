#pragma once
#include <iostream>
#include <cmath>
#include <functional>
#include "PointN.h"
#include <xfunctional>

using namespace std;

const double GS = 1.61803398875;

double f1(double x) {
	return 127 / 4 * x * x - 61 / 4 * x + 2;
}


pair<double, double> find_min(double(*_f)(double), double l, double r, double eps, function<bool(double, double)> _pred = less<double>()) {
	int O = log((r - l) / eps) / log(GS);
	for (int i = 0; i < O + 1; i++) {
		double m1 = r - (r - l) * (GS - 1);
		double m2 = l + (r - l) * (GS - 1);
		printf("it #%2d: l = %11lf; m1 = %13lf; m2 = %15lf; r = %15lf\n", i, l, m1, m2, r);
		if (_pred(_f(m1), _f(m2)))
			r = m2;
		else
			l = m1;
	}
	return{ l, r };
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


PointN find_min_gold(double(*_f)(PointN), PointN l, PointN r, double eps, function<bool(double, double)> _pred = less<double>()) {
	int O = log((r - l).len() / eps) / log(GS);
	for (int i = 0; i < O + 1; i++) {
		PointN m1 = r - (r - l) * (GS - 1);
		PointN m2 = l + (r - l) * (GS - 1);
		cout << "it #" << i << "; l = " << l << "; r = " << r << '\n';
		if (_pred(_f(m1), _f(m2)))
			r = m2;
		else
			l = m1;
	}
	return (l + r) / 2;
}

int sum = 0;

PointN min_incline(double(*_f)(PointN), PointN p, double eps, function<PointN(PointN)> _grad = nullptr, function<bool(double, double)> _pred = less<double>()) {
	PointN p_next(p.dim());
	int counter = 1;
	//cout << "start p #" << counter++ << " = " << p << "; f(p) = " << _f(p) << '\n';
	while (true) {
		if (_grad != nullptr)
			p_next = find_min_gold(_f, p, p - _grad(p), eps);
		else
			p_next = find_min_gold(_f, p, p - gradient(p, _f), eps);
		counter++;
		//cout << "p #" << counter++ << " = " << p_next << "\n\n";
		if ((p_next - p).len() < eps)
			break;
		p = p_next;
	}
	sum += counter;
	//cout << "inclines " << counter << '\n';
	return p_next;
}
