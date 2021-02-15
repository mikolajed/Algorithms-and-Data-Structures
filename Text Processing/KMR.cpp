//
//  main.cpp
//  KMR
//
//  Created by Mikołaj Jędrzejewski on 12/21/20.
//  Copyright © 2020 Mikołaj Jędrzejewski. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp(a, b) make_pair(a, b)

int n, r, pot = 1;
string w;
vector<vector<int>> D;

void KMR() {
    n=(int)w.size();
    r=log2(n)+1;
    D=vector<vector<int>> (r+1, vector<int> (n));
    for (int i=0; i<n; ++i) D[0][i] = w[i] - 'a' + 1;

    vector<pair<int, pair<int, int>>> p(n);
    for (int x=1; x<=r; ++x) {
        for (int i=0; i<n; ++i) {
            if (i+pot>=n) p[i]=mp(D[x-1][i], mp(-1, i));
            else          p[i]=mp(D[x-1][i], mp(D[x-1][i+pot], i));
        }
        sort(p.begin(), p.end());
        
        pair<int, int> d=mp(-1, -1);
        int id=0;
        for (int i=0; i<n; ++i) {
            if (d!=mp(p[i].first, p[i].second.first)) {
                d=mp(p[i].first, p[i].second.first);
                ++id;
            }
            D[x][p[i].second.second]=id;
        }
        pot*=2;
    }
}

bool equal(int a, int b, int c, int d) {
    if (b-a!=d-c) return 0;
    int q=0;
    while (b-a+1>=(1<<(q+1))) ++q;

    return D[q][a]==D[q][c] and D[q][b-(1<<q)+1]==D[q][d-(1<<q)+1];
}

int main() {
    
    string a, b;
    cin>>a>>b;
    w=a+'#'+b;
    
    KMR();
    for (;;) {
        int l1, r1, l2, r2;
        cin>>l1>>r1>>l2>>r2;
        l2+=(int)a.size()+1;
        r2+=(int)a.size()+1;
        
        equal(l1, r1, l2, r2) ? cout<<"Words are equal\n" : cout<<"Words are different\n";
    }
    
        
    return 0;
}
/*
 abcdfabcdef
 
 When comparing two words we join them and put special character between so unnecessary subwords are not generated
 abcdf
 abcdef
 */
