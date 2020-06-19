/*
 * ohs_shell.h
 *
 *  Created on: 19. 10. 2018
 *      Author: vysocan
 */

#ifndef OHS_SHELL_H_
#define OHS_SHELL_H_

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

// FRAM buffers for decode
static char rxBuffer[FRAM_MSG_SIZE];
static char txBuffer[3];

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
  chprintf(chp, "   begin      end   size   used    %% prio     state         name\r\n");
  chprintf(chp, "--------------------------------------------------------------\r\n");

  tp = chRegFirstThread();
  do {
     n = 0;
#if (CH_DBG_ENABLE_STACK_CHECK == TRUE) || (CH_CFG_USE_DYNAMIC == TRUE)
    uint32_t stklimit = (uint32_t)tp->wabase;
#else
    uint32_t stklimit = 0U;
#endif

    uint8_t *begin = (uint8_t *)stklimit;
    //uint8_t *begin = (uint32_t)tp->ctx.sp;
    uint8_t *end = (uint8_t *)tp;
    sz = end - begin;

    while(begin < end) {
      if(*begin++ == CH_DBG_STACK_FILL_VALUE) ++n;
    }

    used_pct = (n * 100) / sz;

    chprintf(chp, "%08lx %08lx %6u %6u %3u%% %4lu %9s %12s\r\n",
             stklimit, (uint32_t)tp, sz, n, used_pct, (uint32_t)tp->prio, states[tp->state], tp->name == NULL ? "" : tp->name);

    tp = chRegNextThread(tp);
  } while (tp != NULL);

  chprintf(chp, "\r\n");
}

const char weekNumber[][7] = {
// 12345678901234567890
  "Last",
  "First",
  "Second",
  "Third",
  "Fourth"
};

const char weekDay[][10] = {
// 12345678901234567890
  "Monday",
  "Tuesday",
  "Wednesday",
  "Thursday",
  "Friday",
  "Saturday",
  "Sunday"
};

const char weekDayShort[][3] = {
  "Mo", "Tu", "We", "Th", "Fr", "Sa", "Su"
};

const char monthName[][4] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

const char durationSelect[][10] = {
// 12345678901234567890
  "second(s)",
  "minute(s)",
  "hour(s)",
  "day(s)"
};

