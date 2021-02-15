//
//  main.cpp
//  Trie 2
//
//  Created by Mikołaj Jędrzejewski on 8/15/20.
//  Copyright © 2020 Mikołaj Jędrzejewski. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

typedef unordered_map<char, int> dict;

class Trie {
private:
    vector<dict> T;
    vector<bool> E;  //contains node number in the Trie where i-th string ends
    int A;  //size of alphabet
    int t;  //number of nodes
    
    void addNode(int j, char l) {
        dict NewDict;
        T.push_back(NewDict);
        E.push_back(0);
        ++t;
        T[j][l]=t;
    }
        
public:
    Trie(int alf_size=26) {
        A=alf_size;
        dict NewDict;
        T.push_back(NewDict);
        E.push_back(1);
        t=0;
    }
        
    void insert(string w) {
        int j=0;
        for (int i=0; i<(int)w.size(); ++i) {
            char l=w[i];
            int index=T[j][l];
            if (index)
                j=index;
            else {
                addNode(j, l);
                j=t;
            }
        }
        E[j]=1;
    }
    
    int search(string w) {
        int j=0, i=0;
        for (; i<(int)w.size(); ++i) {
            char l=w[i];
            int index=T[j][l];
            if (index)
                j=index;
            else
                return -1;
        }
        if (i==(int)w.size() and E[j]) return j;
        return -1;
    }
    
    void printAll(string w="", int j=0) {
        if (E[j])
            cout<<w<<"\n";
        for (auto it: T[j]) {
            if (it.second) {
                w+=it.first;
                printAll(w, it.second);
                w.pop_back();
            }
        }
    }
    
    //given word w find the node index that corresponds to the last letter of w in the Trie
    //if such a prefix w exists otherwise return 0
    int searchPrefix(string w) {
        int j=0;
        for (int i=0; i<(int)w.size(); ++i) {
            char l=w[i];
            int index=T[j][l];
            if (index)
                j=index;
            else
                return 0;
        }
        return j;
    }
    
    //count number of words in the Trie that contain prefix that ends at index j
    int countWords(int j) {
        int ans=0;
        if (E[j]) ++ans;
        for (auto it: T[j]) {
            int index=it.second;
            if (index)
                ans+=countWords(index);
        }
        return ans;
    }

    //given word w find the number of words in the Trie which prefix w
    int countPrefixes(string w) {
        int j=searchPrefix(w);
        return countWords(j);
    }
};

int main() {
    
    Trie D(26);
    
    string w;
    int opt=1;
    while (1) {
        cout<<"(1/2): ";
        cin>>opt;
        cout<<"w: ";
        cin>>w;
        if (opt==1) {
            D.insert(w);
            D.printAll();
        }
        else if (opt==2){
            cout<<D.countPrefixes(w);
        }
        cout<<"\n";
    }
    
    return 0;
}
