//
//  main.cpp
//  Tablica sufiksowa
//
//  Created by Mikołaj Jędrzejewski on 8/19/20.
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
vector<vector<int>> KMR;
vector<int> SA;     //sufix array
vector<int> RANK;
vector<int> LCP;    //longest common palindrome

bool equal(int a, int b, int c, int d) {
    if (b-a!=d-c) return 0;
    int q=0;
    while (b-a+1>=(1<<(q+1))) ++q;

    return KMR[q][a]==KMR[q][c] and KMR[q][b-(1<<q)+1]==KMR[q][d-(1<<q)+1];
}

void CalcKMR() {
    n=(int)w.size();
    r=log2(n)+1;
    KMR=vector<vector<int>> (r+1, vector<int> (n));
    for (int i=0; i<n; ++i) KMR[0][i] = w[i] - 'a' + 1;

    vector<pair<int, pair<int, int>>> p(n);
    for (int x=1; x<=r; ++x) {
        for (int i=0; i<n; ++i) {
            if (i+pot>=n) p[i]=mp(KMR[x-1][i], mp(-1, i));
            else          p[i]=mp(KMR[x-1][i], mp(KMR[x-1][i+pot], i));
        }
        sort(p.begin(), p.end());
        
        pair<int, int> d=mp(-1, -1);
        int id=0;
        for (int i=0; i<n; ++i) {
            if (d!=mp(p[i].first, p[i].second.first)) {
                d=mp(p[i].first, p[i].second.first);
                ++id;
            }
            KMR[x][p[i].second.second]=id;
        }
        pot*=2;
    }
}

void CalcSA() {
    SA=vector<int> (n+1);
    for (int i=1; i<=n; ++i)
        SA[KMR[r][i-1]]=i;
}

void CalcRANK() {
    RANK=KMR[r];
}

void CalcLCP() {
    LCP=vector<int> (n);
    for (int i=0; i<n; ++i) {
        if (RANK[i]>1) {
            int j=SA[RANK[i]-1]-1;
            int u=max(0, LCP[j]-1);
            while (w[i+u]==w[j+u] and i+u<n and j+u<n) ++u;
            LCP[RANK[i]-1]=u;
        }
    }
    LCP[0]=-1;
}

//LCP for sufixes not neighboring in SA is the minium on interval [a+1, b] in LCP
//for a+1=b the answer is LCP[b]
int fLCP(int a, int b) {
    int res=LCP[a+1];
    for (int i=a+1; i<=b; ++i)
        res=min(res, LCP[i]);
    return res;
}

//number of unique subwords of word w
int CountUniqueSubwords() {
    int res=n*(n-1)/2;
    for (int i=1; i<n; ++i) res-=LCP[i];
    return res;
}

int main() {
    cin>>w;
    
    CalcKMR();
    CalcSA();
    CalcRANK();
    CalcLCP();

    return 0;
}
/*
 dbcabd
 ababacc
 abcdfabcdef
 
 When comparing two words we join them and put special character between so unnecessary subwords are not generated
 abcdf
 abcdef
 */
