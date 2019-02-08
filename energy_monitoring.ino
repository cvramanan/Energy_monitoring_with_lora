/*

  RS485_HalfDuplex.pde - example using ModbusMaster library to communicate
  with EPSolar LS2024B controller using a half-duplex RS485 transceiver.

  This example is tested against an EPSolar LS2024B solar charge controller.
  See here for protocol specs:
  http://www.solar-elektro.cz/data/dokumenty/1733_modbus_protocol.pdf

  Library:: ModbusMaster
  Author:: Marius Kintel <marius at kintel dot net>

  Copyright:: 2009-2016 Doc Walker

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

*/

#include <ModbusMaster.h>

/*!
  We're using a MAX485-compatible RS485 Transceiver.
  Rx/Tx is hooked up to the hardware serial port at 'Serial'.
  The Data Enable and Receiver Enable pins are hooked up as follows:
*/
#define MAX485_DE      PB1
#define MAX485_RE_NEG  PB0

// instantiate ModbusMaster object
ModbusMaster node;

void preTransmission()
{
  digitalWrite(MAX485_RE_NEG, 1);
  digitalWrite(MAX485_DE, 1);
}

void postTransmission()
{
  digitalWrite(MAX485_RE_NEG, 0);
  digitalWrite(MAX485_DE, 0);
}

void setup()
{
  pinMode(MAX485_RE_NEG, OUTPUT);
  pinMode(MAX485_DE, OUTPUT);
  // Init in receive mode
  digitalWrite(MAX485_RE_NEG, 0);
  digitalWrite(MAX485_DE, 0);

  // Modbus communication runs at 115200 baud
  Serial.begin(115200);
  Serial1.begin(9600);

  // Modbus slave ID 1
  node.begin(1, Serial1);
  // Callbacks allow us to configure the RS485 transceiver correctly
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
}

bool state = true;
unsigned int sum =0;
void loop()
{
  uint8_t result;
  uint16_t data[6];
  byte dataT[2];
  
   //Toggle the coil at address 0x0002 (Manual Load Control)
  //result = node.writeSingleCoil(0x0000, 0x09);
 // state = !state;
Serial.println("5");
  // Read 16 registers starting at 0x3100)
  result = node.readInputRegisters(0x0000, 60);
  //Serial.println(result);
  if (result == node.ku8MBSuccess)
  {
    
  // dataT = node.getResponseBuffer(0x40);
   
   //Serial.println(node.getResponseBuffer(0x00),HEX);
  // Serial.println(node.getResponseBuffer(0x01),HEX);
   dataT[0] = node.getResponseBuffer(0x00);
   
   dataT[1] = node.getResponseBuffer(0x00);
   //Serial.println(dataT[1],BIN);
   //Serial.println(dataT[0],BIN);
    Serial.println(dataT[1],DEC);
  // Serial.println(dataT[0],DEC);
  // sum = dataT[0]+dataT[1];
  //no Serial.println(sum);
  // Serial.println(dataT[1],DEC);
  // dataT = node.getResponseBuffer(0x00) ;
  //  Serial.println(dataT,DEC);
    
  }
node.clearResponseBuffer();
  delay(1000);
}
