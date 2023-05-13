#include <iostream>
#include<cmath>
using namespace std;
#define Max 5
class Player{
private:
    string name;
    float* trials;
    float tot_diff,perf_in_trial,perf_in_acc,guess_perf;//perf(perfonmance),acc(accuracy)
    int tot_trial = 4, max_trial;///change tot trial


public:
    //constructor takes the  player name and maximum number of trial
   // default  values
    Player(string name="unknown" ,int no_tries=Max){
        max_trial = no_tries;
        this->name= name;
        trials = new float[no_tries];
        trials[0]=18;
        trials[1]=29;
        trials[2]=22;
        trials[3]=25;
        trials[4]=23;

    }
    float* getTrials(){
        return trials;
    }
    string getName(){
        return name;
    }
//calculates the total difference
    float calc_tot_diff(int thouht_no){
        float sum = 0;
        for (int i=0;i<tot_trial;i++){
           // cout<<thouht_no- trials[i]<<endl;
            sum+= abs(thouht_no- trials[i]);
        }
        tot_diff= sum;
        return sum;

    }
//calculates the prerformance intrial in percentage
    float calc_perf_in_trial(){

        cout<< tot_trial<<" "<<max_trial<<endl;
        float res = 100.0-(( float(tot_trial) / float(max_trial) )*100.0);
        cout<< float(tot_trial)/float(max_trial) <<endl;

        perf_in_trial=res;
        return res;

    }
//calculates the performance accuracy in percentage
    float calc_perf_in_acc(int n,int thought_no,int max_no){
        float sum = 0,num=float(thought_no);

        for (int i=0;i<n;i++){
           /// cout<< sum<<endl;
            sum+=i - (((num - float(max_no) )*num+ num));
        }
        perf_in_acc =(tot_diff/sum)*100.0;
        ///cout<< sum<<endl;
        return (tot_diff/sum)*100.0;

    }

};

class Game{

};
int main()
{
    float  tg= 60;
    Player a("bob", Max);
    float* arr = a.getTrials();
    for(int i=0;i<Max;i++){
        cout<< arr[i]<<" ";
    }
    cout<<endl;
    string name = a.getName();
    float td= a.calc_tot_diff(tg),pt,pa;
    pt= a.calc_perf_in_trial();
    pa = a.calc_perf_in_acc(100,tg,100);
    cout <<"td: "<< td << endl;
    cout <<"pt: "<< pt << endl;
    cout <<"pa: "<< pa << endl;
    return 0;
}
