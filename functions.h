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

#endif 