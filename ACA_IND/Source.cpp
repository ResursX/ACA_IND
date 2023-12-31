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

void main() {
	int n;

	std::ifstream finp("inp.txt");
	std::ofstream fout("out.txt", std::ios::app);

	// ���� n
	finp >> n;

	// ������������� ������
	int 
		**g1 = new int*[n],
		**g2 = new int*[n];
	
	for (int  i = 0; i < n; i++) {
		g1[i] = new int[n];
		g2[i] = new int[n];

	// ��������� ������
	//generateGraph(g1, n, 0.5),
	//generateGraph(g2, n, 0.5);

	// ���� ������
	ReadMatrix(finp, g1, n);
	ReadMatrix(finp, g2, n);

	finp.close();

	// Print graphs

	fout << "N = " << n << std::endl << std::endl;

	PrintMatrix(fout, g1, n);

	fout << std::endl;

	PrintMatrix(fout, g2, n);

	fout << std::endl;

	fout << "Full check: " << IsomorphyFull(g1, g2, n) << std::endl;

	fout << "Randic invariant check: " << IsomorphyRandic(g1, g2, n) << std::endl;

	fout << "Order 2 degree vector invariant check: " << IsomorphyDegVector(g1, g2, n) << std::endl << std::endl;

	fout.close();

	for (int i = 0; i < n; i++) {
		delete[] g1[i];
		delete[] g2[i];
	}

	delete[] g1;
	delete[] g2;
}