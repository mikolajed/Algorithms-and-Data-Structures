//
//  main.cpp
//  Szybkie potęgowanie modulo
//
//  Created by Mikołaj Jędrzejewski on 12/23/20.
//

#include <iostream>

using namespace std;

typedef long long ll;

ll pow(ll a, ll x, ll mod) {
    ll w=1;
    while (x>0) {
        if (x%2==1)
            w=(w*a)%mod;
        a=(a*a)%mod;
        x/=2;
    }
    return w;
}

int main() {
    
    int a, x, mod;
    cin>>a>>x>>mod;
    cout<<pow(a, x, mod);
    
    return 0;
}
