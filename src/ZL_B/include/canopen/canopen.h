#pragma once

#include "ros/ros.h"
#include "can_msgs/Frame.h"
#include "safe_queue.h"
#include "global_helper.h"
#include "ZL_B00/pdo_tx_msgs.h"

class Canopen
{
public:
  Canopen();
  virtual ~Canopen();

  void send_sdo(uint8_t node_id, uint8_t cmd, uint16_t index, uint8_t subindex, uint32_t data);
  void enable_nmt(uint8_t node_id);
  void close_nmt(uint8_t node_id);
  void preop_nmt(uint8_t node_id);

protected:
  void    init();
  void    pub_pdo_tx(const can_msgs::Frame::ConstPtr& msg);
  uint8_t _rx_data[8];

  ZL_B00::pdo_tx_msgs              _pdo_tx_msg;
  ros::AsyncSpinner*               _spinner;
  ros::NodeHandle*                 _nh;
  ros::Publisher                   _pub_can0_tx;
  ros::Subscriber                  _sub_can0_rx;
  ros::Publisher                   _pub_pdo_tx;
};