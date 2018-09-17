// Definite Finite Automata Code : Theory of Computation
// Aman Kumar
// BT16CSE020

#include<stdio.h>


/*
	FINITE AUTOMATA 5-TUPLE REPRESENTATION
	
	 Q 	: Set of states 
	 E 	: Set of inputs possible
	 q0	: Initial state
	 D 	: Transition function : List of transitions possible
	 F 	: Set of final/ acceptable states	  
	
	
*/

// Structure for defining transitions
typedef struct Transitions
{
	char c ;	// The input symbol triggering transition
} Trans ;
Trans T[ 50 ][ 50 ] ;	// Set of transitions

int initial_note() ;			// Display initial note	
int print_menu() ;				// Print Main menu
int define_automata() ;			// Define automata
int define_transitions() ;		// Define state transitions
int run_lang() ;				// Input string and check the validity
int check_ip_str() ;			// Check the input string for allowed symbols
int find_last_state() ;			// Simulates the input string and finds the last state achieved by it
int is_last_state_final( int ) ;		// Checks if the passed state is one of the accepted state


int automata_defined = 0 ;		// Is automata defined, 0 : no, 1 : yes

// Automata parts
int num_states = 0 ;					// Number of states and also denotes list of states
int initial_state = 0 ;					// Initial state 

int num_ipsym = 0 ;				// Number of input symbols
char ipsym[100][1] ;			// List of input symbols

// Number of transitions will be 

int num_fist = 0 ;				// Number of final states
int final_states[100] ;			// Set of final states

int optrack = 0 ;				// Ouput tracker

char input_str[200] ;			// Input string

int main()
{
	int run_flag = 1 ;			// For controlling loop
	int menu_choice = 0 ;
	
	initial_note() ;
	
	printf( "\n\n " ) ;
	
	// Main loop
	for( ; run_flag == 1 ; )
	{
		if( automata_defined == 0 )
			printf( "\n > No Automata defined!" ) ;
		
		print_menu() ;
		
		printf( "\n\n\t > " ) ;
		scanf( "%d", &menu_choice ) ;
		
		// Define automata
		if( menu_choice == 1 )
		{
			automata_defined = define_automata() ;
			
			if( automata_defined == 1 )
				printf( "\n\n > Automata defined! " ) ;
		}
		// Input String 
		else if( menu_choice == 2 )
		{
			if( automata_defined == 1 )
			{
				run_lang() ;
			}
			else
			{
				printf( "\n\n > First define Automata!" ) ;
			}
		}
		// Reset automata	
		else if( menu_choice == 3 )
		{
			if( automata_defined == 1 )
			{
				automata_defined = 0 ;
				printf( "\n > Current automata definitions deleted!" ) ;			
			}
			else
			{
				printf( "\n > No definitions to delete!" ) ;
			}
		}
		// Toggle optrack
		else if( menu_choice == 4 )
		{
			if( optrack == 1 )
				optrack = 0 ;
			else
				optrack = 1 ;
		}
		
		// Exit
		else if( menu_choice == 5 )
		{
			printf( "\n\n > Program terminated!" ) ;
			printf( "\n" ) ;
			run_flag = 0 ;
		}
		else 
			;
					
	}	
	
	return 0 ;
}

int initial_note()
{
	printf( "\n\n" ) ;
	printf( "=============================== \n" ) ;
	printf( "    DEFINITE FINTE AUTOMATA	 \n" ) ;
	printf( "===============================" ) ;
	
	printf( "\n\n AUTHOR: Aman Kumar: BT16CSE020" ) ;

	return 0 ;
}

int print_menu()
{
	printf( "\n\n\n\n MENU: =====================" ) ;
	printf( "\n\n\t 1. Define automata" ) ;
	printf( "\n\t 2. Input string " ) ;
	printf( "\n\t 3. Reset automata definition " ) ;
	printf( "\n\t 4. Toggle Output transactions " ) ;
	printf( "\n\t 5. Exit" ) ;	
	
	return 0 ;
}

