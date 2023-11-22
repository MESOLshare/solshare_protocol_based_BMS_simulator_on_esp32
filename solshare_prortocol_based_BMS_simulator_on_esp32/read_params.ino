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
  headerInfoStruct basic_info_header = {0,0,0,0,0};;

  int i = 0, j = 0; //k = 0;
  uint8_t basic_index = 5;
  int basic_data_len = 27;
  uint8_t basic_buff[basic_data_len];

  basic_info.tVoltage = 55555;
  float ieee754Value = -5.0;
  basic_info.RTCurrent = floatToIEEE754(ieee754Value);
  
  basic_info.nCapacity    = 100000;
  basic_info.SOC          = 70; //rand_SOC();
  basic_info.remCapacity  = (basic_info.SOC * basic_info.nCapacity) / 100;
  basic_info.maxTemp = 120;
  basic_info.error_Codes = 2;

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

  Serial.println("*************RAW************");
  for (i = 5; i < 25; i++)
  {
    Serial.println(basic_buff[i], HEX);
  }
  Serial.println("*************************");

  basic_info_header.start = 0x55;
  basic_info_header.srcID = 0x22;
  basic_info_header.snkID = 0x11;
  basic_info_header.cmd = BASIC_INFO;
  basic_info_header.length = basic_data_len;

  memcpy(basic_buff, &basic_info_header, 5);

  basic_buff[basic_index++] = calculateCRC(basic_buff, sizeof(basic_buff));
  basic_buff[basic_index++] = END;

  Serial.println("************ALL*************");
  for (j = 0; j < basic_data_len; j++)
  {
    Serial.println(basic_buff[j], HEX);
  }
  Serial.println("*************************");

  Serial2.write(basic_buff, basic_data_len);

}

void cell_info()
{
  Serial.println("cell info");
  packInfoStruct cell_info;
  headerInfoStruct cell_info_header = {0,0,0,0,0};;

  int i = 0, j = 0, k = 0;
  uint8_t cell_info_index = 5;
  int cell_buff_len = 54;
  uint8_t cell_buff[cell_buff_len];

  cell_info.numOfCells = 20;
  cell_info.cellHigh   = 4200;
  cell_info.cellLow    = 2700;
  cell_info.cellAvg    = 3500;

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

  Serial.println("*************RAW************");
  for (j = 5; j < 52; j++)
  {
    Serial.println(cell_buff[j], HEX);
  }
  Serial.println("*************************");

  cell_info_header.start = 0x55;
  cell_info_header.srcID = 0x22;
  cell_info_header.snkID = 0x11;
  cell_info_header.cmd = CELL_INFO;
  cell_info_header.length = cell_buff_len;

  memcpy(cell_buff, &cell_info_header, 5);

  cell_buff[cell_info_index++] = calculateCRC(cell_buff, sizeof(cell_buff)); 
  cell_buff[cell_info_index++] = END;

  Serial.println("************ALL*************");
  for (k = 0; k < cell_buff_len; k++)
  {
    Serial.println(cell_buff[k], HEX);
  }
  Serial.println("*************************");
  
  Serial2.write(cell_buff, cell_buff_len);
}

void cell_balance()
{
  Serial.println("cell_balance");
  packInfoStruct cell_balance;
  headerInfoStruct cell_balance_header = {0,0,0,0,0};;

  int i = 0, j = 0; //k = 0;
  uint8_t cell_balance_index = 5;
  int balance_buff_len = 11;
  uint8_t balance_buff[balance_buff_len];

  cell_balance.cellString_1 = 0b11111111; 
  cell_balance.cellString_2 = 0b11111111; 
  cell_balance.cellString_3 = 0b00001111; 
  cell_balance.cellString_4 = 0b00000011; 

  balance_buff[cell_balance_index++] = cell_balance.cellString_1 & 0xFF;
  balance_buff[cell_balance_index++] = cell_balance.cellString_2 & 0xFF;
  balance_buff[cell_balance_index++] = cell_balance.cellString_3 & 0xFF;
  balance_buff[cell_balance_index++] = cell_balance.cellString_4 & 0xFF;

  Serial.println("******data*******");
  for (i = 5 ; i <= 8 ; i++)
  {
    Serial.println(balance_buff[i], HEX);
  }
  Serial.println("************");

  cell_balance_header.start = 0x55;
  cell_balance_header.srcID = 0x22;
  cell_balance_header.snkID = 0x11;
  cell_balance_header.cmd = CELL_BALANCE;
  cell_balance_header.length = balance_buff_len;

  memcpy(balance_buff, &cell_balance_header, 5);

  balance_buff[cell_balance_index++] = calculateCRC(balance_buff, sizeof(balance_buff));
  balance_buff[cell_balance_index++] = END;

  Serial.println("*******ALL******");
  for (j = 0 ; j < balance_buff_len  ; j++)
  {
    Serial.println(balance_buff[j], HEX);
  }
  Serial.println("************");

  Serial2.write(balance_buff, balance_buff_len);
}

