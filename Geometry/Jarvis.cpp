//
//  main.cpp
//  Algorytm Jarvisa
//
//  Created by Mikołaj Jędrzejewski on 10/28/19.
//  Copyright © 2019 Mikołaj Jędrzejewski. All rights reserved.
//

#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

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

bool eq(node a, node b) {
    return a.x == b.x && a.y == b.y;
}

void Jarvis(vector<node> &W, int n) {
    node min=W[0];
    for (int i=1; i<n; ++i) {
        if (min.y > W[i].y) min=W[i];
        else if (min.y == W[i].y && min.x > W[i].x) min=W[i];
    }
    int y=-min.y;
    for (int i=0; i<n; ++i) W[i].y+=y;
    
    min.y+=y;
    node curr = min;
    node next;
    
    while (!eq(next, min)) {
        if (!eq(W[0], curr))    next = W[0];
        else                    next = W[1];
        for (int i=0; i<n; ++i)
            if (det(curr.x, curr.y, W[i].x, W[i].y, next.x, next.y)==-1)  next = W[i];
        curr = next;
        cout<<curr.x<<" "<<curr.y-y<<"\n";
    }
    
}

int main()
{
    int n;
    cout << "Podaj liczbę wierzchołków: ";
    cin>>n;
    vector<node> W(n);
    cout<<"Opisz wielokąt: ";
    for (int i=0; i<n; ++i)
        cin>>W[i].x>>W[i].y;
    
    cout<<"\n";
    Jarvis(W, n);
    
    return 0;
}
/*
 10
 -30 10
 20 60
 70 10
 20 -30
 50 50
 20 20
 -40 -30
 -30 50
 0 40
 40 -10
 Wynik:
 70 10
 50 50
 20 60
 -30 50
 -40 -30
 20 -30
 
 */
