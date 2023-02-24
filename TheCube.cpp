// TheCube.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;

const int N = 30;
const double PI = acos(-1);
const double INF = 1e18;

vector<double> multiply(double matrix[3][3], vector<double> coord) {
	vector<double> res{0, 0, 0};
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			res[i] += matrix[i][j] * coord[j];
		}
	}
	return res;
}

void clear(pair<char, double> chcube[2 * N][2 * N]) {
	for (int i = 0; i < 2 * N; i++) {
		for (int j = 0; j < 2 * N; j++) {
			chcube[i][j] = make_pair(' ', -INF);
		}
	}
}

void make_side(vector<double> cube[N][N][N], pair<char, double> chcube[2 * N][2 * N], char pic, int x, int y, int z) {
	if (x == 0) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (chcube[(int)ceil(cube[0][i][j][0]) + N]
						  [(int)ceil(cube[0][i][j][1]) + N].second <= cube[0][i][j][2]) {
					chcube[(int)ceil(cube[0][i][j][0]) + N]
						  [(int)ceil(cube[0][i][j][1]) + N].first = pic;
					chcube[(int)ceil(cube[0][i][j][0]) + N]
						  [(int)ceil(cube[0][i][j][1]) + N].second = cube[0][i][j][2];
				}
			}
		}
	}
	if (x == N - 1) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (chcube[(int)ceil(cube[N - 1][i][j][0] + N)]
						  [(int)ceil(cube[N - 1][i][j][1] + N)].second < cube[N - 1][i][j][2]) {
					chcube[(int)ceil(cube[N - 1][i][j][0] + N)]
						  [(int)ceil(cube[N - 1][i][j][1] + N)].first = pic;
					chcube[(int)ceil(cube[N - 1][i][j][0] + N)]
						  [(int)ceil(cube[N - 1][i][j][1] + N)].second = cube[N - 1][i][j][2];
				}
			}
		}
	}
	if (y == 0) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (chcube[(int)ceil(cube[i][0][j][0] + N)]
						  [(int)ceil(cube[i][0][j][1] + N)].second < cube[i][0][j][2]) {
					chcube[(int)ceil(cube[i][0][j][0] + N)]
						  [(int)ceil(cube[i][0][j][1] + N)].first = pic;
					chcube[(int)ceil(cube[i][0][j][0] + N)]
						  [(int)ceil(cube[i][0][j][1] + N)].second = cube[i][0][j][2];
				}
			}
		}
	}
	if (y == N - 1) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (chcube[(int)ceil(cube[i][N - 1][j][0] + N)]
						  [(int)ceil(cube[i][N - 1][j][1] + N)].second < cube[i][N - 1][j][2]) {
					chcube[(int)ceil(cube[i][N - 1][j][0] + N)]
						  [(int)ceil(cube[i][N - 1][j][1] + N)].first = pic;
					chcube[(int)ceil(cube[i][N - 1][j][0] + N)]
						  [(int)ceil(cube[i][N - 1][j][1] + N)].second = cube[i][N - 1][j][2];
				}
			}
		}
	}
	if (z == 0) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (chcube[(int)ceil(cube[i][j][0][0] + N)]
						  [(int)ceil(cube[i][j][0][1] + N)].second < cube[i][j][0][2]) {
					chcube[(int)ceil(cube[i][j][0][0] + N)]
						  [(int)ceil(cube[i][j][0][1] + N)].first = pic;
					chcube[(int)ceil(cube[i][j][0][0] + N)]
						  [(int)ceil(cube[i][j][0][1] + N)].second = cube[i][j][0][2];
				}
			}
		}
	}
	if (z == N - 1) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (chcube[(int)ceil(cube[i][j][N - 1][0] + N)]
						  [(int)ceil(cube[i][j][N - 1][1] + N)].second < cube[i][j][N - 1][2]) {
					chcube[(int)ceil(cube[i][j][N - 1][0] + N)]
						  [(int)ceil(cube[i][j][N - 1][1] + N)].first = pic;
					chcube[(int)ceil(cube[i][j][N - 1][0] + N)]
						  [(int)ceil(cube[i][j][N - 1][1] + N)].second = cube[i][j][N - 1][2];
				}
			}
		}
	}
}

void smooth(pair<char, double> chcube[2 * N][2 * N]) {
	for (int i = 1; i < 2 * N - 1; i++) {
		for (int j = 1; j < 2 * N - 1; j++) {
			char a = chcube[i - 1][j].first;
			char b = chcube[i + 1][j].first;
			char c = chcube[i][j - 1].first;
			char d = chcube[i][j + 1].first;
			if (a == b and b == c and c == d) {
				chcube[i][j].first = a;
			}
		}
	}
}

int main()
{
	
	vector<double> cube[N][N][N];
	int i, j, k;
	double ii, jj, kk;
	for (i = 0, ii = -N / 2; i < N; i++, ii++) {
		for (j = 0, jj = -N / 2; j < N; j++, jj++) {
			for (k = 0, kk = -N / 2; k < N; k++, kk++) {
				cube[i][j][k] = vector<double>{ ii, jj, kk };
			}
		}
	}

	double theta = 3 * PI / 180;
	double rotation_matrix_x[3][3] = {
		{1, 0, 0},
		{0, cos(theta), -sin(theta)},
		{0, sin(theta), cos(theta)}
	};
	double rotation_matrix_y[3][3] = {
		{cos(theta), 0, -sin(theta)},
		{0, 1, 0},
		{sin(theta), 0, cos(theta)}
	};
	double rotation_matrix_z[3][3] = {
		{cos(theta), -sin(theta), 0},
		{sin(theta), cos(theta), 0},
		{0, 0, 1}
	};
	pair<char, double> chcube[2 * N][2 * N];
	

	while (true) {
		clear(chcube);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				for (int k = 0; k < N; k++) {
					cube[i][j][k] = multiply(rotation_matrix_x, cube[i][j][k]);
					cube[i][j][k] = multiply(rotation_matrix_y, cube[i][j][k]);
					cube[i][j][k] = multiply(rotation_matrix_z, cube[i][j][k]);
				}
			}
		}
		make_side(cube, chcube, '!', 0, -1, -1);
		make_side(cube, chcube, ':', N - 1, -1, -1);
		make_side(cube, chcube, '_', -1, 0, -1);
		make_side(cube, chcube, '$', -1, N - 1, -1);
		make_side(cube, chcube, '&', -1, -1, 0);
		make_side(cube, chcube, '@', -1, -1, N - 1);
		smooth(chcube);
		string outcube = "";
		for (int i = 0; i < 2 * N; i++) {
			for (int j = 0; j < 2 * N; j++) {
				outcube += chcube[i][j].first;
			}
			outcube += '\n';
		}
		system("CLS");
		cout << outcube << endl;
	}
}

