#pragma once
#include <vector>

using AdjacencyMatrix = std::vector<std::vector<int>>;

AdjacencyMatrix generateGraph(size_t vertexes, double edgesRate);

std::vector<AdjacencyMatrix> genNGraphs(int countOfGraphs, size_t countOfVertexes, double edgesRate);