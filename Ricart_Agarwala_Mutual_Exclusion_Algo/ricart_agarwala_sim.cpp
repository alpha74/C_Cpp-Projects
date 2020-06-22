/*
	  Simluation of Ricart Agarwala Algo using loops.
		RICART-AGARWALA DISTRIBUTED MUTUAL EXCLUSION ALGORITHM
		
	  - alpha74
    
*/

#include <iostream>
#include <conio.h>
#include <vector>
#include <algorithm>

using namespace std ;

// Number of time units taken for a process to execute
#define CS_EXEC_TIME 2

/*
	-----------------------------------------
		GLOBAL DATA STRUCTURES
	-----------------------------------------	
*/

/*
	Its object serves as a global time.
*/
class TIMESTAMP
{
	unsigned int value ;
	
	public:
			// Default ctor
			TIMESTAMP()
			{
				value = 0 ;
			}
			
			// Increment clock
			void increment()
			{
				value++ ;
			}
			
			// Get time value
			int get()
			{
				return value ;
			}
	
} ;

/*
	-------------------------------------
		GLOBAL VARIABLES
	-------------------------------------
*/

// Global time
TIMESTAMP GLOBAL_TIME ;


class MESSAGE
{
	public:
			/*
				Message Type
					0 : HEARTBEAT
					1 : REQUEST
					2 : REPLY
			*/
			int msgtype ; 			
			int sendproc ;		// Sender proc ID
			int recvproc ;		// Receiver proc ID
			int timestamp ;		// TimeStamp
	
			MESSAGE()
			{
				msgtype = 0 ;
				sendproc = -1 ;
				recvproc = -1 ;
				timestamp = 0 ;
			}
	
			// Default ctor
			MESSAGE( int m, int s, int r, int t )
			{
				msgtype = m ;
				sendproc = s ;
				recvproc = r ;
				timestamp = t ;
			}
			
			// Returns message string from message type
			string typeToString()
			{
				switch( msgtype )
				{
					case 0 : return "HRTBEAT" ;
					case 1 : return "REQUEST" ;
					case 2 : return "REPLY__" ;
					default: return "_NULL_0" ;
 				}
			}
	
} ;


/*
	Sort messages based on timestamp values
*/
bool SORT_MSG_PRIORITY( MESSAGE m1, MESSAGE m2 )
{
	if( m1.timestamp < m2.timestamp )
		return true ;

	else if( m1.timestamp == m2.timestamp )
	{
		if( m1.sendproc < m2.sendproc )
			return true ;
		else
			return false ;
	}		
	
	else
		return false ;	
}

/*
	Serves as a process
*/
class PROCESS
{
	public:
			int pid ;								// Process ID
			
			/*
				State
					0 : Idle
					1 : Requested CS
					2 : Executing CS
			*/
			int state ;		
			int reqtime ;					// Time stamp at which request was made
			vector<MESSAGE> rqueue ;		// Request buffer queue
			int exec_rem ;					// Number of CS execution units remaining
			int total_proc ;				// Stores total number of process
					
			vector<MESSAGE> lastmsg ;				// Last Received message
			bool msg ;						// True when a message is received
			
			int replied_count ;				// Number of processes replied when REQUEST was sent
			
			// Default ctor
			PROCESS( int p, int t )
			{
				pid = p ;
				reqtime = 0 ;
				state = 0 ;
				exec_rem = 0 ;
				msg = false ;
				total_proc = t ;
			}
	
			// Check if process is still executing
			bool isExecuting()
			{
				if( exec_rem > 0 )
					return true ;
				else
					return false ;
			}
	
			string stateString()
			{
				switch( state )
				{
					case 0 : return "IDLE" ;
					case 1 : return "REQT" ;
					case 2 : return "EXEC" ;
					default : return "NULL" ;
				}
			}
	
			// Execute a CS step
			void executeCS()
			{
				if( exec_rem > 0 )
				{
					exec_rem-- ;
					cout << "\n > EXECUTING_CS : P" << pid ;
				}
						
			}
			
			// Request CS
			void requestCS()
			{
				state = 1 ;
				reqtime = GLOBAL_TIME.get() ;
			}
			
			// Receive Message 
			void recvMessage( MESSAGE newmsg )
			{
				msg = true ;
				lastmsg.push_back( newmsg ) ;
 			}
			
			// Print state
			void printState()
			{
				cout << "[PID: " << pid << "] " ;
				cout << "[STATE: " << stateString() << "] " ;
				
				cout << "[RECV MSG:" ;
				
				if( !msg )
					cout << " _NULL_0" ;
				else
				{
					for( int i = 0 ; i < lastmsg.size() ; i++ )
						cout << " " << lastmsg[i].typeToString() << ":" << lastmsg[i].sendproc ;
				}
				cout << " ] " ;
				
				
				cout << "[REQ_BUFFER: " ;
				
				if( rqueue.size() == 0 )
					cout << "_NULL__0" ;
				else
				{
					for( int i = 0 ; i < rqueue.size() ; i++ )
					{
						cout << rqueue[i].sendproc << " " ; 
					}
				}
				cout << " ] " ;
			}
			
