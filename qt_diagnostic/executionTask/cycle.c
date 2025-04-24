#include <stdio.h>
#include <stdlib.h>
#include "cycle.h"


proc findMaxLevelLinklist(proc head)
{	
	proc current = head;
	int maxlevel = head->level;
	proc res = NULL;
	while(current != NULL)
	{
		if(current->level >= maxlevel)
		{
            res = current;
			maxlevel = current->level;

		}
		current = current->next;
	}
	return res;
}
 
void display(struct pcb* head,int* proc_num) {
	int i;
	proc p = head;
	printf("taskID cpu_time req_time level\n");
	for (i = 0; i < *proc_num; i++) {
		printf("%d\t%d\t%d\t%d\n", p->taskID, p->cputime, p->total_time, p->level);
		p = p->next;
	}
	printf("----------------------------------\n");
}
 
void priority(proc head)
{
	proc currentTask = findMaxLevelLinklist(head);
}
 
proc initTaskLinklist(struct Task task)
{
	proc head = NULL;
	proc tail = NULL;

	proc newNode = (proc)malloc(sizeof(struct pcb));

	if(newNode == NULL)
		return NULL;
	
	newNode->taskID = strtol(task.taskInfo.name,NULL,10);
	newNode->taskinfo = task;
	newNode->level = task.taskInfo.source;
	newNode->mark = 1;
	newNode->state = 'W';
	newNode->cputime = 0;
	newNode->total_time = task.taskInfo.PeriodicTasks.endTime - task.taskInfo.PeriodicTasks.startTime;
	newNode->next = NULL;

	if(head == NULL){
		head = tail = newNode;
	}
	else{
		tail->next = newNode;
		tail = newNode;
	}
	return tail;
}

void insertTaskLinklist(proc* headRef,struct Task task)
{
	proc newNode = (proc)malloc(sizeof(struct pcb));

	if(newNode == NULL)
		return;

	newNode->taskID = strtol(task.taskInfo.name,NULL,10);
	newNode->taskinfo = task;
	newNode->level = task.taskInfo.source;
	newNode->mark = 0;
	newNode->state = 'W';
	newNode->cputime = 0;
	newNode->total_time = task.taskInfo.PeriodicTasks.endTime - task.taskInfo.PeriodicTasks.startTime;

	if(*headRef == NULL)
	{
		newNode->next = *headRef;
		*headRef = newNode;
		return;
	}

	proc current = *headRef;
    proc insert = *headRef;
	
	
	if(newNode->taskinfo.taskInfo.PeriodicTasks.startTime < current->taskinfo.taskInfo.PeriodicTasks.startTime || newNode->taskinfo.taskInfo.PeriodicTasks.startTime < current->taskinfo.taskInfo.PeriodicTasks.endTime)
	{
		newNode->next = *headRef;
		*headRef = newNode;
		if(newNode->taskinfo.taskInfo.PeriodicTasks.startTime < current->taskinfo.taskInfo.PeriodicTasks.endTime)
		{
			newNode->state = 's';
		}
		return;
	}
    
	int count = 0;
	while (current != NULL)
	{
		if(current->taskinfo.taskInfo.PeriodicTasks.startTime < task.taskInfo.PeriodicTasks.startTime)
		{
			if(current->next == NULL)
			{
				current->next = newNode;
				newNode->next = NULL;
				return;
			}
			current = current->next;
			count++;
		}
		else if(current->taskinfo.taskInfo.PeriodicTasks.startTime == task.taskInfo.PeriodicTasks.startTime)
		{
			if(current->level > task.taskInfo.source)
			{
				current->next = newNode;
				newNode->next = current->next;
				return;
			}
			else
			{
				for(int i = 0;i < count -1; i++)
				{
					insert = insert->next;
				}
				newNode->next = insert->next;
				insert->next = newNode;
				return;
				
				
			}
		}
		else
		{
			for(int i = 0;i < count -1; i++)
			{
                insert = insert->next;
			}
			newNode->next = insert->next;
			insert->next = newNode;
			return;
		}
		
	}
	
	return;
}

void deleteTaskLinklist(proc* headRef,struct Task task)
{
	proc current = *headRef;
	proc prev = NULL;

	if (current != NULL && current->taskID == strtol(task.taskInfo.name,NULL,10)) {
        *headRef = current->next;
       // free(current);
        return;
    }

	while (current != NULL && current->taskID != strtol(task.taskInfo.name,NULL,10)) {
        prev = current;
        current = current->next;
    }

    if (current != NULL) {
        prev->next = current->next;
       // free(current);
    }
}

