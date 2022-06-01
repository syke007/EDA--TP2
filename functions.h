/**
 * @file functions.h
 * @author Iuri Rodrigues (a21159@alunos.ipca.cpt)
 * @brief 
 * @version 0.1
 * @date 2022-06-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef Functions
#define Functions

typedef struct _job
{
    int JobID;
    struct _job *next,*prev;
    struct _machine *first,*last;
} Job;

typedef struct _machine
{
    int MachineID;
    int OperationID;
    int Time;
    struct _machine *next,*prev;
} Machine;




Job *insertion_job(Job *list, int JobID);
Machine *insertion_machine(Machine *list, int operationID, int MachineID, int time);
Job *insertion(Job *list, int jobID, int operationID,  int machineID, int time);
Job *LoadData(Job* list);
Job *WriteData(Job* list);
int verifyJob(Job* list,int jobId);
void print(Job *list);
Job * RemoveJob(Job* list,int jobId);
int verifyOperation(Job* list,int jobId, int operationID);
Job * RemoveOperation(Job* list,int jobId, int operationID);
int verifyMachine(Job* list,int jobId, int operationID,int machineID);
Job * UpdateOperation(Job* list,int jobId, int operationID, int newOperationId);
Job * UpdateMachine(Job* list,int jobId, int operationID, int machineID, int newMachineId);
Job * UpdateMachineTime(Job* list,int jobId, int operationID, int machineID, int Time);
Job * bestPath(Job *list,int limit);
#endif 