//
//  main.cpp
//  Centroid Decomposition
//
//  Created by Mikołaj Jędrzejewski on 8/28/20.
//  Copyright © 2020 Mikołaj Jędrzejewski. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

struct node {
    vector<int> adj;
    int c=1;  //size of the substree
    bool vis;
};

struct edge {
    int v, u, w;
};

int n;
int root=1;     //root cannot be a leaf unless it is the only node in the tree
vector<node> T;

int findCentroid(int x=root) {
    for (auto u: T[x].adj) {
        if (T[u].c > n/2) {
            T[x].c-= T[u].c;
            T[u].c=n;
            return findCentroid(u);
        }
    }
    return x;
}

void Calc(int v=root) {
    T[v].vis=1;
    if (T[v].adj.size() == 1)   return;
    else {
        for (auto u: T[v].adj) {
            if (!T[u].vis) {
                Calc(u);
                T[v].c+=T[u].c;
            }
        }
    }
}

void PrintCentroids() {
    Calc();
    int centroid=findCentroid();
    pair<int, int> centroids = {centroid, centroid};
    for (auto u: T[centroid].adj)
        if (T[u].c==n/2)
            centroids.second=u;
    
    centroids.first == centroids.second ? cout<<centroid<<"\n" : cout<<centroids.first<<" "<<centroids.second<<"\n";
}

int CentroidDecomposition(int x=root) {
    //calculate sizes of subtrees
    Calc();
    int centroid=findCentroid();
    for (int i=0; i<n; ++i) T[i].vis=0;
    
    //solve problem for paths of the first kind
    //
    T[centroid].vis=1;
    int ans=0;
    for (auto u: T[centroid].adj) {
        if (!T[u].vis) {
            ans+=CentroidDecomposition(u);
            //or ans=max(ans, CentroidDecomposition(u))
        }
    }
    return ans;
}

//Problem 1
//Given weighted tree, find the number of paths which lengths are equal to 0. Edges lenghts span between [-2, 2]

void Calc1(vector<node> &T, vector<edge> &E, int v) {
    T[v].vis=1;
    if (T[v].adj.size() == 1)   return;
    else {
        for (auto e: T[v].adj) {
            int u=E[e].u;
            if (!T[u].vis) {
                Calc1(T, E, u);
                T[v].c+=T[u].c;
            }
        }
    }
}

int Solve1(vector<node> &T, vector<edge> &E, vector<int> val, int update=0, int v=1) {
    for (int i=(int)val.size()-update; i>=update; --i) val[i+update]=val[i];
    if (T[v].adj.size() == 1) ++val[v];
    int centroid=findCentroid();

    T[centroid].vis=1;
    int ans=0;
    for (auto e: T[centroid].adj) {
        int u=E[e].u;
        int w=E[e].w;
        if (!T[u].vis)
            ans+=Solve1(T, E, val, w, u);
    }
    for (int i=0; i<=2; ++i)
        ans+=min(val[i], val[4-i]);
    return ans;
}

void Problem1() {
    //all posible values that can be obtain by summing any of trees path lengths
    //we need to store the negative values but there is other solvution
    //we can rephrese the problem
    //that is find all path with length 2 where each edge in tree is in [0, 4]
    //in doing so we can easily access the w just by lenght of the path what would not be possible with path of negative length
    vector<int> w(1e5);
    int n;
    cin>>n;
    
    vector<node> T(n);
    vector<edge> E;
    for (int i=0; i<n-1; ++i) {
        int v, u, w;
        cin>>v>>u>>w;
        w+=2;   //[-2, 2] -> [0, 4]
        T[v].adj.push_back((int)E.size());
        E.push_back({v, u, w});
        T[u].adj.push_back((int)E.size());
        E.push_back({u, v, w});
    }
    //calculate sizes of subtrees
    Calc1(T, E, root);
    for (int i=0; i<n; ++i) T[i].vis=0;
    
    cout<<Solve1(T, E, w);
}

int main() {
    
    cin>>n;
    T=vector<node> (n);
    for (int i=0; i<n-1; ++i) {
        int a, b;
        cin>>a>>b;
        T[a].adj.push_back(b);
        T[b].adj.push_back(a);
    }
    
    PrintCentroids();
    
    return 0;
}
/*
 EXAMPLE
 14
 0 1
 1 2
 2 3
 3 4
 4 5
 4 6
 3 7
 7 8
 8 9
 8 10
 7 11
 11 12
 11 13
 
 PROBLEM 1
 */
