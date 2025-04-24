#include <stdio.h>
#include <unistd.h>		/* usleep */
#include <dirent.h>
#include "mainDiag.h"

#define EVENT_SIZE (sizeof(struct inotify_event))

typedef unsigned int bool;

CREATEENUM(sequencelist,
    phyRequest,
    funRequest,
    securityAccess,
    EraseFlash,
    downloadRequest,
    download,
    checkCRC,
    waitTime
)

static proc tasklist;
pthread_mutex_t mutexLinklist;

void* callTask(void* args)
{ 
	tasklist = NULL;
    
	pthread_t monitorTask;
	pthread_create(&monitorTask, NULL, monitorDirectory,NULL);

	#ifndef NO_RT
		mlockall(MCL_CURRENT | MCL_FUTURE);
	#endif
	signal(SIGINT, signal_handler);

	
    
	pthread_mutex_init(&mutexLinklist, NULL);

    pthread_t threadpoll;
//	int err = pthread_create(&threadpoll, NULL, writeLog,NULL);
//	if(err != 0)
//    {
//        printf("CAN't Creat thread:%s\n",strerror(errno));
//    }
    while(1)
    {
        int isruntime = *(int *)args;
        if(isruntime == 0)
        {
            time_t currentTime = time(NULL);
            proc head = tasklist;
            while (head != NULL )
            {
                currentTime = time(NULL);

               // printf("head->taskinfo.taskInfo.PeriodicTasks.startTime = %ld\n",head->taskinfo.taskInfo.PeriodicTasks.startTime);
                if(currentTime == head->taskinfo.taskInfo.PeriodicTasks.startTime || head->state == 's')
                {
                    time_t endTime = time(NULL);
                    int exeCount = 0;
                    int sucessCount = 0;
                    do
                    {
                        struct timeval  tv;

                        tv.tv_sec = 0;
                        tv.tv_usec = head->taskinfo.taskInfo.PeriodicTasks.cycle;
                        pthread_mutex_lock(&mutexLinklist);
                        {
                            sleep(3);
                            if(tasklist->taskID != head->taskID)
                            {
                                pthread_mutex_unlock(&mutexLinklist);
                                head->state = 's';
                                tasklist->taskinfo.taskInfo.PeriodicTasks.startTime = time(NULL);
                                break;
                                fflush(stdout);
                            }
                        }
                        pthread_mutex_unlock(&mutexLinklist);

                        uint8_t exeResult = BOOL_FALSE;
                        exeResult = executeLinklistTask(head->taskinfo.sequence);
                        exeCount++;
                        if(exeResult == BOOL_FALSE)
                            sucessCount++;
                        call_func_showCount(pclass,exeCount,sucessCount);
                        currentTime = time(NULL);

                        select(0, NULL, NULL, NULL, &tv);
                        endTime = time(NULL);
                        if(isruntime != 0)
                        {
                            break;
                        }
                    } while (endTime < head->taskinfo.taskInfo.PeriodicTasks.endTime);

                    if(endTime > head->taskinfo.taskInfo.PeriodicTasks.endTime)
                    {
                        deleteTaskLinklist(&tasklist,head->taskinfo);
                        call_func_showCount(pclass,0,0);
                        printf("delete taskid = %d\n",head->taskID);
                    }

                    if(head->state == 's')
                        break;
                    if(isruntime != 0)
                    {
                        break;
                    }
                }
                //else
                {
                    if(head == NULL)
                        continue;
                    head = head->next;
                }
            }
        }
    }

}

int split(const char* str, int strLen, const char* splitChar, int index, char* result, int maxLen)
{
	int i = 0;
    int ret = 0;	
	int findLen = 0;
	int findFlag = 0;	
	int startIndex = 0;
	int splitCharLen = 0;
	
	//合法性判断
	if(NULL == str || NULL == result || NULL == splitChar || index<=0)
	{
		return -1;
	}		
	splitCharLen = strlen(splitChar);
	findLen = strLen-splitCharLen;
	if(findLen<0)
	{
		return -2;
	}	
	
	//查找结果的左右分隔符位置
	for(; i<=findLen && str[i] != '\0'; i++)
	{
		if(strncmp(&str[i], splitChar, splitCharLen) == 0)
		{
			if(0 == findFlag)//find the left
			{
				startIndex++;
				if(1 == index)//第一个直接返回
				{
					strncpy(result, &str[0], i);
					ret = i;
					break;
				}
				else if(startIndex+1 == index)
				{
					startIndex = i;
					findFlag = 1;
				}
			}
			else//find the right
			{
				findFlag = 2;
				break;
			}
		}
	}	
	
	//截取结果
	if(0 != findFlag && startIndex<strLen-1)
	{
		startIndex += splitCharLen;
		ret = i-startIndex;//结果的字符个数
		if(ret>maxLen || ret>strLen)
		{
			ret = 0;
		}
		else if(ret>0)
		{
			strncpy(result, &str[startIndex], ret);
			ret = strlen(result);
		}
	}
	return ret;
}

