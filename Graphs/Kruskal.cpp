//
//  main.cpp
//  MST-KRUSKAL
//
//  Created by Mikołaj Jędrzejewski on 3/8/19.
//  Copyright © 2019 Mikołaj Jędrzejewski. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct vertex{
    int p;
    int rank;
};

struct edge{
    int V;
    int u;
    int v;
};

void fillGraph(vector<edge> &G, int m){
    edge E;
    for(int i=0; i<m; ++i){
        cin>>E.u;
        cin>>E.v;
        cin>>E.V;
        G.push_back(E);
    }
}

void printGraph(vector<edge> &G){
    for (int i=0; i<G.size(); ++i) cout<<G[i].u<<" "<<G[i].v<<" "<<"\n";//<<G[i].V<<"\n";
        //cout<<char(G[i].u+int('a'))<<" "<<char(G[i].v+int('a'))<<" "<<"\n";//<<G[i].V<<"\n";
}

bool compare(edge A, edge B){
    return A.V<=B.V;
}

int FIND_SET(vector<vertex> &T, int x){
    if(T[x].p!=x)
        x=FIND_SET(T, T[x].p);
    return x;
}

void UNION(vector<vertex> &T, int u, int v){
    if(T[u].rank>T[v].rank) T[v].p=u;
    else{
        T[u].p=v;
        if(T[u].rank==T[v].rank)    ++T[v].rank;
    }
}

void MST_KRASKAL(vector<edge> &G, vector<edge> &A, int n){
    vector<vertex> T;
    vertex x;
    for(int i=0; i<n; ++i){
        T.push_back(x);
        T[i].p=i;
    }
    sort(G.begin(), G.end(), compare);
    for(int i=0; i<G.size(); ++i){
        if(FIND_SET(T, G[i].u)!=FIND_SET(T, G[i].v)){
            A.push_back(G[i]);
            UNION(T, FIND_SET(T, G[i].u), FIND_SET(T, G[i].v));
        }
    }
}

int main()
{
    int n, m;
    cout << "Podaj liczbe wierzcholkow: ";
    cin>>n;
    cout<<"Podaj liczbe krawedzi: ";
    cin>>m;
    vector<edge> G;
    vector<edge> A;

    fillGraph(G, m);

    MST_KRASKAL(G, A, n);
    
    cout<<"MST\n";
    printGraph(A);
    
    return 0;
}
/*
 INPUT
 9 14
 0 1 4
 1 2 8
 2 3 7
 3 4 9
 4 5 10
 5 6 2
 6 7 1
 7 8 7
 7 1 11
 8 2 2
 8 6 6
 2 5 4
 3 5 14
 0 7 8
*/
