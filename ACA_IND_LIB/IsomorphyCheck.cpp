#include "pch.h"

#include "IsomorphyCheck.h"

#include <iostream>
#include <forward_list>
#include <vector>
#include <algorithm>

using namespace std;

bool IsomorphyFull_Rec(AdjacencyMatrix& g1, AdjacencyMatrix& g2, size_t n, size_t* ord, size_t k, bool* used) {
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

			if (IsomorphyFull_Rec(g1, g2, n, ord, k + 1, used))
				return true;

			used[i] = false;
		}
	}

	return false;
}

bool IsomorphyFull_Rec_2(AdjacencyMatrix& g1, AdjacencyMatrix& g2, size_t n, size_t* ord, size_t k, bool* used) {
	if (k + 1 == n) {
		return true;
	}

	bool l;

	for (size_t i = 0; i < n; i++) {
		if (!used[i]) {
			ord[k] = i;
			used[i] = true;

			l = true;

			for (size_t j = 0; j <= k && l; j++) {
				if (g1[i][ord[j]] != g2[k][j]) {
					l = false;
				}
			}

			if (l) {
				if (IsomorphyFull_Rec_2(g1, g2, n, ord, k + 1, used))
					return true;
			}

			used[i] = false;
		}
	}

	return false;
}

// �������� �� ��������� � ������� ������� ��������
bool IsomorphyFull(AdjacencyMatrix& g1, AdjacencyMatrix& g2, size_t n) {
	size_t* ord = new size_t[n];
	bool
		a,
		b,
		* used = new bool[n];

	for (size_t i = 0; i < n; i++) {
		ord[i] = -1;
		used[i] = false;
	}

	a = IsomorphyFull_Rec(g1, g2, n, ord, 0, used);

	//for (size_t i = 0; i < n; i++) {
	//	ord[i] = -1;
	//	used[i] = false;
	//}
	//
	//b = IsomorphyFull_Rec_2(g1, g2, n, ord, 0, used);
	//
	//if (a != b) {
	//	std::cout << "ERROR " << a << " " << b << std::endl;
	//
	//	for (int i = 0; i < n; i++) {
	//		for (int j = 0; j < n; j++) {
	//			std::cout << g1[i][j] << " ";
	//		}
	//
	//		std::cout << std::endl;
	//	}
	//
	//	std::cout << std::endl;
	//
	//	for (int i = 0; i < n; i++) {
	//		for (int j = 0; j < n; j++) {
	//			std::cout << g2[i][j] << " ";
	//		}
	//
	//		std::cout << std::endl;
	//	}
	//
	//	std::cout << std::endl;
	//} 

	delete[] ord;
	delete[] used;

	return a;
}

// ���������� �������� ������
void CalcDeg(AdjacencyMatrix& g, size_t n, size_t* d) {
	for (size_t i = 0; i < n; i++) {
		d[i] = 0;

		for (size_t j = 0; j < n; j++) {
			if (i != j && g[i][j] > 0) {
				d[i]++;
			}
		}
	}
}

// ���������� ������� �������
double CalcRandic(AdjacencyMatrix& g, size_t n) {
	size_t* d = new size_t[n];

	double
		s = 0;

	CalcDeg(g, n, d);

	for (size_t i = 0; i < n; i++) {
		for (size_t j = i + 1; j < n; j++) {
			if (g[i][j] > 0) {
				s += 1 / sqrt(d[i] * d[j]);
			}
		}
	}

	return s;
}

// �������� �� ������������ � ������� ������� �������
const double eps_randic = 1E-12;

bool IsomorphyRandic(AdjacencyMatrix& g1, AdjacencyMatrix& g2, size_t n) {
	double
		r1 = CalcRandic(g1, n),
		r2 = CalcRandic(g2, n);

	// TODO: �������� �� ��������� �������� � �������?
	return abs(r1 - r2) < eps_randic;
}

