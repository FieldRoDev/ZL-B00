#include "ZL_B_traction.h"
#include "object_dictionary.h"
#include "data_converter.h"

ZL_B_traction::ZL_B_traction(TractionCallback traction_callback)
{
  _traction_callback_function = std::move(traction_callback);
  _nh                         = new ros::NodeHandle;
  _spinner                    = new ros::AsyncSpinner(5);
  _spinner->start();
  traction_init();
}

ZL_B_traction::~ZL_B_traction()
{
  stop();
  safe_delete(_spinner);
  safe_delete(_nh);
}

void ZL_B_traction::traction_init()
{
  stop();
  set_din();
  set_velocity_mode();
  _get_velocity_position = _nh->subscribe<ZL_B00::pdo_tx_msgs>("pdo/tx", 100, &ZL_B_traction::get_velocity_position, this);
}

void ZL_B_traction::quick_stop()
{
  _traction_callback_function(COMMAND_WORD::DOUBLE_DATA, CANOPEN_OD::CONTROL_WORD_INDEX, 0x00, CANOPEN_OD::CONTROL_WORD_VALUE::QUICK_STOP);
}

void ZL_B_traction::stop()
{
  _traction_callback_function(COMMAND_WORD::DOUBLE_DATA, CANOPEN_OD::CONTROL_WORD_INDEX, 0x00, CANOPEN_OD::CONTROL_WORD_VALUE::STOP);
}

void ZL_B_traction::reset()
{
  _traction_callback_function(COMMAND_WORD::DOUBLE_DATA, CANOPEN_OD::CONTROL_WORD_INDEX, 0x00, CANOPEN_OD::CONTROL_WORD_VALUE::RESET);
}

void ZL_B_traction::set_position_mode()
{
  stop();
  _opmode = "POSITION";
  _traction_callback_function(COMMAND_WORD::SINGLE_DATA, CANOPEN_OD::OPMODE_INDEX, 0x00, CANOPEN_OD::OPMODE_VALUE::POSITION);
}

void ZL_B_traction::set_velocity_mode()
{
  stop();
  _opmode = "VELOCITY";
  _traction_callback_function(COMMAND_WORD::SINGLE_DATA, CANOPEN_OD::OPMODE_INDEX, 0x00, CANOPEN_OD::OPMODE_VALUE::VELOCITY);
}

void ZL_B_traction::set_position(int32_t position)
{
  _set_position = position;
  _traction_callback_function(COMMAND_WORD::QUAD_DATA, CANOPEN_OD::POSITION_COMMAND_INDEX, 0x00, position);
}

void ZL_B_traction::set_velocity(int32_t rpm)
{
  _set_velocity          = rpm;
  int32_t internal_speed = rpm_to_internal_velocity(rpm);
  if(_opmode == "VELOCITY")
  {
    _traction_callback_function(COMMAND_WORD::QUAD_DATA, CANOPEN_OD::VELOCITY_COMMAND_INDEX, 0x00, static_cast<uint32_t>(internal_speed));
  }
  else if(_opmode == "POSITION")
  {
    _traction_callback_function(COMMAND_WORD::QUAD_DATA, CANOPEN_OD::POSITION_SPEED_COMMAND_INDEX, 0x00, static_cast<uint32_t>(internal_speed));
  }
}

void ZL_B_traction::run_velocity()
{
  if(_opmode != "VELOCITY")
  {
    LOGGER->push_log_format("ERROR", "PROC", "SET VELOCITY MODE FIRST", "");
    return;
  }
  _traction_callback_function(COMMAND_WORD::DOUBLE_DATA, CANOPEN_OD::CONTROL_WORD_INDEX, 0x00, CANOPEN_OD::CONTROL_WORD_VALUE::START);
}

void ZL_B_traction::run_incremental_position()
{
  if(_opmode != "POSITION")
  {
    LOGGER->push_log_format("ERROR", "PROC", "SET POSITION MODE FIRST", "");
    return;
  }
  _traction_callback_function(COMMAND_WORD::DOUBLE_DATA, CANOPEN_OD::CONTROL_WORD_INDEX, 0x00, CANOPEN_OD::CONTROL_WORD_VALUE::INCREMENT_POSITION_RUN_SET1);
  _traction_callback_function(COMMAND_WORD::DOUBLE_DATA, CANOPEN_OD::CONTROL_WORD_INDEX, 0x00, CANOPEN_OD::CONTROL_WORD_VALUE::INCREMENT_POSITION_RUN_SET2);
}

void ZL_B_traction::run_absolute_position()
{
  if(_opmode != "POSITION")
  {
    LOGGER->push_log_format("ERROR", "PROC", "SET POSITION MODE FIRST", "");
    return;
  }
  _traction_callback_function(COMMAND_WORD::DOUBLE_DATA, CANOPEN_OD::CONTROL_WORD_INDEX, 0x00, CANOPEN_OD::CONTROL_WORD_VALUE::ABSOLUTE_POSITION_RUN_SET1);
  _traction_callback_function(COMMAND_WORD::DOUBLE_DATA, CANOPEN_OD::CONTROL_WORD_INDEX, 0x00, CANOPEN_OD::CONTROL_WORD_VALUE::ABSOLUTE_POSITION_RUN_SET2);
}

void ZL_B_traction::set_din()
{
  _traction_callback_function(COMMAND_WORD::DOUBLE_DATA, CANOPEN_OD::DIN_SETTING_INDEX, CANOPEN_OD::DIN_SETTING_SUB_INDEX::DIN1_FUNCTION, CANOPEN_OD::LIMIT_MODE_VALUE::NONE);
  _traction_callback_function(COMMAND_WORD::DOUBLE_DATA, CANOPEN_OD::DIN_SETTING_INDEX, CANOPEN_OD::DIN_SETTING_SUB_INDEX::DIN2_FUNCTION, CANOPEN_OD::LIMIT_MODE_VALUE::NONE);
  _traction_callback_function(COMMAND_WORD::DOUBLE_DATA, CANOPEN_OD::DIN_SETTING_INDEX, CANOPEN_OD::DIN_SETTING_SUB_INDEX::DIN3_FUNCTION, CANOPEN_OD::LIMIT_MODE_VALUE::NONE);
}

void ZL_B_traction::get_velocity_position(ZL_B00::pdo_tx_msgs msg)
{
  switch(msg.id)
  {
    case 0x181:
    {
      int32_t value = static_cast<int32_t>(
                    msg.data[0] |
                    (msg.data[1] << 8) |
                    (msg.data[2] << 16) |
                    (msg.data[3] << 24));
      _current_position = value;
      break;
    }

    case 0x281:
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