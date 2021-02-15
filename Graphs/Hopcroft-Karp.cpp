//
//  main.cpp
//  Hopcroft-Karp
//
//  Created by Mikołaj Jędrzejewski on 5/13/20.
//  Copyright © 2020 Mikołaj Jędrzejewski. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

struct node {
    vector<int> adj;
    int m;
    bool u, d, vis;
};

bool Append(vector<node> &G, int v) {
    int n=(int)G.size();
    for (int i=v; i<n; ++i) {
        if (G[v].adj[i] and G[i].d and !G[i].vis and G[v].m!=i) {
            G[i].vis=1;
            if (G[i].m==-1 or Append(G, G[i].m)) {
                G[v].m=i;
                G[i].m=v;
                return 1;
            }
        }
    }
    return 0;
}

int Match(vector<node> &G) {
    int m=0, n=(int)G.size(), ap;
    do {
        ap=0;
        for (int i=0; i<n; ++i) {
            if (G[i].u and G[i].m==-1) {
                if (Append(G, i)) {
                    ap=1;
                    ++m;
                    for (int j=0; j<n; ++j) G[j].vis=0;
                }
            }
        }
    } while (ap);
    return m;
}

int main() {
    int n, m, u, v;
    cin>>n>>m;
    vector<node> G(n);
    for (int i=0; i<m; ++i) {
        cin>>v>>u;
        G[v].adj.push_back(u);
    }
    
    for (int i=0; i<n; ++i) {
        if (G[0].adj[i])   G[i].u=1;
        if (G[i].adj[n-1]) G[i].d=1;
    }
    
    Match(G);
    
    int c=0;
    for (int i=0; i<n; ++i)
        if (G[i].u and G[i].m!=-1) ++c;
    
    cout<<"Found "<<c<<" matches\n";
    for (int i=0; i<n; ++i)
        if (G[i].u and G[i].m!=-1)
            cout<<G[i].m<<" "<<i<<"\n";
    
    return 0;
}
/*
 
 */
