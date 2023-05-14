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
    int counter=0;//a conter which used as the index for the trials array


public:
    //constructor takes the  player name and maximum number of trial
   // default  values
    Player(string name="unknown" ,int no_tries=Max){
        max_trial = no_tries;
        counter=0;
        this->name= name;
        trials = new float[no_tries];
        trials[0]=11;
        trials[1]=20;
        trials[2]=23;
        trials[3]=25;
        trials[4]=26;

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
            cout<<thouht_no- trials[i]<<endl;
            sum+= abs(thouht_no - trials[i]);
        }
        tot_diff= sum;
        return sum;

    }
//calculates the prerformance intrial in percentage
    float calc_perf_in_trial(){

        ///cout<< "hhih:  "<<tot_trial<<" "<<max_trial<<endl;
        float res = 100.0-(( float(tot_trial) / float(max_trial))*100.0);
        ///cout<< "res"<<  float(tot_trial) / float(max_trial) <<endl;

        perf_in_trial=res;
        return res;

    }
//calculates the performance accuracy in percentage //and returns true if the thought number is
//bigger or returns false if the thought number selected below
    float calc_perf_in_acc(int n,int thought_no,int max_no){

        float sum = 0,tought_num=float(thought_no);

        for (int i=1;i<n;i++){
           /// cout<< sum<<endl;
            sum += i - ((tought_num - float(max_no) )*tought_num + tought_num);
        }
        perf_in_acc =100 - (tot_diff/sum)*100.0;
        ///cout<< sum<<endl;
        return perf_in_acc;

    }
//calculates guess performance
    float calc_guess_perf(){
        guess_perf = (perf_in_trial + perf_in_acc)/2.0;
        return guess_perf;
    }

    void accept_num(){
        if(counter > max_trial){
            cout<<"maximun trial for player reached!"<<endl;
            return;
        }
        cout<< "please enter your guess: ";
        cin>> trials[counter];
        counter++;
    }
//accepts the question from user and answers accordingly
    bool select_range(int tought_no){
        bool  good = false;//boolean checker for invalid enteries
        string resp,opreator;
        float num=0;
        while(!good){
            resp="";
            opreator="";
            num=0;
            cout<<name<<" please write your question: ";
            cin>> resp;
            bool good2= false;
            for(int i=0;i<resp.length();i++){
                if(resp[i]=='?'&& i==resp.length()-1){//skip it there is a question mark at the end of  string
                    good= true;
                    continue;
                }else if((resp[i]=='>' || resp[i]=='<' || resp[i]=='=')){
                    opreator+= resp[i];
                }else if(isdigit(resp[i])){
                    num = num*10 + (resp[i]-'0');
                }else{
                    cout<<"invalid input!"<<endl;
                    break;
                }
                if(i== resp.length()-1){
                    good2 =  true;
                }
                if(good2 == false){
                    continue;
                }else good = true;
            }
        }
        cout<< num<<" "<<opreator<<endl;
        if(opreator==">=" &&  tought_no>=num) return true;
       else if(opreator=="<="&&  tought_no<=num) return false;
        return num;

    }

};

class Game{

};
int main()
{
    float  tg= 24;
    Player a("bob", Max);
        a.accept_range(30);

    float* arr = a.getTrials();
    for(int i=0;i<Max;i++){
        cout<< arr[i]<<" ";
    }
    cout<<endl;
    string name = a.getName();
    float td= a.calc_tot_diff(tg),pt,pa,gp;

    pt= a.calc_perf_in_trial();
    pa = a.calc_perf_in_acc(100,tg,100);
    gp= a.calc_guess_perf();
    cout <<"TD: "<< td << endl;
    cout <<"PT: "<< pt << endl;
    cout <<"PA: "<< pa << endl;
    cout <<"GP: "<< gp << endl;
    return 0;
}
