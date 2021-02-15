//
//  main.cpp
//  Rolling hashes
//
//  Created by Mikołaj Jędrzejewski on 9/1/20.
//  Copyright © 2020 Mikołaj Jędrzejewski. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef long long ll;

//works only when a and b are coprime
int modInverse(int a, int b) {
    int b0 = b;
    int y = 0, x = 1;
    if (b == 1)
        return 0;
    
    while (a > 1) {
        int q = a / b;
        int t = b;
    
        b = a % b;
        a = t;
        t = y;
    
        y = x - q * y;
        x = t;
    }
    
    if (x < 0)
        x += b0;
    
      return x;
}

class RollingHash {
    int k, n, m;
    vector<int> hash;
    vector<int> inv;
    vector<int> M, P;
    deque<int> seq;

public:
    RollingHash (int n, int m, int k, int p, vector<int> mods) {
        this->n=n;
        this->m=m;
        this->k=k;
        M = mods;
        P = vector<int> (n+1, 1);
        P[1] = p;
        for (int j=1; j<=n; ++j)
            P[j]=P[j-1]*p;
        for (int i: M)
            inv.push_back( modInverse(p, i) );
    }
    
    void pushBack(int x) {
        seq.push_back(x);
        for (int i=0; i<k; ++i)
            hash[i]=((hash[i] * P[1])%M[i] + x)%M[i];
    }
    
    void popBack() {
        for (int i=0; i<k; ++i)
            hash[i]=((hash[i] - seq.back() + M[i])%M[i] * inv[i])%M[i];
        seq.pop_back();
    }
    
    void pushFirst(int x) {
        seq.push_front(x);
        for (int i=0; i<k; ++i)
            hash[i]=(hash[i] + (P[ seq.size() ] * x)%M[i] )%M[i];
    }
    
    void popFirst() {
        for (int i=0; i<k; ++i)
            hash[i]=(hash[i] - (P[ seq.size() ] * seq.front() + M[i])%M[i] )%M[i];
        seq.pop_front();
    }
};

int main() {
        
    return 0;
}
