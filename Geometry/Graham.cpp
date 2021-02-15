//
//  main.cpp
//  Algorytm Grahama
//
//  Created by Mikołaj Jędrzejewski on 10/28/19.
//  Copyright © 2019 Mikołaj Jędrzejewski. All rights reserved.
//

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int sgn(int x){
    if(x>0)         return 1;
    else if(x<0)    return -1;
    return 0;
}

int det(int x1, int y1, int x2, int y2, int x3, int y3){
    return sgn(x1*y2+x2*y3+x3*y1-y2*x3-y3*x1-y1*x2);
}

struct node{
    int x;
    int y;
};

int main()
{
    int n;
    cout << "Podaj liczbę wierzchołków: ";
    cin>>n;
    vector<node> W(n);
    cout<<"Opisz wielokąt: ";
    for (int i=0; i<n; ++i)
        cin>>W[i].x>>W[i].y;
    
    stack<node> S;
    S.push(W[0]);
    S.push(W[1]);
    S.push(W[2]);
    node v;
    int j;
    
    for (int i=2; i<n; ++i) {
        j=2;
        while (i>=j and det(W[i-j].x, W[i-j].y, W[i].x, W[i].y, W[i-j+1].x, W[i-j+1].y)==1){
            v=S.top();
            S.pop();
            S.pop();
            S.push(v);
            ++j;
        }
        S.push(W[(i+1)%n]);
    }
    
    S.pop();
    cout<<"Ans: \n";
    while (!S.empty()) {
        cout<<S.top().x<<" "<<S.top().y<<"\n";
        S.pop();
    }
    
    return 0;
}
/*
 10
 0 0
 30 10
 60 30
 40 30
 40 40
 10 40
 10 50
 -20 30
 -30 30
 -20 10
 
 0 0
 30 10
 60 30
 40 40
 10 50
 -30 30
 -20 10
 */
