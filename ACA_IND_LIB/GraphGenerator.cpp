#include "pch.h"

#include "GraphGenerator.h"

#include <iostream>
#include <cstddef>
#include <random>

//using AdjacencyMatrix = std::vector<std::vector<int>>;

std::mt19937 mt = std::mt19937(time(nullptr));

AdjacencyMatrix generateGraph(size_t vertexes, double edgesRate)
{
    AdjacencyMatrix matrix = AdjacencyMatrix(vertexes, std::vector<int>(vertexes, 0));
    size_t edges = (size_t)(vertexes * (vertexes - 1) / 2 * edgesRate);
    if (edges + 1 < vertexes)
    {
        std::cout << "Current rate " << edgesRate << " is too small for connected graph with " << vertexes << " vertexes\n";
        edges = vertexes - 1;
    }

    //std::mt19937 mt(time(nullptr));
    {
        std::vector<bool> used = std::vector<bool>(vertexes, false);
        used[mt() % vertexes] = true;
        for (size_t i = 1; i < vertexes; ++i)
        {
            int u;
            do { u = mt() % vertexes; }
            while (used[u]);
            int v;
            do { v = mt() % vertexes; }
            while (!used[v]);
            matrix[u][v] = matrix[v][u] = 1;
            used[u] = true;
        }
    }
    
    for (size_t i = vertexes - 1; i < edges; ++i)
    {
        int u, v;
        do {
            u = mt() % vertexes;
            v = mt() % vertexes;
        } while (u == v || matrix[u][v] == 1);
        matrix[u][v] = matrix[v][u] = 1;
    }

    return matrix;
}

std::vector<AdjacencyMatrix> genNGraphs(int countOfGraphs, size_t countOfVertexes, double edgesRate)
{
    std::vector<AdjacencyMatrix> graphs;
    for (int k = 0; k < countOfGraphs; ++k)
    {
        bool newGraph = true;
        AdjacencyMatrix graph;
        do {
            graph = generateGraph(countOfVertexes, edgesRate);
            for (auto& g : graphs)
            {
                newGraph = false;
                for (int i = 0; i < g.size(); ++i)
                {
                    if (g[i] != graph[i]) 
                    {
                        newGraph = true;
                        break;
                    }
                }
                if (newGraph) break;
            }
        } while (!newGraph);
        graphs.push_back(graph);
    }
    return graphs;
}