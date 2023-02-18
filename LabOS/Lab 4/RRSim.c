/*
 * 	Lab 4, Threaded Round Robin Simulator
 * 	Fernando Garrote A01027503
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//Structure that defines a process, indicating the process ID and how much time remaining it will run, provided it wont block
typedef struct process{
	int id;
	int runTime;
} process_t;

//Structure that will act as each node of the linked list
typedef struct node{
	process_t proc;
	struct node *next;
}node_t;


//Since we cannot know in advance how many processes we will have, we need a way to have a dynamic queue
//So, here is the code of a linked list that will act as a queue.
//This will be the first node of the linkedlist
node_t * head=NULL;
//This variable counts how many process we have in the process queue.
int processCount;


//Function to add a new process to the queue
void enqueue(int id, int val){
	node_t *current=head;

	if(processCount==0){//check if we have 0 process waiting
		head->proc.id=id;//just give the value to the first element in the queue
		head->proc.runTime=val;
	}else{//We have to add a new node
		//iterate until we find the end of the queue
		while(current->next!=NULL){
			current=current->next;
		}
		//Add to the end of the queue a new process
		current->next=malloc(sizeof(node_t));
		current->next->proc.runTime=val;
		current->next->proc.id=id;
		current->next->next=NULL;
	}
	processCount++;
}


//function that removes the first element of the queue
process_t dequeue(){
	process_t returningValue;
	if(processCount==1){
		returningValue=head->proc;
	}else{

		node_t *nextProc=head->next;
		returningValue=head->proc;
		free(head);
		head=nextProc;
	}
	processCount--;
	return returningValue;
}

int main()
{
	// seed for random generator
	srand(time(0));

	head = malloc(sizeof(node_t));
	head->next = NULL;
	processCount = 0;
	//Add here your code for simulating a round robin scheduler and processor.
	int timeSlice = 6;
	int lower = 5, upper = 30;
	printf("Time slice is %d\n", timeSlice);

	node_t *current = head;
	printf("Process %d has a runtime of %d \n", current->proc.id, current->proc.runTime);
	for (int i = 0; i < 5; i++)
	{

		int num = (rand() % (upper - lower + 1)) + lower;
		enqueue(i + 1, num);

		//printf("Adding process %d with running time of %d\n", i+1, num);
		//printf("Process %d has a runtime of %d \n",current->next->proc.id, current->next ->proc.runTime);
	}

	for (int i = 0; i < 5; i++)
	{
		printf("Process %d has a runtime of %d \n", current->proc.id, current->proc.runTime);
		current = current->next;
	}

	current = head;
	lower = 0;
	upper = 9;
	while (current->next != NULL)
	{
		current = head;
		printf("Running %d remaining time %d \n", current->proc.id, current->proc.runTime);

		for (int i = 0; i < timeSlice; i++)
		{
			current->proc.runTime = current->proc.runTime - 1;
			int num = (rand() % (upper - lower + 1)) + lower;
			//printf("Random chance was %d \n",num);
			//Si el numero aleatorio es 0:
			if (num == 1)
			{
				printf("Process %d blocked for IO and was preempted with remaining time %d \n", current->proc.id, current->proc.runTime);
				enqueue(current->proc.id, current->proc.runTime);
				current = current->next;
				dequeue();
			} //if
			//Si el runtime de un proceso es 0:
			else if (current->proc.runTime <= 0)
			{
				printf("Process %d has finished running.\n", current->proc.id);
				current = current->next;
				dequeue();
			} //else if
			//Si el quantum se acabo
			else if (i == timeSlice - 1)
			{
				printf("Process %d has finished its timeslice and was preempted with remaining time %d \n", current->proc.id, current->proc.runTime);
				enqueue(current->proc.id, current->proc.runTime);
				dequeue();
			} //else if

		} //for
	}	 //while
}
