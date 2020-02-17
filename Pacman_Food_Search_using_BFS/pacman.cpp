/*
	ASSIGNMENT 1 
	
	GROUP 1
	- Aman Kumar
	- Parth Wazurkar
	- Saurav Dubey
	- Braj Kishor
	
	Help Pacman reach the food.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <conio.h>
#include <queue>
#include <set>

using namespace std ;

// Color use definitions

struct Color
{
    int color;

    Color(int color_): color(color_) {}

    Color operator + (const Color & other) const { return Color(this->color | other.color); }
};

#define FORE_LIGHT(color) const Color cfl##color##_ = FOREGROUND_##color | FOREGROUND_INTENSITY;
#define BACK_LIGHT(color) const Color cbl##color##_ = BACKGROUND_##color | BACKGROUND_INTENSITY;
#define FORE_DARK(color)  const Color cfd##color##_ = FOREGROUND_##color;
#define BACK_DARK(color)  const Color cbd##color##_ = BACKGROUND_##color;

FORE_LIGHT(RED) FORE_LIGHT(GREEN) FORE_LIGHT(BLUE)
BACK_LIGHT(RED) BACK_LIGHT(GREEN) BACK_LIGHT(BLUE)
FORE_DARK (RED) FORE_DARK (GREEN) FORE_DARK (BLUE)
BACK_DARK (RED) BACK_DARK (GREEN) BACK_DARK (BLUE)

const Color cdefault_ = cfdRED_ + cfdGREEN_ + cfdBLUE_;

std::ostream & operator << (std::ostream & os, Color c)
{
    return SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c.color), os;
}

class Pair
{
	public:
		int x ;
		int y ;
		
		// Ctor
		Pair()
		{
			x = 0 ;
			y = 0 ;
		}
		
		Pair( int a, int b )
		{
			x = a ;
			y = b ;
		}
		
		Pair( const Pair &pair )
		{
			x = pair.x ;
			y = pair.y ;
		}
		
		void showPair()
		{
			cout << "(" << x << "," << y << ")" ;
		}
		
		// Operator !=
		bool operator!= ( Pair test )
		{
			if( test.x != x )
				return true ;
			
			else
			{
				if( test.y != y )
					return true ;
				else
					return false ;
			}	
			
		}
		
		// Operator ==
		bool operator== ( Pair test )
		{
			if( test.x == x && test.y == y )
				return true ;
			else
				return false ;
		}
		
} ;

class State_Space
{
	public:
		Pair initial ;
		vector<Pair> movements ;
		
		// Ctor
		State_Space()
		{
			initial = Pair() ;
		}
		
		// Display state 
		void showState()
		{
			initial.showPair() ;
			cout << " -> {" ;
			
			int size = movements.size() ;
			
			for( int i = 0 ; i < size ; i++ )
			{
				if( i != 0 )
					cout << ", " ;
				else
					cout << " " ;
					
				movements[ i ].showPair() ;
			}
			
			cout << " }" ;
 		}
} ;

// GOTOXY function
void gotoxy(short x, short y)			 					
{
   COORD pos = {x, y} ;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos) ;
}


// Get initial state space for pacman map
vector<State_Space> get_state_space() ;

// Show the state space
int show_state_space( vector<State_Space> ) ;

// Used to sort the Pairs
bool sort_pair( Pair, Pair ) ;

// Print map. Map starts from passed coordinates
void print_map( Pair ) ;

// Print man. Pass initial coordinate and final coordinate
void print_man( Pair, Pair ) ;	

// Print Food
void print_food( Pair ) ;

// Find food using BFS
void find_food_bfs( vector<State_Space>, Pair, Pair, Pair ) ;

// Get index of the passed state from list of states
int get_curr_state_index( vector<State_Space> &, Pair ) ;

// Print Current State
void print_curr_state( Pair ) ;

// Print final state
void print_final_state( Pair ) ;

// Print Steps of running
void print_step_count( int ) ;

// Generate coordinate from state
Pair get_coord_from_state( Pair, Pair, Pair ) ;

// ============================ main() ========================================
int main()
{

	Pair MAP( 4, 4 ) ;
	Pair MAN( 6, 11 ) ;
	Pair FOOD( 10, 7 ) ;

	Pair initial_state, final_state ;


	// Stores main state space of the problem
	vector<State_Space> problem ;
	
	// Get problem state space
	problem = get_state_space() ;
	
	// Get initial state
	cout << "\n Enter initial state (x,y): " ;
	cin >> initial_state.x >> initial_state.y ;
	
	// Get final state
	cout << "\n Enter final state (x,y) : " ;
	cin >> final_state.x >> final_state.y ;
	
	// Display state space
	show_state_space( problem ) ;	
	getch() ;
	system( "CLS" ) ;

	// ======== Running ===============
	// Print Map
	print_map( MAP ) ;
	print_food( FOOD ) ;
	print_man( MAN, MAN ) ;
		
	// Run the food search
	find_food_bfs( problem, initial_state, final_state, MAN ) ;
	
}

// ========================= FUNCTION DEFINITIONS ============================

// Get initial state space for pacman map
vector<State_Space> get_state_space()
{
	cout << "\n State Space Input" ;
	
	int rows = 0, cols = 0 ;
	
	vector <State_Space> state_space ;
	
	// Get number of rows and columns
	cout << "\n\n Enter number of rows and cols: " ;
	cin >> rows >> cols ;
	
	// Input the state space
	for( int i = 1 ; i <= rows ; i++ )
	{		
		for( int j = 1 ; j <= cols ; j++ )
		{
			int n ;
			vector<Pair> movements ;
			
			cout << "\n Enter number of possible states for (" << i << "," << j << ") : " ;
			cin >> n ;
			
			for( int k = 1 ; k <= n ; k++ )
			{
				Pair new_state ;
				
				cout << "\n State-" << k << " : " ;
				cin >> new_state.x >> new_state.y ;
				
				// Push new pair
				movements.push_back( new_state ) ;				
			}
			
			// Sort movements
			sort( movements.begin(), movements.end(), sort_pair ) ;
			
			// Push: (initial) : (possible states)
			Pair initial_state ;
			initial_state.x = i ;
			initial_state.y = j ;
			
			State_Space new_state ;
			new_state.initial = initial_state ;
			new_state.movements = movements ;
			
			state_space.push_back( new_state ) ;
		}
	}
		
	return state_space ;
}


// Show the state space
int show_state_space( vector<State_Space> state_space ) 
{
	cout << "\n DISPLAY STATE SPACE \n" ;
	
	int size = state_space.size() ;
	
	for( int i = 0 ;  i < size ; i++ )
	{
		cout << "\n " ;
		
		state_space[ i ].showState() ;
	}
	
	return 0 ;
}

// Used to sort Pairs
bool sort_pair( Pair p1, Pair p2 )
{
	if( p1.x != p2.x )
		return ( p1.x < p2.x ) ;
	else
		return ( p1.y < p2.y ) ;
}

// Print map. Map starts from passed coordinates
void print_map( Pair MAP )
{
	int x = MAP.x ;
	int y = MAP.y ;
	
	char block = 'X' ;
	
	gotoxy( x, y++ ) ;
	
	/*
	
	^^^^^^^^^^^^^
	^           ^ 
	^	^^^^^   ^
	^	^   ^   ^
	^	^   ^   ^	
	^		^   ^
	^	^^^^^   ^
	^			^
	^^^^^^^^^^^^^
	
	*/
	
	cout << cflRED_ ;
	
	int count = 13 ;
	while( count-- )
	{
		cout << block ;
	}
	
	gotoxy( x, y++ ) ;
	cout << block << "           " << block ;
	gotoxy( x, y++ ) ;
	cout << block << "   " ;
	
	count = 5 ;
	while( count-- )
	{
		cout << block ;
	}
	
	cout << "   " << block ;
	gotoxy( x, y++ ) ;
	cout << block << "   " << block << "   " << block << "   " << block ;
	gotoxy( x, y++ ) ;
	cout << block << "   " << block << "   " << block << "   " << block ;
	gotoxy( x, y++ ) ;
	cout << block << "       " << block << "   " << block ;
	gotoxy( x, y++ ) ;
	cout << block << "   " ;
	
	count = 5 ;
	while( count-- )
	{
		cout << block ;
	}
	
	cout << "   " << block ;
	gotoxy( x, y++ ) ;
	cout << block << "           " << block ;
	gotoxy( x, y++ ) ;
	
	count = 13 ;
	while( count-- )
	{
		cout << block ;
	}
	
	cout << cdefault_ ;
}	

