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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "functions.h"


/**
 * @brief Insere um job na lista
 * 
 * @param list 
 * @param JobID 
 * @return Job* 
 */
Job *insertion_job(Job *list, int JobID)
{
    Job *new = (Job *)malloc(sizeof(Job));

    new->JobID = JobID;
    new->first = new->last = NULL;
    new->next = list;

    return new;
}


/**
 * @brief insere uma maquina, ooperaçao e tempo na lista
 * 
 * @param list 
 * @param operationID 
 * @param MachineID 
 * @param time 
 * @return Machine* 
 */
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


/**
 * @brief insere a lista de machines dentro da lista de jobs
 * 
 * @param list 
 * @param jobID 
 * @param operationID 
 * @param machineID 
 * @param time 
 * @return Job* 
 */
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


/**
 * @brief mostra ao utilizador os dados 
 * 
 * @param list 
 */
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


/**
 * @brief le os dados do ficheiro txt
 * 
 * @param list 
 * @return Job* 
 */
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


/**
 * @brief escreve os dados para um ficheiro txt
 * 
 * @param list 
 * @return Job* 
 */
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


/**
 * @brief faz a verificação se um job já existe
 * 
 * @param list 
 * @param jobId 
 * @return int 
 */
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

/**
 * @brief faz a remoçao de um job
 * 
 * @param list 
 * @param jobId 
 * @return Job* 
 */
Job * RemoveJob(Job* list,int jobId)
{
    for(; list; list = list->next)
    {
        if(jobId == list->JobID)
        {
            Machine * machine = list->first;

            for(;machine;machine = machine->next)
            { 
                if(list->first->next)
                {
                    list->first = list->first->next;
                    list->next->prev = NULL;
                }
                else
                {
                    list->first = NULL;
                    list->last = NULL;
                }
                free(machine); 
            }
            
        }
    }
}


/**
 * @brief faz a verificação se uma operaçao já existe
 * 
 * @param list 
 * @param jobId 
 * @return int 
 */
int verifyOperation(Job* list,int jobId, int operationID)
{
    for(; list; list = list->next)
    {
        if(jobId == list->JobID)
        {
            Machine * machine = list->first;

            if(machine->OperationID == operationID)
            {
                return 1;
            }
        }
    }
}

/**
 * @brief remove uma operaçao
 * 
 * @param list 
 * @param jobId 
 * @param operationID 
 * @return Job* 
 */
Job * RemoveOperation(Job* list,int jobId, int operationID)
{
    for(; list; list = list->next)
    {
        if(jobId == list->JobID)
        {
            Machine * machine = list->first;
            if(machine->OperationID == operationID)
            {
                for(;machine;machine = machine->next)
                { 
                    if(list->first->next)
                    {
                        list->first = list->first->next;
                        list->next->prev = NULL;
                    }
                    else
                    {
                        list->first = NULL;
                        list->last = NULL;
                    }
                    free(machine); 
                }
            } 
        }
    }
}


/**
 * @brief faz a verificação se uma maquina já existe
 * 
 * @param list 
 * @param jobId 
 * @return int 
 */
int verifyMachine(Job* list,int jobId, int operationID,int machineID)
{
    for(; list; list = list->next)
    {
        if(jobId == list->JobID)
        {
            Machine * machine = list->first;

            if(machine->OperationID == operationID)
            {
                if(machine->MachineID == machineID)
                {
                    return 1;
                }
            }
        }
    }
}


/**
 * @brief altera a operation id
 * 
 * @param list 
 * @param jobId 
 * @param operationID 
 * @param newOperationId 
 * @return Job* 
 */
Job * UpdateOperation(Job* list,int jobId, int operationID, int newOperationId)
{
    for(; list; list = list->next)
    {
        if(jobId == list->JobID)
        {
            Machine * machine = list->first;
            for(;machine;machine = machine->next)
            { 
                if(machine->OperationID == operationID)
                {
                    machine->OperationID = newOperationId;
                }
            } 
        }
    }
}


/**
 * @brief altera o id duma maquina
 * 
 * @param list 
 * @param jobId 
 * @param operationID 
 * @param machineID 
 * @param newMachineId 
 * @return Job* 
 */
Job * UpdateMachine(Job* list,int jobId, int operationID, int machineID, int newMachineId)
{
    for(; list; list = list->next)
    {
        if(jobId == list->JobID)
        {
            Machine * machine = list->first;
            for(;machine;machine = machine->next)
            { 
                if(machine->OperationID == operationID)
                {
                    if(machine->MachineID == machineID)
                    {
                        machine->MachineID = newMachineId;
                    }
                }
            } 
        }
    }
}

/**
 * @brief altera um tempo duma maquina
 * 
 * @param list 
 * @param jobId 
 * @param operationID 
 * @param machineID 
 * @param Time 
 * @return Job* 
 */
Job * UpdateMachineTime(Job* list,int jobId, int operationID, int machineID, int Time)
{
    for(; list; list = list->next)
    {
        if(jobId == list->JobID)
        {
            Machine * machine = list->first;
            for(;machine;machine = machine->next)
            { 
                if(machine->OperationID == operationID)
                {
                    if(machine->MachineID == machineID)
                    {
                        machine->Time = Time;
                    }
                }
            } 
        }
    }
}


/**
 * @brief calcula o melhor tempo para um job
 * 
 * @param list 
 * @param limit 
 * @return Job* 
 */
Job * bestPath(Job *list,int limit)
{
    int Best[50][50][50];
    for(int i = 0; i<50; i++)
    {
        for(int x = 0; x<50; x++)
        {
            for(int y = 0; y<50; y++)
            { Best[i][x][y] = 0; } 
        }
    }

    for(; list; list = list->next)
    {
        Machine * machine = list->first;
        for(; machine; machine = machine->next)
        {
            if(Best[list->JobID][machine->OperationID][machine->MachineID] == 0)
            {
                Best[list->JobID][machine->OperationID][machine->MachineID] = machine->Time; 
            }   
            else
            {
                if(Best[list->JobID][machine->OperationID][machine->MachineID] > machine->Time)
                {
                    Best[list->JobID][machine->OperationID][machine->MachineID] = machine->Time; 
                }
            }
        }
    }
    FILE *file;
    int total = 0;
    file = fopen("index.html", "w"); 
    fprintf(file, "<link rel=\"stylesheet\" href=\"style.css\" type=\"text/css\">\n\n");
    fprintf(file, "<table class=\"zui-table\" >\n");
    fprintf(file, "\t <thead> \n  \t\t<th> Job </th>\n \t\t<th> Operation </th>\n \t\t<th> Machine </th>\n \t\t<th> Time </th>\n \t\t<th> Total Time </th>\n \t </thead> \n ");
    for(int i = 0; i<50; i++)
    {
        for(int x = 0; x<50; x++)
        {
            for(int y = 0; y<50; y++)
            {
                if(Best[i][x][y] != 0)
                {
                    if(total + Best[i][x][y] <= limit)
                    {
                        total = total + Best[i][x][y];
                        fprintf(file, "\t<tr>\n\t \t<td> %d </td>\n \t\t<td> %d </td>\n \t\t<td> %d </td>\n \t\t<td> %d </td>\n \t\t<td> %d </td>\n \t</tr>\n", i,x,y,Best[i][x][y], total);
                    }
                    else break;
                    
                }
            } 
        }
        total = 0;
    }
    fprintf(file, "</table>\n");~
    fclose(file);
}