uint8_t testquenceList(struct can_iso_tp_link_t link,struct DiagnosticSeqence dataflow)
{
	int seqSize = cJSON_GetArraySize(dataflow.sequence);
	struct sendMsg *reqMsg = (struct sendMsg *)malloc(sizeof(struct sendMsg));
	struct sendMsg *respMsg = (struct sendMsg*)malloc(sizeof(struct sendMsg));
    long fileSize = 0;
	FILE* file = fopen(dataflow.file, "rb");
    if (file == NULL) {
        printf("File not found.");
    }
    else
    {
        fseek(file, 0, SEEK_END);
        fileSize = ftell(file);
        fclose(file);
    }


	uint32_t memoryaddr = 0x500000;
	uint32_t memorysize = 0;
	unsigned int blocksize = 0;
    bool isContinue = BOOL_FALSE;
	for(int i = 0;i < seqSize;i++)
	{
		char *seq = cJSON_GetArrayItem(dataflow.sequence,i)->valuestring;
		char seqCommand[128];
		memset(seqCommand,0x00,128);
		split(seq,strlen(seq),";",1,seqCommand,sizeof(seqCommand));
		char seqRequest[128];
		memset(seqRequest,0x00,128);
		split(seq,strlen(seq),";",2,seqRequest,sizeof(seqRequest));
		char seqResp[128] ;
		memset(seqResp,0x00,128);
		split(seq,strlen(seq),";",3,seqResp,sizeof(seqResp));

		switch (TOENUM(sequencelist,seqCommand))
		{
			case phyRequest:
			{
				uint8_t sendData[MAX_BUFF_LEN];
				uint8_t respData[MAX_BUFF_LEN];
				reqMsg->size = str2uint8(seqRequest,sendData);
			    reqMsg->isFunction = 0;
				memcpy(reqMsg->payload,sendData,reqMsg->size);
				if(sendAndReceiveMessage(dataflow.deviceType,&link,reqMsg,respMsg) == Res_OK)
				{
					uint8_t compareSize = str2uint8(seqResp,respData);
                    if(checkResultUDS(respData,compareSize,respMsg) != Res_OK)
					{
						isContinue = BOOL_TRUE;
						break;
					}
				}
				else
				{
					isContinue = BOOL_TRUE;
					break;
				}
			}
				break;
            case funRequest:
			{
				uint8_t sendData[MAX_BUFF_LEN];
				reqMsg->size = str2uint8(seqRequest,sendData);
			    reqMsg->isFunction = 1;
				memcpy(reqMsg->payload,sendData,reqMsg->size);
				if(sendFuntionalMessage(dataflow.deviceType,&link,reqMsg) != Res_OK)
				{
					isContinue = BOOL_TRUE;
					break;
				}
			}
				break;
			case waitTime:
			{
				char *endPointer;
				long sleepTime = strtol(seqRequest, &endPointer, 10);
                usleep(sleepTime*1000);
			}
				break;
			case securityAccess:
			{
				uint8_t sendData[MAX_BUFF_LEN];
				str2uint8(seqRequest,sendData);
				if(SecurityAccess_27(&link,sendData[1]) != Res_OK)
				{
					isContinue = BOOL_TRUE;
					break;
				}
			}
				break;
			case EraseFlash:
			{
    			memorysize = fileSize;
				if(EraseFlash_31(&link,memoryaddr,memorysize) != Res_OK)
				{
					isContinue = BOOL_TRUE;
					break;
				}  
			}
				break;
			case downloadRequest:
			{
				blocksize = downloadRequest_34(&link,memoryaddr,fileSize);
				if(blocksize == 0)
				{
					isContinue = BOOL_TRUE;
					break;
				}
			}
				break;
			case download:
			{
				if(downloadProcess_36(&link,dataflow.file,blocksize -2) != Res_OK)
				{
					isContinue = BOOL_TRUE;
					break;
				}
			}
				break;
			case checkCRC:
			{
				if(verifyIntegrity_31(&link) != Res_OK)
				{
					initialCRC32Value = 0xFFFFFFFF;
					isContinue = BOOL_TRUE;
					break;
				}
				initialCRC32Value = 0xFFFFFFFF;
			}
				break;
			default:
				break;
		}
		if(isContinue == BOOL_TRUE)
		{
			printf("-----------------------------STOP-----------------------------\n");
            return isContinue;
		}
	}
    return  isContinue;
}

