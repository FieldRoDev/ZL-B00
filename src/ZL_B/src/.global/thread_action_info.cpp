#include "thread_action_info.h"

ThreadActionInfo::ThreadActionInfo(std::string file_name)
{
  _hz     = 0;
  _sleep  = 0;
  load_option(file_name);
}

ThreadActionInfo::~ThreadActionInfo()
{
  if (_thread.joinable())
  {
    try
    {
      _thread.join();
    }
    catch(const std::system_error& e)
    {
      std::cerr << "System error during thread join: " << e.what() << std::endl;
    }
    catch(const std::exception& e)
    {
      std::cerr << "Exception during thread join: " << e.what() << std::endl;
    }
  }
}

void ThreadActionInfo::load_option(std::string file_name)
{
  try
  {
    // file open
    std::ifstream yaml_file(file_name);
    YAML::Node    yaml = YAML::Load(yaml_file);
    yaml_file.close();

    // data read
    std::string config_name = yaml["config_name"].as<std::string>();

    // RS485 통신 thread 동작 속도
    _hz = yaml["thread"]["hz"].as<int32_t>();
  }
  catch(YAML::Exception& e)
  {
    std::cout << "YAML Exception : " << e.what() << std::endl;
  }
  catch(std::exception& e)
  {
    std::cout << "Exception : " << e.what() << std::endl;
  }
  catch(...)
  {
    std::cout << "Unknown Exception" << std::endl;
  }

  // _thread_sleep 계산의 경우 설정되는 _thread_hz * 1.1 정도로 설정
  // 해줘야 실제 thread 동작 속도가 _thread_hz에 가까워진다.
  // thread 내에서 동작하는 각종 구현 함수의 overhead 때문에
  _sleep = 1000 / (_hz * 1.1);
}