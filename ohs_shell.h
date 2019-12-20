/*
 * ohs_shell.h
 *
 *  Created on: 19. 10. 2018
 *      Author: vysocan
 */

#ifndef OHS_SHELL_H_
#define OHS_SHELL_H_

#include "memstreams.h"

// FRAM on SPI related
#define CMD_25AA_WRSR     0x01  // Write status register
#define CMD_25AA_WRITE    0x02
#define CMD_25AA_READ     0x03
#define CMD_25AA_WRDI     0x04  // Write Disable
#define CMD_25AA_RDSR     0x05  // Read Status Register
#define CMD_25AA_WREN     0x06  // Write Enable
#define CMD_25AA_RDID     0x9F  // Read FRAM ID
#define STATUS_25AA_WEL   0b00000010  // write enable latch (1 == write enable)
//#define STATUS_25AA_WIP   0b00000001  // write in progress
//#define FRAM_SIZE         32768

#define FRAM_MSG_SIZE     16
volatile uint16_t FRAMWritePos = 0;
volatile uint16_t FRAMReadPos  = 0;
#define LOG_TEXT_LENGTH 80
char logText[LOG_TEXT_LENGTH]; // To decode log text
//#define LOG_TS_LENGTH 40
//char logTimestamp[LOG_TS_LENGTH];

// RTC related
static RTCDateTime timespec;
time_t startTime;  // OHS start timestamp variable

// time_t conversion
union time_tag {
  char   ch[4];
  time_t val;
} timeConv;

static void cmd_threads(BaseSequentialStream *chp, int argc, char *argv[]) {
  (void)argv;
  if (argc > 0) {
    shellUsage(chp, "threads");
    return;
  }

  static const char *states[] = {CH_STATE_NAMES};
  thread_t *tp;
  size_t n = 0;
  size_t sz;
  uint32_t used_pct;

  chprintf(chp, "\r\n");
  chprintf(chp, "     begin        end   size   used    %% prio     state         name\r\n");
  chprintf(chp, "--------------------------------------------------------------------\r\n");

  tp = chRegFirstThread();
  do {
     n = 0;
#if (CH_DBG_ENABLE_STACK_CHECK == TRUE) || (CH_CFG_USE_DYNAMIC == TRUE)
    uint32_t stklimit = (uint32_t)tp->wabase;
#else
    uint32_t stklimit = 0U;
#endif

    uint8_t *begin = (uint8_t *)stklimit;
    uint8_t *end = (uint8_t *)tp;
    sz = end - begin;

    while(begin < end)
       if(*begin++ == CH_DBG_STACK_FILL_VALUE) ++n;

    used_pct = (n * 100) / sz;

    chprintf(chp, "0x%08lx 0x%08lx %6u %6u %3u%% %4lu %9s %12s\r\n",
             stklimit, (uint32_t)tp, sz, n, used_pct, (uint32_t)tp->prio, states[tp->state], tp->name == NULL ? "" : tp->name);

    tp = chRegNextThread(tp);
  } while (tp != NULL);

  chprintf(chp, "\r\n");
}

