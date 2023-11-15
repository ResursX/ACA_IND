#include "pch.h"

#include "IsomorphyCheck.h"

#include <iostream>
#include <forward_list>
#include <algorithm>

using namespace std;

//bool IsomorphyFull_Rec_t(int** g1, int** g2, size_t n, size_t* ord, size_t k, bool* used) {
//	if (k == n) {
//		for (size_t i = 0; i < n; i++) {
//			for (size_t j = i + 1; j < n; j++) {
//				if (g1[ord[i]][ord[j]] != g2[i][j])
//				{
//					return false;
//				}
//			}
//		}
//
//		return true;
//	}
//
//	for (size_t i = 0; i < n; i++) {
//		if (!used[i]) {
//			ord[k] = i;
//			used[i] = true;
//
//			if (IsomorphyFull_Rec_t(g1, g2, n, ord, k + 1, used))
//				return true;
//
//			used[i] = false;
//		}
//	}
//
//	return false;
//}

bool IsomorphyFull_Rec(int** g1, int** g2, size_t n, size_t* ord, size_t k, bool* used) {
	if (k == n) {
		//for (size_t i = 0; i < n; i++) {
		//	for (size_t j = i + 1; j < n; j++) {
		//		if (g1[ord[i]][ord[j]] != g2[i][j])
		//		{
		//			return false;
		//		}
		//	}
		//}

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
				if (IsomorphyFull_Rec(g1, g2, n, ord, k + 1, used))
					return true;
			}

			used[i] = false;
		}
	}

	return false;
}

// Проверка на изоморфию с помощью полного перебора
bool IsomorphyFull(int** g1, int** g2, size_t n) {
	size_t* ord = new size_t[n];
	bool
	//	t,
		b,
		* used = new bool[n];

	//for (size_t i = 0; i < n; i++) {
	//	used[i] = false;
	//}
	//
	//t = IsomorphyFull_Rec_t(g1, g2, n, ord, 0, used);

	for (size_t i = 0; i < n; i++) {
		used[i] = false;
	}

	b = IsomorphyFull_Rec(g1, g2, n, ord, 0, used);

	//if (t != b) {
	//	std::cout << "ERROR " << t << " " << b << std::endl;
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
	//
	//}

	delete[] ord;
	delete[] used;

	return b;
}

// Нахождение степеней вершин
void CalcDeg(int** g, size_t n, size_t* d) {
	for (size_t i = 0; i < n; i++) {
		d[i] = 0;

		for (size_t j = 0; j < n; j++) {
			if (i != j && g[i][j] > 0) {
				d[i]++;
			}
		}
	}
}

// Вычисление индекса Рандича
double CalcRandic(int** g, size_t n) {
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

// Проверка на изоморфность с помощью индекса Рандича
const double eps_randic = 1E-12;

bool IsomorphyRandic(int** g1, int** g2, size_t n) {
	double
		r1 = CalcRandic(g1, n),
		r2 = CalcRandic(g2, n);

	// TODO: заменить на сравнение разности с эпсилон?
	return abs(r1 - r2) < eps_randic;
}

// Вставка в однонаправленный список с сохранением порядка
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
	// Число степенкей в списке
	size_t count;

	// Сумма степеней
	size_t sum;

	// Список степеней вершин
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

// Проверка на изоморфность с помощью вектора степеней второго порядка
bool IsomorphyDegVector(int** g1, int** g2, size_t n) {
	size_t
		* d1 = new size_t[n],
		* d2 = new size_t[n];

	PDegList
		* vd1 = new PDegList[n],
		* vd2 = new PDegList[n];

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

	std::sort(vd1, vd1 + n, CompareDegList);
	std::sort(vd2, vd2 + n, CompareDegList);

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

		delete p1;
		delete p2;
	}

	delete[] d1;
	delete[] d2;

	delete[] vd1;
	delete[] vd2;

	return true;
}