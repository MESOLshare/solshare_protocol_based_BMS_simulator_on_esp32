/*
 * All the reading params reply  
*/
#include <stdio.h>
#include <stdint.h>
#include <math.h>

// Function to convert a float to IEEE 754 single-precision format
uint32_t floatToIEEE754(float floatValue) {
    union {
        float f;
        uint32_t u;
    } converter;

    converter.f = floatValue;
    return converter.u;
}

void send_Basic()
{
  Serial.println("send_Basic");
  packInfoStruct basic_info = {0};
  headerInfoStruct basic_info_header = {0,0,0,0};
  OnlyheaderStruct headerStart = {0};

  int i = 0, j = 0; //k = 0;
  uint8_t basic_index_crc = 4;
  uint8_t basic_index = 0;
  int basic_data_len = 20;
  int basic_buff_len = 27;
  uint8_t basic_buff_crc[basic_buff_len];
  uint8_t basic_buff[basic_buff_len];
  uint8_t crc8_basic_info;

  // basic_info_header.start = 0x55;
  headerStart.start = START;
  basic_info_header.srcID = 0x22;
  basic_info_header.snkID = 0x11;
  basic_info_header.cmd = BASIC_INFO;
  basic_info_header.length = basic_data_len;

  basic_info.tVoltage = 55555;
  float ieee754Value = -5.0;
  basic_info.RTCurrent = floatToIEEE754(ieee754Value);
  
  basic_info.nCapacity    = 100000;
  basic_info.SOC          = 70; //rand_SOC();
  basic_info.remCapacity  = (basic_info.SOC * basic_info.nCapacity) / 100;
  basic_info.maxTemp = 120;
  basic_info.error_Codes = 2;

  basic_buff_crc[basic_index_crc++] = (basic_info.tVoltage >> 24) & 0xFF;
  basic_buff_crc[basic_index_crc++] = (basic_info.tVoltage >> 16) & 0xFF;
  basic_buff_crc[basic_index_crc++] = (basic_info.tVoltage >> 8) & 0xFF;
  basic_buff_crc[basic_index_crc++] = (basic_info.tVoltage >> 0) & 0xFF;

  basic_buff_crc[basic_index_crc++] = (basic_info.RTCurrent >> 24) & 0xFF;
  basic_buff_crc[basic_index_crc++] = (basic_info.RTCurrent >> 16) & 0xFF;
  basic_buff_crc[basic_index_crc++] = (basic_info.RTCurrent >> 8) & 0xFF;
  basic_buff_crc[basic_index_crc++] = (basic_info.RTCurrent >> 0) & 0xFF;

  basic_buff_crc[basic_index_crc++] = (basic_info.nCapacity >> 24) & 0xFF;
  basic_buff_crc[basic_index_crc++] = (basic_info.nCapacity >> 16) & 0xFF;
  basic_buff_crc[basic_index_crc++] = (basic_info.nCapacity >> 8) & 0xFF;
  basic_buff_crc[basic_index_crc++] = (basic_info.nCapacity >> 0) & 0xFF;

  basic_buff_crc[basic_index_crc++] = (basic_info.remCapacity >> 24) & 0xFF;
  basic_buff_crc[basic_index_crc++] = (basic_info.remCapacity >> 16) & 0xFF;
  basic_buff_crc[basic_index_crc++] = (basic_info.remCapacity >> 8) & 0xFF;
  basic_buff_crc[basic_index_crc++] = (basic_info.remCapacity >> 0) & 0xFF;

  basic_buff_crc[basic_index_crc++] = (basic_info.SOC) & 0xFF;

  basic_buff_crc[basic_index_crc++] = (basic_info.maxTemp >> 8) & 0xFF;
  basic_buff_crc[basic_index_crc++] = (basic_info.maxTemp >> 0) & 0xFF;

  basic_buff_crc[basic_index_crc++] = (basic_info.error_Codes) & 0xFF;

  memcpy(basic_buff_crc, &basic_info_header, 4);

  crc8_basic_info = calculateCRC_8(basic_buff_crc, 24);

  Serial.println("*************RAW************");
  for (i = 0; i < 24; i++)
  {  
    Serial.print("0x");
    Serial.print(basic_buff_crc[i], HEX);
    Serial.print(", ");
  }
  Serial.println("");
  Serial.println("*************************");

  Serial.print("** CRC **: ");
  Serial.println(crc8_basic_info, HEX);

  /*--------------------*/

  basic_buff[basic_index++] = headerStart.start;
  basic_buff[basic_index++] = basic_info_header.srcID;
  basic_buff[basic_index++] = basic_info_header.snkID;
  basic_buff[basic_index++] = basic_info_header.cmd;
  basic_buff[basic_index++] = basic_info_header.length;

  basic_buff[basic_index++] = (basic_info.tVoltage >> 24) & 0xFF;
  basic_buff[basic_index++] = (basic_info.tVoltage >> 16) & 0xFF;
  basic_buff[basic_index++] = (basic_info.tVoltage >> 8) & 0xFF;
  basic_buff[basic_index++] = (basic_info.tVoltage >> 0) & 0xFF;

  basic_buff[basic_index++] = (basic_info.RTCurrent >> 24) & 0xFF;
  basic_buff[basic_index++] = (basic_info.RTCurrent >> 16) & 0xFF;
  basic_buff[basic_index++] = (basic_info.RTCurrent >> 8) & 0xFF;
  basic_buff[basic_index++] = (basic_info.RTCurrent >> 0) & 0xFF;

  basic_buff[basic_index++] = (basic_info.nCapacity >> 24) & 0xFF;
  basic_buff[basic_index++] = (basic_info.nCapacity >> 16) & 0xFF;
  basic_buff[basic_index++] = (basic_info.nCapacity >> 8) & 0xFF;
  basic_buff[basic_index++] = (basic_info.nCapacity >> 0) & 0xFF;

  basic_buff[basic_index++] = (basic_info.remCapacity >> 24) & 0xFF;
  basic_buff[basic_index++] = (basic_info.remCapacity >> 16) & 0xFF;
  basic_buff[basic_index++] = (basic_info.remCapacity >> 8) & 0xFF;
  basic_buff[basic_index++] = (basic_info.remCapacity >> 0) & 0xFF;

  basic_buff[basic_index++] = (basic_info.SOC) & 0xFF;

  basic_buff[basic_index++] = (basic_info.maxTemp >> 8) & 0xFF;
  basic_buff[basic_index++] = (basic_info.maxTemp >> 0) & 0xFF;

  basic_buff[basic_index++] = (basic_info.error_Codes) & 0xFF;

  basic_buff[basic_index++] = crc8_basic_info;
  basic_buff[basic_index++] = END;

  Serial.println("************ALL*************");
  for (j = 0; j < basic_buff_len; j++)
  {
    Serial.print("0x");
    Serial.print(basic_buff[j], HEX);
    Serial.print(", ");
  }
  Serial.println("");
  Serial.println("*************************");

  Serial2.write(basic_buff, basic_buff_len);

}

