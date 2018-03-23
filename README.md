MCP4725 ESP-IDF
===============

An MCP4725 component on ESP-IDF. For an example, see https://github.com/Molorius/ESP32-Examples.

To add to a project, type: 
`git submodule add https://github.com/Molorius/esp32-mcp4725.git components/mcp4725`
into the base directory of your project.

Note that this does not initialize the I2C bus.

Table of Contents
=================
* [Enumerations](#enumerations)
  * [mcp4725_power_down_t](#enum-mcp4725_power_down_t)
* [Structures](#structures)
  * [mcp4725_config_t](#struct-mcp4725_config_t)
  * [mcp4725_eeprom_t](#struct-mcp4725_eeprom_t)
* [Functions](#functions)
  * [mcp4725_set_voltage](#esp_err_t-mcp4725_set_voltagemcp4725_config_t-dacuint16_t-value)
  * [mcp4725_power_down](#esp_err_t-mcp4725_power_downmcp4725_config_t-dacmcp4725_power_down_t-mode)
  * [mcp4725_read_eeprom](#esp_err_t-mcp4725_read_eeprommcp4725_config_t-dacmcp4725_eeprom_t-eeprom)
  * [mcp4725_write_eeprom](#esp_err_t-mcp4725_write_eeprommcp4725_config_t-dacmcp4725_eeprom_t-eeprom)

Enumerations
============

enum mcp4725_power_down_t
-------------------------

The normal and power-down modes.

*Values*
  * `MCP4725_POWER_DOWN_0 = 0`: Normal operation.
  * `MCP4725_POWER_DOWN_1`: Power-Down with 1kΩ resistor to ground.
  * `MCP4725_POWER_DOWN_100`: Power-Down with 100kΩ resistor to ground.
  * `MCP4725_POWER_DOWN_500`: Power-Down with 500kΩ resistor to ground.


Structures
==========

mcp4725_config_t
----------------

MCP4725 configuration.

*Members*
  * `i2c_port_t i2c_bus`: The I2C bus the MCP4725 is connected to.
  * `uint8_t address`: The I2C address.
  * `portBASE_TYPE ticks_to_wait`: The maximum wait ticks for all functions.

*Notes*
  * The I2C bus must be initialized before calling any functions.
  * `ticks_to_wait` must be at least 1 tick


struct mcp4725_eeprom_t
-----------------------

Stores the eeprom data for reading and writing.

*Members*
  * `mcp4725_power_down_t power_down_mode`: A normal or power-down mode on start.
  * `uint16_t input_data`: Value to write on start.

*Notes*
  * `input_data` must be no larger than 12 bits (4095).


Functions
=========

esp_err_t mcp4725_set_voltage(mcp4725_config_t dac,uint16_t value)
------------------------------------------------------------------

Sets the voltage on the MCP4725.

*Parameters*
  * `dac`: configuration of the bus, address, etc.
  * `value`: value to write to dac.

*Returns*
  * ESP_OK: Success
  * ESP_ERR_INVALID_ARG: Parameter error
  * ESP_FAIL: Sending command error, slave doesn’t ACK the transfer.
  * ESP_ERR_INVALID_STATE I2C: Driver not installed or not in master mode.
  * ESP_ERR_TIMEOUT: Operation timeout because the bus is busy.

*Notes* 
  * `value` must be no larger than 12 bits (4095).
  * This will wake from power-down mode, if set.


esp_err_t mcp4725_power_down(mcp4725_config_t dac,mcp4725_power_down_t mode)
----------------------------------------------------------------------------

Puts the device into the desired power-down mode. 

*Parameters*
  * `dac`: configuration of the bus, address, etc.
  * `mode`: the desired power-down mode.

*Returns*
  * ESP_OK: Success
  * ESP_ERR_INVALID_ARG: Parameter error
  * ESP_FAIL: Sending command error, slave doesn’t ACK the transfer.
  * ESP_ERR_INVALID_STATE I2C: Driver not installed or not in master mode.
  * ESP_ERR_TIMEOUT: Operation timeout because the bus is busy.

*Notes*
  * Also writes a `value` of 0 to the dac.


esp_err_t mcp4725_read_eeprom(mcp4725_config_t dac,mcp4725_eeprom_t* eeprom)
----------------------------------------------------------------------------

Read the values to be set at start from the eeprom and puts them in `eeprom`.

*Parameters*
  * `dac`: configuration of the bus, address, etc.
  * `eeprom`: structure to hold the saved values.

*Returns*
  * ESP_OK: Success
  * ESP_ERR_INVALID_ARG: Parameter error
  * ESP_FAIL: Sending command error, slave doesn’t ACK the transfer.
  * ESP_ERR_INVALID_STATE I2C: Driver not installed or not in master mode.
  * ESP_ERR_TIMEOUT: Operation timeout because the bus is busy.


esp_err_t mcp4725_write_eeprom(mcp4725_config_t dac,mcp4725_eeprom_t eeprom)
----------------------------------------------------------------------------

Write values to be set at start to the eeprom.

*Parameters*
  * `dac`: configuration of the bus, address, etc.
  * `eeprom`: structure of the desired values.

*Returns*
  * ESP_OK: Success
  * ESP_ERR_INVALID_ARG: Parameter error
  * ESP_FAIL: Sending command error, slave doesn’t ACK the transfer.
  * ESP_ERR_INVALID_STATE I2C: Driver not installed or not in master mode.
  * ESP_ERR_TIMEOUT: Operation timeout because the bus is busy.

*Notes*
  * Wait roughly 40 milliseconds before making another I2C call.
