//
//  main.cpp
//  Dijkstra
//
//  Created by Mikołaj Jędrzejewski on 5/26/20.
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

int main() {
    int n, m, u, v, w;
    cin>>n>>m;
    vector<node> G(n);
    vector<vector<int>> W(n, vector<int> (n, INF));
    
    for (int i=0; i<m; ++i) {
        cin>>v>>u>>w;
        G[v].adj.push_back(u);
        G[u].adj.push_back(v);
        W[v][u]=W[u][v]=w;
    }
    
    vector<int> D(n, INF);
    priority_queue<edge> pq;
    cin>>v;
    D[v]=0;
    pq.push({0, v});
    while (!pq.empty()) {
        v=pq.top().v;
        pq.pop();
        for (auto u: G[v].adj) {
            w=W[v][u];
            if (D[u]>D[v]+w) {
                D[u]=D[v]+w;
                pq.push({D[u], u});
            }
        }
    }
    
    cout<<"D: \n";
    for (auto d: D) cout<<d<<" ";

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
 0
 OUT
 0 4 12 19 21 11 9 8 14
  */
