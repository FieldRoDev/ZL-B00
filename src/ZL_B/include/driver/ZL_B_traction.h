#include "canopen.h"

using TractionCallback = std::function<void(uint8_t cmd, uint16_t index, uint8_t subindex, uint32_t data)>;

class ZL_B_traction
{
public:
  ZL_B_traction(TractionCallback traction_callback);
  virtual ~ZL_B_traction();

  void quick_stop();
  void stop();
  void reset();
  void set_velocity_mode();
  void set_velocity(int32_t rpm);
  void run_velocity();

protected:
  void set_din();
  void traction_init();
  void get_velocity_position(ZL_B00::pdo_tx_msgs msg);

  int32_t _current_position;
  int32_t _current_velocity;
  int32_t _set_velocity;

  ros::AsyncSpinner* _spinner;
  ros::NodeHandle*   _nh;
  ros::Subscriber    _get_velocity_position;
  TractionCallback   _traction_callback_function;
};