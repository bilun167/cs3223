a) 
	Huynh Ngoc Tai -- A0074310W
	Le Vu Nguyen Chuong -- A0088552W
b)
	To implement LRU policy, we introduce struct StackNode as elements of
	a LRU Stack. The Stack is technically a doubly linked list (array implementation)
	with head, tail being maintained as the most recently used and the least recently
	used buffer, respectively. 
	
	Modified Methods:
		StrategyGetBuffer: we keep most of the code except for the clock sweep 
			algorithm. Instead, we replace it with an O(N) traversal through the
			LRU Stack to pick the victim buffer, following the suggested algorithm
			in the guidebook.
		StrategyUpdateAccessedBuffer: we maintain and update our LRU Stack here.
			For every chosen buffer, we promote it to the head of the LRU Stack 
			(hence implies the meaning of the most recently used buffer). Therefore,
			LRU Stack's tail is always guaranteed to keep track of the least recently
			used buffer.
		DeleteLRU_Stack: standard linked list functionality. This is a help function
			for StrategyFreeBuffer.
		StrategyFreeBuffer: besides updating the freelist (original code), we need
			to call DeleteLRU_Stack in order to properly maintain our LRU Stack. The
			corresponding buffer is removed from the stack.
		StrategyShmemSize: we estimate our LRU Stack memory as following
			/* CS3223: size of the LRU stack */
			size = add_size(size, mul_size(NBuffers, sizeof(StackNode)));
		StrategyInitialize: initialize an "empty" stack. Empty here means we prepare
			memory slot for maximum NBuffers to be put in, but at the invoking moment,
			all slots are treated as not being used.
			/* CS3223: size of the LRU stack */
			LRUStack = (StackNode *) ShmemInitStruct("LRU stack", NBuffers * sizeof(StackNode), &stack_found);
c)
	LRU2 policy, to our understanding, is just a variation of LRU policy, to a certain 
	extent. We decided to keep most of the logic part as it is in LRU. Firstly, we traverse
	our LRU Stack (from tail to head) and see if there is at least one buffer that has been 
	accessed at most one time (i.e, to validate that S1 is non-empty). If there exists a 
	buffer that satisfies, choose it as the victim buffer. Otherwise, we traverse the Stack
	another time and 
	/*EDIT HERE giup anh*/
	choose the one with the minimal second accessed time.
	/********************/
	
	To facilitate the implementation, we introduce the following components into our StackNode 
	struct:
		int accessed_time; 			//keep track of whether it is the second or first time 
									//accessing this buffer
		struct timeval curNow;		//EDIT HERE giup anh
		struct timeval secLast;		//EDIT HERE giup anh
	
	We also introduce introduce this component into struct BufferStrategyControl:
		int fromStraGet ;			//EDIT HERE giup anh
		
	Most of our modification happened in 2 methods StrategyGetBuffer and StrategyUpdateAccessedBuffer.
	We basically take care of the accessed_time (system time) so that we can implement LRU2 (for S2) 
	effectively.
	//EDIT HERE giup anh