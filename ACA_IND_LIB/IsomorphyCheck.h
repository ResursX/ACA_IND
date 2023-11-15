#pragma once
#include "GraphGenerator.h"

// Проверка на изоморфию с помощью полного перебора
bool IsomorphyFull(int** g1, int** g2, size_t n);

// Проверка на изоморфность с помощью индекса Рандича
bool IsomorphyRandic(int** g1, int** g2, size_t n);

// Проверка на изоморфность с помощью вектора степеней второго порядка
bool IsomorphyDegVector(int** g1, int** g2, size_t n);