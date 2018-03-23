#include "mcp4725.h"

esp_err_t mcp4725_set_voltage(mcp4725_config_t dac,uint16_t value) {
  i2c_cmd_handle_t cmd = i2c_cmd_link_create(); // make a command
  i2c_master_start(cmd); // start command
  i2c_master_write_byte(cmd,(dac.address << 1) | I2C_MASTER_WRITE,1); // write to address
  
  i2c_master_write_byte(cmd,(value >> 8) | MCP4725_WRITE_FAST,1); // write upper 4 bits
  i2c_master_write_byte(cmd,value & MCP4725_MASK,1); // write lower 8 bits
  
  i2c_master_stop(cmd);
  esp_err_t ret = i2c_master_cmd_begin(dac.i2c_bus,cmd,dac.ticks_to_wait); // begin sending command
  i2c_cmd_link_delete(cmd);
  return ret;
}

esp_err_t mcp4725_power_down(mcp4725_config_t dac,mcp4725_power_down_t mode) {
  i2c_cmd_handle_t cmd = i2c_cmd_link_create(); // make a command
  i2c_master_start(cmd); // start command
  i2c_master_write_byte(cmd,(dac.address << 1) | I2C_MASTER_WRITE,1); // write to address
  
  i2c_master_write_byte(cmd,(mode<<4) | MCP4725_WRITE_FAST,1);
  i2c_master_write_byte(cmd,0,1);
  
  i2c_master_stop(cmd);
  esp_err_t ret = i2c_master_cmd_begin(dac.i2c_bus,cmd,dac.ticks_to_wait); // begin sending command
  i2c_cmd_link_delete(cmd);
  return ret;
}

esp_err_t mcp4725_read_eeprom(mcp4725_config_t dac,mcp4725_eeprom_t* eeprom) {
  uint8_t data_rd[5];
  
  i2c_cmd_handle_t cmd = i2c_cmd_link_create(); // make a command
  i2c_master_start(cmd); // start command
  i2c_master_write_byte(cmd,(dac.address << 1) | I2C_MASTER_READ,1); // read command to address
  
  i2c_master_read(cmd,data_rd,5,0); // read 5 bytes
  
  i2c_master_stop(cmd);
  esp_err_t ret = i2c_master_cmd_begin(dac.i2c_bus,cmd,dac.ticks_to_wait); // begin sending command
  i2c_cmd_link_delete(cmd);
  
  eeprom->power_down_mode =  (uint16_t)data_rd[3] >> 5;
  eeprom->input_data      = ((uint16_t)data_rd[3] & 0b1111) << 8;
  eeprom->input_data     |=  (uint16_t)data_rd[4];
  return ret;
}

esp_err_t mcp4725_write_eeprom(mcp4725_config_t dac,mcp4725_eeprom_t eeprom) {
  i2c_cmd_handle_t cmd = i2c_cmd_link_create(); // make a command
  i2c_master_start(cmd); // start command
  i2c_master_write_byte(cmd,(dac.address << 1) | I2C_MASTER_WRITE,1);
  
  i2c_master_write_byte(cmd,(eeprom.power_down_mode<<1) | MCP4725_WRITE_DAC_EEPROM,1);
  i2c_master_write_byte(cmd,eeprom.input_data>>4,1);
  i2c_master_write_byte(cmd,(eeprom.input_data<<4) & MCP4725_MASK,1);

  i2c_master_stop(cmd);
  esp_err_t ret = i2c_master_cmd_begin(dac.i2c_bus,cmd,dac.ticks_to_wait); // begin sending command
  i2c_cmd_link_delete(cmd);
  return ret;
}
