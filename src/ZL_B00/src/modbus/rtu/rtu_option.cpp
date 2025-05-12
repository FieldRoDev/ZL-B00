#include "modbus_wrapper.h"

void ModbusWrapper::load_option_rtu(std::string file_name)
{
  try
  {
    // file open
    std::ifstream yaml_file(file_name);
    YAML::Node    yaml = YAML::Load(yaml_file);
    yaml_file.close();

    // data read
    std::string config_name = yaml["config_name"].as<std::string>();
    std::cout << config_name << std::endl;

    // modbus rtu 정보
    _retry_limit = yaml["modbus"]["retry_limit"].as<int32_t>();
    _retry_turm  = yaml["modbus"]["retry_turm"].as<int32_t>();
    _device_name = yaml["rtu"]["device"].as<std::string>();
    _baudrate    = yaml["rtu"]["baudrate"].as<int32_t>();
    _stop_bit    = yaml["rtu"]["stop_bit"].as<int32_t>();
    _slave_id    = yaml["rtu"]["slave_id"].as<std::int32_t>();
  }
  catch(YAML::Exception& e)
  {
    LOGGER->push_log_format("ERROR", "PROC", "YAML Exception", e.what());
  }
  catch(std::exception& e)
  {
    LOGGER->push_log_format("ERROR", "PROC", "Standard Exception", e.what());
  }
  catch(...)
  {
    LOGGER->push_log_format("ERROR", "PROC", "Unknown Exception", "");
  }
}