//
//  main.cpp
//  KMP
//
//  Created by Mikołaj Jędrzejewski on 12/15/20.
//

#include <iostream>
#include <vector>

using namespace std;

void ComputeP(string w, vector<int> &P) {
    int t=0;
    int m=(int)w.size();
    P[0]=P[1]=0;
    for (int i=2; i<=m; ++i) {
        while (t>0 and w[t]!=w[i-1]) t=P[t];
        if (w[t]==w[i-1]) ++t;
        P[i]=t;
    }
}

void KMP(string s, string w) {
    int n=(int)s.size();
    int m=(int)w.size();
    vector<int> P(m+1);
    
    ComputeP(w, P);
    int j=1, i=0;
    
    cout<<"Pozycje wzorca w tekście: ";
    while (i<=n-m) {
        j=P[j];
        while (j<m and s[i+j]==w[j]) ++j;
        if (j==m)
            cout<<i<<" ";
        i+=max(1, j-P[j]);
    }
    cout<<"\n";
}

int main() {
    string w, s;
    
    cout<<"Podaj słowo: ";
    cin>>s;
    cout<<"Podaj wzorzec: ";
    cin>>w;
    
    KMP(s, w);
    
    return 0;
}
