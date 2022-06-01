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

int main()
{
    Job *list = NULL;
    int op, jobId, OperationId, newOperationId, machineId, time, limit, newMachineId;

    list = LoadData(list);
    do
    {
        printf("|-------------------------------------------|\n");
        printf("|                Options:               	|\n");
        printf("|-------------------------------------------|\n");
        printf("| 1- Export                                 |\n");
        printf("| 2- Show                               	|\n");
        printf("|--                                     	|\n");
        printf("| 3- Insert Job                         	|\n");
        printf("| 4- Remove Job                          	|\n");
        printf("| 5- Remove Operation                   	|\n");
        printf("|--                                     	|\n");
        printf("| 6- Update OperationID                     |\n");
        printf("| 7- Update MachineID                       |\n");
        printf("| 8- Update Machine Time                    |\n");
        printf("| 9- FJSSP                                  |\n");
        printf("|--                                     	|\n");
        printf("|              0 to exit                  	|\n");
        printf("|-------------------------------------------|\n");

        printf("Choose an option:\n");
        scanf("%d", &op);
        system("cls");
        switch (op)
        {
        case 1:
            system("cls");
            WriteData(list);
            printf("Exported to a File\n");
            system("pause");
            break;
        case 2:
            system("cls");
            print(list);
            system("pause");
            break;
        case 3:
            system("cls");
            printf("JobId -> ");
            scanf("%d", &jobId);
            if (verifyJob(list, jobId) == 1)
            {
                printf("This Job already exists\n");
                system("pause");
                break;
            }
            list = insertion_job(list, jobId);
            system("pause");
            break;
        case 4:
            system("cls");
            printf("JobId -> ");
            scanf("%d", &jobId);
            if (verifyJob(list, jobId) == 0)
            {
                printf("Job doesnt exists\n");
                system("pause");
                break;
            }
            RemoveJob(list, jobId);
            system("pause");
            break;
        case 5:
            system("cls");
            printf("JobId -> ");
            scanf("%d", &jobId);
            printf("OperationId -> ");
            scanf("%d", &OperationId);
            if (verifyJob(list, jobId) == 1)
            {
                if (verifyOperation(list, jobId, OperationId) == 1)
                    RemoveOperation(list, jobId, OperationId);
                else
                    printf("Operation doesnt exists\n");
            }
            else
                printf("Job doesnt exists\n");
            system("pause");
            break;
        case 6:
            system("cls");
            printf("JobId -> ");
            scanf("%d", &jobId);
            printf("OperationId -> ");
            scanf("%d", &OperationId);
            printf("New OperationId -> ");
            scanf("%d", &newOperationId);
            if (verifyJob(list, jobId) == 1)
            {
                if (verifyOperation(list, jobId, OperationId) == 1)
                {
                    if (verifyOperation(list, jobId, newOperationId) == 0)
                        UpdateOperation(list, jobId, OperationId, newOperationId);
                    else
                        printf("New Operation already exists\n");
                }
                else
                    printf("Operation dont exists\n");
            }
            else
                printf("Job dont exists\n");
            system("pause");
            break;

        case 7:
            system("cls");
            printf("JobId -> ");
            scanf("%d", &jobId);
            printf("OperationId -> ");
            scanf("%d", &OperationId);
            printf("MachineID -> ");
            scanf("%d", &machineId);
            printf("New MachineID -> ");
            scanf("%d", &newMachineId);
            if (verifyJob(list, jobId) == 1)
            {
                if (verifyOperation(list, jobId, OperationId) == 1)
                {
                    if (verifyMachine(list, jobId, OperationId, machineId) == 1)
                    {
                        if (verifyMachine(list, jobId, OperationId, newMachineId) == 0)
                            UpdateMachine(list, jobId, OperationId, machineId, newMachineId);
                        else
                            printf("New Machine already exists\n");
                    }
                    else
                        printf("Machine doesnt exists\n");
                }
                else
                    printf("Operation doesnt exists\n");
            }
            else
                printf("Job doesnt exists\n");
            system("pause");
            break;
        case 8:
            system("cls");
            printf("JobId -> ");
            scanf("%d", &jobId);
            printf("OperationId -> ");
            scanf("%d", &OperationId);
            printf("MachineID -> ");
            scanf("%d", &machineId);
            printf("Time -> ");
            scanf("%d", &time);
            if (verifyJob(list, jobId) == 1)
            {
                if (verifyOperation(list, jobId, OperationId) == 1)
                {
                    if (verifyMachine(list, jobId, OperationId, machineId) == 1)
                    {
                        UpdateMachineTime(list, jobId, OperationId, machineId, time);
                    }
                    else
                        printf("Machine doesnt exists\n");
                }
                else
                    printf("Operation doesnt exists\n");
            }
            else
                printf("Job doesnt exists\n");
            system("pause");
            break;
        case 9:
            system("cls");
            printf("Limit -> ");
            scanf("%d", &limit);
            bestPath(list, limit);
            system("pause");
            break;
        case 0:
            system("cls");
            printf("See ya\n");
            break;
        }
    } while (op != 0);
    system("cls");
    return 0;
}