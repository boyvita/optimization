#pragma once

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class SMSolver {
public:
	typedef vector<double> vec1d;
	typedef vector<int> vec1i;
	typedef vector<vector<double>> vec2d;


	vec2d a;
	vec1i b;
	vec1d c;

	SMSolver(vec2d a, vec1d b, vec1d c) {
		this->c = c;
		for (int i = 0; i < b.size(); i++) {
			a[i].insert(a[i].begin(), b[i]);
			for (int j = 0; j < b.size(); j++) {
				a[i].push_back(i == j);
			}
		}

		c.insert(c.begin(), 0);
		for (int i = 0; i < b.size(); i++) {
			this->b.push_back(c.size());
			c.push_back(0);
		}
		a.push_back(c);
		this->a = a;

	}

	void print() {
		size_t w = 8;
		//name
		printf("x");
		//space
		printf(" ");

		for (int j = 0; j < a[0].size(); j++) {
			//x1
			printf("%*d", w, j);
			//space
			printf(" ");
		}
		printf("\n");

		for (int i = 0; i < b.size(); i++) {
			//name
			printf("%d", b[i]);
			//space
			printf(" ");

			for (int j = 0; j < a[i].size(); j++) {
				printf("%*.3lf ", w, a[i][j]);
			}
			printf("\n");
		}
		//name
		printf(" ");
		//space
		printf(" ");

		for (int j = 0; j < a[0].size(); j++) {
			printf("%*.3lf ", w, a.back()[j]);
		}
		printf("\n");
	}

	void print_ans() {
		double ans = 0;
		for (int j = 0; j < c.size(); j++) {
			bool pr = 0;
			for (int i = 0; i < b.size(); i++) {
				if (b[i] == j + 1) {
					ans += a[i][0] * c[j];
					printf("%.3lf * %.0lf", a[i][0], c[j]);
					goto label;
				}
			}
			printf("0 * %.0lf", c[j]);
			label:
			if (j == c.size() - 1) {
				printf(" = %lf\n", ans);
			} else {
				printf(" + ");
			}
		}
	}

	void add_string_to_string(int i1, double multy, int i2) {
		for (size_t j = 0; j < a[0].size(); j++) {
			a[i2][j] += a[i1][j] * multy;
		}
	}

	void multy_string(int i, double multy) {
		for (size_t j = 0; j < a[0].size(); j++) {
			a[i][j] *= multy;
		}
	}

	void optimize() {
		while (true) {
			int j_min = min_element(a.back().begin(), a.back().end()) - a.back().begin();
			if (a.back()[j_min] >= 0) {
				break;
			}
			int i_min = -1;
			for (int i = 0; i < b.size(); i++) {
				if (a[i][j_min] > 0 && (i_min == -1 || (a[i_min][0] / a[i_min][j_min] > a[i][0] / a[i][j_min]))) {
					i_min = i;
				}
			}
			cout << "j_min = " << j_min << "; i_min = " << i_min << ";\n";
			b[i_min] = j_min;
			multy_string(i_min, 1 / a[i_min][j_min]);
			for (int i = 0; i < a.size(); i++) {
				if (i != i_min && a[i][j_min] != 0) {
					add_string_to_string(i_min, -a[i][j_min], i);
				}
			}
			printf("After iteration:\n");
			print();
		}
	}

};