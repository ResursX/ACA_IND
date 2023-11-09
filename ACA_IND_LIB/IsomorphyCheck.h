#pragma once
#include "GraphGenerator.h"

// �������� �� ��������� � ������� ������� ��������
bool IsomorphyFull(AdjacencyMatrix& g1, AdjacencyMatrix& g2, size_t n);

// �������� �� ������������ � ������� ������� �������
bool IsomorphyRandic(AdjacencyMatrix& g1, AdjacencyMatrix& g2, size_t n);

// �������� �� ������������ � ������� ������� �������� ������� �������
bool IsomorphyDegVector(AdjacencyMatrix& g1, AdjacencyMatrix& g2, size_t n);