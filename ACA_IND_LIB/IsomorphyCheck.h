#pragma once
#include "GraphGenerator.h"

// �������� �� ��������� � ������� ������� ��������
bool IsomorphyFull(int** g1, int** g2, size_t n);

// �������� �� ������������ � ������� ������� �������
bool IsomorphyRandic(int** g1, int** g2, size_t n);

// �������� �� ������������ � ������� ������� �������� ������� �������
bool IsomorphyDegVector(int** g1, int** g2, size_t n);