void cell_info()
{
  Serial.println("cell info");
  packInfoStruct cell_info;
  headerInfoStruct cell_info_header = {0,0,0,0};;
  OnlyheaderStruct headerStart = {0};
  uint8_t crc8_cell_info;

  int i = 0, j = 0, k = 0;
  uint8_t cell_info_index_crc = 4;
  uint8_t cell_info_index = 0;
  int cell_buff_len = 54;
  int cell_buff_data_len = 47;
  uint8_t cell_buff_crc[cell_buff_len];
  uint8_t cell_buff[cell_buff_len];

  headerStart.start = START;
  cell_info_header.srcID = 0x22;
  cell_info_header.snkID = 0x11;
  cell_info_header.cmd = CELL_INFO;
  cell_info_header.length = cell_buff_data_len;

  cell_info.numOfCells = 20;
  cell_info.cellHigh   = 4200;
  cell_info.cellLow    = 2700;
  cell_info.cellAvg    = 3500;

  cell_buff_crc[cell_info_index_crc ++] = (cell_info.numOfCells >> 0) & 0xFF;

  cell_buff_crc[cell_info_index_crc ++] = (cell_info.cellHigh >> 8) & 0xFF;
  cell_buff_crc[cell_info_index_crc ++] = (cell_info.cellHigh >> 0) & 0xFF;

  cell_buff_crc[cell_info_index_crc ++] = (cell_info.cellLow >> 8) & 0xFF;
  cell_buff_crc[cell_info_index_crc ++] = (cell_info.cellLow >> 0) & 0xFF;

  cell_buff_crc[cell_info_index_crc ++] = (cell_info.cellAvg >> 8) & 0xFF;
  cell_buff_crc[cell_info_index_crc ++] = (cell_info.cellAvg >> 0) & 0xFF;

  for (i = 0 ; i < cell_info.numOfCells ; i++)
  {
    cell_info.cellVoltage[i] = 3700;
    cell_buff_crc[cell_info_index_crc ++] = (cell_info.cellVoltage[i] >> 8) & 0xFF;
    cell_buff_crc[cell_info_index_crc ++] = (cell_info.cellVoltage[i] >> 0) & 0xFF;
  }

  memcpy(cell_buff_crc, &cell_info_header, 5);

  Serial.println("*************RAW************");
  for (j = 0; j < 47; j++)
  {
    Serial.print("0x");
    Serial.print(cell_buff_crc[j], HEX);
    Serial.print(", ");
  }
  Serial.print("");
  Serial.println("*************************");

  crc8_cell_info = calculateCRC_8(cell_buff_crc, 47);

  Serial.print("** CRC **: ");
  Serial.println(crc8_cell_info, HEX);

  /*---------------------------------------------------------------*/

  cell_buff[cell_info_index ++] = headerStart.start;
  cell_buff[cell_info_index ++] = cell_info_header.srcID;
  cell_buff[cell_info_index ++] = cell_info_header.snkID;
  cell_buff[cell_info_index ++] = cell_info_header.cmd;
  cell_buff[cell_info_index ++] = cell_info_header.length;

  cell_buff[cell_info_index ++] = (cell_info.numOfCells >> 0) & 0xFF;

  cell_buff[cell_info_index ++] = (cell_info.cellHigh >> 8) & 0xFF;
  cell_buff[cell_info_index ++] = (cell_info.cellHigh >> 0) & 0xFF;

  cell_buff[cell_info_index ++] = (cell_info.cellLow >> 8) & 0xFF;
  cell_buff[cell_info_index ++] = (cell_info.cellLow >> 0) & 0xFF;

  cell_buff[cell_info_index ++] = (cell_info.cellAvg >> 8) & 0xFF;
  cell_buff[cell_info_index ++] = (cell_info.cellAvg >> 0) & 0xFF;

  for (i = 0 ; i < cell_info.numOfCells ; i++)
  {
    cell_info.cellVoltage[i] = 3700;
    cell_buff[cell_info_index ++] = (cell_info.cellVoltage[i] >> 8) & 0xFF;
    cell_buff[cell_info_index ++] = (cell_info.cellVoltage[i] >> 0) & 0xFF;
  }

  // Serial.println("*************RAW************");
  // for (j = 5; j < 52; j++)
  // {
  //   Serial.println(cell_buff[j], HEX);
  // }
  // Serial.println("*************************");

  cell_buff[cell_info_index++] = crc8_cell_info;
  cell_buff[cell_info_index++] = END;

  Serial.println("*************ALL************");
  for (j = 0; j < 47; j++)
  {
    Serial.print("0x");
    Serial.print(cell_buff[j], HEX);
    Serial.print(", ");
  }
  Serial.print("");
  Serial.println("*************************");
  
  Serial2.write(cell_buff, cell_buff_len);
}

