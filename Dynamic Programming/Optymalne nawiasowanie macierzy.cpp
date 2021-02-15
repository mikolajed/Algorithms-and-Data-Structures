//
//  main.cpp
//  optymalne nawiasowanie
//
//  Created by Mikołaj Jędrzejewski on 3/21/19.
//  Copyright © 2019 Mikołaj Jędrzejewski. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> matrix;

void matrix_init(matrix &M, int x, int y){
    vector<int> V;
    for(int i=0; i<x; i++)  V.push_back(0);
    for(int i=0; i<y; ++i)  M.push_back(V);
}

void print_matrix(matrix &M){
    for(int i=0; i<M.size(); ++i){
        for(int j=0; j<M[i].size(); ++j)    cout<<M[i][j]<<" ";
        cout<<"\n";
    }
    cout<<"\n";
}

void nawiasowanie(matrix M, int l, int r){
    if(r>l){
        cout<<'(';
        nawiasowanie(M, l, M[r][l]);
        cout<<')';
        if(r>=M[r][l]+1){
            cout<<'(';
            nawiasowanie(M, M[r][l]+1, r);
            cout<<')';
        }
    }
}

int main()
{
    int n;
    cout << "Podaj liczbę macierzy: ";
    cin>>n;
    vector<int> p(n+1);
    for(int i=0; i<n+1; ++i)  cin>>p[i];
    matrix m, s;
    matrix_init(m, n, n);
    matrix_init(s, n, n);
    
    int i=0;
    for(int h=1; h<n; ++h){
        i=h;
        for(int j=0; j<n-h; ++j){
            m[i][j]=m[j][j]+m[i][j+1]+(p[j]*p[j+1]*p[i+1]);
            s[i][j]=j;
            for(int k=j+1; k<i; ++k)
                if(m[i][j]>=m[k][j]+m[i][k+1]+(p[j]*p[k+1]*p[i+1])){
                    m[i][j]=m[k][j]+m[i][k+1]+(p[j]*p[k+1]*p[i+1]);
                    s[i][j]=k;
                }
            ++i;
        }
    }
    
    print_matrix(m);
    print_matrix(s);
    
    nawiasowanie(s, 0, n-1);
    cout<<"\n";
    
    return 0;
}
/*
 6
 30 35 15 5 10 20 25
 */