const char text_System[]            = "System";
const char text_info[]              = "information";
const char text_started[]           = "started";
const char text_Undefined[]         = "Undefined";
const char text_removed[]           = "removed";
const char text_disabled[]          = "disabled";
const char text_address[]           = "address";
const char text_Address[]           = "Address";
const char text_Group[]             = "Group";
const char text_group[]             = "group";
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
const char text_voltage[]           = "voltage";
const char text_Battery[]           = "Battery";
const char text_RTC[]               = "RTC";
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
const char text_1[]                 = "1";
const char text_2[]                 = "2";
const char text_3[]                 = "3";
const char text_4[]                 = "4";
const char text_0x[]                = "0x";
const char text_1x[]                = "1x";
const char text_2x[]                = "2x";
const char text_3x[]                = "3x";
const char text_power[]             = "power";
const char text_monitoring[]        = "monitoring";
const char text_Node[]              = "Node";
const char text_Name[]              = "Name";
const char text_name[]              = "name";
const char text_MQTT[]              = "MQTT";
const char text_Function[]          = "Function";
const char text_Type[]              = "Type";
const char text_type[]              = "type";
const char text_publish[]           = "publish";
const char text_Last[]              = "Last";
const char text_message[]           = "message";
const char text_Queued[]            = "Queued";
const char text_Value[]             = "Value";
const char text_Number[]            = "Number";
const char text_Email[]             = "Email";
const char text_Global[]            = "Global";
const char text_Contact[]           = "Contact";
const char text_User[]              = "User";
const char text_all[]               = "all";
const char text_Key[]               = "Key";
const char text_Open[]              = "Open";
const char text_alarm[]             = "alarm";
const char text_Alarm[]             = "Alarm";
const char text_as[]                = "as";
const char text_tamper[]            = "tamper";
const char text_Delay[]             = "Delay";
const char text_OK[]                = "OK";
const char text_Status[]            = "Status";
const char text_remote[]            = "remote";
const char text_local[]             = "local";
const char text_battery[]           = "battery";
const char text_analog[]            = "analog";
const char text_digital[]           = "digital";
//const char text_seconds[]           = "second(s)";
//const char text_hours[]             = "hour(s)";
//const char text_days[]              = "day(s)";
const char text_Zone[]              = "Zone";
const char text_zone[]              = "zone";
const char text_delay[]             = "delay";
const char text_SMS[]               = "SMS";
const char text_Page[]              = "Page";
const char text_disarmed[]          = "disarmed";
const char text_armed[]             = "armed";
const char text_auto[]              = "auto";
const char text_open[]              = "open";
const char text_allowed[]           = "allowed";
const char text_matched[]           = "matched";
const char text_re[]                = "re";
const char text_Date[]              = "Date";
const char text_Entry[]             = "Entry";
const char text_Alert[]             = "Alert";
const char text_key[]               = "key";
const char text_value[]             = "value";
const char text_once[]              = "once";
const char text_after[]             = "after";
const char text_always[]            = "always";
const char text_constant[]          = "constant";
const char text_Armed[]             = "Armed";
const char text_Arm[]               = "Arm";
const char text_arm[]               = "arm";
const char text_Disarm[]            = "Disarm";
const char text_chain[]             = "chain";
const char text_trigger[]           = "trigger";
const char text_Trigger[]           = "Trigger";
const char text_Auto[]              = "Auto";
const char text_Tamper[]            = "Tamper";
const char text_relay[]             = "relay";
const char text_home[]              = "home";
const char text_away[]              = "away";
const char text_Time[]              = "Time";
const char text_time[]              = "time";
const char text_Start[]             = "Start";
const char text_Up[]                = "Up";
const char text_AC[]                = "AC";
const char text_Register[]          = "Register";
const char text_Signal[]            = "Signal";
const char text_Alive[]             = "Alive";
const char text_Admin[]             = "Admin";
const char text_user[]              = "user";
const char text_Password[]          = "Password";
const char text_password[]          = "password";
const char text_SMTP[]              = "SMTP";
const char text_NTP[]               = "NTP";
const char text_Radio[]             = "Radio";
const char text_Frequency[]         = "Frequency";
const char text_Server[]            = "Server";
const char text_port[]              = "port";
const char text_of[]                = "of";
const char text_at[]                = "at";
const char text_offset[]            = "offset";
const char text_end[]               = "end";
const char text_start[]             = "start";
const char text_DS[]                = "Daylight saving";
const char text_Standard[]          = "Standard";
//const char text_minutes[]           = "minute(s)";
const char text_format[]            = "format";
const char text_oclock[]            = "o'clock";
const char text_Balanced[]          = "Balanced";
const char text_balanced[]          = "balanced";
const char text_low[]               = "low";
const char text_state[]             = "state";
const char text_Blocks[]            = "Blocks";
const char text_Entries[]           = "Entries";
const char text_Used[]              = "Used";
const char text_Free[]              = "Free";
const char text_Total[]             = "Total";
const char text_Metric[]            = "Metric";
const char text_Hash[]              = "Hash";
const char text_Period[]            = "Period";
const char text_Run[]               = "Run";
const char text_Script[]            = "Script";
const char text_Next[]              = "Next";
const char text_on[]                = "on";
const char text_off[]               = "off";
const char text_Calendar[]          = "Calendar";
const char text_Duration[]          = "Duration";
const char text_duration[]          = "duration";
const char text_Timer[]             = "Timer";
const char text_timer[]             = "timer";
const char text_kB[]                = "kB";
const char text_Heap[]              = "Heap";
const char text_heap[]              = "heap";
const char text_Storage[]           = "Storage";
const char text_storage[]           = "storage";
const char text_Fragmentation[]     = "Fragmentation";
const char text_Evaluate[]          = "Evaluate";
const char text_script[]            = "script";
const char text_Result[]            = "Result";
const char text_linked_to[]         = "linked to";
const char text_Condition[]         = "Condition";
const char text_Hysteresis[]        = "Hysteresis";
const char text_Pass[]              = "Pass";
const char text_To[]                = "To";
const char text_queue[]             = "queue";
const char text_full[]              = "full";
const char text_Registration[]      = "Registration";
const char text_not_found[]         = "not found";
const char text_activated[]         = "activated";
const char text_error_free[]        = "Not enough free space in ";

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

