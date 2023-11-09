#pragma once
#include "GraphGenerator.h"

// Проверка на изоморфию с помощью полного перебора
bool IsomorphyFull(AdjacencyMatrix& g1, AdjacencyMatrix& g2, size_t n);

// Проверка на изоморфность с помощью индекса Рандича
bool IsomorphyRandic(AdjacencyMatrix& g1, AdjacencyMatrix& g2, size_t n);

// Проверка на изоморфность с помощью вектора степеней второго порядка
bool IsomorphyDegVector(AdjacencyMatrix& g1, AdjacencyMatrix& g2, size_t n);