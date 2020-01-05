/*
 * Copyright (c) 2001-2003 Swedish Institute of Computer Science.
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 * 
 * Author: Simon Goldschmidt
 *
 */
#ifndef LWIP_HDR_LWIPOPTS_H__
#define LWIP_HDR_LWIPOPTS_H__

/* rand() */
#include <stdlib.h>
#include <hal.h>

/* Fixed settings mandated by the ChibiOS integration.*/
#include "static_lwipopts.h"

/* Optional, application-specific settings.*/
#if !defined(TCPIP_MBOX_SIZE)
#define TCPIP_MBOX_SIZE                 MEMP_NUM_PBUF
#endif
#if !defined(TCPIP_THREAD_STACKSIZE)
#define TCPIP_THREAD_STACKSIZE          2048
#endif

/* Use ChibiOS specific priorities. */
#if !defined(TCPIP_THREAD_PRIO)
#define TCPIP_THREAD_PRIO               (LOWPRIO + 1)
#endif
#if !defined(LWIP_THREAD_PRIORITY)
#define LWIP_THREAD_PRIORITY            (LOWPRIO)
#endif

/* DNS */

#define LWIP_RAND() ((uint32_t)rand())
#define LWIP_DNS 1


//#define LWIP_DHCP 1

/*
 * LWIP DEBUG
 */

#define LWIP_DEBUG LWIP_DBG_ON
//#define ETHARP_DEBUG LWIP_DBG_ON
//#define NETIF_DEBUG LWIP_DBG_ON
//#define ICMP_DEBUG LWIP_DBG_ON
//#define IP_DEBUG LWIP_DBG_ON


/* SNTP */
//#define SNTP_DEBUG LWIP_DBG_ON

#define SNTP_SERVER_DNS 1
#define SNTP_SERVER_ADDRESS "195.113.144.201"
//#define SNTP_SERVER_ADDRESS "10.10.10.254"
#define SNTP_UPDATE_DELAY 900000 // SNTP update every 90 seconds

#define MEMP_NUM_SYS_TIMEOUT 6
#define MEMP_NUM_UDP_PCB 6


//ChibiOS RTC drivers
/* old
#define SNTP_SET_SYSTEM_TIME(sec) rtcSetTimeUnixSec(&RTCD1, (sec))
*/

/*
void SetTimeUnixA(time_t ut){
  RTCDateTime _ts;
  struct tm* _pt;

  _pt = gmtime(&ut);
  rtcConvertStructTmToDateTime( _pt, 0, &_ts);
  rtcSetTime(&RTCD1, &_ts);
}
*/
#define SNTP_SET_SYSTEM_TIME(sec) \
  do{time_t rawtime = (sec);\
     RTCDateTime _ts;\
     struct tm* _pt;\
     _pt = gmtime(&rawtime);\
     rtcConvertStructTmToDateTime(_pt, 0, &_ts);\
     rtcSetTime(&RTCD1, &_ts);}while(0)



/* old
#define SNTP_GET_SYSTEM_TIME(sec, us) \
    do{uint64_t time = rtcGetTimeUnixUsec(&RTCD1);\
       (sec) = time / 1000000;\
       (us) = time % 1000000;}while(0)
*/
/*
#define SNTP_GET_SYSTEM_TIME(sec, us) \
    do{struct tm timestamp;\
       rtcGetTime(&RTCD1, &timespec);\
       rtcConvertDateTimeToStructTm(&timespec, &timestamp, NULL);\
       uint64_t time = mktime(&timestamp);\
       (sec) = time / 1000000;\
       (us) = time % 1000000;}while(0)
*/

#endif /* LWIP_HDR_LWIPOPTS_H__ */