void printNodeAddress(BaseSequentialStream *chp, const uint8_t address, const char type,
                      const char function, const uint8_t number, const bool printName) {
  uint8_t nodeIndex = 0;
  // If address is defined
  if (address) {
    if (address < RADIO_UNIT_OFFSET) { chprintf(chp, "W:%u:", address); }
    else                             { chprintf(chp, "R:%u:", address-RADIO_UNIT_OFFSET); }
    chprintf(chp, "%c:%c:%u - ", type, function, number);
    if (printName) {
      nodeIndex = getNodeIndex(address, type, function, number);
      if (nodeIndex != DUMMY_NO_VALUE) chprintf(chp, "%s ", node[nodeIndex].name);
      else chprintf(chp, "%s ", text_not_found);
    }
  } else {
    chprintf(chp, "%s", NOT_SET);
  }
}

void printFrmTimestamp(BaseSequentialStream *chp, time_t *value) {
  struct tm *ptm;
  char   dateTime[30];

  ptm = gmtime(value);
  // Check if return is 0 then format is invalid
  if (strftime(dateTime, 30, conf.dateTimeFormat, ptm) != 0) chprintf(chp, "%s", dateTime);
  else chprintf(chp, "%s", text_unknown);
}

void printFrmUpTime(BaseSequentialStream *chp, time_t *value) {
  uint16_t days = *value / (time_t)SECONDS_PER_DAY;
  *value -= (days * (time_t)SECONDS_PER_DAY);
  uint8_t hours = *value / (time_t)SECONDS_PER_HOUR;
  *value -= (hours * (time_t)SECONDS_PER_HOUR);
  uint8_t minutes = *value / (time_t)SECONDS_PER_MINUTE;
  *value -= (minutes * (time_t)SECONDS_PER_MINUTE);

  chprintf(chp, "%u day(s), %02u:%02u:%02u", days, hours, minutes, (uint32_t)*value);
}

void printKey(BaseSequentialStream *chp, const char *value){
  for (uint8_t i = KEY_LENGTH; i > 0 ; i--) {
    chprintf(chp, "%02x", value[i - 1]);
  }
}

void printGroup(BaseSequentialStream *chp, const uint8_t value) {
  if (value < ALARM_GROUPS) {
    chprintf(chp, "%u. %s ", value + 1, conf.groupName[value]);
  } else chprintf(chp, "%s ", NOT_SET);
}

void printZone(BaseSequentialStream *chp, const uint8_t value) {
  if (value < ALARM_ZONES) {
    chprintf(chp, "%u. %s ", value + 1, conf.zoneName[value]);
  } else chprintf(chp, "%s ", NOT_SET);
}

/*
 * Decode log entries to string
 * full: decode full string or just short version for alerts.html
 */
