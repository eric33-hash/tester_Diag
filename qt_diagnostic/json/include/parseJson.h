#ifndef PARSEJSON_H_
#define PARSEJSON_H_

#include <stdint.h>
#include <stdio.h>
#include "cJSON.h"
#include <time.h>
#include <errno.h>

#ifdef __cplusplus
extern "C" {
#endif
struct DiagnosticSeqence{
    char* file;
    cJSON* sequence;
    int requestID;
    int responseID;
    unsigned char deviceType;
    long Flashaddr;
    uint8_t cantype;
    uint8_t flashcount;
};

struct DiagnosticTaskInfo
{
    char *name;
    unsigned char source;
    unsigned char *taskType;
    struct {
        unsigned char cycle;
        time_t startTime;
        time_t endTime;
    }PeriodicTasks;
    char *documentation;
};

struct Task
{
    struct DiagnosticSeqence sequence;
    struct DiagnosticTaskInfo taskInfo;
};



time_t string2time(char *stringTime);

extern struct DiagnosticSeqence parseSequence(char *file,int flag);

inline struct DiagnosticTaskInfo parseTaskInfo(char *file);

extern struct Task getTaskInfo(char *file);

extern uint8_t str2uint8(char *str,uint8_t *array);

#ifdef __cplusplus
}
#endif

#endif
