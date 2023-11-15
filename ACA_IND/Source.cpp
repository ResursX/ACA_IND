#include <iostream>
#include <fstream>

#include <vector>

#include "../ACA_IND_LIB/GraphGenerator.h"
#include "../ACA_IND_LIB/IsomorphyCheck.h"

using namespace std;

void ReadMatrix(std::istream& stream, int** matrix, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			stream >> matrix[i][j];
		}
	}
}

void PrintMatrix(std::ostream& stream, int** matrix, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			stream << matrix[i][j] << " ";
		}

		stream << std::endl;
	}
}

// Тестирование оптимизировааного перебора

bool IsomorphyFull_test_1(int** g1, int** g2, size_t n, size_t* ord, size_t k, bool* used) {
	if (k == n) {
		for (size_t i = 0; i < n; i++) {
			for (size_t j = i + 1; j < n; j++) {
				if (g1[ord[i]][ord[j]] != g2[i][j])
				{
					return false;
				}
			}
		}

		return true;
	}

	for (size_t i = 0; i < n; i++) {
		if (!used[i]) {
			ord[k] = i;
			used[i] = true;

			if (IsomorphyFull_test_1(g1, g2, n, ord, k + 1, used))
				return true;

			used[i] = false;
		}
	}

	return false;
}

bool IsomorphyFull_test_2(int** g1, int** g2, size_t n, size_t* ord, size_t k, bool* used, int** tested) {
	if (k == n) {
		cout << "Tested values: ";
		PrintMatrix(cout, tested, n);

		return true;
	}

	bool l;

	for (size_t i = 0; i < n; i++) {
		if (!used[i]) {
			ord[k] = i;
			used[i] = true;

			l = true;

			for (size_t j = 0; j <= k && l; j++) {
				tested[k][j] = 1;
				tested[j][k] = 1;

				if (g1[i][ord[j]] != g2[k][j]) {
					l = false;
				}
			}

			if (l) {
				if (IsomorphyFull_test_2(g1, g2, n, ord, k + 1, used, tested))
					return true;
			}

			for (size_t j = 0; j <= k && l; j++) {
				tested[k][j] = 0;
				tested[j][k] = 0;
			}

			used[i] = false;
		}
	}

	return false;
}

bool IsomorphyFull_test(int** g1, int** g2, size_t n) {
	int
		** tested = new int* [n];

	size_t* ord = new size_t[n];
	bool
		a,
		b,
		* used = new bool[n];

	for (size_t i = 0; i < n; i++) {
		ord[i] = -1;
		used[i] = false;
	}

	a = IsomorphyFull_test_1(g1, g2, n, ord, 0, used);

	for (size_t i = 0; i < n; i++) {
		ord[i] = -1;
		used[i] = false;

		tested[i] = new int[n];

		for (size_t j = 0; j < n; j++) {
			tested[i][j] = 0;
		}
	}
	
	b = IsomorphyFull_test_2(g1, g2, n, ord, 0, used, tested);
	
	if (a != b) {
		std::cout << "ERROR " << a << " " << b << std::endl;
	} 

	delete[] ord;
	delete[] used;

	return a;
}

void main() {
	int n;

	std::ifstream finp("inp.txt");
	std::ofstream fout("out.txt", std::ios::app);

	// Ввод n
	finp >> n;

	// Инициализация матриц
	int 
		**g1 = new int*[n],
		**g2 = new int*[n];
	
	for (int  i = 0; i < n; i++) {
		g1[i] = new int[n];
		g2[i] = new int[n];

	// Генерация графов
	generateGraph(g1, n, 0.5),
	generateGraph(g2, n, 0.5);

	// Ввод матриц
	//ReadMatrix(finp, g1, n);
	//ReadMatrix(finp, g2, n);

	finp.close();

	// Print graphs

	fout << "N = " << n << std::endl << std::endl;

	PrintMatrix(fout, g1, n);

	fout << std::endl;

	PrintMatrix(fout, g2, n);

	fout << std::endl;

	fout << "Full check: " << IsomorphyFull_test(g1, g2, n) << std::endl;

	fout << "Randic invariant check: " << IsomorphyRandic(g1, g2, n) << std::endl;
	//fout << "Randic index for g1: " << CalcRandic(g1, n) << std::endl;
	//fout << "Randic index for g2: " << CalcRandic(g2, n) << std::endl << std::endl;

	fout << "Order 2 degree vector invariant check: " << IsomorphyDegVector(g1, g2, n) << std::endl << std::endl;

	fout.close();

	for (int i = 0; i < n; i++) {
		delete[] g1[i];
		delete[] g2[i];
	}

	delete[] g1;
	delete[] g2;
}