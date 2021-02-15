//
//  main.cpp
//  Środek grafu
//
//  Created by Mikołaj Jędrzejewski on 10/29/19.
//  Copyright © 2019 Mikołaj Jędrzejewski. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    int n, m;
    cout << "Podaj n i m: ";
    cin>>n>>m;
    cout<<"Podaj połączenia:\n";
    vector<int> G[n];
    vector<int> P(n);
    int x, y;
    cin>>x>>y;
    G[x].push_back(y);
    G[y].push_back(x);
    for (int i=1; i<m; ++i) {
        cin>>x>>y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    
    queue<int> Q;
    for (int i=0; i<n; ++i) {
        P[i]=G[i].size();
        if (P[i]==1) Q.push(i);
    }
    int v;
    for (int j=0; j<n-2; ++j) {
        v=Q.front();
        Q.pop();
        for (int i=0; i<G[v].size(); ++i)   --P[G[v][i]];
        for (int i=0; i<G[v].size(); ++i)
            if (P[G[v][i]]==1) Q.push(G[v][i]);
        cout<<v<<": ";
        for (int i=0; i<n; ++i) cout<<P[i]<<" ";
        cout<<"\n";
    }
    cout<<"\nAns: ";
    if (Q.size() == 2) {
        v=Q.front();
        Q.pop();
        int u=Q.front();
        if (P[v] > P[u])      cout<<v;
        else if (P[v] < P[u]) cout<<u;
        else                  cout<<v<<" "<<u;
    }
    else cout<<Q.front();
    cout<<"\n";
    
    return 0;
}

/*
 11 10
 0 1
 0 2
 0 3
 0 4
 6 0
 5 6
 5 10
 6 7
 5 8
 8 9
 
 10 9
 0 1
 0 2
 0 3
 0 4
 6 0
 5 6
 5 9
 6 7
 5 8
 */
