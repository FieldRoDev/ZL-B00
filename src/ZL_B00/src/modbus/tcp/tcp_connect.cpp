#include "modbus_wrapper.h"

bool ModbusWrapper::modbus_tcp_connect_check()
{
  if(_is_connected) return true;

  if(!try_connect_modbus_tcp())
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    return false;
  }

  return true;
}
/**
/* @brief  modbus 연결
/* @param  void
/* @return modbus 연결 결과
*/
bool ModbusWrapper::connect_modbus_tcp()
{
  // 1. modbus context 생성
  //_modbus = modbus_new_tcp(_ip.c_str(), _port);
  _modbus = modbus_new_tcp(_ip.c_str(), _port);

  if(_modbus == nullptr)
  {
    LOGGER->push_log_format("ERROR", "PROC", "modbus_new_tcp context fail !!!", "");
    return false;
  }
  else
  {
    LOGGER->push_log_format("INFO", "PROC", "context success", "");
  }

  // 2. modbus slave 번호 설정
  // 직렬 통신의 경우 slave 번호를 설정해야 하지만
  // TCP 통신의 경우 slave 번호를 설정하지 않아도 된다.

  // 3. modbus 연결
  if(modbus_connect(_modbus) == -1)
  {
    LOGGER->push_log_format("ERROR", "PROC", "modbus_connect fail !!!", "");
    LOGGER->push_log_format("ERROR", "PROC", "Error Number", modbus_strerror(errno));

    modbus_free(_modbus);
    _modbus = nullptr;
    return false;
  }
  else
  {
    LOGGER->push_log_format("INFO", "PROC", "connect success", "");
  }
  return true;
}

bool ModbusWrapper::try_connect_modbus_tcp()
{
  if(_modbus != nullptr) return false;  // 연결 된 상태이다.
  if(_last_try_connect_time + _retry_turm > std::time(nullptr))
    return false;  // turm 이내에 시도한 적이 있다.
  if(_retry_count <= 0)
  {
    LOGGER->push_log_format("ERROR", "PROC", "Retry Count", "0");
    return false;
  }  // 재시도 횟수를 모두 소진했다.

  LOGGER->push_log_format("INFO", "PROC", "Retry Count", std::to_string(_retry_count));
  _last_try_connect_time = std::time(nullptr);
  _retry_count--;

  if(connect_modbus_tcp() == false)
  {
    LOGGER->push_log_format("ERROR", "PROC", "modbus_connect fail !!!", "");
    LOGGER->push_log_format("ERROR", "PROC", "Error Number", modbus_strerror(errno));
    return false;
  }
  else
  {
    LOGGER->push_log_format("INFO", "PROC", "try_connect_modbus_rtu success !!!", "");
  }
  _is_connected = true;
  return true;
}

void ModbusWrapper::disconnect_modbus_tcp()
{
  if(_modbus == nullptr) return;

  _is_connected = false;
  modbus_close(_modbus);  // Modbus TCP Socket Close
  modbus_flush(_modbus);  // Modbus Buffer Clear
  modbus_free(_modbus);   // Modbus Context Association Resource Delete
  _modbus = nullptr;

  LOGGER->push_log_format("INFO", "PROC", "modbus_tcp is disconnect", "");
}