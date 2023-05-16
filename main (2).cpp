#include <iostream>
#include<cmath>
#include<iomanip>
#include<cstdlib>
#include<ctime>
#include<conio.h>
using namespace std;
#define Max 3
/** group members:

 */

class Player{
private:
    string name;
    float* trials=NULL;
    float tot_diff=0,perf_in_trial=0,perf_in_acc=0,guess_perf=0;//perf(perfonmance),acc(accuracy)
    int tot_trial=0, max_trial=0;///change tot trial
    int counter=0;//a conter which used as the index for the trials array


public:
    //constructor takes the  player name and maximum number of trial
   // default  values
    Player(string name="unknown" ,int no_tries=Max){
        max_trial = no_tries;
        counter=0;
        this->name= name;
        trials = new float[no_tries];

    }
    float* getTrials(){
        return trials;
    }
//getters
    float get_tot_diff(){
        return tot_diff;
    }
    float get_perf_in_trial(){
        return perf_in_trial;
    }
    float calc_perf_in_acc(){
        return perf_in_acc;
    }
    float get_guess_perf(){
        return guess_perf;
    }
    float get_tot_trial(){
        return tot_trial;
    }
    int get_no_of_trials(){
        return tot_trial;
    }
    string getName(){
        return name;
    }
//calculates the total difference
    float calc_tot_diff(int thouht_no){
        float sum = 0;
        for (int i=0;i<tot_trial;i++){
           /// cout<<thouht_no- trials[i]<<endl;
            sum+= abs(thouht_no - trials[i]);
        }
        tot_diff= sum;
        return sum;

    }
//calculates the prerformance intrial in percentage
    float calc_perf_in_trial(){

        //cout<< "hhih:  "<<tot_trial<<" "<<max_trial<<endl;
        float res = 100.0-(( float(tot_trial) / float(max_trial))*100.0);
        ///cout<< "res"<<  float(tot_trial) / float(max_trial) <<endl;

        perf_in_trial=res;
        return res;

    }
//calculates the performance accuracy in percentage //and returns true if the thought number is
//bigger or returns false if the thought number selected below
    float calc_perf_in_acc(int n,int thought_no,int max_no){

        float sum = 0,tought_num=float(thought_no);

        for (int i=1;i<=n;i++){
           /// cout<< sum<<endl;
            sum += i - ((tought_num - float(max_no) )*tought_num + tought_num);
        }

    //proportion = 1 - (double)totalDiff / (n * abs(n - thoughtNum));
    //accuracy = proportion * 100;
        perf_in_acc =1 - (double)tot_diff / (max_no * abs(max_no - thought_no));
        perf_in_acc*=100;
        //perf_in_acc =100 - (tot_diff/sum)*100.0;
        ///cout<< sum<<endl;
        return perf_in_acc;

    }
//calculates guess performance
    float calc_guess_perf(){
        guess_perf = (perf_in_trial + perf_in_acc)/2.0;
        return guess_perf;
    }
//accepts a number from a user until maximum number of trial reaches and increment the trial counter
    void accept_num(){
        if(counter > max_trial){
            cout<<"\tmaximun trial for player reached!"<<endl;
            return;
        }
        cout<< "\tplease enter your guess: ";
        cin>> trials[counter];
        counter++;
        //tot_trial++;
    }
    void inc_tot_trial(){
        tot_trial++;
    }
//accepts the question from user and answers accordingly

