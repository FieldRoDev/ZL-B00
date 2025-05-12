#pragma once

#include <ctime>
#include <fstream>
#include <iostream>
#include <mutex>
#include <string>

#include "logger.h"
#include "modbus/modbus.h"
#include "yaml-cpp/yaml.h"

#ifndef LOGGER
#define LOGGER Logger::get("ZL_B00")
#endif

enum class ModbusType
{
  RS232,
  RTU,
  TCP,
  END,
};

class ModbusWrapper
{
public:
  ModbusWrapper(ModbusType type, std::string option_file);
  ~ModbusWrapper();

private:
  ModbusWrapper() {};

public:
  bool connect_check();
  bool is_connect();

  // TCP
  int32_t read_data_tcp(int32_t address, int32_t read_len, uint8_t* dest);
  int32_t write_data_tcp(int32_t address, int32_t status);

  // RTU
  int32_t read_data_rtu(int32_t address, int32_t read_len, uint16_t* dest);
  int32_t write_data_rtu(int32_t address, int32_t status);
  int32_t write_datas_rtu(int32_t address, int32_t size, const uint16_t* data);
  int32_t set_slave_id(int32_t id);

protected:
  modbus_t*         _modbus;
  ModbusType        _type;
  static std::recursive_mutex _mtx;  // 공유를 위한 정적 mutex 객체

  // // ROS Parameter Server 관련 변수
  // ros::NodeHandle* _node_handle;
  // ros::NodeHandle  _private_node_handle;

  // TCP
  std::string _ip;
  int32_t     _port;

  // RTU
  std::string _device_name;
  int32_t     _baudrate;
  int16_t     _stop_bit;
  int16_t     _slave_id;

  bool        _is_connected;
  std::time_t _last_try_connect_time;
  std::time_t _last_retry_time;
  int32_t     _retry_count;
  int32_t     _retry_limit;
  int32_t     _retry_turm;

protected:
  // TCP
  void load_option_tcp(std::string file_name);
  bool try_connect_modbus_tcp();
  bool connect_modbus_tcp();
  void disconnect_modbus_tcp();
  bool modbus_tcp_connect_check();

  // RTU
  void load_option_rtu(std::string file_name);
  bool try_connect_modbus_rtu();
  bool connect_modbus_rtu();
  void disconnect_modbus_rtu();
  bool modbus_rtu_connect_check();
};