void cell_balance()
{
  Serial.println("cell_balance");
  packInfoStruct cell_balance;
  headerInfoStruct cell_balance_header = {0,0,0,0};
  OnlyheaderStruct headerStart = {0};

  int i = 0, j = 0; //k = 0;
  uint8_t cell_balance_index_crc = 4;
  uint8_t cell_balance_index = 0;
  int balance_data_len = 4;
  int balance_buff_len = 11;
  uint8_t balance_buff_crc[balance_buff_len];
  uint8_t balance_buff[balance_buff_len];
  uint8_t crc_cell_balance = 0;

  headerStart.start = START;
  cell_balance_header.srcID = 0x22;
  cell_balance_header.snkID = 0x11;
  cell_balance_header.cmd = CELL_BALANCE;
  cell_balance_header.length = 4;

  cell_balance.cellString_1 = 0b11111111; 
  cell_balance.cellString_2 = 0b11111111; 
  cell_balance.cellString_3 = 0b00001111; 
  cell_balance.cellString_4 = 0b00000011; 

  balance_buff_crc[cell_balance_index_crc++] = cell_balance.cellString_1 & 0xFF;
  balance_buff_crc[cell_balance_index_crc++] = cell_balance.cellString_2 & 0xFF;
  balance_buff_crc[cell_balance_index_crc++] = cell_balance.cellString_3 & 0xFF;
  balance_buff_crc[cell_balance_index_crc++] = cell_balance.cellString_4 & 0xFF;

  memcpy(balance_buff_crc, &cell_balance_header, 4);

  crc_cell_balance = calculateCRC_8(balance_buff_crc, 8);

  Serial.println("******raw*******");
  for (i = 0 ; i < 8 ; i++)
  { 
    Serial.print("0x");
    Serial.print(balance_buff_crc[i], HEX);
    Serial.print(", ");
  }
  Serial.println("");
  Serial.println("************");

  Serial.println("** CRC **: ");
  Serial.println(crc_cell_balance, HEX);
  /*------------------------------------------------------------------*/

  balance_buff[cell_balance_index++] = headerStart.start;
  balance_buff[cell_balance_index++] = cell_balance_header.srcID;
  balance_buff[cell_balance_index++] = cell_balance_header.snkID;
  balance_buff[cell_balance_index++] = cell_balance_header.cmd;
  balance_buff[cell_balance_index++] = cell_balance_header.length;

  balance_buff[cell_balance_index++] = cell_balance.cellString_1 & 0xFF;
  balance_buff[cell_balance_index++] = cell_balance.cellString_2 & 0xFF;
  balance_buff[cell_balance_index++] = cell_balance.cellString_3 & 0xFF;
  balance_buff[cell_balance_index++] = cell_balance.cellString_4 & 0xFF;

  balance_buff[cell_balance_index++] = crc_cell_balance;
  balance_buff[cell_balance_index++] = END;

  Serial.println("******ALL*******");
  for (i = 0 ; i < 11 ; i++)
  { 
    Serial.print("0x");
    Serial.print(balance_buff[i], HEX);
    Serial.print(", ");
  }
  Serial.println("");
  Serial.println("************");

  Serial2.write(balance_buff, balance_buff_len);
}