    bool select_range(int tought_no){
        bool  good = false;//boolean checker for invalid enteries
        string resp,opreator;
        float num=0;
        while(!good){
            resp="";//this  is where the player response is stored as the whole string
            opreator="";//this is where the comparison operators stored
            num=0;//stores the extracted number
            cout<<"\n\n  ==>"<<right<<setw(6)<<name<<" please write your question: ";
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
                    cout<<"\n\t---! invalid input 1---"<<endl;
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

        //if the number is in the seloected range
        if(opreator==">=" &&  tought_no>=num) return true;
       else if(opreator=="<="&&  tought_no<=num) return true;
       //but if the number was found higher or lower return false
        return false;

    }
//function to calculate all valuees
    void calc_all(int thought_no,int n,int maxx){
    	///pass parametres
    	calc_tot_diff(thought_no);
    	calc_perf_in_trial();
    	calc_perf_in_acc(n, thought_no,maxx);
    	calc_guess_perf();


    }
    ~Player(){
     delete []trials;
    }

};
//used to create a single node for the players list
struct node{
    Player* data=NULL;
    struct node* next =NULL;
};
void bubbleSort(node*);//function to sort the linked list_nodes
//linked list for storing players
class singly_LL{
private:
    node* head = NULL;
    node* tail = NULL;
    int SIZE=0;
public:
//insert player and assign name and maximum number of tries
    void insert_first(string name,int max_trial){
        node* temp = new node;//create a new node
        temp->data = new Player(name, max_trial);//assign the data by calling the constructor and assign their names and max_no_trial
        if(head==NULL){//if there is no elements
            head = temp;
            tail = temp;
            SIZE++;
            return;
        }
        temp->next = head;//make the new node next point to head
        head = temp;//and set the head pointer to point to the new node
        SIZE++;
        return;
    }
//display all player/s data
    void disp(){
    node* temp = head;//temp points to the head
    system("CLS");
    cout<<"\n\t\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd"<<endl;
    cout<<"\t\xcd\xcd\xcd\xcd\xcd  |RESULT|  \xcd\xcd\xcd\xcd\xcd\xcd"<<endl;
    cout<<"\t\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd"<<endl;

    while(temp){
      float* arr = temp->data->getTrials();//store the trail of each  player

    cout<<"\n========================"<<endl;
    cout<<temp->data->getName()<<"'s  trial: ";
    for(int i=0;i<temp->data->get_no_of_trials();i++){//until we reach end of list//
        cout<<left<<setw(3)<< arr[i]<<" ";
    }
    cout<<endl;
    string name = temp->data->getName();
    float tot_diff= temp->data->get_tot_diff();
    float perf_in_trial,perf_in_acc,guess_perf;

    perf_in_trial= temp->data->calc_perf_in_trial();
    perf_in_acc= temp->data->calc_perf_in_acc();
    guess_perf= temp->data->get_guess_perf();

    cout <<"\tTD: "<< tot_diff << endl;
    cout <<"\tPT: "<< perf_in_trial << endl;
    cout <<"\tPA: "<< perf_in_acc << endl;
    cout <<"\tGP: "<< guess_perf << endl;
    cout<<"========================\n"<<endl;
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
    node* temp= head;//make the temporary variable point to the head
    head= head->next;//shift the head pointer to the next node
    delete temp->data;//delete its data inthis case the call player destructor
    delete temp;//delete the node
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
     //singly_LL* players;
     bool game_over;

public:
        singly_LL* players;
		Game(){
		  thought_number=NULL;
		  no_of_players=0;
		  players = NULL;
		  low=0;
		  high=100;
		  bool game_over= false;
		}
    void start(){
        system("CLS");
        players= new singly_LL;
        thought_number = gen_rand(low,high);
        cout<<"\n\t*******************************************************\t"<<endl;
        cout<<"\t********************>     WELCOME     <*******************\t"<<endl;
        cout<<"\t*******************************************************\n\t"<<endl;
        cout<<"======================="<<endl;
        cout<<"\t Gussing Game" << endl;
        cout<<"======================="<<endl;
        cout<<"please enter number of players: ";

         cin>>no_of_players;

        string name;
        for(int i=0;i< no_of_players;i++){
            cout<<"please enter player_"<<i+1<<" name: ";
            cin>> name;
            players->insert_first(name,Max);
        }

    }
//calculate all players performance//
    void calc(){
        node* temp = players->get_head();
        while(temp){

            temp->data->calc_all(thought_number,high,high);
            temp = temp->next;

        }
    }
//for each  players in the current round ask each player a question and

    void round(){
    system("CLS");

        cout<<"so lets move on to the rounds!!"<<endl;
        cout<<"GOOD LUCK!!"<<endl;
        node* temp = players->get_head();
//loop which it tracks each player round
    for(int j=0;j<Max;j++){
//this loop gives chance for all  players
        inc_tot_trial();//just increase all players total trial at each round first round
        for(int i=0;i<no_of_players;i++){

        system("CLS");//clear the screen

        cout<<"\t\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd"<<endl;
        cout<<"\t\xcd\xcd\xcd\xcd\xcd  |ROUNDS|  \xcd\xcd\xcd\xcd\xcd\xcd"<<endl;
        cout<<"\t\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd"<<endl;

           /// cout<<"\nANS: "<< thought_number<<endl;
//accepts  player questions//
             bool  resp = temp->data->select_range(thought_number);
             if(resp){
                cout<<"YES!"<<endl;
             }else{
                cout<<"NO!"<<endl;
             }
             temp->data->accept_num();
             if(temp->data->getTrials()[j]== thought_number){//for each round since the j index is the same index for the currently enterd number by the player
                cout<<"\t=====it's Correct!======="<<endl;
                calc();//calculate all players performance

                //players->disp();
                game_over= true;
                end_game();
                return;
             }else{
                cout<<"\t-----it's wrong!------"<<endl;
             }
            if(temp->next == NULL){//if i have reached the end of list before finishing the rounds go back to the first player
               temp=players->get_head();
               cout<<"enter any key to continue.. "<<endl;
               getch();//get a single char before continue
               continue;
            }
            temp = temp->next;
            cout<<"enter any key to continue.. "<<endl;
            getch();
            }

    }
    calc();

    //players->disp();
    game_over = true;
    end_game();

    }
//increase the number of trials of all players
    void inc_tot_trial(){
    node* temp = players->get_head();
        while(temp){//for all players
            temp->data->inc_tot_trial();
            temp = temp->next;
        }
    }
    // a random number generator which generates random number between a given range
    int gen_rand(int minn,int maxx){
        srand(time(0));
        return minn+(rand()%maxx);

    }
//game loops until the player wants to quit
    void game_loop(){
    	bool quit= false;
    	int resp;
    	while(quit==false){
            system("CLS");

            cout<<"\t\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd"<<endl;
    		cout<<"\t\xcd\xcd\xcd\xcd\xcd\xcd\xcd   MENU   \xcd\xcd\xcd\xcd\xcd\xcd"<<endl;
            cout<<"\t\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd"<<endl;
    		cout<<"\n\n\t[1] New Game"<<endl;
    		cout<<"\t[0] quit\n"<<endl;

    		cout<<"enter your choice: ";
    		cin>>resp;
    		switch(resp){
    			case 1:
                    start();//start rhe game
                    round();//start rounds
                    break;
    			case 0:
    				quit= true;
    				break;
    		}
    		delete players;



    	}
    }
//delete all players
    void  end_game(){
        if(game_over){
            system("CLS");
            cout<<"\t\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd"<<endl;
            cout<<"\t\xcd\xcd\xcd  |SCORE BOARD|  \xcd\xcd\xcd\xcd"<<endl;
            cout<<"\t\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd"<<endl;
            cout<<"\nTHANKS FOR PLAYING!!"<<endl;
            cout<<"\nThe Answer was: "<<thought_number<<endl;
            cout<<"======================="<<endl;
            bubbleSort(players->get_head());
            bubbleSort(players->get_head());
            bubbleSort(players->get_head());
            bubbleSort(players->get_head());
            node* temp = players->get_head();
            string word = "";
            int i = 0;

            while(temp){
                ///cout <<"\n"<<i+1<<" "<<temp->data->get_tot_diff()<<endl;
                if(i==0) word = " won's ";
                else if(temp->next!=NULL && i!= no_of_players-1)word = " scores ";
                else word = " losse's ";

                cout <<"\n"<<i+1<<" "<<temp->data->getName()<< word <<"with a guess performance of "<<fixed<<setprecision(2)<<temp->data->get_guess_perf()<<"%"<<endl;
                temp = temp->next;
                i++;

            }
            cout<<"======================="<<endl;
            cout<<"press any key to continue..."<<endl;
            getch();


        }
    }
    ~Game(){
		  delete players;
		}


};
void bubbleSort(node* head) {
    node* current = head;
    node* nextNode = NULL;
    Player* temp;

    if (head == NULL) {
        return;
    }

    do {
        nextNode = current->next;
        while (nextNode != NULL) {
            //cout<<"down it  "<<current->data->get_guess_perf()<<" "<<nextNode->data->get_guess_perf()<<endl;
            if (current->data->get_guess_perf() < nextNode->data->get_guess_perf()) {
                temp = current->data;
                current->data = nextNode->data;
                nextNode->data = temp;
            }
            nextNode = nextNode->next;
        }
        current = current->next;
    } while (current != NULL);
}

///main driver
int main()
{
    Game* game = new Game;

    game->game_loop();
//    game->start();
//    game->round();

    delete game;

}
