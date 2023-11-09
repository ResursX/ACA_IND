#include "../ACA_IND_LIB/GraphGenerator.h"
#include "../ACA_IND_LIB/IsomorphyCheck.h"

#include <iostream>
#include <fstream>

using namespace std;

void main() {
	int n, k;

	double r;

	ifstream finp("in.txt");
	ofstream fout("out.txt", std::ios::app);

	// ¬вод n
	finp >> n >> k >> r;

	vector<AdjacencyMatrix> graphs = genNGraphs(k * 2, n, r);

	int c_randic = 0,
		c_vec = 0;

	bool t1, t2;

	for (int i = 0; i < k; i++) {
		t1 = IsomorphyFull(graphs[2 * i], graphs[2 * i + 1], n);

		t2 = IsomorphyRandic(graphs[2 * i], graphs[2 * i + 1], n);
		if (t2 == t1) c_randic++;

		t2 = IsomorphyDegVector(graphs[2 * i], graphs[2 * i + 1], n);
		if (t2 == t1) c_vec++;
	}

	fout << c_randic << endl;
	fout << c_vec << endl << endl;

	fout.close();
}