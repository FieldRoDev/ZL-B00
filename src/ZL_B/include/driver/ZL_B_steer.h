#include <iostream>

#include "ros/ros.h"
#include "canopen.h"
#include "yaml-cpp/yaml.h"
#include "logger.h"

#ifndef LOGGER
#define LOGGER Logger::get("ZL_B00")
#endif

using SteerCallback = std::function<void(uint8_t cmd, uint16_t index, uint8_t subindex, uint32_t data)>;

class ZL_B_steer
{
public:
  ZL_B_steer(SteerCallback steer_callback, std::string file_name);
  virtual ~ZL_B_steer();

  void quick_stop();
  void stop();
  void reset();
  void move_to_origin();
  void set_position_mode();
  void set_position(int32_t position);
  void set_degree(double degree);
  void set_radian(double radian);
  void set_position_speed(int32_t rpm);
  void run_incremental_position();
  void run_absolute_position();

protected:
  void set_din();
  void steer_init();
  void load_option(std::string file_name);
  void get_velocity_position(ZL_B00::pdo_tx_msgs msg);

  int32_t     _current_position;
  int32_t     _current_velocity;
  int32_t     _set_position;
  int32_t     _set_velocity;
  int32_t     _origin_position;
  int32_t     _origin_speed;
  int32_t     _positive_limit;
  int32_t     _negative_limit;

  ros::AsyncSpinner* _spinner;
  ros::NodeHandle*   _nh;
  ros::Subscriber    _get_velocity_position;
  SteerCallback      _steer_callback_function;
};