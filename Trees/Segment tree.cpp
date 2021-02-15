//
//  main.cpp
//  min i max
//
//  Created by Mikołaj Jędrzejewski on 1/15/20.
//  Copyright © 2020 Mikołaj Jędrzejewski. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

struct node{
    int min;
    int max;
    int s;
};

void update(vector<node> &T) {
    int i=T.size()/2-1;
    while (i>0) {
        T[i].min=min(T[2*i].min, T[2*i+1].min);
        T[i].max=max(T[2*i].max, T[2*i+1].max);
        T[i].s=T[2*i].s+T[2*i+1].s;
        --i;
    }
}

node quary(vector<node> &T, int a, int b) {
    int m=T.size()/2;
    int va=m+a, vb=m+b;
    node w;
    w.min=T[va].min;
    w.max=T[va].max;
    w.s=T[va].s;
    if (a!=b) {
        w.min=min(w.min, T[vb].min);
        w.max=max(w.max, T[vb].max);
        w.s+=T[vb].s;
    }
    while (va/2!=vb/2) {
        if (va%2==0) {
            w.min=min(w.min, T[va+1].min);
            w.max=max(w.max, T[va+1].max);
            w.s+=T[va+1].s;
        }
        if (vb%2==1) {
            w.min=min(w.min, T[vb-1].min);
            w.max=max(w.max, T[vb-1].max);
            w.s+=T[vb-1].s;
        }
        va/=2;
        vb/=2;
    }
    return w;
}

int getSize(int m) {
    int x=1;
    while (x<m) x*=2;
    return x;
}

int main()
{
    int M, m, x, mn, mx;
    cout << "Podaj liczbę elementów: ";
    cin>>M;
    m=getSize(M);
    vector<node> T(2*m);
    
    cin>>x;
    T[m].min=T[m].max=T[m].s=mn=mx=x;
    for (int i=m+1; i<m+M; ++i)  {
        cin>>x;
        T[i].min=T[i].max=T[i].s=x;
        mn=min(mn, x);
        mx=max(mx, x);
    }
    for (int i=m+M; i<2*m; ++i) {
        T[i].min=mx;
        T[i].max=mn;
        T[i].s=0;
    }

    update(T);
    
    int t, a, b;
    node w;
    cout<<"Podaj liczbę zapytań: ";
    cin>>t;
    for (int i=0; i<t; ++i) {
        cout<<"\nQ: ";
        cin>>a>>b;
        w=quary(T, a, b);
        cout<<"Min: "<<w.min<<"\nMax: "<<w.max<<"\nSum: "<<w.s<<"\n";
    }

    return 0;
}
