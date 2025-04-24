#ifndef MAINDIAG_H
#define MAINDIAG_H
#ifdef __cplusplus
extern "C"{
#endif __cplusplus
#include <pthread.h>
#include "diagTP/diagio.h"
#include "json/include/cJSON.h"
#include "json/include/parseJson.h"
#include "json/include/diagnosticConfig.h"
#include "executionTask/cycle.h"
#include "uds/mcu_lock/mcu_lock.h"
#include <time.h>

    uint8_t testquenceList(struct can_iso_tp_link_t link,struct DiagnosticSeqence dataflow);

    uint8_t executeLinklistTask(struct DiagnosticSeqence diagInfo);

    void monitorDirectory();

    void deleteDirectory(char *dir_name);

    void* callTask(void* args);

#ifdef __cplusplus
}
#endif __cplusplus

#endif // MAINDIAG_H
