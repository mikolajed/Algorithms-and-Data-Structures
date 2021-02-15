//
//  main.cpp
//  Algorytm Floyda-Warshalla
//
//  Created by Mikołaj Jędrzejewski on 10/28/19.
//  Copyright © 2019 Mikołaj Jędrzejewski. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

int const INFINITY = 99;

void initGraph(vector<int> *G, vector<int> *P, int n) {
    for (int i=0; i<n; ++i)
        for (int j=0; j<n; ++j) {
            G[i].push_back(INFINITY);
            P[i].push_back(i);
        }
}

void fillGraph(vector<int> *G, int m) {
    int u, v, w;
    for (int i=0; i<m; ++i) {
        cin>>u>>v>>w;
        G[u][v]=w;
    }
}

void print(vector<int> *G, int n) {
    cout<<"\n";
    for (int i=0; i<n; ++i) {
        for (int j=0; j<n; ++j){
            cout<<G[i][j]<<" ";
            if(G[i][j]<=9) cout<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";
}

void FM(vector<int> *G, vector<int> *P, int n) {
    for (int k=0; k<n; ++k)
        for (int i=0; i<n; ++i)
            if (G[i][k]!=INFINITY)
                for (int j=0; j<n; ++j)
                    if (G[i][j] > G[i][k]+G[k][j]) {
                        G[i][j]=G[i][k]+G[k][j];
                        P[i][j]=P[k][j];
                    }
}

void retrievePath(vector<int> *P, int u, int v) {
    if (u!=v)
        retrievePath(P, u, P[u][v]);
    cout<<v<<" ";
}

int main()
{
    int n, m;
    cout << "Podaj n i m: ";
    cin>>n>>m;
    vector<int> G[n];
    vector<int> P[n];
    initGraph(G, P, n);
    fillGraph(G, m);
    FM(G, P, n);
    print(G, n);
    print(P, n);
    int x, y;
    cout<<"Podaj pare wierzcholkow: ";
    cin>>x>>y;
    cout<<"Długość: "<<G[x][y]<<"\n";
    cout<<"Cykl: ";
    retrievePath(P, x, P[x][y]);
    cout<<y;
    cout<<"\n";
    return 0;
}

/*
 7 9
 0 1 3
 0 6 14
 1 2 3
 1 3 2
 2 0 5
 3 4 4
 4 6 -3
 6 2 2
 5 6 1
 
 11 3  6  5  9  N 6
 8  11 3  2  6  N 3
 5  8  11 10 14 N 11
 8  11 3  13 4  N 1
 4  7  -1 9  13 N -3
 8  11 3  13 17 N 1
 7  10 2  12 15 N 13
 */
