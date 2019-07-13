#include <iostream>
#include "TPSolver.h"
#include "SMSolver.h"
using namespace std;

void solve_SM() {
	SMSolver::vec2d a = {
		{ -1, 3, 0, 2, 1 },
		{ 2, -1, 1, 2, 3 },
		{ 1, -1, 2, 1, 0 }
	};
	SMSolver::vec1d b = { 1, 4, 5 };
	SMSolver::vec1d c = { -1, 0, -2, 5, 4 };
	
	SMSolver solver(a, b, c);
	printf("Start table:\n");
	solver.print();
	printf("\n");
	
	printf("Optimization algorithm:\n");
	solver.optimize();

	cout << "Answer:\n";
	solver.print_ans();
}

void solve_TP() {
	TPSolver::vec2d cost = {
	{ 2, 3, 4, 3 },
	{ 5, 3, 1, 2 },
	{ 2, 1, 4, 2 }
	};
	TPSolver::vec1d supply = { 90, 30, 40 };
	TPSolver::vec1d claim = { 70, 30, 20, 40 };

	TPSolver solver(supply, claim, cost);
	cout << "Start table:\n";
	solver.print();
	cout << '\n';

	solver.northwest_corner();
	cout << "After northwest_corner algorithm:\n";
	solver.print();
	cout << '\n';
	
	cout << "Optimization algorithm:\n";
	solver.optimize();
} 

int main() {
	solve_SM();
}