void ctrl_status()
{
  Serial.println("ctrl_status");
  packInfoStruct ctrl_status;
  headerInfoStruct ctrl_status_header = {0,0,0,0,0};;

  int i = 0, j = 0; // k = 0;
  uint8_t ctrl_status_index = 5;
  int status_buff_len = 11;
  uint8_t status_buff[status_buff_len];

  ctrl_status.segCtrlStatus_1 = 0b10110000; 
  ctrl_status.segCtrlStatus_2 = 0b10101010; 
  ctrl_status.segCtrlStatus_3 = 0b11111111; 
  ctrl_status.segCtrlStatus_4 = 0b01010101; 

  status_buff[ctrl_status_index ++] = ctrl_status.segCtrlStatus_1 & 0xFF;
  status_buff[ctrl_status_index ++] = ctrl_status.segCtrlStatus_2 & 0xFF;
  status_buff[ctrl_status_index ++] = ctrl_status.segCtrlStatus_3 & 0xFF;
  status_buff[ctrl_status_index ++] = ctrl_status.segCtrlStatus_4 & 0xFF;

  Serial.println("******data*******");
  for (i = 5 ; i <= 8 ; i++)
  {
    Serial.println(status_buff[i], HEX);
  }
  Serial.println("************");

  ctrl_status_header.start = 0x55;
  ctrl_status_header.srcID = 0x22;
  ctrl_status_header.snkID = 0x11;
  ctrl_status_header.cmd = CTRL_STATUS;
  ctrl_status_header.length = status_buff_len;

  memcpy(status_buff, &ctrl_status_header, 5);

  status_buff[ctrl_status_index++] = calculateCRC(status_buff, sizeof(status_buff));
  status_buff[ctrl_status_index++] = END;

  Serial.println("*******ALL******");
  for (j = 0 ; j < status_buff_len; j++)
  {
    Serial.println(status_buff[j], HEX);
  }
  Serial.println("************");

  Serial2.write(status_buff, status_buff_len);

}

void utilitu_segment()
{
  Serial.println("ctrl_status");
  packInfoStruct utility_seg;
  headerInfoStruct utility_seg_header = {0,0,0,0,0};;

  int i = 0, j = 0, k = 0;
  int utility_seg_index = 5;
  int utility_buff_len = 33;
  uint8_t utility_buff[utility_buff_len];

  utility_seg.currUartB = 1000;
  utility_seg.numChargeCycle = 20345;
  utility_seg.maxTemp = 32;
  utility_seg.minTemp = 15;
  utility_seg.tempSensorSet = 0b10101010;

  utility_buff[utility_seg_index++] = (utility_seg.currUartB >> 8) & 0xFF;
  utility_buff[utility_seg_index++] = (utility_seg.currUartB >> 0) & 0xFF;

  utility_buff[utility_seg_index++] = (utility_seg.numChargeCycle >> 8) & 0xFF;
  utility_buff[utility_seg_index++] = (utility_seg.numChargeCycle >> 0) & 0xFF;

  utility_buff[utility_seg_index++] = (utility_seg.maxTemp >> 8) & 0xFF;
  utility_buff[utility_seg_index++] = (utility_seg.maxTemp >> 0) & 0xFF;

  utility_buff[utility_seg_index++] = (utility_seg.minTemp >> 8) & 0xFF;
  utility_buff[utility_seg_index++] = (utility_seg.minTemp >> 0) & 0xFF;

  utility_buff[utility_seg_index++] = (utility_seg.tempSensorSet >> 0) & 0xFF;

//  for (i = 0 ; i < sizeof(utility_seg.tempSensor) / sizeof(utility_seg.tempSensor[0]) ; i++)
for (i = 0 ; i < sizeof(utility_seg.tempSensor) / sizeof(utility_seg.tempSensor[0]); i++)
  {
    utility_seg.tempSensor[i] = 50;
    utility_buff[utility_seg_index++] = (utility_seg.tempSensor[i] >> 8) & 0xFF;
    Serial.println("******c*******");
    Serial.println(utility_seg_index);
    utility_buff[utility_seg_index++] = (utility_seg.tempSensor[i] >> 0) & 0xFF;
    Serial.println("******d*******");
    Serial.println(utility_seg_index);
  }
  
  utility_seg.errorCodeReg = 6;
  utility_buff[utility_seg_index++] = (utility_seg.errorCodeReg >> 0) & 0xFF;

  Serial.println("******data*******");
  for (j = 5 ; j < 31 ; j++)
  {
    Serial.println(utility_buff[j], HEX);
  }
  Serial.println("************");

  utility_seg_header.start = 0x55;
  utility_seg_header.srcID = 0x22;
  utility_seg_header.snkID = 0x11;
  utility_seg_header.cmd = UTILITY;
  utility_seg_header.length = utility_buff_len;

  memcpy(utility_buff, &utility_seg_header, 5);

  utility_buff[utility_seg_index++] = calculateCRC(utility_buff, sizeof(utility_buff));
  utility_buff[utility_seg_index++] = END;

  Serial.println("******ALL*******");
  for (k = 0 ; k < utility_buff_len; k++)
  {
    Serial.println(utility_buff[k], HEX);
  }
  Serial.println("************");

  Serial2.write(utility_buff, utility_buff_len);
}
