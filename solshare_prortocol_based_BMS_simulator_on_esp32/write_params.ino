
/*
 * write cmd reply
*/

void result_packet(uint8_t cmd, int data)
{
  Serial.println("result_packet");
  // packInfoStruct basic_info = {0};
  headerInfoStruct header = {0,0,0,0,0};

  int j = 0; //k = 0;
  uint8_t index = 5;
  int data_len = 8;
  uint8_t buff[data_len];

  int result = data;

  buff[index++] = result;

  header.start = 0x55;
  header.srcID = 0x22;
  header.snkID = 0x11;
  header.cmd = cmd;
  header.length = 1;

  memcpy(buff, &header, 5);

  buff[index++] = calculateCRC(buff, sizeof(buff));
  buff[index++] = END;

  Serial.println("************gen ALL*************");
  for (j = 0; j < data_len; j++)
  {
    Serial.println(buff[j], HEX);
  }
  Serial.println("*************************");

  Serial2.write(buff, data_len);

}

void mosCtrl()
{
  Serial.println("mosCtrl");

  int response_data = 0x00;
  result_packet(MOS_CTRL, response_data);
}

void nominal_cap()
{
  Serial.println("nominal_cap");
  int response_data = 0x00;
  result_packet(NNCAP_CONFIG, response_data);
}

void cyclic_cap()
{
  Serial.println("cyclic_cap");
  int response_data = 0x00;
  result_packet(CYCAP_CONFIG, response_data);
}

void full_cell_volt()
{
  Serial.println("full_cell_volt");
  int response_data = 0x00;
  result_packet(FULL_CELL_VOLT, response_data);
}

void cell_end_volt()
{
  Serial.println("cell_end_volt");
  int response_data = 0x00;
  result_packet(END_CELL_VOLT, response_data);
}

void temp_CTRL()
{
  Serial.println("temp_CTRL");
  int response_data = 0x00;
  result_packet(TEMP_CTRL, response_data);
}

// void result_packet_node(uint8_t cmd, uint8_t node, int data)
// {
//   Serial.println("result_packet_node");
//   // packInfoStruct basic_info = {0};
//   headerInfoStruct header = {0};

//   int j = 0; //k = 0;
//   uint8_t index = 5;
//   int data_len = 8;
//   uint8_t buff[data_len];

//   int result = data;

//   buff[index++] = result;

//   header.start = 0x55;
//   header.srcID = 0x11;
//   header.snkID = 0x22;
//   header.cmd = cmd;
//   header.length = 1;

//   memcpy(buff, &header, 5);

//   buff[index++] = calculateCRC(buff, sizeof(buff));
//   buff[index++] = END;

//   Serial.println("************gen ALL*************");
//   for (j = 0; j < data_len; j++)
//   {
//     Serial.println(buff[j], HEX);
//   }
//   Serial.println("*************************");

//   Serial2.write(buff, data_len);

// }

void unix_ts()
{
  Serial.println("unix_ts");
  int response_data = 0x00;
  result_packet(COMM_CMD, response_data);
}

void time_before_sleep()
{
  Serial.println("time_before_sleep");
  int response_data = 0x00;
  result_packet(COMM_CMD, response_data);
}

void current_uart_b()
{
  Serial.println("current_uart_b");
  int response_data = 0x00;
  result_packet(COMM_CMD, response_data);
}

void cell_OVP()
{
  Serial.println("cell_OVP");
  int response_data = 0x00;
  result_packet(COMM_CMD, response_data);
}

void cell_OVPD()
{
  Serial.println("cell_OVPD");
  int response_data = 0x00;
  result_packet(COMM_CMD, response_data);
}

void cell_UVP()
{
  Serial.println("cell_UVP");
  int response_data = 0x00;
  result_packet(COMM_CMD, response_data);
}

void cell_UVPD()
{
  Serial.println("cell_UVPD");
  int response_data = 0x00;
  result_packet(COMM_CMD, response_data);
}

void pack_OVP()
{
  Serial.println("pack_OVP");
  int response_data = 0x00;
  result_packet(COMM_CMD, response_data);
}

void pack_OVPD()
{
  Serial.println("pack_OVPD");
  int response_data = 0x00;
  result_packet(COMM_CMD, response_data);
}

void pack_UVP()
{
  Serial.println("pack_UVP");
  int response_data = 0x00;
  result_packet(COMM_CMD, response_data);
}

void pack_UVPD()
{
  Serial.println("pack_UVP");
  int response_data = 0x00;
  result_packet(COMM_CMD, response_data);
}

void crg_OCP()
{
  Serial.println("crg_UVP");
  int response_data = 0x00;
  result_packet(COMM_CMD, response_data);
}

void crg_OCPD()
{
  Serial.println("crg_OCPD");
  int response_data = 0x00;
  result_packet(COMM_CMD, response_data);
}

void crg_OCPRD()
{
  Serial.println("crg_OCPRD");
  int response_data = 0x00;
  result_packet(COMM_CMD, response_data);
}

void dscrg_OCP()
{
  Serial.println("dscrg_OCP");
  int response_data = 0x00;
  result_packet(COMM_CMD, response_data);
}

void dscrg_OCPD()
{
  Serial.println("dscrg_OCPD");
  int response_data = 0x00;
  result_packet(COMM_CMD, response_data);
}

void dscrg_OCPRD()
{
  Serial.println("dscrg_OCPRD");
  int response_data = 0x00;
  result_packet(COMM_CMD, response_data);
}

void crg_OTP()
{
  Serial.println("crg_OTP");
  int response_data = 0x00;
  result_packet(COMM_CMD, response_data);
}

void crg_OTPD()
{
  Serial.println("crg_OTPD");
  int response_data = 0x00;
  result_packet(COMM_CMD, response_data);
}

void crg_OTPRD()
{
  Serial.println("crg_OTPRD");
  int response_data = 0x00;
  result_packet(COMM_CMD, response_data);
}

void crg_UTP()
{
  Serial.println("crg_UTP");
  int response_data = 0x00;
  result_packet(COMM_CMD, response_data);
}

void crg_UTPD()
{
  Serial.println("crg_UTPD");
  int response_data = 0x00;
  result_packet(COMM_CMD, response_data);
}

void crg_UTPRD()
{
  Serial.println("crg_UTPRD");
  int response_data = 0x00;
  result_packet(COMM_CMD, response_data);
}

void dscrg_OTP()
{
  Serial.println("dscrg_OTP");
  int response_data = 0x00;
  result_packet(COMM_CMD, response_data);
}

void dscrg_OTPD()
{
  Serial.println("dscrg_OTPD");
  int response_data = 0x00;
  result_packet(COMM_CMD, response_data);
}

void dscrg_OTPRD()
{
  Serial.println("dscrg_OTPRD");
  int response_data = 0x00;
  result_packet(COMM_CMD, response_data);
}

void dscrg_UTP()
{
  Serial.println("crg_UTP");
  int response_data = 0x00;
  result_packet(COMM_CMD, response_data);
}

void dscrg_UTPD()
{
  Serial.println("crg_UTPD");
  int response_data = 0x00;
  result_packet(COMM_CMD, response_data);
}

void dscrg_UTPRD()
{
  Serial.println("crg_UTPRD");
  int response_data = 0x00;
  result_packet(COMM_CMD, response_data);
}
