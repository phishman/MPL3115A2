#include <inttypes.h>
#include "MPL3115A2.h"
#include "Wire.h"



MPL3115A2Class::MPL3115A2Class()
{
    m_i2c_address = 0x60;
    _p_msb = 0;
    _p_csb = 0;
    _p_lsb = 0;
	_t_msb = 0;
	_t_lsb = 0;

	Wire.begin();
}

void MPL3115A2Class::begin()
{

  SetStatus(STANDBY);
  SetStatus(ACTIVE);
}

bool MPL3115A2Class::Detect(void)
{
  ;
}

void MPL3115A2Class::SetStatus(uint8_t StatMask)
{
  SetStatus(MPL3115_REG_STATUS, StatMask);
}

void MPL3115A2Class::SetStatus(uint8_t ctrl_register, uint8_t StatMask)
{
  Wire.beginTransmission(MPL3115_I2C_ADDRESS); 
  Wire.send(ctrl_register); 
  Wire.send(StatMask);
  Wire.endTransmission();
}

uint8_t MPL3115A2Class::GetStatus(void)
{
  return(GetStatus(MPL3115_REG_STATUS));
}

uint8_t MPL3115A2Class::GetStatus(uint8_t ctrl_register)
{
  uint8_t CurrStatus;
  
  Wire.beginTransmission(MPL3115_I2C_ADDRESS); 
  Wire.send(ctrl_register); 
  Wire.endTransmission();

  Wire.requestFrom(MPL3115_I2C_ADDRESS, 1);
  if (Wire.available()) {
	CurrStatus = Wire.receive();
  }
  
  return(CurrStatus); 
}

float MPL3115A2Class::getPressure()
{
    
  
  Wire.beginTransmission(MPL3115_I2C_ADDRESS); 
  Wire.send(0x01);        // Data_PMSB_reg address
  Wire.endTransmission();    //Stop transmission
  
  Wire.requestFrom(MPL3115_I2C_ADDRESS, 3); // "please send me the contents of your first three registers"
  uint16_t Count = 0; 
  while((Wire.available()==0) && (Count < 5000)) {
   	Count++;
  }
  _p_msb = Wire.receive(); // first received byte stored here
  while((Wire.available()==0) && (Count < 5000)) {
	Count++;
  }
  _p_csb = Wire.receive(); // second received byte stored here
  while((Wire.available()==0) && (Count < 5000)) {
	Count++;
  }
  _p_lsb = Wire.receive(); // third received byte stored here
  
  Baro = convert20bit(_p_msb, _p_csb, _p_lsb);
  
} 


float MPL3115A2Class::getAlt()
{

}

float MPL3115A2Class::getTemp()
{
  Wire.beginTransmission(MPL3115_I2C_ADDRESS); 
  Wire.send(0x04);        // Data_PMSB_reg address
  Wire.endTransmission();    //Stop transmission
  
  Wire.requestFrom(MPL3115_I2C_ADDRESS, 2); // "please send me the contents of your first three registers"
  uint16_t Count = 0;
   while((Wire.available()==0) && (Count < 5000)) {
	Count++;
  }
  _t_lsb = Wire.receive(); // first received byte stored here
  while((Wire.available()==0) && (Count < 5000)) {
	Count++;
  }
  _t_msb = Wire.receive(); // second received byte stored here
}

void MPL3115A2Class::shutdown()
{
  ;
}

uint32_t MPL3115A2Class::convert20bit(uint8_t _msb, uint8_t _csb, uint8_t _lsb)
{
  uint8_t frac, tmp;
  uint32_t val;
  uint32_t retval;
  
  typedef struct {
    uint8_t lsb;
	uint8_t csb;
	uint8_t msb;
	uint8_t mmsb;
  } longstruct;
  
  union {
    longstruct ls;
	uint32_t longval;
  } lu;
  
  lu.ls.mmsb = 0;
  lu.ls.msb = _msb;
  lu.ls.csb = _csb;
  lu.ls.lsb = (_lsb & 0xFC);
  lu.longval <<= 2;
  
  frac = (_lsb & 0x0F);
  frac >>= 4;
  
  retval =  lu.longval;
 /* if(frac & 0x01) {
    retval += 0.5;
  }
  if(frac & 0x02) {
    retval += 0.25;
  }
  */
  return(retval);
}

MPL3115A2Class MPL3115A2;