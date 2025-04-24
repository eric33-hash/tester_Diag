#ifndef _ISO_TP_CONFIG_H
#define _ISO_TP_CONFIG_H

#include "./can_iso_tp/can_iso_tp_private.h"
#if defined (WIN32)||defined (_WIN32)
#include "diagTP/PCANBasic.h"
#include "diagTP/vectorCan.h"
#else
#include "src/Ubuntu/libpcanbasic.h"
#endif
#include "memory.h"
#include <time.h>
#include <stdio.h>

static void print_debug_info(const char* msg);

static int L_Data_request(can_iso_tp_link_t_p link_src, const struct CAN_msg* msg);

static void N_USData_indication(can_iso_tp_link_t_p link, const uint8_t mpayload[], uint32_t size, CAN_ISO_TP_RESAULT error);

static void N_USData_confirm(can_iso_tp_link_t_p link, const uint8_t payload[], uint32_t size, CAN_ISO_TP_RESAULT error);

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_BUFF_LEN 4096
 extern uint8_t rx_buff[MAX_BUFF_LEN];
 extern uint8_t payload[MAX_BUFF_LEN];
 extern uint32_t rxSize ;
 extern uint8_t tool;

 extern struct can_iso_tp_link_t link_iso;

 extern void *pclass;

 void init_for_can_iso_tp(int i,struct can_iso_tp_init_t* init,uint32_t req,uint32_t resp,uint8_t cantype);

#ifdef __cplusplus
}
#endif

#endif
