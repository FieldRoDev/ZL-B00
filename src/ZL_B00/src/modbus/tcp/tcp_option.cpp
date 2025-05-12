#include "modbus_wrapper.h"

void ModbusWrapper::load_option_tcp(std::string file_name)
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

    // modbus tcp ip, port 정보
    _ip          = yaml["tcp"]["ip"].as<std::string>();
    _port        = yaml["tcp"]["port"].as<int32_t>();
    _retry_count = yaml["Modbus"]["retry_count"].as<int32_t>();
    _retry_turm  = yaml["Modbus"]["retry_turm"].as<int32_t>();
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