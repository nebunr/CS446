Name: Benjamin Estela  
Class: CS 446  
Assignment: 2 
Due Date: March 15, 2019  
Grade: 97% - “Readme missing the pcb and pthread file name and file number.”

---  

Given archive:  
Sim02_Estela_Benjamin.tar.gz  

Given files:  
README.md, makefile, PA02.cpp, Config.h, 
Config.cpp, MetaData.h, MetaData.cpp,  
pcbstates.h, pcb.h, pcb.cpp  

Needed files:  
config file (ex. config_1.conf)  
meta data file (ex. Test_1a.conf)  
---  

How to run:  

Begin by opening your terminal, unpacking the given .tar.gz archive, 
and heading to the directory where the files are located. 
Next, type:   

>`make`  

The code should be compiled and an executable, titled sim1 will be available. 
To run it, you first need your config file available (ex. config_1.conf).
Then, type:

>`./sim2 config_1.conf`

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
