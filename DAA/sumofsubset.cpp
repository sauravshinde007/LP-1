#include <iostream>
#include <vector>
using namespace std;
//backtracking soln

// i-> represents current index
// n-> length of set
void printSumofSubset(int i, int n, int targetSum, int set[], vector<int> &subset){
    //base case

    //it means we have reached the sum
    if(targetSum == 0){
        //print the subset
        cout<<"[ ";
        for(int i=0; i<subset.size(); i++){
            cout<<subset[i]<<" ";
        }
        cout<<"]"<<endl;

        //return from recursion
        return;
    }

    if(i == n){
        //it means we have reached the end of set
        return;
    }

    //don't include current elem
    printSumofSubset(i+1,n,targetSum,set,subset);

    //include curr elem if less than target sum
    if(targetSum >= set[i]){
        //add elem to subset
        subset.push_back(set[i]);
        //recursion
        printSumofSubset(i+1,n,targetSum-set[i],set,subset);
        //backtrack
        subset.pop_back();
    }
}

int main(){
    int set[] = {10,20,30,40};
    int target = 50;
    vector<int>subset;

    printSumofSubset(0,4,target,set,subset);
    return 0;
}