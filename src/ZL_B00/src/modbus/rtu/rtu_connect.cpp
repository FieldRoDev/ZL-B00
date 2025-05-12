#include "modbus_wrapper.h"

bool ModbusWrapper::modbus_rtu_connect_check()
{
  if(_is_connected) return true;
  if(_retry_count == 0) return false;

  if(!try_connect_modbus_rtu())
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
bool ModbusWrapper::connect_modbus_rtu()
{
  std::lock_guard<std::recursive_mutex> lock(_mtx);
  // 1. modbus context 생성
  _modbus = modbus_new_rtu(_device_name.c_str(), _baudrate, 'N', 8, _stop_bit);

  if(_modbus == nullptr)
  {
    LOGGER->push_log_format("ERROR", "PROC", "modbus_new_rtu context fail !!!", "");
    return false;
  }
  else
  {
    LOGGER->push_log_format("INFO", "PROC", "context success", "");
  }

  // 2. modbus rtu mode 설정
  modbus_rtu_set_serial_mode(_modbus, MODBUS_RTU_RS485);

  // // 3. modbus rtu RTS 설정
  // // RTS(Request To Send) 신호 동작 설정
  // modbus_rtu_set_rts(_modbus, MODBUS_RTU_RTS_UP);

  // 4. modbus slave 번호 설정
  // 직렬 통신의 경우 slave 번호를 설정
  if((modbus_set_slave(_modbus, _slave_id)) == -1)
    LOGGER->push_log_format("ERROR", "PROC", "Fail to set slave id", "");

  // 5. modbus 연결
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
    LOGGER->push_log_format("INFO", "PROC", "Slave ID ", std::to_string(_slave_id));
    LOGGER->push_log_format("INFO", "PROC", "connect success", "");
  }
  return true;
}

bool ModbusWrapper::try_connect_modbus_rtu()
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

  if(connect_modbus_rtu() == false)
  {
    LOGGER->push_log_format("ERROR", "PROC", "modbus_connect fail !!!", "");
    LOGGER->push_log_format("ERROR", "PROC", "Error Number", modbus_strerror(errno));
    return false;
  }
  else
  {
    LOGGER->push_log_format("INFO", "PROC", "try_connect_modbus_rtu success !!!", "");
    _retry_count = _retry_limit;
  }
  _is_connected = true;
  return true;
}

void ModbusWrapper::disconnect_modbus_rtu()
{
  std::lock_guard<std::recursive_mutex> lock(_mtx);

  if(_modbus == nullptr) return;
  if(!_is_connected) return;

  _is_connected = false;
  modbus_close(_modbus);  // Modbus RTU Socket Close
  modbus_flush(_modbus);  // Modbus Buffer Clear
  modbus_free(_modbus);   // Modbus Context Association Resource Delete
  _modbus = nullptr;

  LOGGER->push_log_format("INFO", "PROC", "Slave ID ", std::to_string(_slave_id));
  LOGGER->push_log_format("INFO", "PROC", "modbus_rtu is disconnect", "");
}

int32_t ModbusWrapper::set_slave_id(int32_t id)
{
  if (_modbus == NULL) {
    LOGGER->push_log_format("ERROR", "PROC", "modbus_rtu is empty.", "");
    return -1;
  }
  return modbus_set_slave(_modbus, id);
}