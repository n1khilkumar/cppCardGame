#include<bits/stdc++.h>
#include<conio.h>
#include<windows.h>
#include <time.h>
using namespace std;
vector<int> shuffled_deck;
unordered_set<int> player_c;
set<int> cpu_c;
set<int> tableau_pile;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
class cards
{
	private:
		int id;
		char rank;
		int suits;
		char colour;
		
	public:
		
		cards(int i,char r,int s,char c)
		{
			id = i;
			rank = r;
			suits = s;
			colour = c;
		}
		
		char returnRank()
		{
			return rank;
		}
		
		int returnId()
		{
			return id;
		}
		
		void print_c()								//Function that prints card
		{	
			cout<<endl;
			if(colour=='b') SetConsoleTextAttribute(hConsole,8);
			else SetConsoleTextAttribute(hConsole,12);
				
			cout<<" ________"<<endl;
			for(int i=0;i<5;i++)
			{	
				cout<<"|";
				if(i==1)
				{	
					if(rank == '0')
					{
						cout<<"10";
						cout<<"  "<<char(suits);
						cout<<"   |"<<endl;
						continue;
					}
					else
					{
						cout<<rank;
					}
					cout<<"   "<<char(suits);
					cout<<"   |"<<endl;
					continue;
				}
						
				if(i<4) cout<<"        |"<<endl;
				else cout<<"________|"<<endl;
			}
			SetConsoleTextAttribute(hConsole,15);
		}
}card[52] = {{1,'2',3,'r'},{2,'2',4,'r'},{3,'2',5,'b'},{4,'2',6,'b'},{5,'3',3,'r'},{6,'3',4,'r'},{7,'3',5,'b'},{8,'3',6,'b'},{9,'4',3,'r'},{10,'4',4,'r'},{11,'4',5,'b'},{12,'4',6,'b'},{13,'5',3,'r'},{14,'5',4,'r'},{15,'5',5,'b'},{16,'5',6,'b'},{17,'6',3,'r'},{18,'6',4,'r'},{19,'6',5,'b'},{20,'6',6,'b'},{21,'7',3,'r'},{22,'7',4,'r'},{23,'7',5,'b'},{24,'7',6,'b'},{25,'8',3,'r'},{26,'8',4,'r'},{27,'8',5,'b'},{28,'8',6,'b'},{29,'9',3,'r'},{30,'9',4,'r'},{31,'9',5,'b'},{32,'9',6,'b'},{33,'0',3,'r'},{34,'0',4,'r'},{35,'0',5,'b'},{36,'0',6,'b'},{37,'A',3,'r'},{38,'A',4,'r'},{39,'A',5,'b'},{40,'A',6,'b'},{41,'J',3,'r'},{42,'J',4,'r'},{43,'J',5,'b'},{44,'J',6,'b'},{45,'Q',3,'r'},{46,'Q',4,'r'},{47,'Q',5,'b'},{48,'Q',6,'b'},{49,'k',3,'r'},{50,'k',4,'r'},{51,'k',5,'b'},{52,'k',6,'b'}};

void shuffle_cards(int n)							//Function that shuffles card
{
	
	for(int i = 1;i<=52;i++) shuffled_deck.emplace_back(i);
	
	srand(time(0));
	unsigned seed = rand();
    	shuffle(shuffled_deck.begin(), shuffled_deck.end(), default_random_engine(seed));
	
	for(int i=0;i<n;i++) 
	{	
		player_c.emplace(shuffled_deck[i]);
	}
	for(int i = n;i<2*n;i++) 
	{
		cpu_c.emplace(shuffled_deck[i]);
	}
}

int findJustHigh(int x)								//Function that finds the higher card than the tableau card for computer
{
	int t = 0;
	for(auto it:cpu_c)
	{
		if(card[it-1].returnRank() == card[x-1].returnRank() || it>x) return it;
	}
	return t;
}

void printPlayerCards()								//Function that prints player card
{
	int i=1;
	cout<<"\n\nPlayer's' pile: "<<endl;
	for(auto it:player_c)
	{
		cout<<i<<".";i++;
		card[it-1].print_c();
		cout<<endl;
	}
}

void printCpuCards()								//Function that prints cpu card (Not used : Fair Play)
{
	cout<<"\nCPU cards are: "<<endl;
	for(auto it:cpu_c)
	{
		card[it-1].print_c();
	}
}

void check(int &p,int &q)							//checks if p or q reaches 0, p means total cards on player, q means total cards on cpu
{
	if(p==0)
	{
		cout<<"\n\nCONGRATULATIONS!! YOU WIN!! \n\nGG";
		exit(0);
	}
	else if(q==0)
	{
		cout<<"\n\nCOMPUTER WINS!! \n\nTOUGH LUCK!";
		exit(0);
	}
}

void computerTurn(int &p,int &q,int key);

