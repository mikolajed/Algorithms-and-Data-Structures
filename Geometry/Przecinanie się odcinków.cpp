//
//  main.cpp
//  Przeciananie się odcinków
//
//  Created by Mikołaj Jędrzejewski on 9/10/19.
//  Copyright © 2019 Mikołaj Jędrzejewski. All rights reserved.
//

#include <iostream>

using namespace std;

int sgn(int x){
    if(x>0)         return 1;
    else if(x<0)    return -1;
    return 0;
}

int det(int x1, int y1, int x2, int y2, int x3, int y3){
    return sgn(x1*y2+x2*y3+x3*y1-y2*x3-y3*x1-y1*x2);
}

bool cross(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4){
    if(
       (det(x1, y1, x2, y2, x3, y3)!=det(x1, y1, x2, y2, x4, y4) &&
        det(x3, y3, x4, y4, x1, y1)!=det(x3, y3, x4, y4, x2, y2)) ||
       (det(x1, y1, x2, y2, x3, y3)==0 && det(x1, y1, x2, y2, x4, y4)==0 &&
        ((x3>=min(x1, x2) && x3<=max(x1, x2) && y3>=min(y1, y2) && y3<=max(y1, y2)) ||
         (x4>=min(x1, x2) && x4<=max(x1, x2) && y4>=min(y1, y2) && y4<=max(y1, y2)))) ||
       (det(x3, y3, x4, y4, x1, y1)==0 && det(x3, y3, x4, y4, x2, y2)==0 &&
        ((x1>=min(x3, x4) && x1<=max(x3, x4) && y1>=min(y3, y4) && y1<=max(y3, y4)) ||
         (x2>=min(x3, x4) && x2<=max(x3, x4) && y1>=min(y3, y4) && y2<=max(y3, y4))))
       ) return 1;
    return 0;
}

int main()
{
    int n;
    cout<<"Podaj n: ";  cin>>n;
    int x1, y1, x2, y2, x3, y3, x4, y4;
    cout<<"\n";
    for(int i=0; i<n; ++i){
        cin>>x1>>y1>>x2>>y2>>x3>>y3>>x4>>y4;
        (cross(x1, y1, x2, y2, x3, y3, x4, y4))? cout<<"t" : cout<<"n";
        cout<<"\n";
    }
    return 0;
}

/*
 14
 10 30 20 40 30 50 40 60
 10 15 20 15 15 10 15 20
 30 30 30 40 40 30 40 40
 50 30 50 40 50 40 50 50
 60 30 60 40 60 50 60 60
 70 30 80 30 80 30 90 30
 10 50 20 50 30 50 40 50
 30 10 40 20 40 10 50 20
 60 10 70 20 60 20 70 10
 10 60 20 70 20 70 30 80
 40 60 40 70 30 80 50 80
 70 50 80 50 90 40 90 60
 60 70 60 90 60 80 60 100
 30 80 30 100 30 90 40 90
 
 
 n
 t
 n
 t
 n
 t
 n
 n
 t
 t
 n
 n
 t
 t
 
 
 */
