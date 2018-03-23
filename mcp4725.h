#ifdef __cplusplus
extern "C" {
#endif

#ifndef MCP4725_H
#define MCP4725_H


#include <stdio.h>
#include "driver/i2c.h"

#define MCP4725_WRITE_FAST        0x00
#define MCP4725_WRITE_DAC         0x40
#define MCP4725_WRITE_DAC_EEPROM  0x60
#define MCP4725_MASK              0xFF

typedef enum {
  MCP4725_POWER_DOWN_0 = 0,
  MCP4725_POWER_DOWN_1,
  MCP4725_POWER_DOWN_100,
  MCP4725_POWER_DOWN_500
} mcp4725_power_down_t;

typedef struct {
  i2c_port_t i2c_bus;
  uint8_t address;
  portBASE_TYPE ticks_to_wait;
} mcp4725_config_t;

typedef struct {
  mcp4725_power_down_t power_down_mode;
  uint16_t input_data;
} mcp4725_eeprom_t;

esp_err_t mcp4725_set_voltage(mcp4725_config_t dac,uint16_t value);
esp_err_t mcp4725_power_down(mcp4725_config_t dac,mcp4725_power_down_t mode);
esp_err_t mcp4725_read_eeprom(mcp4725_config_t dac,mcp4725_eeprom_t* eeprom);
esp_err_t mcp4725_write_eeprom(mcp4725_config_t dac,mcp4725_eeprom_t eeprom);

#endif

#ifdef __cplusplus
}
#endif