void playerTurnInitial(int &p,int &q)						//Function that begins the game
{
	int p_i;
	char inp;
	check(p,q);
	int playerInput;
	printPlayerCards();
	cout<<"\nIts your turn play a card from your deck of cards (type 1 to draw first card, 2 to draw second and so on...): ";
	cin>>playerInput;
	int player_pile = player_c.size();
	if(!(playerInput>0&&player_pile>=playerInput))
	{
		cout<<"\nCard "<<playerInput<<" is not present in player's pile.."<<endl;
		char temp2;
		cout<<"\nPress any key to continue: ";
		temp2 = getch();
		playerTurnInitial(p,q);
	}
	cout<<"\nTableau Pile (Top Card): "<<endl;
	auto it1 = player_c.begin();
    	advance(it1, playerInput-1);
  	card[*it1-1].print_c();
    	p--;
    	int temp1 = *it1;
    	tableau_pile.emplace(*it1);
    	player_c.erase(*it1);
    	computerTurn(p,q,temp1);
}

void playerTurn(int &p,int &q,int key);

void computerTurn(int &p,int &q,int key)					//Function that initiate computer's turn
{
	check(p,q);
	string temp;
	cout<<"\nWaiting for computer's turn...\nPress any key to continue..";
	temp = getch();
	int justHigh = findJustHigh(key);
    	if(justHigh==0) 
    	{
    		cout<<"\nComputer's hand doesn't have a card having higher rank than your card..";
    		cout<<"\nComputer will now take cards in tableau pile... press any key to continue: ";
    		for(auto it:tableau_pile)
    		{
    			cpu_c.emplace(it);
    			q++;
		} 
		tableau_pile.clear();
		temp = getch();
    		playerTurnInitial(p,q);
	}
	else
	{
		cout<<"\nComputer found a card higher than your card as shown below ";
		cout<<"\nTableau Pile (Top Card): "<<endl;
		card[justHigh-1].print_c();
		tableau_pile.emplace(justHigh);
		int t = justHigh;
		cpu_c.erase(justHigh);
		q--;
		playerTurn(p,q,t);
	}
}

void playerTurn(int &p,int &q,int key)						//Function that initiate player's turn after computer made its move
{
	check(p,q);
	int playerInput;
	char temp;
	printPlayerCards();
	cout<<"\nIts your turn pick a card from your deck of card: ";
	cin>>playerInput;
	int player_pile = player_c.size();
	if(!(playerInput>0&&player_pile>=playerInput))
	{
		cout<<"\nCard "<<playerInput<<" is not present in player's pile.."<<endl;
		char temp2;
		cout<<"\nPress any key to continue.. ";
		temp2 = getch();
		playerTurn(p,q,key);
	}
	auto it = player_c.begin();
    	advance(it, playerInput-1);
    	if(card[*it-1].returnId()>card[key-1].returnId()||card[*it-1].returnRank()==card[key-1].returnRank())
    	{
    		cout<<"\nCard is higher or equal than the tableau card.."<<endl;
    		cout<<"\nTableau Pile (Top Card): "<<endl;
   	 	card[*it-1].print_c();
   	 	tableau_pile.emplace(*it);
   	 	int t = *it;
   	 	player_c.erase(*it);
		p--;
   	 	computerTurn(p,q,t);
	}
	else
	{
		cout<<"\nCard played is NOT higher card than tableau card... You'll now TAKE ALL CARDS in tableau pile"<<endl;
		cout<<"\nPress any key to continue: ";
		temp = getch();
		for(auto iter:tableau_pile)
    		{
    			player_c.emplace(iter);
    			p++;
		}
		tableau_pile.clear();
		playerTurnInitial(p,q);
	}
}

int main()
{
	int n;
	char temp;
	cout<<"\t\t\tMINOR PROJECT, C++ CARD GAME\n";
	cout<<"\nEnter how many cards each do you want to deal (min 1, max 26, ideal 5)"<<endl;
	cout<<"\n(Note: Game will take longer to beat for more cards...)"<<"\nEnter: ";
	cin>>n;
	while(true)
	{
		if(!(n>=1&&n<=26))
		{
			cout<<"\nYou cannot deal "<<n<<" numbers of cards..\nTry again: ";
			cin>>n;
		}
		else break;
	};
	cout<<"\n\n\t\t\t    RULES OF THE GAME";
	cout<<"\n(GOAL: To get rid of all of your cards..)";
	cout<<"\n1. "<<n<<" cards are dealed to the player and computer from a deck of well shuffled card.";
	cout<<"\n2. Player makes the move by playing a card in the middle (tableau pile)";
	cout<<"\n3. Opponent now plays the card by choosing a card with higher or equal rank \nthan that of card at the top of the tableau pile";
	cout<<"\n4. Ranking of cards: 2<3<4<5<6<7<8<9<10<A<J<Q<K";
	cout<<"\n5. If in case its player's or opponent's turn and their deck doesn't have a higher or equal rank card \nthan card at the top of the tableau pile then all the card present in the tableau pile \nwill have to be picked by the player/opponent";
	cout<<"\n6. Process is repeated until player/opponent plays all their cards.. first to loose all their cards win!!";
	cout<<"\n\nPress any key to continue: ";
	temp = getch();
	int p=n,q=n;
	shuffle_cards(n);
//	printCpuCards();
	playerTurnInitial(p,q);
	return 0;	
}
