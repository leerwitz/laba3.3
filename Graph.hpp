#pragma once

#include <iostream>
#include <stack>
#include <vector>

// Структура данных для хранения узлов списка смежности
struct Node{
    int val;
    Node* next;
};


// Структура данных для хранения ребра Graph
struct Edge {
    int src, dest, weight;
};

struct Edge_ {
    int src, dest;
};

// Структура данных для определения посещенных вершин
struct Visited {
    bool atAll = false, InCycle = false;
};

class Graph
{

    int V;    // общее количество вершин в Graph
    int M;
    const int max = 1000000000;

public:
    std:: vector < std:: vector < std:: pair<int,int> > > head;
    std:: vector < std:: vector <int> > head1;

    // Конструктор
    Graph(const std::vector<Edge_>& edges, int M, int V)
    {
        head1.resize(V+1);
        //auto  head = new std:: vector < std:: vector < std:: pair<int,int> > >(V);
        this->V = V;
        this->M = M;

        for (unsigned i = 0; i < M; ++i)
        {

            head1[edges[i].src].push_back(edges[i].dest);


        }
    }

    Graph(const std::vector<Edge>& edges, int M, int V)
    {
        head.resize(V+1);
        this->V = V;
        this->M = M;

        std:: pair<int,int> d;

        for (unsigned i = 0; i < M; ++i)
        {
            int src = edges[i].src;
            d.first = edges[i].dest;
            d.second = edges[i].weight;
            head[src].push_back(d);
        }
    }

    ~Graph() {}


    // реалезация поиска в глубину
    void TopologicalSortUtil(int v, Visited *vis,  std::stack<int> & Stack){
        vis[v].atAll = true;
        vis[v].InCycle = true;
        // пока смежные вершины не кончатся
        for (int p = 0;p < head1[v].size();++p ){
            // если в графе имеется цикл немедленная остановка сортировки
            if (vis[head1[v][p]].InCycle){
                this->V = -1;
                break;
            }
                // если смежная вершина никогда не посещалась применяем к ней DFS
            else if (!vis[head1[v][p]].atAll)
                TopologicalSortUtil(head1[v][p], vis,Stack);
        }
        Stack.push(v);
        vis[v].InCycle = false;
    }

    // топологическая сортировка
    std::vector<int> TopologicalSort(){
        std::stack<int> Stack;
        std::vector<int> vector;
        auto vis = new Visited[V];
        // применяем метод DFS к каждое вершине графа
        for (unsigned i = 0; i < V; ++i) {
            if (!vis[i].atAll)
                TopologicalSortUtil(i, vis, Stack);
            if (this->V == -1)
                break;
        }
        //если граф циклический выводим -1
        if (this->V == -1) {
            vector.push_back(V);
            std::cout << V;
        }
        else
            //иначе выводим  отсортированные вершины
            while (Stack.empty() == false)
            {
                for (int i = 0; i < 16; ++i) {
                    vector.push_back(Stack.top());
                    std::cout << Stack.top() << " ";
                    Stack.pop();
                }
                std::cout << '\n';
            }
        return vector;
    }

    std::vector<int> AlgDykstra(int s){
        std:: vector<int> dist (V, max),  prev (V);
        dist[s] = 0;
        std:: vector<bool> u (V);
        for (int i=0; i<V; ++i) {
            int v = -1;
            for (int j=0; j<V; ++j)
                if (!u[j] && (v == -1 || dist[j] < dist[v]))
                    v = j;
            if (dist[v] == max)
                break;
            u[v] = true;

            for (size_t j=0; j<head[v].size(); ++j) {
                int to = head[v][j].first,
                        len = head[v][j].second;
                if (dist[v] + len < dist[to]) {
                    dist[to] = dist[v] + len;
                    prev[to] = v;
                }
            }
        }
        return dist;
    }

    std::vector<std::vector<int>> Floyd_Warshall(){
        std::vector<std::vector<int>> dist(V);
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                dist[i].push_back(max);

            }
            for (auto p : head[i])
                dist[i][p.first] = p.second;
        }
        for (int i = 0; i < V; ++i)
            dist[i][i] = 0;

        for (int k=0; k<V; ++k)
            for (int i=0; i<V; ++i)
                for (int j=0; j<V; ++j)
                    if (dist[i][k] < max && dist[k][j] < max)
                        dist[i][j] = std:: min (dist[i][j], dist[i][k] + dist[k][j]);
        return dist;
    }

    std::vector<int> ford(int s,std::vector<Edge> edges) {
        std:: vector<int> dist (V, max);
        dist[s] = 0;
        bool any = true;
        while (any) {
            any = false;
            for (int j=0; j<M; ++j)
                if (dist[edges[j].src] < max)
                    if (dist[edges[j].dest] > dist[edges[j].src] + edges[j].weight) {
                        dist[edges[j].dest] = dist[edges[j].src] + edges[j].weight;
                        any = true;
                    }
            if (!any)  break;
        }
        return dist;
    }
};