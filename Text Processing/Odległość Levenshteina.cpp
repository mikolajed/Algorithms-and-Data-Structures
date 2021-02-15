//
//  main.cpp
//  Odległość Levenshteina
//
//  Created by Mikołaj Jędrzejewski on 1/28/20.
//  Copyright © 2020 Mikołaj Jędrzejewski. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    string s, t;
    cout<<"s: ";
    cin>>s;
    cout<<"t: ";
    cin>>t;
    int n=s.size(), m=t.size();
    vector<int> V[n+1];
    for (int i=0; i<=n; ++i)
        for (int j=0; j<=m; ++j)
            V[i].push_back(0);
    
    for (int i=0; i<=n; ++i) V[i][0]=i;
    for (int j=0; j<=m; ++j) V[0][j]=j;
    
    int cost;
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=m; ++j) {
            (s[i]==t[j])? cost=0 : cost=1;
            V[i][j]=min(V[i-1][j-1]+cost, min(V[i-1][j]+1, V[i][j-1]+1));
        }
    }
    
    for (int i=0; i<=n; ++i) {
        for (int j=0; j<=m; ++j)
            cout<<V[i][j]<<" ";
        cout<<"\n";
    }
    
    return 0;
}
/*
 marka
 ariada
 */
