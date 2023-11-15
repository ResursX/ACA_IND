#include "pch.h"

#include "GraphGenerator.h"

#include <iostream>
#include <cstddef>
#include <random>

std::mt19937 mt(time(nullptr));

int** generateGraph(size_t vertexes, double edgesRate)
{
    int** matrix = new int*[vertexes]; //AdjacencyMatrix(vertexes, std::vector<int>(vertexes, 0));

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

    bool* used = new bool[vertexes];

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
    int*** graphs = new int**[countOfGraphs];

    for (int k = 0; k < countOfGraphs; ++k)
    {
        bool newGraph = true;

        int** graph;

        do {
            graph = generateGraph(countOfVertexes, edgesRate);

            for (int i = 0; i < k; k++) {
                int** g = graphs[i];

                newGraph = false;

                for (int i = 0; i < countOfVertexes && !newGraph; i++)
                {
                    for (int j = 0; j < countOfVertexes && !newGraph; j++)
                    {
                        if (g[i][j] != graph[i][j])
                        {
                            newGraph = true;
                        }
                    }
                }
                if (newGraph) break;
            }

            //for (auto& g : graphs)
            //{
            //    newGraph = false;
            //    for (int i = 0; i < g.size(); ++i)
            //    {
            //        if (g[i] != graph[i]) 
            //        {
            //            newGraph = true;
            //            break;
            //        }
            //    }
            //    if (newGraph) break;
            //}
        } while (!newGraph);

        graphs[k] = graph; //graphs.push_back(graph);
    }
    return graphs;
}