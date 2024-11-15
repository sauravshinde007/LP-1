#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item{
    int profit, weight;

    //constructor
    Item(int p,int w){
        this->profit = p;
        this->weight = w;
    }
};

static bool cmp(struct Item a, struct Item b){
    double r1 = (double)a.profit/(double)a.weight;
    double r2 = (double)b.profit/(double)b.weight;

    return r1 > r2;

}

double fractionalKnapSack(struct Item items[], int N, int W){

    //sort items using p/w ratio
    sort(items, items+N, cmp);

    double finalValue = 0.0;

    //iterate over items
    for(int i=0; i<N; i++){
        //check whether curr Weight exceeds W or not
        if(items[i].weight <= W){
            finalValue += items[i].profit;
            W -= items[i].weight; 
        }else{
            //remaining weight is less (use all remaining weight)
            finalValue += items[i].profit*((double)W/(double)items[i].weight);
            break;
        }
    }

    return finalValue;
}

int main(){
    Item items[] = {{60,10}, {100,20}, {120,30}};
    int N = 3;
    int W = 50;

    cout<<"Total profit : "<<fractionalKnapSack(items,N,W);

    return 0;
}