// ������� � ���������������� ������ � ����������� �������
void ForawardListInsertSorted(forward_list<size_t>& list, size_t item) {
	forward_list<size_t>::iterator
		i = list.begin(),
		ip = list.before_begin();

	while (i != list.end() && (*i) < item) {
		ip = i;
		i++;
	}

	list.insert_after(ip, item);
}

struct TDegList {
	// ����� ��������� � ������
	size_t count;

	// ����� ��������
	size_t sum;

	// ������ �������� ������
	forward_list<size_t> degs;
};
typedef TDegList* PDegList;

struct {
	bool operator()(PDegList a, PDegList b) const {
		if (a->sum == b->sum) {
			size_t t1, t2;

			forward_list<size_t>::iterator
				i1 = a->degs.begin(),
				i1e = a->degs.end(),
				i2 = b->degs.begin(),
				i2e = b->degs.end();

			while (i1 != i1e && i2 != i2e) {
				t1 = *i1;
				t2 = *i2;

				if (t1 < t2) return false;
				if (t1 > t2) return true;

				i1++;
				i2++;
			}

			return false;
		}

		return a->sum < b->sum;
	}
} CompareDegList;

// �������� �� ������������ � ������� ������� �������� ������� �������
bool IsomorphyDegVector(AdjacencyMatrix& g1, AdjacencyMatrix& g2, size_t n) {
	size_t
		* d1 = new size_t[n],
		* d2 = new size_t[n];

	vector<PDegList> vd1(n), vd2(n);

	CalcDeg(g1, n, d1);
	CalcDeg(g2, n, d2);

	for (size_t i = 0; i < n; i++) {
		vd1[i] = new TDegList;

		vd1[i]->count = 0;
		vd1[i]->sum = 0;

		vd2[i] = new TDegList;

		vd2[i]->count = 0;
		vd2[i]->sum = 0;

		for (size_t j = 0; j < n; j++) {
			if (i != j) {
				if (g1[i][j] > 0) {
					ForawardListInsertSorted(vd1[i]->degs, d1[j]);

					vd1[i]->count++;
					vd1[i]->sum += d1[j];
				}

				if (g2[i][j] > 0) {
					ForawardListInsertSorted(vd2[i]->degs, d2[j]);

					vd2[i]->count++;
					vd2[i]->sum += d2[j];
				}
			}
		}
	}

	std::sort(vd1.begin(), vd1.end(), CompareDegList);
	std::sort(vd2.begin(), vd2.end(), CompareDegList);

	//cout << "VD1: " << endl;
	//for (size_t i = 0; i < n; i++) {
	//	PDegList tp = vd1[i];
	//
	//	cout << "V" << i << endl;
	//	cout << "S: " << tp->sum << endl;
	//	cout << "C: " << tp->count << endl;
	//	cout << "D:";
	//
	//	for (forward_list<size_t>::iterator it = tp->degs.begin(); it != tp->degs.end(); it++) {
	//		cout << " " << *it;
	//	}
	//
	//	cout << endl << endl;
	//}
	//
	//cout << "VD2: " << endl;
	//for (size_t i = 0; i < n; i++) {
	//	PDegList tp = vd2[i];
	//
	//	cout << "V" << i << endl;
	//	cout << "S: " << tp->sum << endl;
	//	cout << "C: " << tp->count << endl;
	//	cout << "D:";
	//
	//	for (forward_list<size_t>::iterator it = tp->degs.begin(); it != tp->degs.end(); it++) {
	//		cout << " " << *it;
	//	}
	//
	//	cout << endl << endl;
	//}

	PDegList p1, p2;

	forward_list<size_t>::iterator i1, i1e, i2;

	for (size_t i = 0; i < n; i++) {
		p1 = vd1[i];
		p2 = vd2[i];

		if (p1->count != p2->count || p1->sum != p2->sum) return false;

		i1 = p1->degs.begin();
		i1e = p1->degs.end();
		i2 = p2->degs.begin();

		while (i1 != i1e) {
			if ((*i1) != (*i2)) return false;

			i1++;
			i2++;
		}
	}

	return true;
}