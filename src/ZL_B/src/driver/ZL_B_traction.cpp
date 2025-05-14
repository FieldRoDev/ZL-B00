#include "ZL_B_traction.h"
#include "object_dictionary.h"
#include "data_converter.h"

ZL_B_traction::ZL_B_traction(TractionCallback traction_callback)
{
  _traction_callback_function = std::move(traction_callback);
  traction_init();
}

ZL_B_traction::~ZL_B_traction()
{
  stop();
}

void ZL_B_traction::traction_init()
{
  stop();
  set_velocity_mode();
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

void ZL_B_traction::set_velocity_mode()
{
  _traction_callback_function(COMMAND_WORD::SINGLE_DATA, CANOPEN_OD::OPMODE_INDEX, 0x00, CANOPEN_OD::OPMODE_VALUE::VELOCITY);
}

void ZL_B_traction::set_velocity(int32_t rpm)
{
  int32_t internal_speed = rpm_to_internal_velocity(rpm);
  _traction_callback_function(COMMAND_WORD::QUAD_DATA, CANOPEN_OD::VELOCITY_COMMAND_INDEX, 0x00, static_cast<uint32_t>(internal_speed));
}

void ZL_B_traction::run_velocity()
{
  _traction_callback_function(COMMAND_WORD::DOUBLE_DATA, CANOPEN_OD::CONTROL_WORD_INDEX, 0x00, CANOPEN_OD::CONTROL_WORD_VALUE::START);
}

void ZL_B_traction::set_din()
{
  _traction_callback_function(COMMAND_WORD::DOUBLE_DATA, CANOPEN_OD::DIN_SETTING_INDEX, CANOPEN_OD::DIN_SETTING_SUB_INDEX::DIN1_FUNCTION, CANOPEN_OD::LIMIT_MODE_VALUE::NONE);
  _traction_callback_function(COMMAND_WORD::DOUBLE_DATA, CANOPEN_OD::DIN_SETTING_INDEX, CANOPEN_OD::DIN_SETTING_SUB_INDEX::DIN2_FUNCTION, CANOPEN_OD::LIMIT_MODE_VALUE::NONE);
  _traction_callback_function(COMMAND_WORD::DOUBLE_DATA, CANOPEN_OD::DIN_SETTING_INDEX, CANOPEN_OD::DIN_SETTING_SUB_INDEX::DIN3_FUNCTION, CANOPEN_OD::LIMIT_MODE_VALUE::NONE);
}