//
//  main.cpp
//  LCA
//
//  Created by Mikołaj Jędrzejewski on 8/26/20.
//  Copyright © 2020 Mikołaj Jędrzejewski. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

struct node {
    int p;      //parent node
    int d;      //depth from the root
    int deg=1;  //degree of a node, including the parent node
};

int n;
int root=1;
vector<node> T;                  //contains parent node
vector<vector<int>> Ancestor;

void CalcAncestorTable(int k) {
    Ancestor=vector<vector<int>> (n, vector<int> (k));
    
    for (int i=1; i<=n; ++i) Ancestor[i][0]=T[i].p;
    for (int i=1; i<k; ++i)
        for (int j=1; j<=n; ++j)
            Ancestor[j][i]=Ancestor[Ancestor[j][i-1]][i-1];
}

void CalcDepths() {
    for (int i=1; i<=n; ++i) ++T[T[i].p].deg;
    stack<int> S;
    queue<int> Q;
    for (int i=1; i<=n; ++i)
        if (T[i].deg==1) {
            Q.push(i);
            S.push(i);
        }
    
    vector<bool> vis(n+1);
    while (!Q.empty()) {
        int v=Q.front();
        Q.pop();
        if (!vis[T[v].p]) {
            Q.push(T[v].p);
            S.push(T[v].p);
        }
        vis[v]=1;
    }
    int r=S.top();    //root
    S.pop();
    T[r].d=0;
    while (!S.empty()) {
        int v=S.top();
        S.pop();
        T[v].d=T[ T[v].p ].d+1;
    }
}

int LCA(int a, int b) {
    if (T[a].d<T[b].d) swap(a, b);
    
    for (int k=20; k>=0; --k)
        if (T[Ancestor[b][k]].d >= T[a].d) b=Ancestor[b][k];
    
    if (a==b) return a; //b is in the subtree of a
    
    for (int k=20; k>=0; --k)
        if (Ancestor[a][k] != Ancestor[b][k]) {
            a=Ancestor[a][k];
            b=Ancestor[b][k];
        }
    return T[a].p;
}

int main() {
    
    cin>>n;
    T=vector<node> (n+1);
    for (int i=1; i<=n; ++i) cin>>T[i].p;
    
    CalcAncestorTable(21);
    
    return 0;
}
