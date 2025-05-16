#include "ros_topic_manager.h"

RosTopicManager::RosTopicManager(ros::NodeHandle* node_handle)
{
  _node_handle = node_handle;
}

RosTopicManager::~RosTopicManager()
{
  
}

void RosTopicManager::add_required_subscribers(
    const std::map<std::string, std::vector<std::string>>& subscriber_map)
{
  for(const auto& pair : subscriber_map)
  {
    const std::string&              topic       = pair.first;
    const std::vector<std::string>& subscribers = pair.second;

    // 기존 구독자 목록에 새 구독자들을 추가
    _required_subscribers[topic].insert(_required_subscribers[topic].end(),
                                        subscribers.begin(), subscribers.end());
    _is_topic_connection[topic] = false;  // 초기 상태를 false로 설정
  }
}

bool RosTopicManager::check_subscriber()
{
  bool all_connected = true;
  for(const auto& topic_pair : _required_subscribers)
  {
    const std::string&              topic                = topic_pair.first;
    const std::vector<std::string>& required_subscribers = topic_pair.second;
    bool                            topic_connected      = true;
    XmlRpc::XmlRpcValue             subscriber_list;

    if(ros::param::get("/subscriber_ready/" + topic, subscriber_list))
    {
      if(subscriber_list.getType() == XmlRpc::XmlRpcValue::TypeStruct)
      {
        for(const auto& required_subscriber : required_subscribers)
        {
          if(!subscriber_list.hasMember(required_subscriber) ||
             !static_cast<bool>(subscriber_list[required_subscriber]))
          {
            // ROS_WARN_STREAM("Required subscriber " << required_subscriber << " for
            // topic "
            //                                        << topic << " is not ready");
            topic_connected = false;
            all_connected   = false;
          }
          else
          {
            // ROS_WARN_STREAM("Required subscriber " << required_subscriber
            //                                        << " is ready for topic " << topic);
          }
        }
      }
    }
    else
    {
      // ROS_WARN_STREAM("No subscriber information found for topic " << topic);
      topic_connected = false;
      all_connected   = false;
    }
    _is_topic_connection[topic] = topic_connected;
  }
  return all_connected;
}

bool RosTopicManager::is_all_connected() const
{
  for(std::map<std::string, bool>::const_iterator it = _is_topic_connection.begin();
      it != _is_topic_connection.end(); ++it)
  {
    if(!it->second) return false;
  }
  return true;
}

bool RosTopicManager::is_topic_connected(const std::string& topic) const
{
  std::map<std::string, bool>::const_iterator it = _is_topic_connection.find(topic);
  if(it != _is_topic_connection.end())
  {
    // ROS_INFO_STREAM("Topic " << topic << " connection status: "
    //                          << (it->second ? "Connected" : "Disconnected"));

    return it->second;
  }
  // ROS_WARN_STREAM("Topic " << topic << " not found in connection map");
  return false;  // 토픽이 등록되지 않은 경우 false 반환
}

// 모든 토픽의 연결 상태를 반환하는 메서드
std::map<std::string, bool> RosTopicManager::get_all_topic_connection_status() const
{
  return _is_topic_connection;
}