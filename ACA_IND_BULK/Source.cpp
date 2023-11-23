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

	//int*** graphs = genNGraphs(k * 2, n, r);

	int
		** g1 = new int* [n],
		** g2 = new int* [n];

	for (int i = 0; i < n; i++)
	{
		g1[i] = new int[n];
		g2[i] = new int[n];
	}

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

		generateGraph(g1, n, r);
		generateGraph(g2, n, r);

		// Перебор
		t = getCPUTime();

		l1 = IsomorphyFull(g1, g2, n);

		t_full += getCPUTime() - t;

		// Рандич
		t = getCPUTime();

		l2 = IsomorphyRandic(g1, g2, n);

		t_randic += getCPUTime() - t;

		if (l2 == l1) c_randic++;

		// Вектор
		t = getCPUTime();

		l2 = IsomorphyDegVector(g1, g2, n);

		t_vec += getCPUTime() - t;

		if (l2 == l1) c_vec++;
	}

	fout << "N = " << n << ", r = " << r << ", K = " << k  << endl;

	fout << "Pr = " << fixed << (double)c_randic / k * 100 << endl;
	fout << "Pv = " << fixed << (double)c_vec / k * 100 << endl;

	fout << "Tf = " << scientific << t_full << endl;
	fout << "Tr = " << scientific << t_randic << endl;
	fout << "Tv = " << scientific << t_vec << endl << endl;

	fout.close();

	//for (int i = 0; i < k * 2; i++) {
	//	for (int j = 0; j < n; j++) {
	//		delete[] graphs[i][j];
	//	}
	//
	//	delete[] graphs[i];
	//}
	//
	//delete[] graphs;

	for (int i = 0; i < n; i++) {
		delete[] g1[i];
		delete[] g2[i];
	}

	delete[] g1;
	delete[] g2;
}