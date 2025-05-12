#include "modbus_wrapper.h"

std::recursive_mutex ModbusWrapper::_mtx;

ModbusWrapper::ModbusWrapper(ModbusType type, std::string option_file)
{
  _type = type;

  _modbus                = nullptr;  // modbus 객체 초기화
  _is_connected          = false;    // modbus 연결 여부 초기화
  _last_try_connect_time = 0;        // 마지막 modbus 연결 시도 시간 초기화
  _last_retry_time       = 0;

  switch(_type)
  {
    case ModbusType::RS232: break;
    case ModbusType::RTU: load_option_rtu(option_file); break;
    case ModbusType::TCP: load_option_tcp(option_file); break;
  }

  _retry_count = _retry_limit;
}

ModbusWrapper::~ModbusWrapper()
{
  switch(_type)
  {
    case ModbusType::RS232: break;
    case ModbusType::RTU: disconnect_modbus_rtu(); break;
    case ModbusType::TCP: disconnect_modbus_tcp(); break;
  }
}

bool ModbusWrapper::connect_check()
{
  switch(_type)
  {
    case ModbusType::RS232: return false;
    case ModbusType::RTU: return modbus_rtu_connect_check();
    case ModbusType::TCP: return modbus_tcp_connect_check();
  }
  return false;
}

bool ModbusWrapper::is_connect() { return _is_connected; }