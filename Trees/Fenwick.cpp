//
//  main.cpp
//  Drzewo potęgowe
//
//  Created by Mikołaj Jędrzejewski on 1/24/20.
//  Copyright © 2020 Mikołaj Jędrzejewski. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

void init(vector<int> &T) {
    int n=T.size(), leap=2, x;
    while (leap<n) {
        x=leap/2;
        while (x<=n) {
            T[x+(x & -x)]+=T[x];
            x+=leap;
        }
    }
}

int beforeeq(vector<int> &T, int x) {
    int n=T.size()-1, sum=0;
    while (x>0) {
        sum+=T[x];
        x-=(x & -x);
    }
    return sum;
}

void update(vector<int> &T, int x, int cnt) {
    int n=T.size()-1;
    while (x<=n) {
        T[x]+=cnt;
        x+=(x & -x);
    }
}

int nth(vector<int> &T, int i) {
    int n=T.size()-1, l=n, x=0;
    while (l>0) {
        if (x+l<n and T[x+l]<i) {
            i-=T[x+l];
            x+=l;
        }
        l/=2;
    }
    return x;
}

int main() {
    int n;
    cin>>n;
    vector<int> T(n+1);
    
    for (int i=1; i<=n; ++i) cin>>T[i];
    
    return 0;
}
