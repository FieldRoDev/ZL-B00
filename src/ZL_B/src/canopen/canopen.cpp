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
  safe_delete(_spinner);
  safe_delete(_nh);
}

void Canopen::init()
{
  _pub_can0_tx = _nh->advertise<can_msgs::Frame>("can0/tx", 10);
  _pub_pdo_tx = _nh->advertise<ZL_B00::pdo_tx_msgs>("pdo/tx", 10);
  _sub_can0_rx = _nh->subscribe<can_msgs::Frame>("can0/rx", 100, &Canopen::pub_pdo_tx, this);
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

void Canopen::close_nmt(uint8_t node_id)
{
  while (_pub_can0_tx.getNumSubscribers() == 0)
  {
    ros::Duration(0.01).sleep();
    ros::spinOnce();
  }
  can_msgs::Frame nmt_msg;
  nmt_msg.id = 0x000;
  nmt_msg.dlc = 2;
  nmt_msg.data[0] = 0x02;
  nmt_msg.data[1] = node_id;

  _pub_can0_tx.publish(nmt_msg);
}

void Canopen::preop_nmt(uint8_t node_id)
{
  while (_pub_can0_tx.getNumSubscribers() == 0)
  {
    ros::Duration(0.01).sleep();
    ros::spinOnce();
  }
  can_msgs::Frame nmt_msg;
  nmt_msg.id = 0x000;
  nmt_msg.dlc = 2;
  nmt_msg.data[0] = 0x80;
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

void Canopen::pub_pdo_tx(const can_msgs::Frame::ConstPtr& msg)
{
  while (_pub_pdo_tx.getNumSubscribers() == 0)
  {
    ros::Duration(0.01).sleep();
    ros::spinOnce();
  }
  if(msg->dlc != 4) return;

  _pdo_tx_msg.id = msg->id;
  for(int i = 0; i < 4; ++i)
  {
    _pdo_tx_msg.data[i] = msg->data[i];
  }
  _pub_pdo_tx.publish(_pdo_tx_msg);
}