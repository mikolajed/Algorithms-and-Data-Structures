//
//  main.cpp
//  Mnożenie rosyjskich chłopów
//
//  Created by Mikołaj Jędrzejewski on 12/23/20.
//

#include <iostream>

using namespace std;

typedef long long ll;

ll multiply(ll a, ll b, ll mod) {
    a%=mod;
    b%=mod;
    ll w=0;
    ll p=1;
    while (b>0) {
        if (b%2==1)
            w=(w+(p*a)%mod)%mod;
        p=(p*2)%mod;
        b/=2;
    }
    return w;
}

int main() {
    
    ll a, b, mod;
    cin>>a>>b>>mod;
    
    cout<<multiply(a, b, mod)<<"\n";
    
    return 0;
}
