
/*
Comm. (Protocol):	UART
Baud rate:	9600
Interval Between Consecutive Commands:	100[ms]
UART voltage:		12V
*/

// Header params
#define START 0x55
#define SRC_ID 0x11
#define SNK_ID 0x22
#define END 0xAA

// read info
#define LEN_READ 9 // max 12
#define BASIC_INFO    0xA1
#define CELL_INFO     0xA2
#define CELL_BALANCE  0xA3
#define CTRL_STATUS   0xA4
#define UTILITY       0xA5

// write info
#define MOS_CTRL        0xB1
#define NNCAP_CONFIG    0xB2
#define CYCAP_CONFIG    0xB3
#define FULL_CELL_VOLT  0xB4
#define END_CELL_VOLT   0xB5
#define TEMP_CTRL       0xB6

#define COMM_CMD        0xBB

#define TS_UNIX         0x01
#define TIME_TO_SLEEP   0x02
#define CURR_UART_B     0x03

#define CELL_OVP        0x04
#define CELL_OVPD       0x05
#define CELL_UVP        0x06
#define CELL_UVPD       0x07

#define PACK_OVP        0x08
#define PACK_OVPD       0x09
#define PACK_UVP        0x0A
#define PACK_UVPD       0x0B

#define CRG_OCP         0x0C
#define CRG_OCPD        0x0D
#define CRG_OCPRD       0x0E

#define DSCRG_OCP       0x0F
#define DSCRG_OCPD      0x10
#define DSCRG_OCPRD     0x11

#define CRG_OTP         0x12
#define CRG_OTPD        0x13
#define CRG_OTPRD       0x14

#define CRG_UTP         0x15
#define CRG_UTPD        0x16
#define CRG_UTPRD       0x17

#define DSCRG_OTP       0x18
#define DSCRG_OTPD      0x19
#define DSCRG_OTPRD     0x1A

#define DSCRG_UTP         0x1B
#define DSCRG_UTPD        0x1C
#define DSCRG_UTPRD       0x1D

//HW info
#define RXD2 16
#define TXD2 17

typedef struct packInfoStruct{
  uint8_t numOfCells;
  uint16_t cellVoltage[20]; // Max 20 Cell BMS
  uint16_t cellLow;   // Minimal voltage in cells
  uint16_t cellHigh; // Maximal voltage in cells
  uint16_t cellDiff; // difference between highest and lowest
  uint16_t cellAvg; // Average voltage in cells
  uint32_t tVoltage;
  uint32_t tCurrent;
  uint32_t RTCurrent;
  uint32_t nCapacity;
  uint32_t remCapacity;
  uint8_t SOC;
  uint8_t error_Codes;
  uint8_t cellString_1;
  uint8_t cellString_2;
  uint8_t cellString_3;
  uint8_t cellString_4;
  uint8_t segCtrlStatus_1;
  uint8_t segCtrlStatus_2;
  uint8_t segCtrlStatus_3;
  uint8_t segCtrlStatus_4;
  uint16_t currUartB;
  uint16_t numChargeCycle;
  uint16_t maxTemp;
  uint16_t minTemp;
  uint8_t  tempSensorSet;
  uint16_t tempSensor[8];
  uint8_t errorCodeReg;
} packInfoStruct;

typedef struct headerInfoStruct{
  // uint8_t start ;
  uint8_t srcID ;
  uint8_t snkID ;
  uint8_t cmd;
  uint8_t length;
} headerInfoStruct;

typedef struct OnlyheaderStruct{
  uint8_t start ;
  // uint8_t srcID ;
  // uint8_t snkID ;
  // uint8_t cmd;
  // uint8_t length;
} OnlyheaderStruct;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);                         // console
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);  // Dongle

  Serial.println("Init");
}

bool get_bytes(uint8_t *t_outMessage) {
  uint8_t i = 0;
  bool startByte = false;
  while (i <= LEN_READ - 1) {
    if (Serial2.available() > 0) {
      // uint8_t thisByte = m_port->read();
      uint8_t thisByte = Serial2.read();
      if (thisByte == START)  // START
      {
        startByte = true;
      }
      if (startByte) {
        t_outMessage[i] = thisByte;
        i++;
      }
    }
  }
  return true;
}

uint8_t rand_SOC()
{
  uint8_t testSoc = random(1, 99);
  return testSoc;
}