static uint8_t decodeLog(char *in, char *out, bool full){
  uint8_t groupNum = DUMMY_NO_VALUE;
  memset(&out[0], 0x0, LOG_TEXT_LENGTH);
  MemoryStream ms;
  BaseSequentialStream *chp;
  // Memory stream object to be used as a string writer, reserving one byte for the final zero.
  msObjectInit(&ms, (uint8_t *)out, LOG_TEXT_LENGTH-1, 0);
  // Performing the print operation using the common code.
  chp = (BaseSequentialStream *)(void *)&ms;


  switch(in[0]){
    case 'S': // System
      chprintf(chp, "%s ", text_System);
      switch(in[1]){
        case 's': chprintf(chp, "%s", text_started); break; // boot
        case 'S': chprintf(chp, "%s %s", text_monitoring, text_started); break; // Zone thread start
        case 'X': chprintf(chp, "%s", text_alarm);
          if (full) chprintf(chp, "! %s %u.%s", text_Group, (uint8_t)in[2] + 1, conf.groupName[(uint8_t)in[2]]);
          groupNum = (uint8_t)in[2];
          break;
        case 'B': chprintf(chp, "%s ", text_battery);
          if (full) {
            switch(in[2]){
              case 'L': chprintf(chp, "%s", text_low); break;
              default:  chprintf(chp, "%s", text_OK); break;
            }
          } else {
            chprintf(chp, " %s", text_state);
          }
          break;
        case 'A': chprintf(chp, "%s ", text_power);
          if (full) {
            switch(in[2]){
              case 'L': chprintf(chp, "%s", text_Off); break;
              default:  chprintf(chp, "%s", text_On); break;
            }
          } else {
            chprintf(chp, " %s", text_state);
          }
          break;
        case 'R': chprintf(chp, "%s %s ", text_RTC, text_battery);
          if (full) {
            switch(in[2]){
              case 'L': chprintf(chp, "%s", text_low); break;
              default:  chprintf(chp, "%s", text_OK); break;
            }
          } else {
            chprintf(chp, " %s", text_state);
          }
          break;
        default: chprintf(chp, "%s", text_unknown); break; // unknown
      }
    break;
    case 'N': // Remote nodes
      printNodeType(chp, in[3]); chprintf(chp, ":");
      printNodeFunction(chp, in[4]);
      chprintf(chp, " %s ", text_address);
      printNodeAddress(chp, (uint8_t)in[2], (uint8_t)in[3], (uint8_t)in[4], (uint8_t)in[5], false);
      if (in[1] != 'E') {chprintf(chp, "%s ", text_is);}
      switch(in[1]){
        case 'Z' : chprintf(chp, "%s", text_removed); break;
        case 'F' : chprintf(chp, "%s", text_disabled); break;
        case 'R' : chprintf(chp, "%s", text_registered); break;
        case 'r' : chprintf(chp, "%s%s", text_re, text_registered); break;
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
          default : chprintf(chp, "%s", text_error); break;
        }
      }
    break;
    case 'G': // Group related
      chprintf(chp, "%s ", text_Group);
      if (full) {
        printGroup(chp, (uint8_t)in[2]);
      }
      switch(in[1]){
        case 'F': chprintf(chp, "%s %s", text_is, text_disabled); break;
        case 'S': chprintf(chp, "%s", text_armed); break;
        case 'D': chprintf(chp, "%s", text_disarmed); break;
        case 'A': chprintf(chp, "%s %s", text_auto, text_armed); break;
        default: chprintf(chp, "%s", text_unknown); break;
      }
      groupNum = (uint8_t)in[2];
    break;
    case 'Z': // Zone
      chprintf(chp, "%s ", text_Zone);
      if (full) {
        if ((uint8_t)in[2] < ALARM_ZONES) {
          chprintf(chp, "%u %s ", (uint8_t)in[2] + 1, conf.zoneName[(uint8_t)in[2]]);
        } else {
          chprintf(chp, "%s ", text_unknown);
        }
      }
      switch(in[1]){
        case 'P': chprintf(chp, "%s", text_alarm); break;
        case 'T': chprintf(chp, "%s", text_tamper); break;
        case 'O': chprintf(chp, "%s", text_open); break;
        case 'R': chprintf(chp, "%s", text_registered); break;
        case 'r': chprintf(chp, "%s%s", text_re, text_registered); break;
        case 'E': chprintf(chp, "%s %s", text_registration, text_error); break;
        case 'e': chprintf(chp, "%s, %s %s ", text_error, text_address, text_not);
          switch(in[3]){
            case 'M': chprintf(chp, "%s", text_matched); break;
            default : chprintf(chp, "%s", text_allowed); break;
          }
        break;
        default: chprintf(chp, "%s", text_unknown); break;
      }
      groupNum = GET_CONF_ZONE_GROUP((uint8_t)in[2]);
    break;
    case 'A': // Authentication
      chprintf(chp, "%s ", text_Key);
      if (full) {
        if (in[1] != 'U') {
          chprintf(chp, "#%u, %s ", (uint8_t)in[2] + 1, text_linked_to);
          if (conf.keyContact[(uint8_t)in[2]] == DUMMY_NO_VALUE) chprintf(chp, "%s ", NOT_SET);
          else chprintf(chp, "%s ", conf.contactName[(conf.keyContact[(uint8_t)in[2]])]);
          groupNum = GET_CONF_CONTACT_GROUP(conf.keyContact[(uint8_t)in[2]]);
        }
      }
      switch(in[1]){
        case 'D': chprintf(chp, "%s", text_disarmed); break;
        case 'A': chprintf(chp, "%s %s", text_armed, text_away); break;
        case 'H': chprintf(chp, "%s %s", text_armed, text_home); break;
        case 'U': chprintf(chp, "%s %s ", text_is, text_unknown);
          if (full) {
            printKey(chp, &in[2]);
          }
          break;
        case 'F': chprintf(chp, "%s %s", text_is, text_disabled); break;
        default : chprintf(chp, "%s", text_unknown); break;
      }

    break;
    case 'F': // Fifos
      switch(in[1]){
        case 'S' : chprintf(chp, "%s", text_Sensor); break;
        case 'T' : chprintf(chp, "%s", text_Trigger); break;
        case 'R' : chprintf(chp, "%s", text_Registration); break;
        case 'A' : chprintf(chp, "%s", text_Alarm); break;
        case 'N' : chprintf(chp, "%s", text_Node); break;
        default : chprintf(chp, "%s", text_unknown); break;
      }
      chprintf(chp, " %s %s", text_queue, text_full);
    break;
    case 'R': // Triggers
      chprintf(chp, "%s %u. %s", text_Trigger, (uint8_t)in[2], conf.trigger[(uint8_t)in[2]].name);
      switch(in[1]){
        case 'A' : chprintf(chp, "%s", text_activated); break;
        case 'N' : chprintf(chp, "de%s", text_activated); break;
        default : chprintf(chp, "%s", text_unknown); break;
      }
      chprintf(chp, " %s %s", text_queue, text_full);
    break;
    default: chprintf(chp, "%s", text_Undefined);
      for(uint16_t ii = 0; ii < LOGGER_MSG_LENGTH; ii++) {
        chprintf(chp, "-%x", in[ii], in[ii]);
      }
    break; // unknown
  }
  //chprintf(chp, "."); // "." as end

  return groupNum;
}

