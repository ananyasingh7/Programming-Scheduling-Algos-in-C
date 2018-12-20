# Programming-Scheduling-Algos-in-C
CS 332 - Operating Systems Final Project


CS 332 Project - Programming Scheduling Algorithms in C



Overview:



You will be given a template in C for testing a series of scheduling algorithms which we will be going over later in class. The template code will provide a series of tests and function outlines, and it is your job to fill in these outlines to make the functions behave properly. You can find the template code on our class Moodle page. 



The skeleton code will define prototypes for five functions, each pertaining to a different scheduling algorithm. You will earn 20% of your final project grade for each of these functions that you complete successfully. A double pointer (pointer to an array) of process structs will be pre-populated and provided for you to use as a parameter to each function. After running the function, the processes should be output in the order expected by the given algorithm. These algorithms are well-documented online, as well as your chapter 9 notes, available on Moodle. The only algorithm below not in our notes is the priority-based scheduling algorithm, which will take in a second associated array of priorities for the processes, and sort the processes by these priorities before outputting them. This algorithm will be non-preemptive.



NOTE: The skeleton code files were written on a Linux system, so they are using Unix line endings. To view the files normally from Windows, you will need a text editor that can properly convert these line endings to DOS. VSCode is one editor I know of that can accomplish this.



The following is a snippet from sched_algos.h which contains the definitions of the five functions.



 //First-Come-First-Served

 void sched_fcfs(struct process ** processes, int arrSize);



 //Priority Scheduling

 void sched_priority(struct process ** processes, int arrSize, int ** priorities);



 //Shortest Process Next

 void sched_spn(struct process ** processes, int arrSize);

 

 //Shortest Remaining Time

 void sched_srt(struct process ** processes, int arrSize, int timeSlice);



//Round Robin

 void sched_round_robin(struct process ** processes, int arrSize, int timeSlice);

 

You will also be given the definition of a struct (similar to a class) representing a single process:



struct process {                                                                                                                                                                   int id;

int duration;

};


All code changes should be completed within your main.c file. Sched_algos.h is only for your reference, and should remain untouched.



Additional Grading Criteria:



Aside from implementing the five scheduling functions provided in the skeleton code, you will also be graded on a smaller scale for your code efficiency, neatness, and proper memory management. You may receive a few extra points on your final project code for hitting these three marks, or you may lose some points for extremely inefficient/sloppy code. These points will be entirely at my discretion and will only be a minor part of your final project grade. This is intended to be an opportunity for you to get some bonus points, even if you do not finish all five functions completely.



Ground Rules:



No using any non-standard libraries that do any of these functions for you. In fact, all #include statements that you will need are already in main.c.

You will have to write a sort at some point in this project. Please write your own, and only use one of the three following sorts: merge sort, quick sort, or heap sort. I chose these three because they are some of the most efficient sorting algorithms from a runtime perspective.

No copying and pasting code from the internet - this is fairly simple to check.

You may collaborate to bounce ideas off of each other, but you are each responsible for your own code. Two or more people with exactly the same code would be considered copying.

Please use any functions provided in the skeleton code. Do not write redundant code that accomplishes the same thing.



C Basics:



C is one of the more complex programming languages you will learn. It is completely understandable if you have some trouble grasping the concepts at first, especially if you don’t come from a programming background. Fortunately, there are plenty of online tutorials and documents to help you. The following document taught me basically everything I know about C, and it covers all of the language-specific topics needed for this project:






Project Submission:



A link to upload your final code to Moodle will be posted in the coming weeks. You will submit ONLY your main.c file. This file should contain all of your source code (excluding the templates provided in sched_algos.h). I will be compiling each submission and testing it myself. You will lose points if your code looks nice but doesn’t actually work.



A due date for the project is still TBD and will be announced on Moodle at a later date. It will be within the last couple of weeks of the semester.




