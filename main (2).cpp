#include <iostream>
#include<cmath>
#include<iomanip>
#include<cstdlib>
#include<ctime>
#include<conio.h>
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
//        trials[0]=11;
//        trials[1]=20;
//        trials[2]=23;
//        trials[3]=25;
//        trials[4]=26;

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
        ///cout<< num<<" "<<opreator<<endl;
        //if the number is in the seloected range
        if(opreator==">=" &&  tought_no>=num) return true;
       else if(opreator=="<="&&  tought_no<=num) return true;
       //but if the number was found higher or lower return false
        return false;

    }
    ~Player(){
     delete []trials;
    }

};
struct node{
    Player* data=NULL;
    struct node* next =NULL;
};
//linked list for storing players
class singly_LL{
private:
    node* head = NULL;
    int SIZE=0;
public:
//insert player and assign name and maximum number of tries
    void insert_first(string name,int max_trial){
        node* temp = new node;//create a new node
        temp->data = new Player(name, max_trial);//assign the data by calling the constructor and assign their names and max_no_trial
        if(head==NULL){
            head = temp;
            SIZE++;//increment size of the LL
            return;
        }
        temp->next = head;
        head = temp;
        SIZE++;
        return;
    }
    void disp(){
    node* temp = head;
    while(temp){
        cout<<temp->data->getName()<<endl;
        temp= temp->next;
    }

  }
  node* get_head(){
    return head;
    }
    int get_size(){
        return SIZE;
   }
   void rem_first(){
    node* temp= head;
    head= head->next;
    delete temp;
   }
//destructor to free the occopied space after game ends
 ~singly_LL(){
  while(head){
   rem_first();
  }
 }


};
class Game{
    int thought_number,low,high,no_of_players;
     singly_LL* players = NULL;

public:

    void start(){
        players= new singly_LL;
        thought_number = gen_rand(0,100);
        cout<<"\n\t \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd"<<endl;
        cout<<"\t \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd WELCOME! \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n"<<endl;
        cout<<"please enter how many players are there: "<<endl;

         cin>>no_of_players;

        string name;
        for(int i=0;i< no_of_players;i++){
            cout<<"please enter player_"<<i+1<<" name: "<<endl;
            cin>> name;
            players->insert_first(name,Max);
        }

    }
//for each  players in the current round ask each player a question and
    void round(){
        system("CLS");
        //cout<<"\nANS: "<< thought_number<<endl;
        cout<<"so lets move on to the rounds!!"<<endl;
        cout<<"GOOD LUCK!!"<<endl;
        node* temp = players->get_head();
    for(int j=0;j<Max;j++){
        for(int i=0;i<no_of_players;i++){
            system("CLS");//clear the screen
                    //cout<<"\nANS: "<< thought_number<<endl;
             //accepts  player questions//
             bool  resp = temp->data->select_range(thought_number);
             if(resp){
                cout<<"YES!"<<endl;
             }else{
                cout<<"NO!"<<endl;
             }
             temp->data->accept_num();
             if(temp->data->getTrials()[j]== thought_number){
                cout<<"it's Correct! "<<endl;
                return;
             }else{
                cout<<"it's wrong! "<<endl;
             }
            if(temp->next == NULL){//if i have reached the end of list before finishing the rounds go back to the first player
               temp=players->get_head();
               cout<<"enter any key to continue.. "<<endl;
               getch();
               continue;
            }
            temp = temp->next;
            cout<<"enter any key to continue.. "<<endl;
            getch();
            }
    }
    }
    // a random number generator which generates random number between a given range
    int gen_rand(int minn,int maxx){
        srand(time(0));
        return minn+(rand()%maxx);

    }


};
int main()
{
//    Player* players= new Player[5];
//    float  tg= 24;
//    Player a("bob", Max);
//        a.select_range(30);
//
//    float* arr = a.getTrials();
//    for(int i=0;i<Max;i++){
//        cout<< arr[i]<<" ";
//    }
//    cout<<endl;
//    string name = a.getName();
//    float td= a.calc_tot_diff(tg),pt,pa,gp;
//
//    pt= a.calc_perf_in_trial();
//    pa = a.calc_perf_in_acc(100,tg,100);
//    gp= a.calc_guess_perf();
//    cout <<"TD: "<< td << endl;
//    cout <<"PT: "<< pt << endl;
//    cout <<"PA: "<< pa << endl;



//    singly_LL* players = new singly_LL;
//    players->insert_first("bob",Max);
//    players->insert_first("abc",Max);
//    players->insert_first("asd",Max);
//    players->disp();

    Game* game = new Game;

    game->start();
    game->round();
//    cout <<"GP: "<< gp << endl;
//    return 0;



}