// Print man. Pass initial coordinate and final coordinate
void print_man( Pair initial, Pair final )
{
	int x = initial.x ;
	int y = initial.y ;
	
	char PLAYER = 'P' ;
	
	gotoxy( x, y ) ;
	cout << ' ' ;
	
	x = final.x ;
	y = final.y ;
	
	gotoxy( x, y ) ;
	cout << cflRED_ + cflGREEN_ << PLAYER ;
	cout << cdefault_ ;
	
} 

// Print Food
void print_food( Pair FOOD_C )
{
	char FOOD = '$' ;
	
	gotoxy( FOOD_C.x, FOOD_C.y ) ;
	cout << cflGREEN_ << FOOD ;
	cout << cdefault_ ;
}

// Find food using BFS
void find_food_bfs( vector<State_Space> space, Pair curr, Pair final, Pair MAN )
{
	// Implementing Breadth First Search to search for food
	
	queue<Pair> possible ;
	
	possible.push( curr ) ;
	
	bool found_food = false ;
	int steps = 0 ;
	
	set<int> visited ;
	
	// Print final state
	print_final_state( final ) ;
	
	while( possible.front() != final && !possible.empty() )
	{
		steps++ ;
		Sleep( 600 ) ;
		
		// Update step count on Map
		print_step_count( steps ) ;
		
		// Find the index of state which is front of queue
		int curr_state_index = get_curr_state_index( space, possible.front() ) ;
		
		// Check if already visited
		auto iter = visited.find( curr_state_index ) ;
		
		if( iter == visited.end() )
		{
			visited.insert( curr_state_index ) ;
			
			// Push all possible movements in queue
			for( int i = 0 ; i < space[ curr_state_index ].movements.size() ; i++ )
			{
				possible.push( space[ curr_state_index ].movements[ i ] ) ;
			}
		}
		
		Pair prev = possible.front() ;
		
		// Pop the first element from queue
		possible.pop() ;
		
		Pair newMAN = get_coord_from_state( prev, possible.front(), MAN ) ;
		print_man( MAN, newMAN ) ;
		MAN = newMAN ;
		
		// Update curr state on Map
		print_curr_state( possible.front() ) ;
		
		if( possible.front() == final )
			found_food = true; 
	}
	
	if( found_food == true )
		cout << "\n Food found ! " ;
	else
		cout << "\n Food NOT found ! " ;
	
	cout << "\a" ;	
	
}

