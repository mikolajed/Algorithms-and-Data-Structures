//
//  main.cpp
//  Modular inverse (Fermat's little theorem)
//
//  Created by Mikołaj Jędrzejewski on 12/24/20.
//

#include <iostream>

using namespace std;

typedef long long ll;

ll pow(ll a, ll x, ll p) {
    ll w=1;
    while (x>0) {
        if (x & 1)
            w=(w*a)%p;
        a=(a*a)%p;
        x/=2;
    }
    
    return w;
}

ll ModInverse(ll a, ll p) {
    ll inv=pow(a, p-2, p);
    
    return inv;
}

int main() {
    
    for (;;) {
        ll a, p;
        cout<<"a= ";    cin>>a;
        cout<<"p= ";    cin>>p;
        cout<<"inv= "<<ModInverse(a, p)<<"\n\n";
    }
    
    return 0;
}
