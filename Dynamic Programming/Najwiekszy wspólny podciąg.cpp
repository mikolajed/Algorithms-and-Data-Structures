//
//  main.cpp
//  NWP
//
//  Created by Mikołaj Jędrzejewski on 2/5/19.
//  Copyright © 2019 Mikołaj Jędrzejewski. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int nwp(vector<int> *T, string s1, string s2, int d1, int d2){
    for(int i=1; i<d2+1; i++){
        for(int j=1; j<d1+1; j++){
            if(s1[j-1]==s2[i-1])
                T[i][j]=T[i-1][j-1]+1;
            else
                T[i][j]=max(T[i-1][j], T[i][j-1]);
        }
    }
    return T[d2][d1];
}

void wypisz(vector<int> *T, int d1, int d2){
    for(int i=0; i<d2+1; i++){
        for(int j=0; j<d1+1; j++)
            cout<<T[i][j]<<" ";
        cout<<"\n";
    }
}

void nwp_str(vector<int> *T, int i, int j, string s){
    while(T[i][j]!=0){
        while(T[i][j]==T[i][j-1])j--;
        j--;
        while(T[i][j]==T[i-1][j])i--;
        //cout<<T[i][j]<<" ";
        cout<<s[j];
    }
    cout<<"\n";
}

void NwpStrRek(vector<int> *T, int i, int j, string s){
    if(T[i][j]>0){
        while(T[i][j]==T[i][j-1])j--;
        j--;
        while(T[i][j]==T[i-1][j])i--;
        NwpStrRek(T, i, j, s);
        cout<<s[j];
    }
    cout<<"\n";
}

int main()
{
    string s1, s2;
    cout << "Podaj 1 wyraz: ";
    cin>>s1;
    cout << "Podaj 2 wyraz: ";
    cin>>s2;
    int d1=s1.length();
    int d2=s2.length();
    
    vector<int> T[d1+1];
    
    for(int i=0; i<d1+1; i++)
        T[0].push_back(0);
    for(int i=1; i<d2+1; i++)
        for(int j=0; j<d1+1; j++)
            T[i].push_back(0);
    
    cout<<"NWP: "<<nwp(T, s1, s2, d1, d2)<<"\n";
    //nwp_str(T, d2, d1, s1);
    NwpStrRek(T, d2, d1, s1);
    wypisz(T, d1, d2);
    return 0;
}
/*
 algorytm
 logarytm
 */
