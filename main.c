/**
 * Ananya Singh
 * CS 332 - Lay
 * Final Project
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sched_algos.h"

void fillProcessArr(struct process ** processArr, int arrSize) { //Helper function to fill our array with randomly generated processes.
  int currIdx = 0;
  while(currIdx < arrSize) {
    processArr[currIdx] = malloc(sizeof(struct process));
    processArr[currIdx]->id = currIdx + 1;
    processArr[currIdx]->duration = rand() % 5 + 1;
    processArr[currIdx]->priority = rand() % 10 + 1;
    currIdx++;
  }
}

void outputProcess(struct process *process) { //Helper function to output a single process.
    printf("Process ID: %i, Duration: %i, Priority: %i\n", process->id, process->duration, process->priority);
}

void outputProcessRR(struct process *process) { //Helper function to output a single process.
    printf("Process ID: %i\n", process->id);
}

void outputProcesses(struct process ** processes, int arrSize) {
  int idx = 0;
  while(idx < arrSize) {
    outputProcess(processes[idx]);
    idx++;
  }
}

void arrayDup(struct process ** original, struct process ** copied){
  	for(int i =0; i< 10;i ++){
		  copied[i] = malloc(sizeof(struct process));
		  copied[i]->duration = original[i]->duration;
		  copied[i]->id = original[i]->id;
		  copied[i]->priority = original[i]->priority;
    }
}


int dorpsort(struct process ** array, int first, int last, char PoD){
  if(PoD == 'D'){
      int p = array[last]->duration;
      int a = first-1;
      int b = first;

      while(b <= last-1){
        if(array[b]->priority < p){
			  a++;
        struct process temp = *array[b];
        *array[b] = *array[a];
        *array[a] = temp;
      }
      b++;
    }
    struct process temp = *array[b];
    *array[b] = *array[a+1];
    *array[a+1] = temp;

    return a+1;
  }else{
      int p = array[last]->priority;
      int a = first-1;
      int b = first;

      while(b <= last-1){
        if(array[b]->priority < p){
			    a++;
          struct process temp = *array[b];
          *array[b] = *array[a];
          *array[a] = temp;
        }
        b++;
      }
      struct process temp = *array[b];
      *array[b] = *array[a+1];
      *array[a+1] = temp;

      return a+1;


  }

}
void qSort(struct process ** array, int f, int l, char PoD){
  if(f<l)
  {
    if(PoD == 'P'){
      int index = dorpsort(array, f, l, 'P');
      qSort(array, f, index-1, 'P');
      qSort(array, index+1,l, 'P');
    }
    if(PoD == 'D'){
      int index = dorpsort(array, f, l, 'D');
      qSort(array, f, index-1, 'D');
      qSort(array, index+1,l, 'D');
    }
  }
}

void freeArray(struct process ** array,int arrSize){ //deallocate all objects on the original array, including the space allocated for the array itself. This goes for the priorities array as well.
  for(int i = 0; i < arrSize; i++){
    free(array[i]); //C
  }
}


int main(int argc, char ** argv) {
  srand(time(NULL)); //Seed our random with the current time.
  const int ARR_SIZE = 10; //The size of our array of randomly generated processes.
  const int TIME_SLICE = 2; //The time slice for any preemptive scheduling algorithms.
  struct process ** processes = malloc(sizeof(struct process *) * ARR_SIZE); //Our process array, used in each of our scheduling algorithms.
  int ** priorities = malloc(sizeof(int *) * ARR_SIZE); //Our priorities array, used for priority scheduling. Index i of the priorities array corresponds to the same index of the processes array.

  fillProcessArr(processes, ARR_SIZE);
  //fillPrioritiesArr(priorities, ARR_SIZE); HINT: you will need to fill up the priorities array similarly to how the processes one is filled.
  printf("Outputting initial process array:\n");
  outputProcesses(processes, ARR_SIZE);
  printf("\n\n");

  //Each of the below function calls should NOT change the original processes array. For sorting, you must create a copy of the original array within the function.

  sched_fcfs(processes, ARR_SIZE);
  sched_priority(processes, ARR_SIZE, priorities);
  sched_spn(processes, ARR_SIZE);
  sched_srt(processes, ARR_SIZE, TIME_SLICE);
  sched_round_robin(processes, ARR_SIZE, TIME_SLICE);

  //Final heap cleanup should go here - deallocate all objects on the original array, including the space allocated for the array itself. This goes for the priorities array as well.
  freeArray(processes,ARR_SIZE);
}


void sched_fcfs(struct process ** processes, int arrSize) {
  printf("FIRST COME FIRST SERVED:\n");
  outputProcesses(processes,arrSize);
  printf("\n\n");
}


void sched_priority(struct process ** processes, int arrSize, int ** priorities) {
  printf("PRIORITIES:\n");
  qSort(processes, 0, arrSize-1, 'P');
  int f = 0;
  int l = arrSize-1;
  outputProcesses(processes, arrSize);
  printf("\n\n");
}

void sched_spn(struct process ** processes, int arrSize) {
  printf("SHORTEST PROCESS NEXT:\n");
  struct process ** sortedArray = malloc(sizeof(struct process*) * arrSize);
  arrayDup(processes,sortedArray);
  qSort(sortedArray,0,arrSize-1, 'D');

  printf("First Two Processes:\n");
  outputProcess(sortedArray[0]);
  outputProcess(sortedArray[1]);

  printf("Two New Processes:\n");
  for(int i = 0; i<2; ++i){
    sortedArray[i]->id = 11+i;
    sortedArray[i]->duration = rand() % 5 + 1;
    sortedArray[i]->priority = rand() % 10 + 1;
  }
  outputProcess(sortedArray[0]);
  outputProcess(sortedArray[1]);
  printf("\n");


  printf("New Sorted Array: \n");
  qSort(sortedArray,0,arrSize-1, 'D');
  outputProcesses(sortedArray,arrSize);
  printf("\n\n");
  freeArray(sortedArray,arrSize);
}

void sched_srt(struct process ** processes, int arrSize, int timeSlice) {
  printf("SHORTEST TIME REMAINING:\n");
  printf("Time Slice: %i\n", timeSlice); //2
  struct process ** sortedArray = malloc(sizeof(struct process*) * arrSize);
  arrayDup(processes,sortedArray);
  qSort(sortedArray,0,arrSize-1, 'D');

  printf("Process after time slices: \n");
  for(int i=0; i<3; ++i){
    while(sortedArray[i]->duration>0){
      sortedArray[i]->duration = sortedArray[i]->duration-timeSlice;
      outputProcess(sortedArray[i]);
    }
  }

  printf("\nTwo New Processes:\n");
  for(int i = 0; i<2; ++i){
    sortedArray[i]->id = 11+i;
    sortedArray[i]->duration = rand() % 5 + 1;
    sortedArray[i]->priority = rand() % 10 + 1;
  }
  outputProcess(sortedArray[0]);
  outputProcess(sortedArray[1]);
  printf("\n");

  printf("New Sorted Array: \n");

  qSort(sortedArray,0,arrSize-1,'D');
  for(int i=0; i<arrSize; i++){
    while(sortedArray[i]->duration > 0){
      sortedArray[i]->duration = sortedArray[i]->duration-timeSlice;
      printf("Process with time slice: \n");
      outputProcess(sortedArray[i]);
    }
  }
  freeArray(sortedArray,arrSize);
  printf("\n\n");



}

void sched_round_robin(struct process ** processes, int arrSize, int timeSlice) {
  printf("ROUND ROBIN:\n\n");
  int init = 0;
  for(int i = 0; i<arrSize; ++i){
    if(processes[i]->duration % timeSlice != 0){
      init += processes[i]->duration/timeSlice;
    }
  }
  int i = 0;
	int k = 0;
	while(k < init){
    k++;
		if(processes[i]->duration > timeSlice){
			printf("Time Slice: %i\n", timeSlice);
      printf("Process ID: %d\n",processes[i]->id);
		}
		if(i == arrSize-1){
      i=0;
    }else{
      i++;
    }
  }
  freeArray(processes,arrSize);
  printf("\n\n");
}

