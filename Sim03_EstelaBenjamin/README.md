Name: Benjamin Estela  
Class: CS 446  
Assignment: 3  
Due Date: April 7, 2019  
Grade: 100%

---  

Given archive:  
Sim03_Estela_Benjamin.tar.gz  

Given files:  
README.md, makefile, PA03.cpp,  
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

The code should be compiled and an executable, titled sim3 will be available. 
To run it, you first need your config file available (ex. config_1.conf).
Then, type:

>`./sim3 config_1.conf`

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
of the functions to align with assignment 2 instructions. On line 88 of 
MetaData.cpp the pthread is created for use in the ThreadMeta function.

For assignment 3, mutexes are used to complete the requirements. In 
MetaData.cpp, on line 36, a global mutex is created for use in the 
PrintMeta functions such that the critical section may occur which involves 
waiting for a threaded IO operation to occur. Alongside this, semaphores are 
used where counts are used such as projector and hard drive where it is defined
on line 37.