void ctrl_status()
{
  Serial.println("ctrl_status");
  packInfoStruct ctrl_status;
  headerInfoStruct ctrl_status_header = {0,0,0,0};;
  OnlyheaderStruct headerStart = {0};

  int i = 0, j = 0; // k = 0;
  uint8_t ctrl_status_index_crc = 4;
  uint8_t ctrl_status_index = 0;
  int status_data_len = 4;
  int status_buff_len = 11;
  uint8_t status_buff_crc[status_buff_len];
  uint8_t status_buff[status_buff_len];
  uint8_t crc_ctrl_status = 0;

  headerStart.start = START;
  ctrl_status_header.srcID = 0x22;
  ctrl_status_header.snkID = 0x11;
  ctrl_status_header.cmd = CTRL_STATUS;
  ctrl_status_header.length = status_data_len;

  ctrl_status.segCtrlStatus_1 = 0b10110000; 
  ctrl_status.segCtrlStatus_2 = 0b10101010; 
  ctrl_status.segCtrlStatus_3 = 0b11111111; 
  ctrl_status.segCtrlStatus_4 = 0b01010101; 

  status_buff_crc[ctrl_status_index_crc ++] = ctrl_status.segCtrlStatus_1 & 0xFF;
  status_buff_crc[ctrl_status_index_crc ++] = ctrl_status.segCtrlStatus_2 & 0xFF;
  status_buff_crc[ctrl_status_index_crc ++] = ctrl_status.segCtrlStatus_3 & 0xFF;
  status_buff_crc[ctrl_status_index_crc ++] = ctrl_status.segCtrlStatus_4 & 0xFF;

  memcpy(status_buff_crc, &ctrl_status_header, 4);

  Serial.println("******RAW*******");
  for (i = 0 ; i < 8 ; i++)
  {
    Serial.print("0x");
    Serial.print(status_buff_crc[i], HEX);
    Serial.print(", ");
  }
  Serial.println("");
  Serial.println("************");

  crc_ctrl_status = calculateCRC_8(status_buff_crc, 8);

  /*-------------------------------------------------------------------*/

  status_buff[ctrl_status_index ++] = headerStart.start;
  status_buff[ctrl_status_index ++] = ctrl_status_header.srcID;
  status_buff[ctrl_status_index ++] = ctrl_status_header.snkID;
  status_buff[ctrl_status_index ++] = ctrl_status_header.cmd;
  status_buff[ctrl_status_index ++] = ctrl_status_header.length;

  status_buff[ctrl_status_index ++] = ctrl_status.segCtrlStatus_1 & 0xFF;
  status_buff[ctrl_status_index ++] = ctrl_status.segCtrlStatus_2 & 0xFF;
  status_buff[ctrl_status_index ++] = ctrl_status.segCtrlStatus_3 & 0xFF;
  status_buff[ctrl_status_index ++] = ctrl_status.segCtrlStatus_4 & 0xFF;

  status_buff[ctrl_status_index ++] = crc_ctrl_status;
  status_buff[ctrl_status_index ++] = END;

  Serial.println("*******ALL******");
  for (j = 0 ; j < status_buff_len; j++)
  {
    Serial.print("0x");
    Serial.print(status_buff[j], HEX);
    Serial.print(", ");
  }
  Serial.println("");
  Serial.println("************");

  Serial2.write(status_buff, status_buff_len);

}