			// Sets state of process as Exec CS
			void setStateExecCS()
			{
				state = 2 ;
				replied_count = 0 ;
				exec_rem = CS_EXEC_TIME ;
			}
			
			// Set state as IDLE
			void setStateIdle()
			{
				state = 0 ;
				replied_count = 0 ;
			}
			
			// Update state
			vector<MESSAGE> updateState()
			{
				vector<MESSAGE> retmsg ;
				int temp_exec_rem = exec_rem ;
				
				/*
					- updateState()
				
					# READING MESSAGES 
					
					- IF yes: 
						- Message : REQUEST
							- IF state is IDLE, REPLY to sender
							- IF state is REQT, 
								- IF lastmsg.TIMESTAMP is less, send REPLY
								- ELSE, DEFER : Add sender ID to rqueue.
							
						- Message : REPLY
							- Increment replied_count
					
					
					# CHANGING STATES
					
					- IF state is REQT
						- If replied_count == proc.size()-1, set STATE to EXEC	
						
					- IF state is EXEC
						executeCS()	
						
						
					# MESSAGE RESET
				*/
				
				// READ MESSAGE
				if( msg )
				{
					for( int i = 0 ; i < lastmsg.size() ; i++ )
					{
						if( lastmsg[i].msgtype == 1 )				// REQUEST received
						{
							if( state == 0 )			// If curr proc is idle
							{
								MESSAGE msgREPLY( 2, pid, lastmsg[i].sendproc, GLOBAL_TIME.get() ) ;
								retmsg.push_back( msgREPLY ) ;
							}
							else if( state == 1 ) 		// If curr proc has Requested CS
							{
								// IF lastmsg.timestamp is less, send REPLY
								if( lastmsg[i].timestamp < reqtime )
								{
									MESSAGE msgREPLY( 2, pid, lastmsg[i].sendproc, GLOBAL_TIME.get() ) ;
									retmsg.push_back( msgREPLY ) ;
								}
								else if( lastmsg[i].timestamp == reqtime && lastmsg[i].sendproc < pid )
								{
									MESSAGE msgREPLY( 2, pid, lastmsg[i].sendproc, GLOBAL_TIME.get() ) ;
									retmsg.push_back( msgREPLY ) ;
								}
								// Buffer the message
								else
								{
									rqueue.push_back( lastmsg[i] ) ;
									sort( rqueue.begin(), rqueue.end(), SORT_MSG_PRIORITY ) ;
								}
							}
							else if( state == 2 )		// If curr proc is executing CS
							{
								executeCS() ;			// Execute CS 
								
								// If execution is finished
								if( exec_rem == 0 )
								{
									setStateIdle() ;
									// Generate replies to be send
									// Generate REPLY messages for sites in rqueue
									for( int i = 0 ; i < rqueue.size() ; i++ )
									{
										MESSAGE newREPLY( 2, pid, rqueue[i].sendproc, GLOBAL_TIME.get() ) ;
										retmsg.push_back( newREPLY ) ;
									}
									rqueue.clear() ;
								}
								// Buffer the message
								else
								{
									rqueue.push_back( lastmsg[i] ) ;
									sort( rqueue.begin(), rqueue.end(), SORT_MSG_PRIORITY ) ;
								}
							}
						}
						else if( lastmsg[i].msgtype == 2 ) 		// REPLY received
						{
							replied_count++ ;
							
							if( replied_count == total_proc - 1 )
								setStateExecCS() ;
						}
					
						else ;
					}
				}
				
				// CHANGE STATE
				// If process did not receive a message, and is Executing CS
				if( state == 2 && temp_exec_rem == exec_rem )
				{
					executeCS() ;
					// If execution is finished
					if( exec_rem == 0 )
					{
						setStateIdle() ;
						// Generate replies to be send
						// Generate REPLY messages for sites in rqueue
						for( int i = 0 ; i < rqueue.size() ; i++ )
						{
							MESSAGE newREPLY( 2, pid, rqueue[i].sendproc, GLOBAL_TIME.get() ) ;
							retmsg.push_back( newREPLY ) ;
						}
						rqueue.clear() ;
					}
				}
				
				// RESET MESSAGE
				msg = false ;
				lastmsg.clear() ;
				
				
				return retmsg ;
			}
			
} ;
 
/*
	-------------------------------------
		USER DEFINED FUNCTIONS
	-------------------------------------
*/


