//
//  main.cpp
//  Izomorfizm drzew
//
//  Created by Mikołaj Jędrzejewski on 4/7/20.
//  Copyright © 2020 Mikołaj Jędrzejewski. All rights reserved.
//

#include <iostream>
#include <map>
#include <unordered_map>
#include <set>
#include <vector>
#include <queue>

using namespace std;

struct node {
    vector<int> adj;
    int index=-1;
    multiset<int> L;
};

int h(multiset<int> M) {
    int x=13;
    int mod=1e9+7;
    int h=0;
    for (auto it=M.begin(); it!=M.end(); ++it) {
        h+=*it;
        h*=x;
        h%=mod;
    }
    return h;
}

bool Izomorfic (vector<node> &T1, vector<node> &T2, int r1, int r2, int n, int m) {
    queue<int> Q1, Q2;
    unordered_map<int, int> A;
    multiset<int> L1, L2;
    for (int i=0; i<n; ++i) {
        if (T1[i].adj.size()==1) {
            Q1.push(i);
            T1[i].index=0;
        }
        if (T2[i].adj.size()==1) {
            Q2.push(i);
            T2[i].index=0;
        }
    }
    int ix=0, v, u, s1, s2, hash;
    while (!Q1.empty() and !Q2.empty()) {
        s1=(int)Q1.size();
        s2=(int)Q2.size();
        L1.clear();
        L2.clear();
        for (int i=0; i<s1; ++i) {
            v=Q1.front();
            Q1.pop();
            L1.insert(T1[v].index);
            for (int j=0; j<T1[v].adj.size(); ++j) {
                u=T1[v].adj[j];
                if (T1[u].index==-1) {
                    T1[u].L.insert(T1[v].index);
                    if (T1[u].L.size()+1==T1[u].adj.size()) {
                        hash=h(T1[u].L);
                        if (!A[hash]) {
                            ++ix;
                            A[hash]=ix;
                        }
                        T1[u].index=A[hash];
                        Q1.push(u);
                    }
                }
            }
        }
        for (int i=0; i<s2; ++i) {
            v=Q2.front();
            Q2.pop();
            L2.insert(T2[v].index);
            for (int j=0; j<T2[v].adj.size(); ++j) {
                u=T2[v].adj[j];
                if (T2[u].index==-1) {
                    T2[u].L.insert(T2[v].index);
                    if (T2[u].L.size()+1==T2[u].adj.size()) {
                        hash=h(T2[u].L);
                        if (!A[hash]) {
                            ++ix;
                            A[hash]=ix;
                        }
                        T2[u].index=A[hash];
                        Q2.push(u);
                    }
                }
            }
        }
        if (L1!=L2) return 0;
    }
    return T1[r1].index==T2[r2].index;
}

int main() {
    int n1, n2, m1, m2;
    cout<<"n1, m1: ";
    cin>>n1>>m1;
    cout<<"n2, m2: ";
    cin>>n2>>m2;
    if (n1!=n2 or m1!=m2) {
        cout<<"NIE";
        return 0;
    }
    int n=n1, m=m1;
    vector<node> T1(n);
    vector<node> T2(n);
    int v, u;
    cout<<"T1: \n";
    for (int i=0; i<m; ++i) {
        cin>>v>>u;
        --v;
        --u;
        T1[v].adj.push_back(u);
        T1[u].adj.push_back(v);
    }
    cout<<"T2: \n";
    for (int i=0; i<m; ++i) {
        cin>>v>>u;
        --v;
        --u;
        T2[v].adj.push_back(u);
        T2[u].adj.push_back(v);
    }
    cout<<"\n";
    
    int r1, r2;
    cout<<"r1, r2: ";
    cin>>r1>>r2;
    
    (Izomorfic(T1, T2, r1, r2, n, m))? cout<<"TAK" : cout<<"NIE";
    
    return 0;
}

/*
 13 12
 13 12
 
 3 1
 3 2
 1 12
 1 13
 1 6
 2 4
 2 5
 2 7
 4 8
 4 9
 7 10
 7 11
 
 1 2
 1 3
 2 4
 2 8
 2 7
 4 5
 4 6
 7 9
 7 10
 3 11
 3 12
 3 13
 
 2 0
 */
