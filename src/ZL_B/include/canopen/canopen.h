#pragma once

#include "ros/ros.h"
#include "can_msgs/Frame.h"
#include "ros_topic_manager.h"

class Canopen
{
public:
  Canopen();
  virtual ~Canopen();

  void send_sdo(uint8_t node_id, uint8_t cmd, uint16_t index, uint8_t subindex, uint32_t data);

protected:
  void init();

  ros::NodeHandle* _nh;
  RosTopicManager* _topic_manager;
};