const char text_System[]            = "System";
const char text_started[]           = "started";
const char text_Undefined[]         = "Undefined";
const char text_removed[]           = "removed";
const char text_disabled[]          = "disabled";
const char text_address[]           = "address";
const char text_Address[]           = "Address";
const char text_Group[]             = "Group";
const char text_registration[]      = "registration";
const char text_error[]             = "error";
const char text_registered[]        = "registered";
const char text_is[]                = "is";
const char text_Authentication[]    = "Authentication";
const char text_Sensor[]            = "Sensor";
const char text_Input[]             = "Output"; // :) Input on node is Output to GW
const char text_iButton[]           = "iButton";
const char text_Temperature[]       = "Temperature";
const char text_Humidity[]          = "Humidity";
const char text_Pressure[]          = "Pressure";
const char text_Voltage[]           = "Voltage";
const char text_Battery[]           = "Battery";
const char text_Digital[]           = "Digital";
const char text_Analog[]            = "Analog";
const char text_Float[]             = "Float";
const char text_TX_Power[]          = "TX_Power";
const char text_Gas[]               = "Gas";
const char text_not[]               = "not";
const char text_strength[]          = "strength";
const char text_unknown[]           = "unknown";
const char text_roaming[]           = "roaming";
const char text_searching[]         = "searching";
const char text_network[]           = "network";
const char text_denied[]            = "denied";
const char text_cosp[]              = ", ";
const char text_Modem[]             = "Modem";
const char text_On[]                = "On";
const char text_Off[]               = "Off";
const char text_power[]             = "power";
const char text_monitoring[]        = "monitoring";
const char text_Node[]              = "Node";
const char text_Name[]              = "Name";
const char text_MQTT[]              = "MQTT";
const char text_Function[]          = "Function";
const char text_Type[]              = "Type";
const char text_publish[]           = "publish";
const char text_Last[]              = "Last";
const char text_message[]           = "message";
const char text_Queued[]            = "Queued";
const char text_Value[]             = "Value";
const char text_Number[]            = "Number";
const char text_Email[]             = "Email";
const char text_Global[]            = "Global";
const char text_Contact[]           = "Contact";
const char text_all[]               = "all";
const char text_Key[]               = "Key";


void printNodeType(BaseSequentialStream *chp, const char type) {
  switch(type){
    case 'K': chprintf(chp, "%s", text_Authentication); break;
    case 'S': chprintf(chp, "%s", text_Sensor); break;
    case 'I': chprintf(chp, "%s", text_Input); break;
    default: chprintf(chp, "%s", text_Undefined); break;
  }
}

void printNodeFunction(BaseSequentialStream *chp, const char function) {
  switch(function){
    case 'i': chprintf(chp, "%s", text_iButton); break;
    case 'T': chprintf(chp, "%s", text_Temperature); break;
    case 'H': chprintf(chp, "%s", text_Humidity); break;
    case 'P': chprintf(chp, "%s", text_Pressure); break;
    case 'V': chprintf(chp, "%s", text_Voltage); break;
    case 'B': chprintf(chp, "%s", text_Battery); break;
    case 'D': chprintf(chp, "%s", text_Digital); break;
    case 'A': chprintf(chp, "%s", text_Analog); break;
    case 'F': chprintf(chp, "%s", text_Float); break;
    case 'X': chprintf(chp, "%s", text_TX_Power); break;
    case 'G': chprintf(chp, "%s", text_Gas); break;
    default : chprintf(chp, "%s", text_Undefined); break;
  }
}

void printNodeAddress(BaseSequentialStream *chp, const uint8_t address, const uint8_t number) {
  if (address < RADIO_UNIT_OFFSET) { chprintf(chp, "W:%u:%u ", address, number); }
  else                             { chprintf(chp, "R:%u:%u ", address-RADIO_UNIT_OFFSET, number); }
}

void printFrmTimestamp(BaseSequentialStream *chp, time_t *value) {
  struct tm *ptm;
  char   dateTime[30];

  ptm = gmtime(value);
  // Check if return is 0 then format is invalid
  if (strftime(dateTime, 30, conf.dateTimeFormat, ptm) != 0) chprintf(chp, "%s", dateTime);
  else chprintf(chp, "%s", text_unknown);
}

/*
 * helper function
 */
void SetTimeUnixSec(time_t unix_time) {
  struct tm tim;
  struct tm *canary;

  /* If the conversion is successful the function returns a pointer
     to the object the result was written into.*/
  canary = localtime_r(&unix_time, &tim);
  osalDbgCheck(&tim == canary);

  rtcConvertStructTmToDateTime(&tim, 0, &timespec);
  rtcSetTime(&RTCD1, &timespec);
}
time_t GetTimeUnixSec(void) {
  struct tm timestamp;

  rtcGetTime(&RTCD1, &timespec);
  rtcConvertDateTimeToStructTm(&timespec, &timestamp, NULL);
  return mktime(&timestamp);
}

