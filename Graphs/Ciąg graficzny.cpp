//
//  main.cpp
//  Ciąg graficzny
//
//  Created by Mikołaj Jędrzejewski on 4/21/20.
//  Copyright © 2020 Mikołaj Jędrzejewski. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp (int a, int b) {
    return a>b;
}

bool method1(vector<int> &C, int n) {
    int i;
    sort(C.begin(), C.end(), cmp);
    while (C[0]>0) {
        i=1;
        while (C[0]>0 and i<n and C[i]>0) {
            --C[0];
            --C[i];
            ++i;
        }
        if (C[0]>0) break;
        sort(C.begin(), C.end(), cmp);
    }
    bool z=1;
    for (int i=0; i<n; ++i)
        if (C[i]>0) {
            z=0;
            break;
        }
    return z;
}

bool method2(vector<int> &C, int n) {
    vector<int> D(n);
    vector<int> M(n+1);
    D[0]=C[0];
    for (int i=1; i<n; ++i) D[i]=C[i]+D[i-1];
    M[n]=min(n-1, C[n-1]);
    for (int i=n-1; i>0; --i) M[i]=min(i, C[i-1])+M[i+1];
    bool z=1;
    if (D[n-1]%1) z=0;
    for (int k=1; k<=n; ++k)
        if (D[k-1]>(k-1)*k+M[k]) {
            z=0;
            break;
        }
    return z;
}

int main() {
    int n;
    cout<<"n: ";
    cin>>n;
    vector<int> C(n);
    for (int i=0; i<n; ++i) cin>>C[i];
    
    (method1(C, n))? cout<<"T" : cout<<"N";
    cout<<"\n";
    (method2(C, n))? cout<<"T" : cout<<"N";
    cout<<"\n";
    
    return 0;
}
