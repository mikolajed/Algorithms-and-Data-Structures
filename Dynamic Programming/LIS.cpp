//
//  main.cpp
//  Longest Increasing Subsequence
//
//  Created by Mikołaj Jędrzejewski on 1/24/21.
//

#include <iostream>
#include <vector>
#include <list>

using namespace std;

list<int> LIS(vector<int> a, int n) {
    list<int> seq;          //LIS
    vector<int> dp(n+1);    //for given lentgh
    vector<int> h(n);       //helps to reconstruct the LIS
    
    int lis=0;
    for (int i=0; i<n; ++i) {
        int l=1, r=n;
        while (l<r) {
            int m=(l+r+1)/2;
            if (dp[m-1]<=a[i] and (dp[m-1]!=0 or m-1==0)) l=m;
            else                                          r=m-1;
        }
        lis = max(lis, l);
        dp[l]=a[i];
        h[i]=l;
    }
    
    int i=n-1;
    while (i>=0 and h[ a[i] ]!=lis) --i;
    int f=a[i];
    seq.push_front(a[i]);
    while (i>=0) {
        if (a[i] < f and h[ a[i] ]>=h[f]-1) {
            seq.push_front(a[i]);
            f=a[i];
        }
        --i;
    }
        
    return seq;
}

int main() {
    
    int n;
    cin>>n;
    vector<int> a(n);
    
    for (int i=0; i<n; ++i) cin>>a[i];
    
    list<int> seq = LIS(a, n);
    
    cout<<"LIS: ";
    for (auto it: seq)
        cout<<it<<" ";
    cout<<"\n";
    
    return 0;
}
/*
 8
 6 2 3 5 4 5 1 2
 */
