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
  void    traction_init();

  TractionCallback _traction_callback_function;
};