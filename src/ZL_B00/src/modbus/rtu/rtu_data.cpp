#include "modbus_wrapper.h"

int32_t ModbusWrapper::read_data_rtu(int32_t address, int32_t read_len, uint16_t* dest)
{
  // modbus 연결 되어있지 않으면 return
  if(!_is_connected) return -1;

  // data 읽기
  std::lock_guard<std::recursive_mutex> lock(_mtx);
  int32_t   read_bits = modbus_read_registers(_modbus, address, read_len, dest);

  // 읽어들인 Data 길이 확인
  if(read_bits != read_len)
  {
    LOGGER->push_log_format("ERROR", "PROC", "modbus_read_registers fail !!!", "");
    LOGGER->push_log_format("ERROR", "PROC", "Error Number", modbus_strerror(errno));
    LOGGER->push_log_format("ERROR", "PROC", "Register Address", std::to_string(address));
    LOGGER->push_log_format("ERROR", "PROC", "read_len", std::to_string(read_len));
    LOGGER->push_log_format("ERROR", "PROC", "read_registers", std::to_string(read_bits));
    disconnect_modbus_rtu();
    return -1;
  }
  return read_bits;
}

int32_t ModbusWrapper::write_data_rtu(int32_t address, int32_t status)
{
  // modbus 연결 되어있지 않으면 return
  if(!_is_connected) return -1;
  std::stringstream log_stream;
  // data 쓰기
  std::lock_guard<std::recursive_mutex> lock(_mtx);
  int32_t                     write_bits = modbus_write_register(_modbus, address, status);
  log_stream << "address : " << std::hex << address << ", status : " << std::hex << status;
  // 쓰기 성공 여부 확인
  if(write_bits != 1)
  {
    LOGGER->push_log_format("ERROR", "PROC", "Error Number", modbus_strerror(errno));
    LOGGER->push_log_format("ERROR", "PROC", "Register Address", std::to_string(address));
    LOGGER->push_log_format("ERROR", "PROC", "Status", std::to_string(status));
    disconnect_modbus_rtu();
    return -1;
  }
  LOGGER->push_log_format("INFO", "PROC", "Success modbus write. ", log_stream.str());
  
  return write_bits;
}

int32_t ModbusWrapper::write_datas_rtu(int32_t address, int32_t size, const uint16_t* data)
{
  // modbus 연결 되어있지 않으면 return
  if(!_is_connected) return -1;
  std::stringstream log_stream;
  // data 쓰기
  std::lock_guard<std::recursive_mutex> lock(_mtx);
  int32_t                     write_bits = modbus_write_registers(_modbus, address, size, data);
  log_stream << "address : " << std::hex << address 
             << ", size : " << std::hex << size 
             << ", data : " << std::hex << *data << " " << std::hex << *(data+1) ;
  // 쓰기 성공 여부 확인
  if(write_bits != size)
  {
    LOGGER->push_log_format("ERROR", "PROC", "modbus_write_registers fail !!!", "");
    LOGGER->push_log_format("ERROR", "PROC", "Error Number", modbus_strerror(errno));
    LOGGER->push_log_format("ERROR", "PROC", "Register Address", std::to_string(address));

    disconnect_modbus_rtu();
    return -1;
  }
  LOGGER->push_log_format("INFO", "PROC", "Success modbus write. ", log_stream.str());
  return write_bits;
}