//
//  main.cpp
//  Rabin-Karp
//
//  Created by Mikołaj Jędrzejewski on 1/29/20.
//  Copyright © 2020 Mikołaj Jędrzejewski. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

int mod=1e9+7;
int d=26;

int main() {
    string s, w;
    cin>>s>>w;
    int n=s.size();
    int m=w.size();
    
    int pow=1;
    for (int i=1; i<m; ++i) pow*=d;
    
    int hw=0;
    for (int i=0; i<m-1; ++i) {
        hw+=int(w[i])-int('a')+1;
        hw%=mod;
        hw*=d;
        hw%=mod;
    }
    hw+=int(w[m-1])-int('a')+1;
    hw%=mod;
    
    int last;
    vector<int> W(n-m+1);
    int h=0;
    last=(int(s[0])-int('a')+1)*pow;
    for (int i=0; i<m-1; ++i) {
        h+=int(s[i])-int('a')+1;
        h*=d;
        h%=mod;
    }
    h+=int(s[m-1])-int('a')+1;
    h%=mod;
    W[0]=h;
    
    for (int i=m; i<n; ++i) {
        h-=last;
        h*=d;
        h+=int(s[i])-int('a')+1;
        h%=mod;
        W[i-m+1]=h;
        last=(int(s[i-m+1])-int('a')+1)*pow;
    }
    
    cout<<"Wzorzec znaleziony na pozycjach: ";
    for (int i=0; i<n-m+1; ++i)
        if (W[i]==hw) cout<<i<<" ";
    cout<<"\n";
    
    return 0;
}

/*
 abaabbab
 ab
 */
