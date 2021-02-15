//
//  main.cpp
//  Bloom Filter
//
//  Created by Mikołaj Jędrzejewski on 9/1/20.
//  Copyright © 2020 Mikołaj Jędrzejewski. All rights reserved.
//

#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

typedef long long ll;

class BloomFilter {
    //good primes are 1e9+7, 1e9+9, 1e9+23 as an example
    int k;  //number of hash functions
    vector<ll> P, M;
    vector<bitset<1000000000>> B;
    
public:
    BloomFilter (vector<ll> mods, vector<ll> primes, int k) {
        this->k = k;
        M = mods;
        P = primes;
        B = vector<bitset<1000000000>> (k);
    }
    
    vector<ll> ComputeHashes(vector<int> data) {
        vector<ll> H(k);
        for (int i=0; i<k; ++i) {
            ll hsh=data[0];
            for (auto ele: data)
                hsh=(((hsh*P[i])%M[i])+ele)%M[i];
            H[i]=hsh;
        }
        return H;
    }
    
    void insert(vector<int> data) {
        vector<ll> H = ComputeHashes(data);
        for (int i=0; i<k; ++i)
            B[i][ H[i] ]=1;
    }
    
    //checks if the data is in the Bloom Filter
    bool query(vector<int> data) {
        vector<ll> H = ComputeHashes(data);
        bool ans=true;
        for (int i=0; i<k; ++i)
            ans &= B[i][ H[i] ];
        
        return ans;
    }
};

int main() {
    
    return 0;
}
