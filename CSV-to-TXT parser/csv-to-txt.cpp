#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<fstream>

using namespace std ;

#define INPUT_FILE "input.csv" 

int show_file_content() ;		// Prints input file contents on the console

int main()
{
	show_file_content() ;
	
	return 0 ;
}

int show_file_content()
{
	ifstream A ;
	ofstream B ;
	
	int rows = 1 ;
	char c ;
	
	A.open( INPUT_FILE, ios :: binary ) ;
	B.open( "output.txt", ios :: out | ios :: trunc ) ;
	
	if( !A )
		cout << "\n Error in opening file" ;
	else
	{ 		
		while( A )
		{		
			c = A.get() ;
			
			if( c != EOF )
			{
				
				// New line condition
				if( c == '\n' )
				{
					cout << "\n" ;
					B << '\n' ;
				}
				// Comman condition
				else if( c == ',' )
				{
					cout << " " ;
					B << ' ' ;
				}
				// Default condition
				else
				{
					cout << c ;
					B << c ;
				}
			}
		}
		
		A.close() ;
		B.close() ;
	}
}

