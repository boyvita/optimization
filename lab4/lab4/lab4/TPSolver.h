#pragma once
#include <iostream>
#include <vector>
#include <queue>

using namespace std;
struct Coordinate {
	int i, j;
	Coordinate(int i, int j) : i(i), j(j) {}
	bool operator == (Coordinate b) {
		return i == b.i && j == b.j;
	}
	bool operator != (Coordinate b) {
		return !((*this) == b);
	}
};
ostream& operator << (ostream &os, Coordinate const& c) {
	return os << "(" << c.i << ", " << c.j << ")";
}

class TPSolver {
public:
	const double EPS = 0.1;
	typedef vector<double> vec1d;
	typedef vector<vector<double>> vec2d;
	typedef vector<int> vec1i;
	typedef vector<vector<int>> vec2i;
	typedef vector<Coordinate> vec1c;
	typedef vector<vector<Coordinate>> vec2c;

	static vec2d make_vec2d(int n, int m) {
		return vec2d(n, vec1d(m, 0));
	}

	static vec2i make_vec2i(int n, int m) {
		return vec2i(n, vec1i(m, 0));
	}

	static vec2c make_vec2c(int n, int m) {
		return vec2c(n, vec1c(m, Coordinate(-1, -1)));
	}

	vec1d resource;
	vec1d request;
	vec2d cost;
	vec2d plan;

	vec1d u_res;
	vec1d u_req;

	vec1i u_res_used;
	vec1i u_req_used;

	vec2d grade;

	vec2i used;
	vec2c previous;

	TPSolver(vec1d resource, vec1d request, vec2d cost) : resource(resource), request(request), cost(cost) {
		plan = make_vec2d(resource.size(), request.size());
		grade = make_vec2d(resource.size(), request.size());
		u_res = vec1d(resource.size());
		u_req = vec1d(request.size());
	}

	double resource_sum(int i) {
		double ans = 0;
		for (int j = 0; j < request.size(); j++) {
			ans += plan[i][j];
		}
		return ans;
	}

	double request_sum(int j) {
		double ans = 0;
		for (int i = 0; i < resource.size(); i++) {
			ans += plan[i][j];
		}
		return ans;
	}

	void print() {
		size_t w = 6;

		printf("plan ");
		for (int j = 0; j < request.size(); j++)
			printf("%*.0lf   ", w, request[j]);

		printf("     grades ");
		for (int j = 0; j < request.size(); j++)
			printf("%*.0lf ", w, u_req[j]);
		printf("\n");


		for (int i = 0; i < resource.size(); i++) {
			printf("%*.1lf ", 4, resource[i]);
			for (int j = 0; j < request.size(); j++) {
				printf("%*.1lf*%.0lf ", w, plan[i][j], cost[i][j]);
			}
			
			printf("%s", string(5, ' ').c_str());

			printf("%*.1lf ", w, u_res[i]);
			for (int j = 0; j < request.size(); j++) {
				printf("%*.1lf ", w, grade[i][j]);
			}
			printf("\n");
		}
	}

	void northwest_corner() {
		int i = 0, j = 0;
		while (true) {
			if (i == resource.size() - 1 && j == request.size() - 1) {
				plan[i][j] = resource[i] - resource_sum(i);
				break;
			}
			if (resource[i] - resource_sum(i) > request[j] - request_sum(j)) {
				plan[i][j] = request[j] - request_sum(j);
				j++;
			}
			else if (resource[i] - resource_sum(i) < request[j] - request_sum(j)) {
				plan[i][j] = resource[i] - resource_sum(i);
				i++;
			}
			else if (resource[i] - resource_sum(i) == request[j] - request_sum(j)) {
				resource[i] += EPS;
				resource.back() -= EPS;
			}
		}
	}

	void dfs_potentials(Coordinate c) {
		for (int i = 0; i < resource.size(); i++) {
			int j = c.j;
			if (!used[i][j] && plan[i][j]) {
				used[i][j] = 1;
				if (!u_req_used[j]) {
					u_req[j] = cost[i][j] - u_res[i];
					u_req_used[j] = 1;
				}
				if (!u_res_used[i]) {
					u_res[i] = cost[i][j] - u_req[j];
					u_res_used[i] = 1;
				}
				dfs_potentials(Coordinate(i, j));
			}
		}

		for (int j = 0; j < request.size(); j++) {
			int i = c.i;
			if (!used[i][j] && plan[i][j]) {
				used[i][j] = 1;
				if (!u_req_used[j]) {
					u_req[j] = cost[i][j] - u_res[i];
					u_req_used[j] = 1;
				}
				if (!u_res_used[i]) {
					u_res[i] = cost[i][j] - u_req[j];
					u_res_used[i] = 1;
				}
				dfs_potentials(Coordinate(i, j));
			}
		}
	}

