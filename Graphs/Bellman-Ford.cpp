//
//  main.cpp
//  Bellman-Ford
//
//  Created by Mikołaj Jędrzejewski on 8/27/20.
//  Copyright © 2020 Mikołaj Jędrzejewski. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF=1e8;

struct edge {
    int w, v;
    bool operator<(const edge& e) const
    {
        return w > e.w;
    }
};

struct node {
    vector<int> adj;
};

int n, m;
int s=0; //starting node
vector<node> G;
vector<vector<int>> W;
vector<int> D;

void InitGraph() {
    G=vector<node> (n);
    W=vector<vector<int>> (n, vector<int> (n, INF));
    D=vector<int> (n, INF);
    D[s]=0;
}

bool BellmanFord() {
    priority_queue<edge> pq;
    D[s]=0;
    pq.push({0, s});
    for (int I=1; I<n; ++I)
        for (int v=0; v<n; ++v)
            for (auto u: G[v].adj)
                if (D[v] + W[v][u] < D[u])
                    D[u]=D[v] + W[u][v];
    //checking if a cycle exists
    for (int v=1; v<n; ++v)
        for (int i: G[v].adj)
            if (D[v] + W[v][i] < D[i])
                return false;
    return true;
}

int main() {
    cin>>n>>m;
    
    InitGraph();
    
    for (int i=0; i<m; ++i) {
        int u, v, w;
        cin>>v>>u>>w;
        G[v].adj.push_back(u);
        G[u].adj.push_back(v);
        W[v][u]=W[u][v]=w;
    }
    
    if (BellmanFord()) {
        cout<<"D: \n";
        for (auto d: D) cout<<d<<" ";
    }
    else {
        cout<<"Negative cycle detectd.\n";
    }
    
    return 0;
}
/*
 IN
 9 14
 0 1 4
 0 7 8
 1 2 8
 1 7 11
 2 3 7
 2 8 2
 2 5 4
 3 4 9
 3 5 14
 4 5 10
 5 6 2
 6 7 1
 6 8 6
 7 8 7
 OUT
 0 4 12 19 21 11 9 8 14
 
 IN
 9 14
 0 1 -4
 0 7 -8
 1 2 8
 1 7 -11
 2 3 7
 2 8 2
 2 5 4
 3 4 9
 3 5 14
 4 5 10
 5 6 2
 6 7 1
 6 8 6
 7 8 7
  */

