#include <iostream>
#include <map>
#include <mutex>

#include "ros/ros.h"
#include "canopen.h"
#include "ZL_B_traction.h"
#include "ZL_B_steer.h"
#include "thread_action_info.h"
#include "global_helper.h"

enum NODE_ID
{
  TRACTION = 1,
  STEER,
};

class ZL_B
{
public:
  ZL_B(int argc, char** argv);
  virtual ~ZL_B();

  void control(std::string str);

protected:
  Canopen*                          _canopen;
  ZL_B_traction*                    _traction;
  ZL_B_steer*                       _steer;
  std::mutex                        _callback_lock;
  std::mutex                        _update_lock;
  std::map<std::string, double>     _command_map;
  std::unique_ptr<ThreadActionInfo> _thread_update;
  ros::NodeHandle*                  _nh;

  void traction_callback(uint8_t cmd, uint16_t index, uint8_t subindex, uint32_t data);
  void steer_callback(uint8_t cmd, uint16_t index, uint8_t subindex, uint32_t data);
  void thread_update();
  void stop();
  void reset();
};