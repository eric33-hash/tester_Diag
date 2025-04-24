#ifndef CYCLE_H_
#define CYCLE_H_

#include "json/include/parseJson.h"

typedef struct pcb {
	int taskID;
	char state;//E为完成，R为正在运行，W为在就绪队列
	int total_time;//需要的时间
	int level;//优先级
	int cputime;//已经执行的时间
	int mark;//标志位，用来表示正在执行的进程，1为在cpu，0为不在cpu
	struct Task taskinfo;
	struct pcb* next;
}*proc;

extern proc initTaskLinklist(struct Task task);

extern void insertTaskLinklist(proc* headRef,struct Task task);

extern void deleteTaskLinklist(proc* headRef,struct Task task);

extern proc findMaxLevelLinklist(proc head);

#endif
