#include "canopen.h"

Canopen::Canopen()
{
  _topic_manager = new RosTopicManager(_nh);
  init();
}

Canopen::~Canopen()
{
  delete _topic_manager;
}

void Canopen::init()
{
  _topic_manager->add_publisher<can_msgs::Frame>("can0/tx", 10);
}

void Canopen::send_sdo(uint8_t node_id, uint8_t cmd, uint16_t index, uint8_t subindex, uint32_t data)
{
  if(_topic_manager == nullptr) return;

  can_msgs::Frame msg;
  msg.id      = 0x600 + node_id;
  msg.dlc     = 8;
  msg.data[0] = cmd;
  msg.data[1] = index & 0xFF;
  msg.data[2] = index >> 8;
  msg.data[3] = subindex;
  msg.data[4] = data & 0xFF;
  msg.data[5] = (data >> 8) & 0xFF;
  msg.data[6] = (data >> 16) & 0xFF;
  msg.data[7] = (data >> 24) & 0xFF;

  _topic_manager->publish("can0/tx", msg);
}