int define_automata()
{
	
	int i = 0, ret = 1 ;
	
	// Define total states
	printf( "\n\n Enter total number states |Q|: " ) ;
	scanf( "%d", &num_states ) ;
	
	// Define initial state
	printf( " Enter Initial state no: " ) ;
	scanf( "%d", &initial_state ) ;
	
	// Define number of input symbols
	printf( "\n\n Enter number of input symbols E: " ) ;
	scanf( "%d", &num_ipsym ) ;
	
	for( i = 0 ; i < num_ipsym ; i++ )
	{
		printf( " Enter input symbol%d: ", i + 1 ) ;
		scanf( " %c", &ipsym[ i ][ 0 ] ) ;
	}
	
	// Define final states
	printf( "\n Enter number of final states |F|: " ) ;
	num_fist = num_states + 1 ;
	
	while( num_fist > num_states )
	{
		scanf( "%d", &num_fist ) ;
		
		if( num_fist > num_states )
		{
			printf( "\n > ERROR: Input number final states greater than total states!") ;
			printf( "\n\n Enter number of final states |F|: " ) ;
		}
	}
	
	for( i = 0 ; i < num_fist ; i++ )
	{
		printf( " Enter final state%d: ", i + 1 ) ;
		scanf( "%d", &final_states[ i ] ) ;	
		
		// Safety condition : will decrement i so that correct value can be entered again
		if( final_states[ i ] > ( num_states - 1 ) )
		{
			printf( "\n > Error: Invalid final state!" ) ;
			i = i - 1 ;
		}
	}
	
	if( ret == 1 )
		define_transitions() ;
	
	return ret ;
}

int define_transitions()
{
	fflush( stdin ) ;
	int i = 0, j = 0 ;
	
	printf( "\n Enter input symbol for following transitions: \n" ) ;
	
	for( i = 0 ; i < num_states ; i++ )
	{
		printf( "\n" ) ;
		for( j = 0 ; j < num_states ; j++ )
		{
			printf( " Symbol to go from q%d to q%d (# for none): ", i, j ) ;
			scanf( " %c", &T[i][j].c ) ;
		}
	}
	
	return 1 ;
}

int run_lang() 
{
	int ret = 1, last_state ;
	
	printf( "\n\n Enter input string(without spaces): " ) ;
	scanf( " %s", input_str ) ;
	
	if( check_ip_str() == 1 )
	{
		last_state = find_last_state() ;	
		
		ret = is_last_state_final( last_state ) ;
		
		if( ret == 1 )
			printf( "\n\n > SUCCESS : Input string is ACCEPTED by automata!" ) ;
		else
			printf( "\n\n FAILURE : Input string is NOT ACCEPTED by automata!" ) ;		
	}
	else
	{
		printf( "\n > ERROR: Input string contains un-defined input symbols! " ) ;
		ret = -1 ;
	}
	
	return ret ;
}

int check_ip_str()
{
	int i = 0, j = 0, flag1 = 1, flag2 = 1 ;
		
	for( i = 0 ; input_str[ i ] != '\0' && flag1 == 1 ; i++ )
	{
		flag2 = 1 ;
		for( j = 0 ; j < num_ipsym && flag2 == 1 ; j++ )
		{
			if( optrack == 1 )
				printf( "\n input_str[%d]: %c  ipsym[%d][0]: %c", i, input_str[i], j, ipsym[j][0] ) ;
			
			if( input_str[ i ] == ipsym[ j ][ 0 ] ) 
			{
				flag1 = 1 ;
				flag2 = 0 ;
			}
			else
				flag1 = 0 ;
			
			if( optrack == 1 )	
				printf( " new flag1: %d", flag1 ) ;	
		}
	}
		
	return flag1 ;	// 1 : If string is OK ; 0 : Un-defined input symbol found	
}

int find_last_state()
{
	int i, j, flag = 0 ;
	int last_state = 0 ;	// Initially state is 0
	
	printf( "\n" ) ;
	
	for( i = 0 ; input_str[ i ] != '\0' ; i++ )
	{
		flag = 0 ;
		
		// Finding next state
		for( j = 0 ; j < num_states && flag == 0 ; j++ )
		{
			if( optrack == 1 )
				printf( "\n > Last_state: %d  T[%d][%d]: %c  Input sym: %c", last_state, last_state, j, T[ last_state][j].c, input_str[i] ) ;
			
			if( T[ last_state ][ j ].c == input_str[ i ] )
			{
				flag = 1 ;
				last_state = j ;
			}
		}
	}
	return last_state ;
}

int is_last_state_final( int last_state )
{
	int i = 0, flag = 0 ;
	
	for( i = 0 ; i < num_fist && flag == 0 ; i++ )
	{
		if( final_states[ i ] == last_state )
			flag = 1 ;
	}
	return flag ;
}
