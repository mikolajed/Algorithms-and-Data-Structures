//
//  main.cpp
//  Równania diofantyczne
//
//  Created by Mikołaj Jędrzejewski on 12/23/20.
//

#include <iostream>
#include <vector>

using namespace std;

pair<int, int> extgcd(int a, int b) {
    if (b==0)
        return {1, 0};
    pair<int, int> p=extgcd(b, a%b);
    int x=p.first;  int y=p.second;
    
    return {y, x-(a/b)*y};
}

int main() {
    int a, b, m;
    
    cout<<"ax + by = m\n";
    cout<<"a = "; cin>>a;
    cout<<"b = "; cin>>b;
    cout<<"m = "; cin>>m;

    int x1=1, y1=0, x2=0, y2=1, z, q, r1=a, r2=b;
    
    while (r2>0) {
        q = r1/r2;
        z = r2;
        r2 = r1 - r2*q;
        r1 = z;
        
        z = x2;
        x2 = x1 - x2*q;
        x1 = z;
        
        z = y2;
        y2 = y1 - y2*q;
        y1 = z;
    }
    q = m/(r1+r2);
    if ((r1+r2)*q != m) cout<<"No solution\n";
    else {
        x1 = x1*q;
        y1 = y1*q;
        if (a*x1 + b*y1 != m) {
            x1 = -x1;
            y1 = -y1;
        }
        cout<<"x = "<<x1<<"\n";
        cout<<"y = "<<y1<<"\n";
    }
    
    return 0;
}
/*
 87 64 3
 240 46 2
 11 7 1
 
 7*8 11*5
*/