/*
 * Console applet to show log entries
 */
#define LOGGER_OUTPUT_LEN 20
static void cmd_log(BaseSequentialStream *chp, int argc, char *argv[]) {
  (void)argv;

  if (argc > 1)  { goto ERROR; }
  if (argc == 1) { FRAMReadPos = (atoi(argv[0]) - LOGGER_OUTPUT_LEN + 1) * FRAM_MSG_SIZE; }
  if (argc == 0) { FRAMReadPos = FRAMWritePos - (FRAM_MSG_SIZE * LOGGER_OUTPUT_LEN); }

  spiAcquireBus(&SPID1);              // Acquire ownership of the bus.
  for(uint16_t i = 0; i < LOGGER_OUTPUT_LEN; i++) {
    txBuffer[0] = CMD_25AA_READ;
    txBuffer[1] = (FRAMReadPos >> 8) & 0xFF;
    txBuffer[2] = FRAMReadPos & 0xFF;

    spiSelect(&SPID1);                  // Slave Select assertion.
    spiSend(&SPID1, 3, txBuffer);       // Send read command
    spiReceive(&SPID1, FRAM_MSG_SIZE, rxBuffer);
    spiUnselect(&SPID1);                // Slave Select de-assertion.

    memcpy(&timeConv.ch[0], &rxBuffer[0], sizeof(timeConv.ch)); // Prepare timestamp
    decodeLog(&rxBuffer[4], logText, true);

    chprintf(chp, "#%d\t", (FRAMReadPos/FRAM_MSG_SIZE));
    printFrmTimestamp(chp, &timeConv.val);
    chprintf(chp, " : %s", logText);
    chprintf(chp, " Flags: %x\r\n", rxBuffer[FRAM_MSG_SIZE-1]);

    FRAMReadPos+=FRAM_MSG_SIZE; // Advance for next read
  }
  spiReleaseBus(&SPID1);              // Ownership release.
  return;

ERROR:
  shellUsage(chp, "log\r\n       log N - where N is log last entry point");
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
    unix_time = getTimeUnixSec();

    if (unix_time == -1){
      chprintf(chp, "Incorrect time in RTC cell.\r\n");
    }
    else{
      ptm = gmtime(&unix_time);
      strftime(dateTime, 30, conf.dateTimeFormat, ptm); // Format date time as needed
      chprintf(chp, "Current: %d %s,", unix_time, &durationSelect[0][0]);
      chprintf(chp, "%s\r\n", dateTime);
    }
    return;
  }

  if ((argc == 2) && (strcmp(argv[0], "set") == 0)){
    unix_time = atol(argv[1]);
    if (unix_time > 0){
      // TODO OHS Check if to remove the setTimeUnixSec
      //setTimeUnixSec(unix_time);
      convertUnixSecondToRTCDateTime(&timespec, unix_time);
      rtcSetTime(&RTCD1, &timespec);
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

  if (argc == 1) {
    if (strcmp(argv[0], "on") == 0) {
      // Reroute all console to USB
      console = (BaseSequentialStream*)&SDU1;
      return;
    } else if (strcmp(argv[0], "off") == 0) {
      // Reroute all console back to SD3
      console = (BaseSequentialStream*)&SD3;
      chprintf(chp, "\r\nstopped\r\n");
      return;
    }
  }
  // Rest is error
  shellUsage(chp, "debug on|off");
}

// Routing console to USB
static void cmd_ubs(BaseSequentialStream *chp, int argc, char *argv[]) {
  (void)argv;

  if (argc == 1) {
    switch (argv[0][0]) {
      case 's':
        chprintf(chp, "uBS     total    free    used\r\n");
        chprintf(chp, "blocks: %5u   %5u   %5u\r\n", UBS_BLOCK_COUNT, uBSFreeBlocks,
                 UBS_BLOCK_COUNT - uBSFreeBlocks);
        chprintf(chp, "space:  %5u   %5u   %5u\r\n", UBS_SPACE_MAX, uBSFreeSpace,
                 UBS_SPACE_MAX - uBSFreeSpace);
        break;
      case 'f':
        uBSFormat();
        uBSInit();
        chprintf(chp, "uBS formated and re-initialized.\r\n");
        break;
      default: goto ERROR;
        break;
    }
  } else goto ERROR;

  return;

  ERROR:
    shellUsage(chp, "ubs status|format");
}

// Commands
static const ShellCommand commands[] = {
  {"date",  cmd_date},
  {"log",  cmd_log},
  {"mythreads",  cmd_threads},
  {"debug",  cmd_debug},
  {"ubs",  cmd_ubs},
  {NULL, NULL}
};

static const ShellConfig shell_cfg = {
  (BaseSequentialStream *)&SDU1,
  commands
};

#endif /* OHS_SHELL_H_ */
