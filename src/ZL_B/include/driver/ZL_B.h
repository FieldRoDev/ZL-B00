#include <iostream>
#include <map>
#include <mutex>

#include "canopen.h"
#include "ZL_B_traction.h"
#include "ZL_B_steer.h"
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
  ros::NodeHandle*                  _nh;
  std::mutex                        _callback_lock;
  std::map<std::string, double>     _command_map;

  void traction_callback(uint8_t cmd, uint16_t index, uint8_t subindex, uint32_t data);
  void steer_callback(uint8_t cmd, uint16_t index, uint8_t subindex, uint32_t data);
  void stop();
  void reset();
};