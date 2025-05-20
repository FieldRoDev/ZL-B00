#include "ZL_B_steer.h"
#include "object_dictionary.h"
#include "data_converter.h"

ZL_B_steer::ZL_B_steer(SteerCallback steer_callback, std::string file_name)
{
  _steer_callback_function = std::move(steer_callback);
  _nh                      = new ros::NodeHandle;
  _spinner                 = new ros::AsyncSpinner(5);
  _spinner->start();
  load_option(file_name);
  steer_init();
}

ZL_B_steer::~ZL_B_steer()
{
  stop();
  safe_delete(_spinner);
  safe_delete(_nh);
}

void ZL_B_steer::steer_init()
{
  stop();
  set_din();
  set_position_mode();
  _get_velocity_position = _nh->subscribe<ZL_B00::pdo_tx_msgs>("pdo/tx", 100, &ZL_B_steer::get_velocity_position, this);
}

void ZL_B_steer::quick_stop()
{
  _steer_callback_function(COMMAND_WORD::DOUBLE_DATA, CANOPEN_OD::CONTROL_WORD_INDEX, 0x00, CANOPEN_OD::CONTROL_WORD_VALUE::QUICK_STOP);
}

void ZL_B_steer::stop()
{
  _steer_callback_function(COMMAND_WORD::DOUBLE_DATA, CANOPEN_OD::CONTROL_WORD_INDEX, 0x00, CANOPEN_OD::CONTROL_WORD_VALUE::STOP);
}

void ZL_B_steer::reset()
{
  _steer_callback_function(COMMAND_WORD::DOUBLE_DATA, CANOPEN_OD::CONTROL_WORD_INDEX, 0x00, CANOPEN_OD::CONTROL_WORD_VALUE::RESET);
}

void ZL_B_steer::move_to_origin()
{
  set_position(_origin_position);
  set_position_speed(_origin_speed);
  run_absolute_position();
}

void ZL_B_steer::set_position_mode()
{
  _steer_callback_function(COMMAND_WORD::SINGLE_DATA, CANOPEN_OD::OPMODE_INDEX, 0x00, CANOPEN_OD::OPMODE_VALUE::POSITION);
}

void ZL_B_steer::set_position(int32_t position)
{
  _set_position = position;
  _steer_callback_function(COMMAND_WORD::QUAD_DATA, CANOPEN_OD::POSITION_COMMAND_INDEX, 0x00, position);
}

void ZL_B_steer::set_degree(double degree)
{
  set_position(degree_to_position(degree));
}

void ZL_B_steer::set_radian(double radian)
{
  set_position(radian_to_position(radian));
}

void ZL_B_steer::set_position_speed(int32_t rpm)
{
  _set_velocity          = rpm;
  int32_t internal_speed = rpm_to_internal_velocity(rpm);
  _steer_callback_function(COMMAND_WORD::QUAD_DATA, CANOPEN_OD::POSITION_SPEED_COMMAND_INDEX, 0x00, static_cast<uint32_t>(internal_speed));
}

void ZL_B_steer::run_absolute_position()
{
  if(_positive_limit < _set_position)
  {
    LOGGER->push_log_format("ERROR", "PROC", "Positive limit over.", "positive limit : " + std::to_string(_positive_limit));
    return;
  }
  else if(_negative_limit > _set_position)
  {
    LOGGER->push_log_format("ERROR", "PROC", "Negative limit over.", "negative limit : " + std::to_string(_negative_limit));
    return;
  }
  else
  {
    _steer_callback_function(COMMAND_WORD::DOUBLE_DATA, CANOPEN_OD::CONTROL_WORD_INDEX, 0x00, CANOPEN_OD::CONTROL_WORD_VALUE::ABSOLUTE_POSITION_RUN_SET1);
    _steer_callback_function(COMMAND_WORD::DOUBLE_DATA, CANOPEN_OD::CONTROL_WORD_INDEX, 0x00, CANOPEN_OD::CONTROL_WORD_VALUE::ABSOLUTE_POSITION_RUN_SET2);
  }
}

void ZL_B_steer::run_incremental_position()
{
  if(_positive_limit < (_current_position + _set_position))
  {
    LOGGER->push_log_format("ERROR", "PROC", "Positive limit over.", "positive limit : " + std::to_string(_positive_limit));
    return;
  }
  else if(_negative_limit > (_current_position +_set_position))
  {
    LOGGER->push_log_format("ERROR", "PROC", "Negative limit over.", "negative limit : " + std::to_string(_negative_limit));
    return;
  }
  else
  {
    _steer_callback_function(COMMAND_WORD::DOUBLE_DATA, CANOPEN_OD::CONTROL_WORD_INDEX, 0x00, CANOPEN_OD::CONTROL_WORD_VALUE::INCREMENT_POSITION_RUN_SET1);
    _steer_callback_function(COMMAND_WORD::DOUBLE_DATA, CANOPEN_OD::CONTROL_WORD_INDEX, 0x00, CANOPEN_OD::CONTROL_WORD_VALUE::INCREMENT_POSITION_RUN_SET2);
  }
}

void ZL_B_steer::set_din()
{
  _steer_callback_function(COMMAND_WORD::DOUBLE_DATA, CANOPEN_OD::DIN_SETTING_INDEX, CANOPEN_OD::DIN_SETTING_SUB_INDEX::DIN1_FUNCTION, CANOPEN_OD::LIMIT_MODE_VALUE::POSITIVE);
  _steer_callback_function(COMMAND_WORD::DOUBLE_DATA, CANOPEN_OD::DIN_SETTING_INDEX, CANOPEN_OD::DIN_SETTING_SUB_INDEX::DIN2_FUNCTION, CANOPEN_OD::LIMIT_MODE_VALUE::NONE);
  _steer_callback_function(COMMAND_WORD::DOUBLE_DATA, CANOPEN_OD::DIN_SETTING_INDEX, CANOPEN_OD::DIN_SETTING_SUB_INDEX::DIN3_FUNCTION, CANOPEN_OD::LIMIT_MODE_VALUE::NEGATIVE);
}

void ZL_B_steer::get_velocity_position(ZL_B00::pdo_tx_msgs msg)
{
  switch(msg.id)
  {
    case 0x182:
    {
      int32_t value = static_cast<int32_t>(
                    msg.data[0] |
                    (msg.data[1] << 8) |
                    (msg.data[2] << 16) |
                    (msg.data[3] << 24));
      _current_position = value;
      break;
    }

    case 0x282:
    {
      int32_t value = static_cast<int32_t>(
                    msg.data[0] |
                    (msg.data[1] << 8) |
                    (msg.data[2] << 16) |
                    (msg.data[3] << 24));
      _current_velocity = internal_velocity_to_rpm(value);
      break;
    }

    default: return;
  }
}

void ZL_B_steer::load_option(std::string file_name)
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

    // modbus rtu information
    _origin_position = yaml["steer"]["origin"].as<int32_t>();
    _origin_speed = yaml["steer"]["origin_speed"].as<int32_t>();
    _positive_limit = yaml["steer"]["positive_limit"].as<int32_t>();
    _negative_limit = yaml["steer"]["negative_limit"].as<int32_t>();
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