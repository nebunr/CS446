Name: Benjamin Estela  
Class: CS 446  
Assignment: 5  
Due Date: May 8, 2019  
Grade: 80% - “algorithms are not working as expected.”

---  

Given archive:  
Sim05_Estela_Benjamin.tar.gz  

Given files:  
README.md, makefile, main.cpp,  
Config.h, Config.cpp, MetaData.h, MetaData.cpp,  
pcbstates.h, pcb.h, pcb.cpp  

Needed files:  
config file (ex. config_1.conf)  
meta data file (ex. Test_1a.mdf)  
---  

How to run:  

Begin by opening your terminal, unpacking the given .tar.gz archive, 
and heading to the directory where the files are located. 
Next, type:   

>`make`  

The code should be compiled and an executable, titled sim5 will be available. 
To run it, you first need your config file available (ex. config_1.conf).
Then, type:

>`./sim5 config_1.conf`

Possible errors that could occur are that you may not have a meta data 
file (ex. Test_1a.mdf) available. This file is determined in the config file.
Also, there may be typos in your files. The terminal will output any possible
errors found in your config or meta data files.

---  

Program Information:  
This program reads into the given configuration file and takes in necessary 
variables that are stored into a class, Config. From there, the MetaData 
function is called, which is found in the MetaData files to output to the
monitor and/or given log. What is output are the cycle times for various
components of a simulated operating system.  

In order for the every file to be opened/closed once, all ifstream 
declarations occur in the main function. Threads are created in the 
PrintMeta function once an IO operation is found. From there, the 
pthread_create function waits for the set time then joins itself 
back. Timers are also added using chrono with a timer T1 being apart of 
every major functions to timestamp using the TimeStamp function. The PCB 
class appropriately sets the process states using an enum for START, READY, 
RUNNING, WAIT, and EXIT.  

Pthreads (-lpthread) and the PCB class are accessed in the MetaData.cpp file with many 
of the functions to align with assignment 2 instructions. On line 84 of 
MetaData.cpp the pthread is created for use in the ThreadMeta function.

For assignment 3, mutexes are used to complete the requirements. In 
MetaData.cpp, on line 42, a global mutex is created for use in the 
PrintMeta functions such that the critical section may occur which involves 
waiting for a threaded IO operation to occur. Alongside this, semaphores are 
used where counts are used such as projector and hard drive where it is defined
on line 43.

For assignment 4, the scheduling algorithms of FIFO, PS, and SJF are implemented.
Alongside this, metadata is saved to a data structure for easier use.  
For FIFO, the regular print functions are used and is called at line 109.  
For PS, the metadata is printed at times where the most IO tasks in a process 
are first, this is called at line 137.  
For SJF, the metadata is printed at times where the least tasks in a process 
are first, this is called at line 149.  

For assignment 5, the scheduling algorithms of RR and STR are implemented.
The PrintMeta function was changed for use with RR with an added boolean.
For RR, the metadata goes through every process and handles tasks with no 
time remaining to be set to -1, this is called at line 161.
For STR, the metadata is printed at times where the processes with shortest 
times goes first, assuming an arrival time of 0, this is called at line 173.
