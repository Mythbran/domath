/*
* This program takes in an arbitrary amount of 
* command line arguments and find different 
* stats for those numbers
* Developed by Matthew D'Angelo & Gurbir Matharu
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

//DATA STRUCT
struct data{
	int argNum;
	int numArray[];
};
//PROTOTYPES
void* avg(void* d);
void* min(void* d);
void* max(void* d);
void* med(void* d);
void* std(void* d);

//GLOBAL VARIABLES
float avgNum = 0; 
int minNum = 0;
int maxNum = 0;
int medNum = 0; //MAYBE IMPLEMENTED 
int stdNum = 0; //MAYBE IMPLEMENTED 
typedef struct data Data;

int main(int argc, char *argv[]){

	//ERROR HANDLING FOR TOO FEW ARGUMENTS
	if(argc <= 1){
		printf("Use case is ./os3.1 arg1 arg2 arg3 ... \n");
		fprintf(stderr, "%s", "Error: Too Few Arguments\n");
		exit(1);
	}

	//LOCAL VARIABLES FOR MAIN
	//SETTING UP STRUCT
	Data *d; 
	d=(Data *)malloc(sizeof(Data) + 100* sizeof(argc-1));
	if(d==NULL){
		fprintf(stderr, "%s", "Error: Failed to allocate memory\n");
	}
	//COPY DATA INTO STRUCT
	d->argNum = argc-1;
	printf("You have entered: ");
	for(int i = 1; i<argc; i++){
		d->numArray[i-1] = strtol(argv[i], NULL, 10);
		printf("%d, ", d->numArray[i-1]);
		
	}
	puts("");	

	//CREATING ALL THE THREADS AND WAITING FOR THEM
	pthread_t calcAvg, calcMin, calcMax;
	if( (pthread_create(&calcAvg, NULL, avg, d)) != 0) 
		perror("Error creating Average Calculation thread");
	if( (pthread_create(&calcMin, NULL, min, d)) != 0) 
		perror("Error creating Minimum Calculation thread");
	if( (pthread_create(&calcMax, NULL, max, d)) != 0) 
		perror("Error creating Minimum Calculation thread");	
	if( (pthread_join(calcAvg, NULL))!= 0)
		perror("Error waiting for thread");
	if( (pthread_join(calcMin, NULL))!= 0)
		perror("Error waiting for thread");
	if( (pthread_join(calcMax, NULL))!= 0)
		perror("Error waiting for thread");

	//PRINT ALL NUMBERS FROM GLOBAL VARIABLES
	printf("The average value is %.2f.\n", avgNum);
	printf("The minimum value is %d.\n", minNum);
	printf("The maximum value is %d.\n", maxNum);
}

void* avg(void* d){
	//LOCAL VARIABLES
	Data *davg; 
	davg = (Data*)d; 

	//ERROR HANDLING If struct doesn't copy 
	if(davg == NULL){
		fprintf(stderr, "%s", "Fatal Error: Avg Thread struct does not exist\n");
		exit(2);
	}

	//TESTING STUFF
	//printf("ArgNum: %d\n", davg->argNum);
	/*for(int t = 0; t<davg->argNum; t++)
		printf("%d, ", davg->numArray[t]);
	puts("");
	*/

	//LOGIC
	for(int i = 0; i < davg->argNum; i++)
		avgNum += davg->numArray[i];
	
	avgNum /= davg->argNum;
}

void* min(void* d){
	//LOCAL VARIABLES 
	int i= 0;
	Data *dmin; 
	dmin = (Data*)d; 

	//ERROR HANDLING If struct doesn't copy 
	if(dmin == NULL){
		fprintf(stderr, "%s", "Fatal Error: Min Thread struct does not exist\n");
		exit(2);
	}

	//TESTING STUFF
	//printf("ArgNum: %d\n", dmin->argNum);
	/*for(int t = 0; t<dmin->argNum; t++)
		printf("%d, ", dmin->numArray[t]);
	puts("");*/
	

	//LOGIC
	minNum = dmin->numArray[0];
	while(i<dmin->argNum){
		if(minNum > dmin->numArray[i]){
			minNum = dmin->numArray[i];
		}
		i++;
	}
}


void* max(void* d){
	//LOCAL VARIABLES 
	int i= 0;
	Data *dmax; 
	dmax = (Data*)d; 

	//ERROR HANDLING: If struct doesn't copy
	if(dmax == NULL){
		fprintf(stderr, "%s", "Fatal Error: Max Thread struct does not exist\n");
		exit(2);
	}

	//TESTING STUFF
	//printf("ArgNum: %d\n", dmax->argNum);
	/*for(int t = 0; t<dmax->argNum; t++)
		printf("%d, ", dmax->numArray[t]);
	puts("");
	*/
	
	//LOGIC
	maxNum = dmax->numArray[0];
	while(i>dmax->argNum){
		if(maxNum > dmax->numArray[i]){
			maxNum = dmax->numArray[i];
		}
		i++;
	}
}

void* med(void* d){
	//LOCAL VARIABLES 
	int x= 0;
	Data *dmed; 
	dmed = (Data*)d; 

	//ERROR HANDLING: If struct doesn't copy
	if(dmed == NULL){
		fprintf(stderr, "%s", "Fatal Error: Med Thread struct does not exist\n");
		exit(2);
	}

	//TESTING STUFF
	//printf("ArgNum: %d\n", dmax->argNum);
	/*for(int t = 0; t<dmax->argNum; t++)
		printf("%d, ", dmax->numArray[t]);
	puts("");
	*/
	
	//LOGIC
	for(int i=0; i < dmed->argNum; i++){
		for(int j = i+1; j<dmed->argNum; j++){
			if(dmed->numArray[i] < dmed->numArray[j]){
				x = dmed->numArray[i];
				dmed->numArray[i] = dmed->numArray[j];
				dmed->numArray[j] = x;
			}
		}
	}
}