//
//  main.cpp
//  Przynależność do wielokąta log
//
//  Created by Mikołaj Jędrzejewski on 9/23/19.
//  Copyright © 2019 Mikołaj Jędrzejewski. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

struct node{
    int x;
    int y;
};

int sgn(int x){
    if(x>0)         return 1;
    else if(x<0)    return -1;
    else            return 0;
}

int det(int x1, int y1, int x2, int y2, int x3, int y3){
    return sgn(x1*y2+x2*y3+x3*y1-y2*x3-y3*x1-y1*x2);
}

bool contain(node p1, node p2, node p3){
    return (p3.x>=min(p1.x, p2.x) && p3.x<=max(p1.x, p2.x) &&
            p3.y>=min(p1.y, p2.y) && p3.y<=max(p1.y, p2.y));
}

bool inside(vector<node> &W, node p, int l, int r){
    if(l+1==r){
        int d1=det(W[0].x, W[0].y, W[l].x, W[l].y, p.x, p.y);
        if(d1==0) return contain(W[0], W[l], p);
    
        int d2=det(W[l].x, W[l].y, W[r].x, W[r].y, p.x, p.y);
        if(d2==0) return contain(W[l], W[r], p);
        
        int d3=det(W[r].x, W[r].y, W[0].x, W[0].y, p.x, p.y);
        if(d3==0) return contain(W[r], W[0], p);
        
        return (d1==d2 && d1==d3);
    }
    else{
        int m=(l+r)/2;
        int d=det(W[0].x, W[0].y, W[m].x, W[m].y, p.x, p.y);
        if(d==0)      return contain(W[0], W[m], p);
        if(d==1)      return inside(W, p, m, r);
        else          return inside(W, p, l, m);
    }
}

int main() {
    int n, k;
    cout<<"Podaj n i k: ";
    cin>>n>>k;
    vector<node> W(n);
    cout<<"Opisz wielokąt: ";
    for(int i=0; i<n; ++i) cin>>W[i].x>>W[i].y;
    node p;
    cout<<"Podaj punkty: ";
    for(int i=0; i<k; ++i){
        cin>>p.x>>p.y;
        inside(W, p, 0, n-1)? cout<<"t" : cout<<"n";
        cout<<"\n";
    }
    return 0;
}

/*
 10
 6
 -50 -40
 0 -50
 30 -40
 50 -20
 60 20
 50 40
 20 50
 -20 50
 -40 40
 -50 0
 0 0
 80 20
 -50 -20
 -40 40
 -100 100
 40 -40
 */
