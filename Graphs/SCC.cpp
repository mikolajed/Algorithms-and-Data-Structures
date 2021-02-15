//
//  main.cpp
//  Silnie Spójne Składowe
//
//  Created by Mikołaj Jędrzejewski on 10/8/19.
//  Copyright © 2019 Mikołaj Jędrzejewski. All rights reserved.
//

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

void dfs(vector<int> *G, vector<bool> &V, int v, stack<int> &S) {
    int u;
    V[v]=1;
    for (int i=0; i<G[v].size(); ++i) {
        u=G[v][i];
        if (!V[u]) dfs(G, V, u, S);
    }
    S.push(v);
}

void SCC(vector<int> *G, vector<bool> &V, int v) {
    int u;
    V[v]=1;
    cout<<v<<" ";
    for (int i=0; i<G[v].size(); ++i) {
        u=G[v][i];
        if (!V[u]) SCC(G, V, u);
    }
}

void print(vector<int> *G, int n) {
    for (int i=0; i<n; ++i) {
        cout<<i<<": ";
        for (int j=0; j<G[i].size(); ++j)   cout<<G[i][j]<<" ";
        cout<<"\n";
    }
}

int main() {
    int n, m;
    cout<<"n, m: ";
    cin>>n>>m;
    vector<int> G[n], T[n];
    vector<bool> V1(n), V2(n);
    int x, y;
    for (int i=0; i<m; ++i) {
        cin>>x>>y;
        G[x].push_back(y);
        T[y].push_back(x);
    }
    cout<<"\n";
    
    stack <int> S;
    
    for (int i=0; i<n; ++i)
        if (!V1[i]) dfs(G, V1, i, S);
    
    int v;
    int c=0;
    while (!S.empty()) {
        v=S.top();
        S.pop();
        if (!V2[v]) {
            ++c;
            cout<<c<<": ";
            SCC(T, V2, v);
            cout<<"\n";
        }
    }

    return 0;
}

/*
 8 10
 0 3
 0 2
 0 4
 2 1
 3 1
 3 4
 3 5
 5 6
 6 7
 7 5
 */
