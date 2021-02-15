//
//  main.cpp
//  Średnica drzewa
//
//  Created by Mikołaj Jędrzejewski on 4/7/20.
//  Copyright © 2020 Mikołaj Jędrzejewski. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct node {
    vector<int> adj;
    int t=-1;
};

void bfs (vector<node> &G, int n, int v) {
    queue<int> Q, L;
    int u;
    Q.push(v);
    int t=0;
    G[v].t=0;
    while (!Q.empty()) {
        ++t;
        while (!Q.empty()) {
            v=Q.front();
            Q.pop();
            for (int i=0; i<G[v].adj.size(); ++i) {
                u=G[v].adj[i];
                if (G[u].t==-1) L.push(u);
            }
        }
        while (!L.empty()) {
            v=L.front();
            L.pop();
            G[v].t=t;
            Q.push(v);
        }
    }
}

vector<int> Central (vector<node> &G, int a, int b, int c) {
    if (G[a].t!=c) {
        int mx=0, u;
        for (int i=0; i<G[a].adj.size(); ++i) {
            u=G[a].adj[i];
            if (G[u].t>G[mx].t) mx=u;
        }
        return Central(G, G[a].adj[mx], b, c);
    }
    else {
        vector<int> C;
        C.push_back(a);
        int mx=0, u;
        if (G[b].t%2) {
            for (int i=0; i<G[a].adj.size(); ++i) {
                u=G[a].adj[i];
                if (G[u].t>G[mx].t) mx=u;
            }
            C.push_back(G[a].adj[mx]);
        }
        return C;
    }
}

void retireve (vector<node> &G, int a, int b) {
    int u, mx;
    while (a!=b) {
        cout<<a<<" ";
        mx=0;
        for (int i=0; i<G[a].adj.size(); ++i) {
            u=G[a].adj[i];
            if (G[u].t>G[mx].t) mx=i;
        }
        a=G[a].adj[mx];
    }
    cout<<b<<"\n";
}

int main() {
    int n, m;
    cout<<"n, m: ";
    cin>>n>>m;
    cout<<"T: \n";
    vector<node> T(n);
    int u, v;
    for (int i=0; i<m; ++i) {
        cin>>v>>u;
        --u;
        --v;
        T[v].adj.push_back(u);
        T[u].adj.push_back(v);
    }
    
    int r=0;
    for (int i=0; i<n; ++i)
        if (T[i].adj.size()==1) {
            r=i;
            break;
        }
    
    bfs(T, n, r);
    
    int a=0, b=0;
    for (int i=0; i<n; ++i)
        if (T[i].t>T[a].t) a=i;
    for (int i=0; i<n; ++i) T[i].t=-1;
    
    bfs(T, n, a);
    for (int i=0; i<n; ++i)
        if (T[i].t>T[b].t) b=i;
    
    /*cout<<"Lonest path: "<<a<<"-"<<b<<"\n";
    vector<int> C=Central(T, a, b, T[b].t/2);
    cout<<"Central: ";
    for (int i=0; i<C.size(); ++i) cout<<C[i]<<" ";
    cout<<"\n";
     */
    
    retireve(T, a, b);
    
    return 0;
}

/*
 6 5
 1 2
 2 3
 3 4
 4 5
 4 6
 
 7 6
 1 2
 2 3
 3 4
 4 5
 4 6
 5 7
 */
