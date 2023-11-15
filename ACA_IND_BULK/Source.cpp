#include "../ACA_IND_LIB/GraphGenerator.h"
#include "../ACA_IND_LIB/IsomorphyCheck.h"
#include "../ACA_IND_LIB/GetCPUTime.h"

#include <iostream>
#include <fstream>

using namespace std;

void main() {
	int n, k;

	double r;

	ifstream finp("in.txt");
	ofstream fout("out.txt", std::ios::app);

	// Ввод n
	finp >> n >> k >> r;

	vector<AdjacencyMatrix> graphs = genNGraphs(k * 2, n, r);

	int c_randic = 0,
		c_vec = 0;

	double
		t,
		t_full = 0,
		t_randic = 0,
		t_vec = 0;

	bool l1, l2;

	for (int i = 0; i < k; i++) {
		//cout << i << endl;

		// Перебор
		t = getCPUTime();

		l1 = IsomorphyFull(graphs[2 * i], graphs[2 * i + 1], n);

		t_full += getCPUTime() - t;

		// Рандич
		t = getCPUTime();

		l2 = IsomorphyRandic(graphs[2 * i], graphs[2 * i + 1], n);

		t_randic += getCPUTime() - t;

		if (l2 == l1) c_randic++;

		// Вектор
		t = getCPUTime();

		l2 = IsomorphyDegVector(graphs[2 * i], graphs[2 * i + 1], n);

		t_vec += getCPUTime() - t;

		if (l2 == l1) c_vec++;
	}

	fout << "N = " << n << ", K = " << k << ", r = " << r << endl;

	fout << "Pr = " << fixed << (double)c_randic / k * 100 << endl;
	fout << "Pv = " << fixed << (double)c_vec / k * 100 << endl;

	fout << "Tf = " << scientific << t_full << endl;
	fout << "Tr = " << scientific << t_randic << endl;
	fout << "Tv = " << scientific << t_vec << endl << endl;

	fout.close();
}