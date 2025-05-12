#pragma once

#include <ros/ros.h>
#include <xmlrpcpp/XmlRpcValue.h>

#include <functional>
#include <map>
#include <string>
#include <vector>

class RosTopicManager
{
public:
  RosTopicManager(ros::NodeHandle* node_handle);
  ~RosTopicManager();

private:
  ros::NodeHandle* _node_handle;
  std::string      _node_name;
  /// @brief Key: topic_name, Value: Publisher
  std::map<std::string, ros::Publisher> _publishers;
  /// @brief Key: topic_name, Value: message_type
  std::map<std::string, std::string> _publisher_types;
  /// @brief Key: topic_name, Value: Subscriber
  std::map<std::string, ros::Subscriber> _subscribers;
  /// @brief Key: topic_name, Value: Subscriber_list
  std::map<std::string, std::vector<std::string>> _required_subscribers;
  /// @brief Key: topic_name, Value: is_connection
  std::map<std::string, bool> _is_topic_connection;

public:
  /// @brief Publisher 객체 생성
  /// @tparam MsgType
  /// @param topic
  /// @param queue_size
  /// @note 발행자가 가질 수 있는 미전송 메세지의 최대 개수
  template <typename MsgType>
  void add_publisher(const std::string& topic, int queue_size)
  {
    _publishers[topic]      = _node_handle->advertise<MsgType>(topic, queue_size);
    _publisher_types[topic] = typeid(MsgType).name();
  }

  /// @brief Subscriber 객체 생성
  /// @tparam MsgType
  /// @tparam T
  /// @param topic
  /// @param queue_size
  /// @param callback
  /// @param obj
  /// @note 콜백 처리 전 버퍼링할 수 있는 메세지의 최대 개수
  template <typename MsgType, typename T>
  void add_subscriber(const std::string& topic, int queue_size,
                      void (T::*callback)(const typename MsgType::ConstPtr&), T* obj)
  {
    _subscribers[topic] =
        _node_handle->subscribe<MsgType>(topic, queue_size, callback, obj);
    if(!_subscribers[topic]) std::cout << "Fail to Create Subscriber" << topic << std::endl;
  }

  /// @brief
  /// @tparam MsgType
  /// @param msg
  template <typename MsgType>
  void publish(const MsgType& msg)
  {
    for(std::map<std::string, ros::Publisher>::const_iterator it = _publishers.begin();
        it != _publishers.end(); ++it)
    {
      if(_publisher_types[it->first] == typeid(MsgType).name())
      {
        it->second.publish(msg);
        return;
      }
    }
    ROS_WARN_STREAM("No publisher found for message type: " << typeid(MsgType).name());
  }

  // 여러 개의 같은 타입 publisher를 위한 오버로드
  template <typename MsgType>
  void publish(const std::string& topic, const MsgType& msg)
  {
    std::map<std::string, ros::Publisher>::iterator it = _publishers.find(topic);
    if(it != _publishers.end() && _publisher_types[topic] == typeid(MsgType).name())
    {
      it->second.publish(msg);
    }
    else
    {
      ROS_WARN_STREAM("Publisher for topic " << topic << " not found or type mismatch.");
    }
  }

  /// @brief 여러 구독자를 list로 한 번에 추가하는 함수
  /// @param topic
  /// @param subscribers
  void add_required_subscribers(
      const std::map<std::string, std::vector<std::string>>& subscriber_map);

  /// @brief ros_param_manger에서 활성화된 구독자 정보 확인
  /// @return
  bool check_subscriber();

  /// @brief 전체 연결 상태를 확인하는 메서드
  bool is_all_connected() const;

  /// @brief 특정 토픽의 연결 상태를 확인하는 메서드
  bool is_topic_connected(const std::string& topic) const;

  /// @brief 모든 토픽의 연결 상태를 반환하는 메서드
  std::map<std::string, bool> get_all_topic_connection_status() const;
};