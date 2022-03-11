#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;      //introduces namespace std

class player
{
     private:
          int archers; 
          int catapults; 
          int swordsmen;
     public:
          player();
          player(int archers,int catapults,int swordsmen);
          int checkSoldiers(int k);
          void change(int k,int num);
          void fight(player target,int catapults_sent,int swordsmen_sent,int archers_sent);
};

player::player()
{
     srand(time(0)); //seed the random number generator

     //units that the player start with (random)
     //random number between 70 and 20
     this->archers = rand() % (51) + 20; 
     //between 50 and 10
     this->catapults = rand() % (41) + 10;
     //between 150 and 50
     this->swordsmen = rand() % (101) + 50; 
}

player::player(int archers,int catapults,int swordsmen)
{
     //units that the player starts with
     this->archers=archers;
     this->catapults=catapults;
     this->swordsmen=swordsmen;
}

int player::checkSoldiers(int k)
{
     if(k==1)
          return this->archers;
     else if(k==2)
          return this->catapults;
     else if(k==3)
          return this->swordsmen;
}

void player::change(int k,int num)
{
     if(k==1)
          this->archers-=num;
     else if(k==2)
          this->catapults-=num;
     else if(k==3)
          this->swordsmen-=num;
}

void player::fight(player target,int catapults_sent,int swordsmen_sent,int archers_sent)
{
     int archers_dead, catapults_dead, swordsmen_dead;
     int g_archers_dead, g_catapults_dead;
     int g_swordsmen_dead;
   
     //each catapult kills 2 archers
     archers_dead = 2 * target.checkSoldiers(2);
     //each swordsman kills 1 catapult
     catapults_dead = target.checkSoldiers(3);
     //each archer kills 3 swordsmen
     swordsmen_dead = 3 * target.checkSoldiers(1);

     g_archers_dead = 2 * catapults_sent;
     g_catapults_dead = swordsmen_sent;
     g_swordsmen_dead = 3 * archers_sent;
        
     //makes sure that the number of 
     //units does not go below 0.
     this->archers = (archers_dead < this->archers) ?
          this->archers - archers_dead : 0;
     this->catapults = (catapults_dead < this->catapults) ?
          this->catapults - catapults_dead : 0;
     this->swordsmen = (swordsmen_dead < this->swordsmen) ?
          this->swordsmen - swordsmen_dead : 0;
     target.change(1,(g_archers_dead < target.checkSoldiers(1)) ?
          target.checkSoldiers(1) - g_archers_dead : 0);
     target.change(2,(g_archers_dead < target.checkSoldiers(2)) ?
          target.checkSoldiers(2) - g_catapults_dead : 0);
     target.change(3,(g_archers_dead < target.checkSoldiers(3)) ?
          target.checkSoldiers(3) - g_swordsmen_dead : 0);

     cout << "It was a long battle. " 
          << archers_dead << " archers died.\n"
          << catapults_dead << " catapults died.\n"
          << swordsmen_dead << " swordsmen died.\n";
}


int main( void )
{
     string name; //used to store the player’s name
     bool end = false; //used to test if the user chose to quit
     bool lost; //used to test if the user lost the game
    
     int menu_choice; //stores the user’s choice from the menu
    
     player User(50,25,100);
     player Germanians; 
    
     //stores which numbers correspond to which menu choices
     int archers_menu, catapults_menu, swordsmen_menu;
     int fight_menu;
        
     cout << "Welcome Adventurer, what is your name?\n";
     cin >> name;
     cout << "Well, " << name 
          << " welcome to the Roman Commander Game.\n"
          << "\nYou are the commander of the Roman Army"
          << " attacking Germania.";
     while (!end) //main game loop
     {
          //variables to store how many units the player sends
          int archers_sent=0, catapults_sent=0;
          int swordsmen_sent=0;
          cout << "\nYou have " << User.checkSoldiers(1)
               << " archers, " << User.checkSoldiers(2)
               << " catapults, and "
               << User.checkSoldiers(3) << " swordsmen.\n"
               << "\nGermania has " << Germanians.checkSoldiers(1) 
               << " archers, "
               << Germanians.checkSoldiers(2) << " catapults, and " 
               << Germanians.checkSoldiers(3)
               << " swordsmen.\n";
          do //pre-battle loop
          {
               //keeps track of which menu numbers
               //are being used
               int i = 1; 
               if (User.checkSoldiers(1) > 0 && 
                    ((User.checkSoldiers(1) - archers_sent) != 0))
               {
                    archers_menu = i;
                    cout << "[" << i << "] Send Archers\n";
                    i++;
               }
               else archers_menu = 0;
               if (User.checkSoldiers(2) > 0 && 
                    ((User.checkSoldiers(2) - catapults_sent) != 0))
               {
                    catapults_menu = i;
                    cout << "[" << i << "] Send Catapults\n";
                    i++;
               }
               else catapults_menu = 0;
               if (User.checkSoldiers(3) > 0 && 
                    ((User.checkSoldiers(3) - swordsmen_sent) != 0))
               {
                    swordsmen_menu = i;
                    cout << "[" << i << "] Send Swordsmen\n";
                    i++;
               }
               else swordsmen_menu = 0;
               fight_menu = i;
               cout <<"["<< i <<"] Go Fight\n";
            
               cin >> menu_choice;
               if (menu_choice == archers_menu) 
               {
                    do {
                         cout << "How many archers"
                              " would you like to send?\n";
                         cin >> archers_sent;
                    }while (!(archers_sent > -1 
                         && archers_sent <= User.checkSoldiers(1)));
               }
               else if  (menu_choice == catapults_menu)
               {     
                    do {
                         cout << "How many catapults"
                              " would you like to send?\n";
                         cin >> catapults_sent;
                    }while (!(catapults_sent > -1 && 
                         catapults_sent <= User.checkSoldiers(2)));
               }      
               else if (menu_choice == swordsmen_menu)
               {
                    do {
                         cout << "How many swordsmen"
                              " would you like to send?\n";
                         cin >> swordsmen_sent;
                    }
                    while (!(swordsmen_sent > -1 &&
                         swordsmen_sent <= User.checkSoldiers(3)));
                }
          }
          //end pre-battle loop
          while (menu_choice != fight_menu); 
        
          cout << "\nEntering Battle...\n";
        
          User.fight(Germanians,catapults_sent,swordsmen_sent,archers_sent);
          //if player’s army is dead than they have lost
          if ((User.checkSoldiers(1) + User.checkSoldiers(2) + User.checkSoldiers(3)) == 0)
               end = lost = true;
          //if germanium army is dead, player has won
          else if ((Germanians.checkSoldiers(1) + Germanians.checkSoldiers(2)
               + Germanians.checkSoldiers(3)) == 0)
          {
               end = true;
               lost = false;
          }
     } //end of main game loop
    
     //display appropriate ending message
     if (lost)
     {
          cout << "\nYou lost. Try again next time.\n";
          return 0;
     }
     cout << "\nCongratulations, you won!\n";
     return 0;
}