uint8_t executeLinklistTask(struct DiagnosticSeqence diagInfo)
{
	if(connectDevice(diagInfo.deviceType) != Res_OK)
	{
        printf("Device init not successfully\n");
		return;
	}
    printf("Device init successfully\n");

	struct can_iso_tp_init_t *init = NULL;
	init = (struct can_iso_tp_init_t *)malloc(sizeof(struct can_iso_tp_init_t)); 
    init_for_can_iso_tp(0,init,diagInfo.requestID,diagInfo.responseID);

	iso_can_tp_create(&link_iso,init);

	link_iso.devicetype = diagInfo.deviceType;

	struct itimerval timerdoip;

    timerdoip.it_value.tv_sec = 0;
    timerdoip.it_value.tv_usec = 10;

    timerdoip.it_interval.tv_sec = 0;
    timerdoip.it_interval.tv_usec = 50000;
    
	if(diagInfo.deviceType == CAN)
    	signal(SIGALRM,iso_to_poll);
	else if(diagInfo.deviceType == Ethernet)
        //signal(SIGALRM,DoIP_MainFunction);
    setitimer(ITIMER_REAL,&timerdoip,NULL);
    
    uint8_t exeResult = BOOL_FALSE;
    exeResult = testquenceList(link_iso,diagInfo);
	

	// if(DoIP_ReceiveRoutingActive() == Res_OK)
	// {
	// 	testquenceList(link_iso,diagInfo);
	// }
	CAN_Uninitialize(0x51);
    return exeResult;
}

void monitorDirectory()
{
   	DIR *dir;
	struct dirent *entry;
    
    char *folder = "/home/zihaohu/code/diag/qtbuild/task";
    dir = opendir(folder);
    if (dir == NULL) {
        printf("can't open folder\n");
        return 1;
    }

	while ((entry = readdir(dir)) != NULL) {
	if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
        continue;
    }
    if (entry->d_type == 4) {
		char path[1024];
		strcpy(path,folder);
		strcat(path,"/");
		strcat(path,entry->d_name);
		struct Task taskinfo = getTaskInfo(path);
		pthread_mutex_lock(&mutexLinklist);
		insertTaskLinklist(&tasklist,taskinfo);
		int x = pthread_mutex_unlock(&mutexLinklist);
		printf("x = %d\n",x);
		//deleteDirectory(path);
    	}
	}

	int inotifyFd = inotify_init();
    if (inotifyFd == -1) {
        perror("inotify_init");
		return;
    }

    int watchFd = inotify_add_watch(inotifyFd, folder, IN_CREATE | IN_ISDIR);
    if (watchFd == -1) {
        perror("inotify_add_watch");
        return;
    }

    char buffer[1024];

    printf("Monitoring folder: %s\n", folder);

    while (1) {
        ssize_t bytesRead = read(inotifyFd, buffer, 1024);
        if (bytesRead == -1) {
            perror("read");
            //exit(EXIT_FAILURE);
        }

        for (char *ptr = buffer; ptr < buffer + bytesRead;) {
            struct inotify_event *event = (struct inotify_event *)ptr;

            if (event->mask & IN_CREATE) {
                if (event->mask & IN_ISDIR) {
					char path[1024];
					strcpy(path,folder);
					strcat(path,"/");
					strcat(path,event->name);
					pthread_mutex_lock(&mutexLinklist);
					sleep(1);
					struct Task taskinfo = getTaskInfo(path);
					insertTaskLinklist(&tasklist,taskinfo);
					pthread_mutex_unlock(&mutexLinklist);
                    printf("New folder created: %s\n", event->name);
                }
            }

            ptr += EVENT_SIZE + event->len;
        }
    }

    close(inotifyFd);
}

void deleteDirectory(char *dir_name)
{
	struct dirent *dp;

	DIR *dirp = opendir(dir_name);

	while ((dp = readdir(dirp)) != NULL){
	if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
            continue;
        }
	char name[1024];
    
	sprintf(name, "%s/%s", dir_name, dp->d_name);

	remove(name);

	}

	closedir(dirp);
    rmdir(dir_name);
}
