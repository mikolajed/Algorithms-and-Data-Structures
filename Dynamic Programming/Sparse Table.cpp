//
//  main.cpp
//  Sparse Table
//
//  Created by Mikołaj Jędrzejewski on 8/19/20.
//  Copyright © 2020 Mikołaj Jędrzejewski. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int n;

vector<vector<int>> BuildSparseTable(vector<int> &A) {
    int lg=floor(log2(n))+1;
    vector<vector<int>> S(lg);
    for (int i=0; i<n; ++i) S[0].push_back(A[i]);
    for (int i=1; i<lg; ++i)
        for (int j=0; j<=n-(1<<i); ++j)
            S[i].push_back(min(S[i-1][j], S[i-1][j+(1<<(i-1))]));
    
    return S;
}

int RMQ(vector<vector<int>> &S, int l, int r) {
    int p = 31 - __builtin_clz(r-l);
    return min(S[p][l], S[p][r-(1<<p)+1]);
}

int main() {
    cin>>n;
    vector<int> A(n);
    for (int i=0; i<n; ++i) cin>>A[i];
    
    vector<vector<int>> S=BuildSparseTable(A);
    
    cout<<RMQ(S, 3, 6);
    
    return 0;
}
/*
 8
 3 1 5 3 4 7 6 1
 */
