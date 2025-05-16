#include "canopen.h"

Canopen::Canopen()
{
  _nh            = new ros::NodeHandle;
  _spinner       = new ros::AsyncSpinner(5);
  _spinner->start();
  init();
} 

Canopen::~Canopen()
{
  safe_delete(_nh);
}

void Canopen::init()
{
  _pub_can0_tx = _nh->advertise<can_msgs::Frame>("can0/tx", 10);
  _pub_pdo_tx = _nh->advertise<ZL_B00::pdo_tx_msgs>("pdo/tx", 10);
  _sub_can0_rx = _nh->subscribe<can_msgs::Frame>("can0/rx", 100, &Canopen::sub_rx, this);
}

void Canopen::enable_nmt(uint8_t node_id)
{
  while (_pub_can0_tx.getNumSubscribers() == 0)
  {
    ros::Duration(0.01).sleep();
    ros::spinOnce();
  }
  can_msgs::Frame nmt_msg;
  nmt_msg.id = 0x000;
  nmt_msg.dlc = 2;
  nmt_msg.data[0] = 0x01;
  nmt_msg.data[1] = node_id;

  _pub_can0_tx.publish(nmt_msg);
}

void Canopen::send_sdo(uint8_t node_id, uint8_t cmd, uint16_t index, uint8_t subindex, uint32_t data)
{
  while (_pub_can0_tx.getNumSubscribers() == 0)
  {
    ros::Duration(0.01).sleep();
    ros::spinOnce();
  }
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

  _pub_can0_tx.publish(msg);
}

void Canopen::sub_rx(const can_msgs::Frame::ConstPtr& msg)
{
  while (_pub_can0_tx.getNumSubscribers() == 0)
  {
    ros::Duration(0.01).sleep();
    ros::spinOnce();
  }

  if (msg->dlc != 4) return;

  int32_t value = static_cast<int32_t>(
                    msg->data[0] |
                    (msg->data[1] << 8) |
                    (msg->data[2] << 16) |
                    (msg->data[3] << 24));

  switch (msg->id)
  {
    case 0x181:
      _last_pdo_msg.traction_position = value;
      break;
    case 0x281:
      _last_pdo_msg.traction_velocity = internal_velocity_to_rpm(value);
      break;
    case 0x182:
      _last_pdo_msg.steer_position = value;
      break;
    case 0x282:
      _last_pdo_msg.steer_velocity = internal_velocity_to_rpm(value);
      break;
    default:
      return;
  }

  _pub_pdo_tx.publish(_last_pdo_msg);
}