//
//  main.cpp
//  Układy kongruencji
//
//  Created by Mikołaj Jędrzejewski on 1/3/21.
//

#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

ll ModularInverse(ll a, ll p) {
    ll r=1;
    ll mod=p;
    p = p-2;
    
    while (p>0) {
        if (p%2)
            r = (r*a)%mod;
        a = (a*a)%mod;
        p /= 2;
    }
    
    return r;
}

int main() {
    
    int k;
    cout<<"k = ";
    cin>>k;
    
    //x ≡ a (mod b)
    ll x=0;
    //B = b1 * b2 * ... * bk
    ll B=1;
    vector<ll> a(k), b(k);
    for (int i=0; i<k; ++i) {
        cout<<"a = ";   cin>>a[i];
        cout<<"b = ";   cin>>b[i];
        B *= b[i];
    }
    for (int i=0; i<k; ++i)
        x += B/b[i] * ModularInverse(B/b[i], b[i]) * a[i];
    x %= B;
    cout<<"x = "<<x<<"\n";
    
    return 0;
}
