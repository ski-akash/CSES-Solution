#include <bits/stdc++.h>
using namespace std;

/* Implementation of Fenwick Trees - Easiest to Build */
vector<int> fn;
int n;

/* Build Fenwick Tree */
void build(vector<int> &arr){
    /* Obvious Approach := n * lg(n) */
    /* Optimized Approach := n */

    for(int i=1;i<=n;i++){
        fn[i] += arr[i];   
        int par = i + (i&-i);
        if(par <= n) fn[par] += fn[i]; /* Just check for the parent only!! */
    }
}

/* Sum Query */
int sum(int R){
    int S = 0;
    while(R > 0){
        S += fn[R];
        R = R - (R & -R);
    }
    return S;
}

/* Add */
void add(int indx, int u){
    while(indx <= n){
        fn[indx] += u;
        indx = indx + (indx & -indx);
    }
} 

int main(){
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    arr.insert(arr.begin(),0); /* making array 1-based index */

    fn.resize(arr.size(),0); /* cz it uses 1-based indexing */
    n = arr.size()-1;

    build(arr);
    cout << sum(4) << endl;

    add(2,5);
    cout << sum(4) << endl;

    return 0;
}