// Get index of the passed state from list of states
int get_curr_state_index( vector<State_Space> &state_space, Pair target ) 
{
	int size = state_space.size() ;
	
	int index = -1 ;
	
	for( int i = 0 ; i < size && index == -1 ; i++ )
	{
		if( state_space[ i ].initial == target )
			index = i ;
	}
	
	return index ;
}


// Print Current State
void print_curr_state( Pair p )
{
	int x = 4, y = 20 ;
	
	gotoxy( x, y ) ;
	cout << "CURR: " ;
	p.showPair() ;	
	cout << "  " ;
} 

// Print final state
void print_final_state( Pair p ) 
{
	int x = 20, y = 20 ;
	
	gotoxy( x, y ) ;
	cout << "FINAL: " ;
	p.showPair() ;
	cout << "  " ;
}

// Print Steps of running
void print_step_count( int steps ) 
{
	int x = 40 , y = 20 ;
	
	gotoxy( x, y ) ;
	cout << "STEPS: " << steps << "  " ;
}

// Generate coordinate from state
Pair get_coord_from_state( Pair prev, Pair curr, Pair coord ) 
{
	int x = ( curr.x - prev.x ) ;
	x = coord.x + x * 4 ;
	
	int y = ( curr.y - prev.y ) ;
	y = y * -1 ;
	
	y = coord.y + y * 2 ;
	
	Pair mapxy( x, y ) ;
	
	return mapxy ;
	
} 
