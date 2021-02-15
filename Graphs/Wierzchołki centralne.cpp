//
//  main.cpp
//  Wierzchołki centralne
//
//  Created by Mikołaj Jędrzejewski on 4/1/20.
//  Copyright © 2020 Mikołaj Jędrzejewski. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct node {
    int c;
    bool vis;
    vector<int> adj;
};

void Central(vector<node> &G, queue<int> &Q) {
    int v, u, p=0;
    queue<int> PQ;
    while (p+Q.size()<G.size()) {
        while (!Q.empty()) {
            v=Q.front();
            for (int i=0; i<G[v].adj.size(); ++i)  {
                u=G[v].adj[i];
                ++G[u].c;
            }
            PQ.push(v);
            Q.pop();
            ++p;
        }
        while (!PQ.empty()) {
            v=PQ.front();
            for (int i=0; i<G[v].adj.size(); ++i)  {
                u=G[v].adj[i];
                if (!G[u].vis and (G[u].adj.size()-1==G[u].c or p+1==G.size())) {
                    Q.push(u);
                    G[u].vis=1;
                }
            }
            PQ.pop();
        }
    }
    while (!Q.empty()) {
        cout<<Q.front()<<" ";
        Q.pop();
    }
}

int main() {
    int n, m;
    cout<<"N, m: ";
    cin>>n>>m;
    vector<node> G(n);
    cout<<"Podaj krawędzi: ";
    int v, u;
    for (int i=0; i<m; ++i) {
        cin>>v>>u;
        G[v].adj.push_back(u);
        G[u].adj.push_back(v);
    }
    queue<int> Q;
    for (int i=0; i<n; ++i)
        if (G[i].adj.size()-1==G[i].c) {
            Q.push(i);
            G[i].vis=1;
        }
    
    cout<<"\nWierzchołki centralne: \n";
    Central(G, Q);
    cout<<"\n";
    
    return 0;
}
/*
 IN:
 11 10
 0 1
 0 2
 0 3
 0 4
 6 0
 5 6
 5 10
 6 7
 5 8
 8 9
 OUT: 5 6
 
 IN:
 10 9
 0 1
 0 2
 0 3
 0 4
 6 0
 5 6
 5 9
 6 7
 5 8
 OUT: 6
 */
