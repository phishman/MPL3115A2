#ifndef MPL3115A2_h
#define MPL3115A2_h

#include <inttypes.h>
#include <Wire.h>

#define MPL3115_I2C_ADDRESS         0x60

#define MPL3115_REG_STATUS          0x00
#define MPL3115_REG_OUT_P_MSB       0x01
#define MPL3115_REG_OUT_P_CSB       0x02
#define MPL3115_REG_OUT_P_LSB       0x03
#define MPL3115_REG_OUT_T_MSB       0x04
#define MPL3115_REG_OUT_T_LSB       0x05
#define MPL3115_REG_DR_STATUS       0x06
#define MPL3115_REG_WHO_AM_I        0x0C
#define MPL3115_REG_SYSMOD          0x11
#define MPL3115_REG_PT_DATA_CFG     0x13
#define MPL3115_REG_BAR_IN_MSB      0x14
#define MPL3115_REG_BAR_IN_LSB      0x15
#define MPL3115_REG_CTRL_REG1       0x26
#define MPL3115_REG_CTRL_REG2       0x27
#define MPL3115_REG_CTRL_REG3       0x28
#define MPL3115_REG_CTRL_REG4       0x29
#define MPL3115_REG_CTRL_REG5       0x2A
#define MPL3115_REG_OFF_P           0x2B
#define MPL3115_REG_OFF_T           0x2C
#define MPL3115_REG_OFF_H           0x2D

/* Register values, masks */
#define MPL3115_WHO_AM_I_RESP       0xC4

#define MPL3115_PT_DATA_DREM        0x04
#define MPL3115_PT_DATA_PDEF        0x02
#define MPL3115_PT_DATA_TDEF        0x01
                                    
#define MPL3115_DR_STATUS_TDR       0x02
#define MPL3115_DR_STATUS_PDR       0x04
#define MPL3115_DR_STATUS_PTDR      0x08
#define MPL3115_DR_STATUS_DR        (MPL3115_DR_STATUS_TDR | MPL3115_DR_STATUS_PDR | MPL3115_DR_STATUS_PTDR)
                                    
#define MPL3115_DR_STATUS_TOW       0x20
#define MPL3115_DR_STATUS_POW       0x40
#define MPL3115_DR_STATUS_PTOW      0x80

#define MPL3115_CTRL_REG1_ALT       0x80
#define MPL3115_CTRL_REG1_RAW       0x40
#define MPL3115_CTRL_REG1_OST_MASK  0x38
#define MPL3115_CTRL_REG1_OST_1     0x00
#define MPL3115_CTRL_REG1_OST_2     0x08
#define MPL3115_CTRL_REG1_OST_4     0x10
#define MPL3115_CTRL_REG1_OST_8     0x18
#define MPL3115_CTRL_REG1_OST_16    0x20
#define MPL3115_CTRL_REG1_OST_32    0x28
#define MPL3115_CTRL_REG1_OST_64    0x30
#define MPL3115_CTRL_REG1_OST_128   0x38
#define MPL3115_CTRL_REG1_RST       0x04
#define MPL3115_CTRL_REG1_OST       0x02
#define MPL3115_CTRL_REG1_SBYB      0x01
#define MPL3115_CTRL_REG1_SBYB_MASK 0xFE

#define MPL3115_NUM_CONV_VALS       5


/* ------------ Normalization ------------ */
/* Mean sea level pressure normalization methods */
#define MSLP_NONE          0
#define MSLP_INTERNATIONAL 1
#define MSLP_DEU_WETT      2

#define STANDBY	0x00
#define ACTIVE 0x01
#define ALTMODE 0x80
#define BARMODE 0x7F

class MPL3115A2Class{
public:
  MPL3115A2Class(); 
  void begin();
  bool Detect(void);
  float getPressure();
  float getAlt();
  float getTemp();
  void shutdown();
  uint8_t GetStatus(void);
  uint8_t GetStatus(uint8_t ctrl_register);
  void SetStatus(uint8_t StatusMask);
  void SetStatus(uint8_t ctrl_register, uint8_t StatusMask);
  uint8_t _p_msb, _p_csb, _p_lsb, _t_msb, _t_lsb;
  uint32_t Baro;
private:
  int m_i2c_address;
  uint32_t convert20bit(uint8_t _msb, uint8_t _csb, uint8_t _lsb);
};

extern MPL3115A2Class MPL3115A2;

#endif 