	void find_potentials() {
		used = make_vec2i(resource.size(), request.size());
		u_res = vec1d(resource.size());
		u_req = vec1d(request.size());
		u_res_used = vec1i(resource.size());
		u_req_used = vec1i(request.size());
		for (int i = 0; i < resource.size(); i++) {
			for (int j = 0; j < request.size(); j++) {
				if (!used[i][j] && plan[i][j]) {
					u_req[j] = 0;
					u_req_used[j] = 1;
					u_res[i] = cost[i][j] - u_req[j];
					u_res_used[i] = 1;
					used[i][j] = 1;
					dfs_potentials(Coordinate(i, j));
				}
			}
		}
	}

	bool dfs_cycle(Coordinate c) {
		if (used[c.i][c.j] % 2) {
			for (int j = 0; j < request.size(); j++) {
				if (plan[c.i][j] && j != c.j) {
					if (used[c.i][j] == 1) {
						previous[c.i][j] = c;
						return true;
					}
					if (!used[c.i][j]) {
						used[c.i][j] = used[c.i][c.j] + 1;
						previous[c.i][j] = c;
						if (dfs_cycle(Coordinate(c.i, j)))
							return true;
						previous[c.i][j] = Coordinate(-1, -1);
						used[c.i][j] = 0;
					}
				}
			}
		}
		else {
			for (int i = 0; i < resource.size(); i++) {
				if (i != c.i && (used[i][c.j] == 1 || plan[i][c.j])) {
					if (used[i][c.j] == 1) {
						previous[i][c.j] = c;
						return true;
					}
					if (!used[i][c.j]) {
						used[i][c.j] = used[i][c.j] + 1;
						previous[i][c.j] = c;
						if (dfs_cycle(Coordinate(i, c.j)))
							return true;
						previous[i][c.j] = Coordinate(-1, -1);
						used[i][c.j] = 0;
					}
				}
			}
		}

		return false;
	}

	void optimize() {
		while (true) {
			find_potentials();
			for (int i = 0; i < resource.size(); i++) {
				for (int j = 0; j < request.size(); j++) {
					grade[i][j] = cost[i][j] - u_res[i] - u_req[j];
				}
			}
			cout << "New potentials, grades:\n";
			print();
			Coordinate c_min = { 0, 0 };
			for (int i = 0; i < resource.size(); i++) {
				for (int j = 0; j < request.size(); j++) {
					if (grade[i][j] < grade[c_min.i][c_min.j]) {
						c_min.i = i;
						c_min.j = j;
					}
				}
			}
			if (grade[c_min.i][c_min.j] >= 0) {
				break;
			}
			used = make_vec2i(resource.size(), request.size());
			previous = make_vec2c(resource.size(), request.size());
			used[c_min.i][c_min.j] = 1;
			dfs_cycle(c_min);
			Coordinate now = c_min;
			vec1c cycle;
			cycle.push_back(now);
			now = previous[now.i][now.j];
			while (now != c_min) {
				cycle.push_back(now);
				now = previous[now.i][now.j];
			}

			cout << "Find cycle: ";
			for (auto val : cycle)
				cout << val << ' ';
			cout << "\n";

			Coordinate cycle_c_min = cycle[1];
			for (int k = 3; k < cycle.size(); k++) {
				if (plan[cycle_c_min.i][cycle_c_min.j] > plan[cycle[k].i][cycle[k].j]) {
					cycle_c_min = cycle[k];
				}
			}
			double delta = plan[cycle_c_min.i][cycle_c_min.j];
			for (int k = 0; k < cycle.size(); k++) {
				if (k % 2) {
					plan[cycle[k].i][cycle[k].j] -= delta;
				} else {
					plan[cycle[k].i][cycle[k].j] += delta;
				}
			}
			cout << "After iteration (new plan):\n";
			print();
			cout << '\n';
		}
	}

};