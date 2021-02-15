//
//  main.cpp
//  Edmonds-Karp
//
//  Created by Mikołaj Jędrzejewski on 5/8/20.
//  Copyright © 2020 Mikołaj Jędrzejewski. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF=1e10;

struct edge {
    int v, u, cap, flow;
};

int bfs(vector<vector<int>> &G, vector<edge> &E, int s, int t) {
    int n=(int)G.size();
    int v, u, id;
    vector<int> f(n, -1);
    queue<int> Q;
    Q.push(s);
    f[s]=0;
    while (!Q.empty()) {
        v=Q.front();
        Q.pop();
        for (int i=0; i<G[v].size(); ++i) {
            id=G[v][i];
            u=E[id].u;
            if (E[id].flow<E[id].cap and f[u]==-1) {
                f[u]=id;
                Q.push(u);
            }
        }
    }
    if (f[t]==-1) return 0;
    int flow=INF;
    u=t;
    while (u!=s) {
        flow=min(flow, E[f[u]].cap-E[f[u]].flow);
        u=E[f[u]].v;
    }
    u=t;
    while (u!=s) {
        E[f[u]].flow+=flow;
        E[f[u]^1].flow-=flow;
        u=E[f[u]].v;
    }
    return flow;
}

int EdmondsKarp(vector<vector<int>> &G, vector<edge> &E, int s, int t) {
    int flow=0;
    int pushed;
    for (;;) {
        pushed=bfs(G, E, s, t);
        if (pushed==0) break;
        flow+=pushed;
    }
    return flow;
}

int main() {
    int n, m, v, u, c, s, t;
    cout<<"n, m, s, t: ";
    cin>>n>>m>>s>>t;
    vector<vector<int>> G(n, vector<int> {});
    edge e;
    vector<edge> E;
    for (int i=0; i<m; ++i) {
        cin>>v>>u>>c;
        e={v, u, c, 0};
        G[v].push_back((int)E.size());
        E.push_back(e);
        e={u, v, 0, 0};
        G[u].push_back((int)E.size());
        E.push_back(e);
    }
    
    cout<<"MAX FLOW: "<<EdmondsKarp(G, E, s, t)<<"\n";
    
    return 0;
}

/*
 6 9 0 5
 0 1 16
 0 2 13
 1 3 12
 2 1 4
 2 4 14
 3 2 9
 3 5 20
 4 3 7
 4 5 4
 */
