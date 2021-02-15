//
//  main.cpp
//  Manacher
//
//  Created by Mikołaj Jędrzejewski on 12/22/20.
//  Copyright © 2020 Mikołaj Jędrzejewski. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

void Manacher(vector<int> &P, string &T) {
    int C = 0, R = -1, rad;
    for (int i = 0; i < T.size(); ++i) {
        if (i <= R) {
            rad = min(P[2*C-i], R-i);
        } else {
            rad = 0;
        }
        while (i+rad < T.size() and i-rad >= 0 and T[i-rad] == T[i+rad])
            rad++;

        P[i] = rad;
        if (i + rad - 1 > R) {
            C = i;
            R = i + rad - 1;
        }
    }
}

int main() {
    string S, T="";
    cin>>S;
    for (auto i: S) {
        T+='#';
        T+=i;
    }
    T+='#';
    cout<<T<<"\n";
    
    vector<int> P(T.size());
    Manacher(P, T);
    for (int i=0; i<T.size(); ++i) --P[i];
    
    return 0;
}
/*
 aaabbaab
 */
