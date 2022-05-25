#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "functions.h"


Job *insertion_job(Job *list, int JobID)
{
    Job *new = (Job *)malloc(sizeof(Job));

    new->JobID = JobID;
    new->first = new->last = NULL;
    new->next = list;

    return new;
}

Machine *insertion_machine(Machine *list, int operationID, int MachineID, int time)
{
    Machine *new = (Machine *)malloc(sizeof(Machine));
    new->MachineID = MachineID;
    new->Time = time;
    new->OperationID = operationID;
    new->next  = NULL;
    new->prev = list;

    if (new->prev)
    {
        new->prev->next = new;
    }
    return new;
}

Job *insertion(Job *list, int jobID, int operationID,  int machineID, int time)
{
	if (list != NULL)
	 {
		for (; list; list = list->next)
		{
			if(list->JobID == jobID)
			{
				if (!list->last)
				{
					list->first = list->last =  insertion_machine(list->last, operationID, machineID, time);
				}
				else
				{
					list->last =  insertion_machine(list->last, operationID, machineID, time);
				}
				return list;

			}
		}
	}		
 }

Job *LoadData(Job* list)
{
    FILE *file;
    file = fopen("jobs.txt", "r");
    while (!feof(file))
    {
        char line[50];
        int JobID,operationID, machineID, time;
        fgets(line, 50, file);
        sscanf(line, "%d,%d,%d,%d", &JobID,&operationID, &machineID, &time);

        list = insertion_job(list, JobID);
        list = insertion(list, JobID, operationID, machineID, time);  
    }
    fclose(file);
    return list;
}

Job *WriteData(Job* list)
{
    FILE *file;
    file = fopen("jobs_write.txt", "w");
    for(; list; list = list->next)
    {
        Machine * machine = list->first;
        for(;machine; machine = machine->next)
        {
            fprintf(file, "%d,%d,%d,%d\n", list->JobID,machine->OperationID,machine->MachineID, machine->Time);
        }   
    }
    fclose(file);
    return list;
}



int verifyJob(Job* list,int jobId)
{
    for(; list; list = list->next)
    {
        if(jobId == list->JobID)
        {
            return 1;
        }
    }

    return 0;
}

void print(Job *list)
{
    for(; list; list = list->next)
    {
        Machine * machine = list->first;
        for(;machine; machine = machine->next)
        {
            printf("Job -> %d | Operation -> %d | Machine -> %d | Time -> %d\n",list->JobID,machine->OperationID,machine->MachineID, machine->Time);
        }   
    }
}