/*
 * Decode log entries to string
 */
static void decodeLog(char *in, char *out){
  memset(&out[0], 0x0, LOG_TEXT_LENGTH);

  MemoryStream ms;
  BaseSequentialStream *chp;
  /* Memory stream object to be used as a string writer, reserving one
     byte for the final zero.*/
  msObjectInit(&ms, (uint8_t *)out, LOG_TEXT_LENGTH-1, 0);
  /* Performing the print operation using the common code.*/
  chp = (BaseSequentialStream *)(void *)&ms;
  //out = (char *)&ms.buffer; -- not needed to reroute

  switch(in[0]){
    case 'S': // System
      chprintf(chp, "%s ", text_System);
      switch(in[1]){
        case 's': chprintf(chp, "%s", text_started); break; // boot
        case 'S': chprintf(chp, "%s %s", text_monitoring, text_started); break; // Zone thread start
        default:  chprintf(chp, "%s", text_unknown); break; // unknown
      }
    break;
    case 'N': // remote nodes
      printNodeType(chp, in[4]); chprintf(chp, ":");
      printNodeFunction(chp, in[5]);
      chprintf(chp, " %s ", text_address);
      printNodeAddress(chp, (uint8_t)in[2], (uint8_t)in[3]);
      if (in[1] != 'E') {chprintf(chp, "%s ", text_is);}
      switch(in[1]){
        case 'F' : chprintf(chp, "%s", text_disabled); break;
        case 'R' : chprintf(chp, "%s", text_registered); break;
        case 'r' : chprintf(chp, "%s", text_removed); break;
        default : chprintf(chp, "%s %s", text_registration, text_error); break; // 'E'
      }
    break;
    case 'M': // Modem
      chprintf(chp, "%s ", text_Modem);
      if ((uint8_t)in[1] <= 5) {
        chprintf(chp, "%s ", text_network);
        switch(in[1]){
          case 0 : chprintf(chp, "%s %s", text_not, text_registered); break;
          case 1 : chprintf(chp, "%s", text_registered); break;
          case 2 : chprintf(chp, "%s", text_searching); break;
          case 3 : chprintf(chp, "%s %s", text_registration, text_denied); break;
          case 5 : chprintf(chp, "%s", text_roaming); break;
          default : chprintf(chp, "%s", text_unknown); break; // 4 = unknown
        }
        chprintf(chp, "%s%s %u%%", text_cosp, text_strength, (uint8_t)in[2]);
      } else {
        chprintf(chp, "%s ", text_power);
        switch(in[1]){
          case 'O' : chprintf(chp, "%s", text_On); break;
          case 'F' : chprintf(chp, "%s", text_Off); break;
          default : chprintf(chp, "%s", text_unknown); break;
        }
      }
    break;
    default: chprintf(chp, "%s", text_Undefined);
      for(uint16_t ii = 0; ii < LOGGER_MSG_LENGTH; ii++) {
        chprintf(chp, ", %c-%x", in[ii], in[ii]);
      }
    break; // unknown
  }
  chprintf(chp, "."); // "." as end
}

/*
 * Console applet to show log entries
 */
