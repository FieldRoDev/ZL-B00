
#pragma once

#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include <algorithm>
#include <boost/filesystem.hpp>
#include <cctype>
#include <chrono>
#include <condition_variable>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>

class Logger
{
public:
  ~Logger();
  static Logger* get(const std::string& custom_folder = "dafault");
  void           push_log(const std::string& time_operator, const std::string& msg);
  void           push_log_format(const std::string level, const std::string& action,
                                 const std::string& target, const std::string& value);

private:
  static Logger* instance;

  std::string             _custom_folder;
  std::string             _component;
  std::mutex              _file_mutex;
  std::mutex              _list_mutex;
  std::condition_variable _log_condition;
  std::list<std::string>  _log_list;
  std::string             _dir;
  std::thread             _thread;
  bool                    _exit_flag;

  Logger(const std::string& custom_folder = "dafault");
  Logger(const Logger&)            = delete;  // 복사 생성자 삭제
  Logger& operator=(const Logger&) = delete;  // 대입 연산자 삭제

  void update();  // Logger 객체 동작 thread

  bool        create_directory(std::string& file_path);  // 디렉토리 생성
  std::string make_filepath(std::string mode, std::string& log_time);  // file path 생성

  // // 사용하지 않음
  // bool is_directory_exist(std::string& file_path, bool create_flag);     // 디렉토리가
  // 존재하는지 확인 및 생성
};