#include "pch.h"

#include "GraphGenerator.h"

#include <iostream>
#include <cstddef>
#include <random>

std::mt19937 mt(time(nullptr));

int** generateGraph(size_t vertexes, double edgesRate)
{
    int** matrix = new int*[vertexes];

    for (size_t i = 0; i < vertexes; i++) {
        matrix[i] = new int[vertexes];

        for (size_t j = 0; j < vertexes; j++) {
            matrix[i][j] = 0;
        }
    }

    size_t edges = (size_t)(vertexes * (vertexes - 1) / 2 * edgesRate);
    if (edges + 1 < vertexes)
    {
        std::cout << "Current rate " << edgesRate << " is too small for connected graph with " << vertexes << " vertexes\n";
        edges = vertexes - 1;
    }

    {
        std::vector<bool> used = std::vector<bool>(vertexes, false);
        used[mt() % vertexes] = true;
        for (size_t i = 1; i < vertexes; ++i)
        {
            int u;
            do { u = mt() % vertexes; } while (used[u]);
            int v;
            do { v = mt() % vertexes; } while (!used[v]);
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

int*** genNGraphs(int countOfGraphs, size_t countOfVertexes, double edgesRate)
{
    int its = 0;

    int*** graphs = new int**[countOfGraphs];

    for (int k = 0; k < countOfGraphs; ++k)
    {
        bool newGraph = true;

        int** graph;

        do {
            graph = generateGraph(countOfVertexes, edgesRate);

            for (int p = 0; p < k && newGraph; p++) {
                int** g = graphs[p];

                newGraph = false;

                for (size_t i = 0; i < countOfVertexes && !newGraph; i++)
                {
                    for (size_t j = 0; j < countOfVertexes && !newGraph; j++)
                    {
                        if (g[i][j] != graph[i][j])
                        {
                            newGraph = true;
                        }
                    }
                }
            }

            its++;
        } while (!newGraph);

        graphs[k] = graph;
    }

    std::cout << its << std::endl;

    return graphs;
}