/*
write start:
DD 5A 00 02 56 78 FF 30 77

basic info:
DD A5 03 00 FF FD 77 

cell info:
DD A5 04 00 FF FC 77 

write start/stop reply:
{0xDD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x77};

pxCmd_dischargeStart:
0xDD, 0x5A, 0xE1, 0x02, 0x00, 0x00, 0xFF, 0x1D, 0x77

pxCmd_dischargeStop:
0xDD, 0x5A, 0xE1, 0x02, 0x00, 0x02, 0xFF, 0x1B, 0x77

pxRes_dischargeStart/stop reply:
0xDD, 0xE1, 0x00, 0x00, 0x00, 0x00, 0x77
*/

void loop() {
  // put your main code here, to run repeatedly:

  cell_balance();
  delay(5000);


  uint8_t responce[LEN_READ];
  if (get_bytes(responce)) 
  { 
    Serial.println("BMS data:");
    for (int i = 0; i < LEN_READ; i++) {
      Serial.print(responce[i], HEX);
      Serial.print(" ");
    }
    Serial.println();

    switch(responce[3])
    {
      case BASIC_INFO :
        Serial.println("BASIC_INFO");
        send_Basic();
        break;

      case CELL_INFO : 
        Serial.println("CELL_INFO");
        cell_info();
        break;

      case CELL_BALANCE :  
        Serial.println("CELL_BALANCE");
        cell_balance();
        break;
      
      case CTRL_STATUS :  
        Serial.println("CTRL_STATUS");
        ctrl_status();
        break;

      case UTILITY :  
        Serial.println("UTILITY");
        utilitu_segment();
        break;

      case MOS_CTRL : 
        mosCtrl();
        break;
      case NNCAP_CONFIG : 
        nominal_cap();
        break;
      case CYCAP_CONFIG : 
        cyclic_cap();
        break;
      case FULL_CELL_VOLT : 
        full_cell_volt();
        break;
      case END_CELL_VOLT : 
        cell_end_volt();
        break;
      case TEMP_CTRL : 
        temp_CTRL();
        break;

      case COMM_CMD:

        if (responce[5] == TS_UNIX)       {unix_ts();}
        if (responce[5] == TIME_TO_SLEEP) {time_before_sleep();}
        if (responce[5] == CURR_UART_B)   {current_uart_b();}
        if (responce[5] == CELL_OVP)      {cell_OVP();}
        if (responce[5] == CELL_OVPD)     {cell_OVPD();}
        if (responce[5] == CELL_UVP)      {cell_UVP();}
        if (responce[5] == CELL_UVPD)     {cell_UVPD();}
        if (responce[5] == PACK_OVP)      {pack_OVP();}
        if (responce[5] == PACK_OVPD)     {pack_OVPD();}
        if (responce[5] == PACK_UVP)      {pack_UVP();}
        if (responce[5] == PACK_UVPD)     {pack_UVPD();}
        if (responce[5] == CRG_OCP)       {crg_OCP();}
        if (responce[5] == CRG_OCPD)      {crg_OCPD();}
        if (responce[5] == CRG_OCPRD)     {crg_OCPRD();}
        if (responce[5] == DSCRG_OCP)     {dscrg_OCP();}
        if (responce[5] == DSCRG_OCPD)    {dscrg_OCPD();}
        if (responce[5] == DSCRG_OCPRD)   {dscrg_OCPRD();}
        if (responce[5] == CRG_OTP)       {crg_OTP();}
        if (responce[5] == CRG_OTPD)      {crg_OTPD();}
        if (responce[5] == CRG_OTPRD)     {crg_OTPRD();}
        if (responce[5] == CRG_UTP)       {crg_UTP();}
        if (responce[5] == CRG_UTPD)      {crg_UTPD();}
        if (responce[5] == CRG_UTPRD)     {crg_UTPRD();}
        if (responce[5] == DSCRG_OTP)     {dscrg_OTP();}
        if (responce[5] == DSCRG_OTPD)    {dscrg_OTPD();}
        if (responce[5] == DSCRG_OTPRD)   {dscrg_OTPRD();}
        if (responce[5] == DSCRG_UTP)     {dscrg_UTP();}
        if (responce[5] == DSCRG_UTPD)    {dscrg_UTPD();}
        if (responce[5] == DSCRG_UTPRD)   {dscrg_UTPRD();}
    }
  }
  
}
