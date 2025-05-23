#include "ZL_B.h"

ZL_B::ZL_B(int argc, char** argv)
{
  ros::init(argc, argv, "ZL_B_node");
  _nh      = new ros::NodeHandle;
  _canopen = new Canopen();
  _canopen->enable_nmt(NODE_ID::TRACTION);
  _canopen->enable_nmt(NODE_ID::STEER);
  _traction               = new ZL_B_traction([this](uint8_t cmd, uint16_t index, uint8_t subindex, uint32_t data) 
                                                -> void { return traction_callback(cmd, index, subindex, data); });
  _steer                  = new ZL_B_steer([this](uint8_t cmd, uint16_t index, uint8_t subindex, uint32_t data) 
                                                -> void { return steer_callback(cmd, index, subindex, data); },
                                                "/home/fieldro/Dev/ZL_B00/src/ZL_B/config/ZL_B.yaml");
}

ZL_B::~ZL_B()
{
  safe_delete(_steer);
  safe_delete(_traction);
  safe_delete(_canopen);
  safe_delete(_nh);
}

void ZL_B::control(std::string str)
{
  std::string cmd = parsing_command_map(str, _command_map);

  if(cmd=="stop") stop();
  else if(cmd == "reset") reset();

  else if(cmd == "traction")
  {
    if(_command_map.find("stop") != _command_map.end())               _traction->stop();
    else if(_command_map.find("posmode") != _command_map.end())       _traction->set_position_mode();
    else if(_command_map.find("velmode") != _command_map.end())       _traction->set_velocity_mode();
    else if(_command_map.find("set") != _command_map.end())
    {
      if(_command_map.find("rpm") != _command_map.end())              _traction->set_velocity(static_cast<int32_t>(_command_map["rpm"]));
      if(_command_map.find("pos") != _command_map.end())              _traction->set_position(static_cast<int32_t>(_command_map["pos"]));
    }
    else if(_command_map.find("run") != _command_map.end())
    {
      if(_command_map.find("vel") != _command_map.end())              _traction->run_velocity();
      else if(_command_map.find("abs") != _command_map.end())         _traction->run_absolute_position();
      else if(_command_map.find("inc") != _command_map.end())         _traction->run_incremental_position();
    }
  }

  else if(cmd=="steer")
  {
    if(_command_map.find("stop") != _command_map.end())               _steer->stop();
    else if(_command_map.find("posmode") != _command_map.end())       _steer->set_position_mode();
    else if(_command_map.find("velmode") != _command_map.end())       _steer->set_velocity_mode();
    else if(_command_map.find("origin") != _command_map.end())        _steer->move_to_origin();
    else if(_command_map.find("set") != _command_map.end())
    {
      if(_command_map.find("rpm") != _command_map.end())              _steer->set_velocity(static_cast<int32_t>(_command_map["rpm"]));
      if(_command_map.find("pos") != _command_map.end())              _steer->set_position(static_cast<int32_t>(_command_map["pos"]));
      else if(_command_map.find("deg") != _command_map.end())         _steer->set_degree(_command_map["deg"]);
      else if(_command_map.find("rad") != _command_map.end())         _steer->set_radian(_command_map["rad"]);
    }
    else if(_command_map.find("run") != _command_map.end())
    {
      if(_command_map.find("vel") != _command_map.end())              _steer->run_velocity();
      else if(_command_map.find("abs") != _command_map.end())         _steer->run_absolute_position();
      else if(_command_map.find("inc") != _command_map.end())         _steer->run_incremental_position();
    }
  }
}

void ZL_B::stop()
{
  _traction->stop();
  _steer->stop();
}

void ZL_B::reset()
{
  _traction->reset();
  _steer->reset();
}

void ZL_B::traction_callback(uint8_t cmd, uint16_t index, uint8_t subindex, uint32_t data)
{
  std::lock_guard<std::mutex> lock(_callback_lock);
  _canopen->send_sdo(NODE_ID::TRACTION, cmd, index, subindex, data);
}

void ZL_B::steer_callback(uint8_t cmd, uint16_t index, uint8_t subindex, uint32_t data)
{
  std::lock_guard<std::mutex> lock(_callback_lock);
  _canopen->send_sdo(NODE_ID::STEER, cmd, index, subindex, data);
}