#define LOGGER_OUTPUT_LEN 15
static void cmd_log(BaseSequentialStream *chp, int argc, char *argv[]) {
  (void)argv;

  char   rxBuffer[FRAM_MSG_SIZE];
  char   txBuffer[3];

  if (argc > 1)  { goto ERROR; }
  if (argc == 1) { FRAMReadPos = (atoi(argv[0]) - LOGGER_OUTPUT_LEN + 1) * FRAM_MSG_SIZE; }
  if (argc == 0) { FRAMReadPos = FRAMWritePos - (FRAM_MSG_SIZE * LOGGER_OUTPUT_LEN); }

  for(uint16_t i = 0; i < LOGGER_OUTPUT_LEN; i++) {
    txBuffer[0] = CMD_25AA_READ;
    txBuffer[1] = (FRAMReadPos >> 8) & 0xFF;
    txBuffer[2] = FRAMReadPos & 0xFF;

    spiAcquireBus(&SPID1);              // Acquire ownership of the bus.
    spiSelect(&SPID1);                  // Slave Select assertion.
    spiSend(&SPID1, 3, txBuffer);       // Send read command
    spiReceive(&SPID1, FRAM_MSG_SIZE, rxBuffer);
    spiUnselect(&SPID1);                // Slave Select de-assertion.
    spiReleaseBus(&SPID1);              // Ownership release.

    memcpy(&timeConv.ch[0], &rxBuffer[0], sizeof(timeConv.ch)); // Prepare timestamp
    decodeLog(&rxBuffer[4], logText);

    chprintf(chp, "#%d\t", (FRAMReadPos/FRAM_MSG_SIZE));
    printFrmTimestamp(chp, &timeConv.val);
    chprintf(chp, " : %s", logText);
    chprintf(chp, " Flags: %x\r\n", rxBuffer[FRAM_MSG_SIZE-1]);
    chThdSleepMilliseconds(2);

    FRAMReadPos+=FRAM_MSG_SIZE; // Advance for next read
  }
  return;

ERROR:
  chprintf(chp, "Usage: log\r\n");
  chprintf(chp, "       log N - where N is log last entry point\r\n");
  return;
}

/*
 * Console applet for date set and get
 */
static void cmd_date(BaseSequentialStream *chp, int argc, char *argv[]) {
  (void)argv;
  struct tm *ptm;
  char   dateTime[30];
  time_t unix_time;

  if (argc == 0) {
    unix_time = GetTimeUnixSec();

    if (unix_time == -1){
      chprintf(chp, "Incorrect time in RTC cell.\r\n");
    }
    else{
      ptm = gmtime(&unix_time);
      strftime(dateTime, 30, conf.dateTimeFormat, ptm); // Format date time as needed
      chprintf(chp, "Current: %d\t", unix_time);
      chprintf(chp, "%s\r\n", dateTime);
    }
    return;
  }

  if ((argc == 2) && (strcmp(argv[0], "set") == 0)){
    unix_time = atol(argv[1]);
    if (unix_time > 0){
      SetTimeUnixSec(unix_time);
      return;
    }
    else{
      goto ERROR;
    }
  }
  else{
    goto ERROR;
  }

ERROR:
  chprintf(chp, "Usage: date\r\n");
  chprintf(chp, "       date set N\r\n");
  chprintf(chp, "where N is time in seconds sins Unix epoch\r\n");
  chprintf(chp, "you can get current N value from unix console by the command:\r\n");
  chprintf(chp, "%s", "date +\%s\r\n");
  return;
}

// Routing console to USB
static void cmd_debug(BaseSequentialStream *chp, int argc, char *argv[]) {
  (void)argv;

  if (argc != 1) {
    chprintf(chp, "Usage: debug on/off\r\n");
    return;
  }
  // Reroute all console to USB
  if ((argc == 1) && (strcmp(argv[0], "on") == 0)){
    console = (BaseSequentialStream*)&SDU1;
  }

  // Reroute all console back to SD3
  if ((argc == 1) && (strcmp(argv[0], "off") == 0)){
    console = (BaseSequentialStream*)&SD3;
    chprintf(chp, "\r\nstopped\r\n");
  }
}

/*
 *
 */
static const ShellCommand commands[] = {
  {"date",  cmd_date},
  {"log",  cmd_log},
  {"threads",  cmd_threads},
  {"debug",  cmd_debug},
  {NULL, NULL}
};

/*
 *
 */
/*static const ShellConfig shell_cfg1 = {
  (BaseSequentialStream  *)&SD3,
  commands
};*/

static const ShellConfig shell_cfg1 = {
  (BaseSequentialStream *)&SDU1,
  commands
};

/*
 * working area for shell thread
 */
#define SHELL_WA_SIZE   THD_WORKING_AREA_SIZE(2048)
//static THD_WORKING_AREA(waShell, 2048);


#endif /* OHS_SHELL_H_ */
