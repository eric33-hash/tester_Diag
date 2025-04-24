#include <stdio.h>
#include <string.h>
#include "json/include/cJSON.h"
#include "json/include/parseJson.h"

#include <stdlib.h>


struct Task getTaskInfo(char *file)
{
	struct Task task;
    task.sequence = parseSequence(file,1);
	task.taskInfo = parseTaskInfo(file);
	return task;
}

struct DiagnosticSeqence parseSequence(char *fileName,int flag)
{
	char path[1024] = {0};
	strcpy(path, fileName);
    if(flag == 1)
    {
        strcat(path, "/dataflow.json");
    }
    else if(flag == 0)
    {
        strcat(path, "/data27.json");
    }
	FILE *file = fopen(path,"rb");
    struct DiagnosticSeqence dataflow;

    if(!file)
	{
		printf("failed to open fail,error: %s\n",strerror(errno));
        return dataflow;
	}
	fseek(file,0,SEEK_END);
	int length = ftell(file);
	fseek(file,0,SEEK_SET);
	char* buf = (char*)malloc(length + 1);

	fread(buf,1,length,file);
	buf[length] = '\0';
	cJSON *json = NULL;
	json = cJSON_Parse(buf);
	if(!json)
	{
		printf("failed to parse json\n");
	}
    dataflow.sequence = cJSON_GetObjectItem(json,"sequences");/*
    dataflow.file = cJSON_GetObjectItem(json,"flashFile")->valuestring;*/
    dataflow.deviceType = strcmp(cJSON_GetObjectItem(json,"deviceType")->valuestring,"CAN") ==0 ? 1 : 0;
    sscanf(cJSON_GetObjectItem(json,"PhyRequestID")->valuestring,"%x",&dataflow.requestID);
    sscanf(cJSON_GetObjectItem(json,"ResponseID")->valuestring,"%x",&dataflow.responseID);
	fclose(file);
    return dataflow;
}

struct DiagnosticTaskInfo parseTaskInfo(char *fileName)
{
	char path[1024] = {0};
	strcpy(path, fileName);
    strcat(path, "/task.json");
	FILE *file = fopen(path,"rb");
    struct DiagnosticTaskInfo taskInfo;

    if(!file)
	{
		printf("failed to open fail,error: %s\n",strerror(errno));
        return taskInfo;
	}
	fseek(file,0,SEEK_END);
	int length = ftell(file);
	fseek(file,0,SEEK_SET);
	char* buf = (char*)malloc(length + 1);

	fread(buf,1,length,file);
	buf[length] = '\0';
	cJSON *json = NULL;
	json = cJSON_Parse(buf);
	if(!json)
	{
		printf("failed to parse json\n");
	}
	taskInfo.name = cJSON_GetObjectItem(json,"name")->valuestring;
	char *source = cJSON_GetArrayItem(cJSON_GetObjectItem(json,"priority"),0)->valuestring;
	if(strcmp(source,"OBD") == 0)
	{
		taskInfo.source = 3;
	}
	else if(strcmp(source , "HMI") == 0)
	{
		taskInfo.source = 2;
	}
	else if(strcmp(source , "WIFI") == 0)
	{
		taskInfo.source = 1;
	} 
	else if(strcmp(source , "4/5G") == 0)
	{
		taskInfo.source = 0;
	} 
    taskInfo.taskType = cJSON_GetObjectItem(json,"strategy")->valuestring;
	cJSON *period = cJSON_GetObjectItem(json,"period");
	taskInfo.PeriodicTasks.cycle = cJSON_GetObjectItem(period,"cycle")->valueint;
	taskInfo.PeriodicTasks.startTime = string2time(cJSON_GetObjectItem(period,"startingTime")->valuestring);
	taskInfo.PeriodicTasks.endTime = string2time(cJSON_GetObjectItem(period,"endingTime")->valuestring);
	taskInfo.documentation = cJSON_GetObjectItem(json,"documentation")->valuestring;

	fclose(file);
	
	return taskInfo;
}

uint8_t str2uint8(char *str,uint8_t *array)
{
	char *endPoter;
	char *subStr = strtok(str, " ");
	array[0] = strtol(subStr,&endPoter,16);
    uint8_t index = 1;
	while (subStr != NULL)
	{
		subStr = strtok(NULL, " ");
		if(NULL == subStr)
	    	break;
	    array[index] = strtol(subStr,&endPoter,16);
		index++;
 	}
	return index;
}
 
time_t string2time(char *stringTime)
{
	struct tm tm_time;
	sscanf(stringTime , "%4d-%2d-%2d %2d:%2d:%2d", &tm_time.tm_year, &tm_time.tm_mon, &tm_time.tm_mday, 
												&tm_time.tm_hour, &tm_time.tm_min, &tm_time.tm_sec);

	tm_time.tm_year -= 1900;
	tm_time.tm_mon -=1; 				
    tm_time.tm_isdst = 0;
	time_t time = mktime(&tm_time);

	return time;
}