/*
	Broadcast message to all process
		@senderID : Sender process ID
*/
void broadcastRequest( vector<PROCESS> &proc, int &senderID, MESSAGE &newmsg )
{
	// Set lastmsg of each process as 'newmsg'
	for( int i = 0 ; i < proc.size() ; i++ )
	{
		if( i != senderID )
		{
			newmsg.recvproc = i ;
			proc[i].recvMessage( newmsg ) ;
			
			cout << "\n > Send " << newmsg.typeToString() << " from P" << newmsg.sendproc << " to P" << newmsg.recvproc ;
		}
	}
	
	proc[ senderID ].requestCS() ;
}

/*
	Sends message between processes
		@listmsg : list of all messages
		@proc : list of all processes
		
*/
void sendAllMsgs( vector<MESSAGE> &listmsg, vector<PROCESS> &proc )
{
	int listsize = listmsg.size() ;
	
	for( int i = 0 ; i < listsize ; i++ )
	{
		int recvID = listmsg[i].recvproc ;
		
		// Send message to process
		proc[ recvID ].recvMessage( listmsg[i] ) ;
		
		cout << "\n > Will send " << listmsg[i].typeToString() << " from P" << listmsg[i].sendproc << " to P" << listmsg[i].recvproc ;
 	}
}

/*
	Prints detailed system state
		@proc : list of all processes
*/
void printSystemState( vector<PROCESS> &proc )
{
	cout << "\n\n ===================================================" ;
	cout << "\n" ;
	
	cout << "\n TIME: " << GLOBAL_TIME.get() ;
	
	// Print all process information
	for( int i = 0 ; i < proc.size() ; i++ )
	{
		cout << "\n  " ;
		proc[i].printState() ;	
	}
	
	cout << "\n\n ===================================================" ;
	cout << "\n" ;
}


/*
	Run process state update on each process.
		@proc : list of all processes
	
	Returns list of message to be sent.
*/
vector<MESSAGE> processStateUpdate( vector<PROCESS> &proc )
{
	vector<MESSAGE> genmsg ;
	for( int i = 0 ; i < proc.size() ; i++ )
	{
		vector<MESSAGE> newlist ;
		newlist = proc[i].updateState() ;
		
		if( newlist.size() > 0 )
			genmsg.insert( genmsg.end(), newlist.begin(), newlist.end() ) ; 
	}
	
	return genmsg ;
}

/*
	Main event loop
		@proc : list of all processes
*/
void runEventLoop( vector<PROCESS> &proc )
{
	int action_proc = -1 ;
	int proc_size = proc.size() ;
	
	do
	{
		printSystemState( proc ) ;
		GLOBAL_TIME.increment() ;
		
		cout << "\n > Select process for CS exec [0-" << proc_size -1 << "] : " ;
		cin >> action_proc ;
		
		// If pid is >= 0 
		if( action_proc >= 0 && action_proc <= proc.size() -1 )
		{			
			/*
				- Broadcast message to all processes leaving it.
					- Create a new message
					- Set the 'lastmsg' of each process as 'newmsg'
					
				- After broadcast is complete, run updateState() for each process.
			*/
			
			// Action performed is always REQUEST
			// Create a new message
			MESSAGE newmsg( 1, action_proc, -1, GLOBAL_TIME.get() ) ;
			
			// Broadcast this message
			broadcastRequest( proc, action_proc, newmsg ) ;
		}
		
		// Run state udpates for each process
		vector<MESSAGE> genmsg ;
		genmsg = processStateUpdate( proc ) ;
		
		// Send all the generated messages to processes.
		sendAllMsgs( genmsg, proc ) ;
		
	} while( action_proc >= -1 ) ;  // Input -ve ID as procID will end the event loop
	
}

/*
	Starts and initializes process. Returns proc list
		@num_proc : number of process to be started
*/
vector<PROCESS> startProc( int num_proc )
{
	vector<PROCESS> proc ;
	
	for( int i = 0 ; i < num_proc ; i++ )
	{
		PROCESS newProc( i, num_proc ) ;
		proc.push_back( newProc ) ;
	}
	
	return proc ;
}


/*
	Prints title message
*/
void titleMessage()
{
	cout << "\n\n\t\t RICART AGARWALA ALGO IMPLEMENTATION" ;
	cout << "\n\n - Aman Kumar" ;
	cout << "\n\n - BT16CSE020" ;
}






/*
 ======================== MAIN ===========================
*/



int main()
{	
	// Print title message
	titleMessage() ;
	getch() ;
	
	/*
		Get initialization data
	*/
	cout << "\n\n\n INITIALIZATION \n" ;
	int num_proc = 0;
	cout << "\n Enter number of processes: " ;
	cin >> num_proc ;
	
	/*
		Start processes
	*/
	vector<PROCESS> proc ;
	
	proc = startProc( num_proc ) ;
	cout << "\n > Processes initialized." ;
	getch() ;
	
	system( "CLS" ) ;
	
	runEventLoop( proc ) ;
	cout << "\n\n > Program Terminated." ;
	
	return 0 ;
}
