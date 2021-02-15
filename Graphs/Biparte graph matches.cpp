//
//  main.cpp
//  Bipartite graph matches
//
//  Created by Mikołaj Jędrzejewski on 5/12/20.
//  Copyright © 2020 Mikołaj Jędrzejewski. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

struct node {
    vector<int> adj;
    int m=-1;
    int vis;
    int color;
};

void devide(vector<node> &G, int v, int c) {
    G[v].color=c;
    int u;
    for (int i=0; i<(int)G[v].adj.size(); ++i) {
        u=G[v].adj[i];
        if (G[u].color==0) devide(G, u, c^3);
    }
}

bool match(vector<node> &G, int v, int &vis) {
    G[v].vis=vis;
    int u;
    for (int i=0; i<(int)G[v].adj.size(); ++i) {
        u=G[v].adj[i];
        if (G[u].m==-1) {
            G[u].m=v;
            return 1;
        }
    }
    for (int i=0; i<(int)G[v].adj.size(); ++i) {
        u=G[v].adj[i];
        if (G[G[u].m].vis!=vis and match(G, G[u].m, vis)) {
            G[u].m=v;
            return 1;
        }
    }
    return 0;
}

int main() {
    int n, m, v, u;
    cin>>n>>m;
    vector<node> G(n);
    for (int i=0; i<m; ++i) {
        cin>>v>>u;
        G[v].adj.push_back(u);
        G[u].adj.push_back(v);
    }
    devide(G, 0, 1);
    
    int c=0, vis=1;
    for (int i=0; i<n; ++i) {
        if (G[i].color==1 and match(G, i, vis)) {
            ++c;
            ++vis;
        }
    }
    
    cout<<c<<" matches:\n";
    for (int i=0; i<n; ++i)
        if (G[i].color==2 and G[i].m!=-1)
            cout<<G[i].m<<" "<<i<<"\n";
    
    return 0;
}
/*
 10 11
 0 7
 0 8
 1 5
 1 6
 1 8
 2 5
 3 6
 3 8
 3 9
 4 7
 4 8
 */
