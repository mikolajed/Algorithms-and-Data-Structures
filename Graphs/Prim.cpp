//
//  main.cpp
//  Prim-Dijkstra
//
//  Created by Mikołaj Jędrzejewski on 10/22/19.
//  Copyright © 2019 Mikołaj Jędrzejewski. All rights reserved.
//

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct edge {
    int u;
    int v;
    int w;
    
    bool operator<(const edge &e) const {
        return w>e.w;
    }
};
/*
struct cmp {
    bool operator ()( const edge & e1, const edge & e2 ) {
        if( e1.w > e2.w ) return true; //porzadek niemalej�cy
        return false;
    }
};
*/
void fillGraph(vector<edge> *G, int n) {
    edge e;
    for (int i=0; i<n; ++i) {
        cin>>e.u;
        cin>>e.v;
        cin>>e.w;
        G[e.u].push_back(e);
        swap(e.u, e.v);
        G[e.u].push_back(e);
    }
}

int main() {
    int n, m;
    cout<<"Podaj n  i m: ";
    cin>>n>>m;
    //priority_queue < edge, vector < edge >, cmp > pQ;
    priority_queue <edge> pQ;
    edge e, ne;
    vector<edge> G[n];
    vector<bool> Vis(n);
    fillGraph(G, m);
    
    for (int i=0; i<G[0].size(); ++i)
        pQ.push(G[0][i]);
    Vis[0]=1;
    
    cout<<"MST: \n";
    while( !pQ.empty() ){
        e = pQ.top();
        pQ.pop();
        if(!Vis[e.v]) {
            cout<<e.u<<" "<<e.v<<" "<<e.w<<"\n";
            Vis[e.v]=1;
            for (int i=0; i<G[e.v].size(); ++i) {
                if (!Vis[G[e.v][i].v]) {
                    ne.u=e.v;
                    ne.v=G[e.v][i].v;
                    ne.w=G[e.v][i].w;
                    pQ.push(ne);
                }
            }
        }
    }
    
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
  
  0 1
  0 7
  7 6
  6 5
  5 2
  2 8
  2 3
  3 4
  */