void utilitu_segment()
{
  Serial.println("ctrl_status");
  packInfoStruct utility_seg;
  headerInfoStruct utility_seg_header = {0,0,0,0};
  OnlyheaderStruct headerStart = {0};

  int i = 0, j = 0, k = 0;
  int utility_seg_index_crc = 4;
  int utility_seg_index = 0;
  int utility_data_len = 26;
  int utility_buff_len = 33;
  uint8_t utility_buff[utility_buff_len];
  uint8_t utility_buff_crc[utility_buff_len];
  uint8_t crc_utilitu_segment = 0;

  headerStart.start = START;
  utility_seg_header.srcID = 0x22;
  utility_seg_header.snkID = 0x11;
  utility_seg_header.cmd = UTILITY;
  utility_seg_header.length = utility_data_len;

  utility_seg.currUartB = 1000;
  utility_seg.numChargeCycle = 20345;
  utility_seg.maxTemp = 32;
  utility_seg.minTemp = 15;
  utility_seg.tempSensorSet = 0b10101010;
  utility_seg.errorCodeReg = 6;

  utility_buff_crc[utility_seg_index_crc ++] = (utility_seg.currUartB >> 8) & 0xFF;
  utility_buff_crc[utility_seg_index_crc ++] = (utility_seg.currUartB >> 0) & 0xFF;

  utility_buff_crc[utility_seg_index_crc ++] = (utility_seg.numChargeCycle >> 8) & 0xFF;
  utility_buff_crc[utility_seg_index_crc ++] = (utility_seg.numChargeCycle >> 0) & 0xFF;

  utility_buff_crc[utility_seg_index_crc ++] = (utility_seg.maxTemp >> 8) & 0xFF;
  utility_buff_crc[utility_seg_index_crc ++] = (utility_seg.maxTemp >> 0) & 0xFF;

  utility_buff_crc[utility_seg_index_crc ++] = (utility_seg.minTemp >> 8) & 0xFF;
  utility_buff_crc[utility_seg_index_crc ++] = (utility_seg.minTemp >> 0) & 0xFF;

  utility_buff_crc[utility_seg_index_crc ++] = (utility_seg.tempSensorSet >> 0) & 0xFF;

  Serial.print("temp sensor size:");
  Serial.println(sizeof(utility_seg.tempSensor) / sizeof(utility_seg.tempSensor[0]));

  for (i = 0 ; i < sizeof(utility_seg.tempSensor) / sizeof(utility_seg.tempSensor[0]); i++)
  {
    utility_seg.tempSensor[i] = 50;
    utility_buff_crc[utility_seg_index_crc ++] = (utility_seg.tempSensor[i] >> 8) & 0xFF;
    utility_buff_crc[utility_seg_index_crc ++] = (utility_seg.tempSensor[i] >> 0) & 0xFF;
  }
  utility_buff_crc[utility_seg_index_crc++] = (utility_seg.errorCodeReg >> 0) & 0xFF;

  memcpy(utility_buff_crc, &utility_seg_header, 4);

  Serial.println("******RAW*******");
  for (j = 0 ; j < 30 ; j++)
  {
    Serial.print("0x");
    Serial.print(utility_buff_crc[j], HEX);
    Serial.print(", ");
  }
  Serial.println("");
  Serial.println("************");

  crc_utilitu_segment = calculateCRC_8(utility_buff_crc, 26);

  /*-------------------------------------------------------------------------*/

  utility_buff[utility_seg_index++] = headerStart.start;
  utility_buff[utility_seg_index++] = utility_seg_header.srcID;
  utility_buff[utility_seg_index++] = utility_seg_header.snkID;
  utility_buff[utility_seg_index++] = utility_seg_header.cmd;
  utility_buff[utility_seg_index++] = utility_seg_header.length;

  utility_buff[utility_seg_index++] = (utility_seg.currUartB >> 8) & 0xFF;
  utility_buff[utility_seg_index++] = (utility_seg.currUartB >> 0) & 0xFF;

  utility_buff[utility_seg_index++] = (utility_seg.numChargeCycle >> 8) & 0xFF;
  utility_buff[utility_seg_index++] = (utility_seg.numChargeCycle >> 0) & 0xFF;

  utility_buff[utility_seg_index++] = (utility_seg.maxTemp >> 8) & 0xFF;
  utility_buff[utility_seg_index++] = (utility_seg.maxTemp >> 0) & 0xFF;

  utility_buff[utility_seg_index++] = (utility_seg.minTemp >> 8) & 0xFF;
  utility_buff[utility_seg_index++] = (utility_seg.minTemp >> 0) & 0xFF;

  utility_buff[utility_seg_index++] = (utility_seg.tempSensorSet >> 0) & 0xFF;

  for (i = 0 ; i < sizeof(utility_seg.tempSensor) / sizeof(utility_seg.tempSensor[0]); i++)
    {
      utility_seg.tempSensor[i] = 50;
      utility_buff[utility_seg_index++] = (utility_seg.tempSensor[i] >> 8) & 0xFF;
      utility_buff[utility_seg_index++] = (utility_seg.tempSensor[i] >> 0) & 0xFF;
    }
  
  utility_buff[utility_seg_index++] = (utility_seg.errorCodeReg >> 0) & 0xFF;

  utility_buff[utility_seg_index++] = crc_utilitu_segment;
  utility_buff[utility_seg_index++] = END;

  Serial.println("******ALL*******");
  for (k = 0 ; k < utility_buff_len; k++)
  {
    Serial.print("0x");
    Serial.print(utility_buff[k], HEX);
    Serial.print(", ");
  }
  Serial.println("");
  Serial.println("************");

  Serial2.write(utility_buff, utility_buff_len);
}
