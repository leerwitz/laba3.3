#pragma once

#include <iostream>
#include "Graph.hpp"
#include <vector>
#include <assert.h>

void Test_of_TopSort () {
    auto edges = std::vector<Edge_>(6);
    edges[0].src = 5;
    edges[0].dest = 2;
    edges[1].src = 5;
    edges[1].dest = 0;
    edges[2].src = 4;
    edges[2].dest = 0;
    edges[3].src = 4;
    edges[3].dest = 1;
    edges[4].src = 2;
    edges[4].dest = 3;
    edges[5].src = 3;
    edges[5].dest = 1;
    Graph graph = Graph(edges, 6,6);
    std:: vector<int> vector(6);
    vector[0]= 5;
    vector[1]= 4;
    vector[2]= 2;
    vector[3]= 3;
    vector[4]= 1;
    vector[5]= 0;
    std::vector<int> graph_ = graph.TopologicalSort();
    for (int i = 0; i < graph_.size(); ++i) {
        assert(graph_[i] == vector[i]);
    }
}

void Test_of_TopSort_Cycle() {
    auto edges = std::vector<Edge_>(6);
    for (int i = 0; i < 5; ++i) {
        edges[i].src = i;
        edges[i].dest = i+1;
    }
    edges[5].src = 5;
    edges[5].dest = 0;
    Graph graph = Graph(edges, 6,6);
    std::vector<int> graph_ = graph.TopologicalSort();
    assert(graph_.size() == 1);
    assert(graph_[0] == -1);
}

void Test_of_AlgDykstra(){
    auto edges = std::vector<Edge>(5);
    edges[0].src = 3;
    edges[0].dest = 1;
    edges[0].weight = 5;
    edges[1].src = 3;
    edges[1].dest = 2;
    edges[1].weight = 6;
    edges[2].src = 2;
    edges[2].dest = 1;
    edges[2].weight = 7;
    edges[3].src = 2;
    edges[3].dest = 4;
    edges[3].weight = 3;
    edges[4].src = 4;
    edges[4].dest = 3;
    edges[4].weight = 8;
    Graph graph = Graph(edges, 5,5);
    std:: vector<int> graph_ = graph.AlgDykstra(4);
    std:: vector<int> vector(5);
    vector[0] = 1000000000;
    vector[1] =13;
    vector[2] = 14;
    vector[3] = 8;
    vector[4] = 0;
    for (int i = 0; i < graph_.size(); ++i) {
        assert(graph_[i] == vector[i]);
    }
}


void Test_of_Floyd_Warshall(){
    auto edges = std::vector<Edge>(5);
    edges[0].src = 0;
    edges[0].dest = 1;
    edges[0].weight = 5;
    edges[1].src = 0;
    edges[1].dest = 2;
    edges[1].weight = 6;
    edges[2].src = 2;
    edges[2].dest = 1;
    edges[2].weight = 7;
    edges[3].src = 2;
    edges[3].dest = 0;
    edges[3].weight = 3;
    edges[4].src = 1;
    edges[4].dest = 2;
    edges[4].weight = 8;
    Graph graph = Graph(edges, 5,3);
    auto graph_ = graph.Floyd_Warshall();
    std::vector<std::vector<int>> vector(3);
    vector[0].resize(3);
    vector[1].resize(3);
    vector[2].resize(3);
    vector[0][0] = 0;
    vector[0][1] = 5;
    vector[0][2] = 6;
    vector[1][0] = 11;
    vector[1][1] = 0;
    vector[1][2] = 8;
    vector[2][0] = 3;
    vector[2][1] = 7;
    vector[2][2] = 0;
    for (int i = 0; i < vector.size(); ++i) {
        for (int j = 0; j < vector.size(); ++j) {
            assert(graph_[i][j] == vector[i][j]);
        }
    }
}

void Test_of_Ford (){
    auto edges = std::vector<Edge>(5);
    edges[0].src = 3;
    edges[0].dest = 1;
    edges[0].weight = 5;
    edges[1].src = 3;
    edges[1].dest = 2;
    edges[1].weight = 6;
    edges[2].src = 2;
    edges[2].dest = 1;
    edges[2].weight = 7;
    edges[3].src = 2;
    edges[3].dest = 4;
    edges[3].weight = 3;
    edges[4].src = 4;
    edges[4].dest = 3;
    edges[4].weight = 8;
    Graph graph = Graph(edges, 5,5);
    std:: vector<int> graph_ = graph.ford(4,edges);
    std:: vector<int> vector(5);
    vector[0] = 1000000000;
    vector[1] =13;
    vector[2] = 14;
    vector[3] = 8;
    vector[4] = 0;
    for (int i = 0; i < graph_.size(); ++i) {
        assert(graph_[i] == vector[i]);
    }
}


void Run_All_Tests(){
    Test_of_TopSort();
    Test_of_TopSort_Cycle();
    Test_of_AlgDykstra();
    Test_of_Floyd_Warshall();
    Test_of_Ford();
}