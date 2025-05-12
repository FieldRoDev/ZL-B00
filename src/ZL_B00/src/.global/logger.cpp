
#include "logger.h"

Logger* Logger::instance = nullptr;

/**
/* @brief  			Logger객체를 singleton pattern으로 획득하기 위한 함수
*/
Logger* Logger::get(const std::string& custom_folder)
{
  if(instance == nullptr) instance = new Logger(custom_folder);
  return instance;
}

/**
/* @brief  			Logger 생성자
*/
Logger::Logger(const std::string& custom_folder)
{
  char path[PATH_MAX];

  _custom_folder = custom_folder;
  _component     = custom_folder;

  std::transform(_component.begin(), _component.end(), _component.begin(),
                 [](unsigned char c) { return std::toupper(c); });

  if(getcwd(path, PATH_MAX))
  {
    _dir = std::string(path) + "/log/" + _custom_folder;
  }
  else
  {
    std::cerr << "getcwd error" << std::endl;
    throw std::runtime_error("Failed to get current directory");
  }

  _exit_flag = false;
  _thread    = std::thread(&Logger::update, this);
}

/**
/* @brief  			Logger 객체 소멸자
/* @note        자체적으로 thread가 동작하고 있으므로 thread를 멈춰야 한다.
*/
Logger::~Logger()
{
  _exit_flag = true;
  _log_condition.notify_one();

  if(_thread.joinable())
  {
    _thread.join();
  }
}

/**
/* @brief  			파일로 남기고자 하는 로그 기록
/* @param
/* @return
*/
void Logger::push_log(const std::string& time_operator, const std::string& msg)
{
  // lock_guard scope 때문에 아래의 {} 풀면 안된다
  {
    std::lock_guard<std::mutex> guard(_list_mutex);
    _log_list.push_back(msg);
  }
  _log_condition.notify_one();
}

/** @brief Log Format 지정 함수
 * @param level
 * @param action
 * @param target
 * @param value
 * @note level[INFO, WARN, ERROR]
 * @note action[PUB, SUB, PROC]
 */
// void Logger::push_log_format(const std::string level, const std::string& action,
//                              const std::string& target, const std::string& value)
// {
//   std::stringstream ss;

//   if(value == "")
//   {
//     // Format: [INFO ] [COMPONENT   ] ACTION    |
//     ss << "[" << std::left << std::setw(5) << level << "] " << "[" << std::left
//        << std::setw(15) << _component << "] " << std::left << std::setw(5) << action
//        << "| " << std::left << std::setw(30) << target;
//   }
//   else
//   {
//     // Format: [INFO ] [COMPONENT   ] ACTION    |
//     ss << "[" << std::left << std::setw(5) << level << "] " << "[" << std::left
//        << std::setw(15) << _component << "] " << std::left << std::setw(5) << action
//        << "| " << std::left << std::setw(30) << target << "-> " << std::left
//        << std::setw(10) << value;
//   }

//   push_log(std::string("sec"), ss.str());
// }
void Logger::push_log_format(const std::string level, const std::string& action,
                             const std::string& target, const std::string& value)
{
  std::stringstream ss;

  if(value == "")
  {
    // 공백 없이 출력
    ss << "[" << level << "] [" << _component << "] " << action << "| " << target;
  }
  else
  {
    // 공백 없이 출력
    ss << "[" << level << "] [" << _component << "] " << action << "| " << target << " -> " << value;
  }

  push_log(std::string("sec"), ss.str());
}


/**
/* @brief  			Logger 객체의 thread 함수
/* @note        _log_condition.notify_one() 되면 _log_list에 추가된 message를 로그로 기록
/* @attention   _log_condition.notify_one() 조건과
                !_log_list.empty() || _exit_flag 조건이 참이 되어야 wait가 깨어난다.
*/
void Logger::update()
{
  while(!_exit_flag)
  {
    std::unique_lock<std::mutex> listLock(_list_mutex);

    // 통보가 오길 기다린다
    _log_condition.wait(listLock, [this] { return !_log_list.empty() || _exit_flag; });

    while(!_log_list.empty())
    {
      std::string logMessage = _log_list.front();
      _log_list.pop_front();
      listLock.unlock();

      // 파일로 기록
      std::lock_guard<std::mutex> fileLock(_file_mutex);
      std::string                 tag       = "";
      std::string                 file_path = make_filepath("sec", tag);

      // 파일경로 중간의 디렉토리들이 없으면 생성
      create_directory(file_path);

      std::ofstream ofs(file_path, std::ios_base::out | std::ios_base::app);
      if(ofs.is_open())
      {
        ofs << tag << '\t' << logMessage << std::endl;        // 파일에 기록
        std::cout << tag << '\t' << logMessage << std::endl;  // 콘솔에 기록
      }
      else
      {
        std::cerr << "Failed to open log file" << std::endl;
      }

      // 통보가 올 때까지 다시 lock
      listLock.lock();
    }
  }
}

/**
/* @brief  			기록하여야 하는 file path를 만들기 (파일명 포함)
/* @param  			std::string mode : 기록 모드
/* @param       std::string& log_time : 각 로그기록 앞에 붙여야 할 tag (일반적으로 시간)
/* @return 			std::string : 파일명이 포함된 전체 경로
*/
std::string Logger::make_filepath(std::string mode, std::string& log_time)
{
  auto     now       = std::chrono::system_clock::now();
  auto     in_time_t = std::chrono::system_clock::to_time_t(now);
  std::tm* now_tm    = std::localtime(&in_time_t);

  // File Path
  std::stringstream file_path;
  // file_path << _dir << "/" << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d") <<
  // "/";   // Dir명 만들기
  file_path << _dir << "/";
  file_path << std::setfill('0') << std::setw(4) << now_tm->tm_year + 1900 << "-";
  file_path << std::setfill('0') << std::setw(2) << now_tm->tm_mon + 1 << "-";
  file_path << std::setfill('0') << std::setw(2) << now_tm->tm_mday << "/";
  file_path << std::setfill('0') << std::setw(2) << now_tm->tm_hour
            << ".log";  // 파일명 만들기

  // log 기록 시간 만들기
  std::stringstream logtime;
  if(mode == "sec")
  {
    logtime << std::put_time(std::localtime(&in_time_t), "%X");
    log_time = logtime.str();
  }
  else
  {
    auto now_ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) %
        1000;
    logtime << std::setfill('0') << std::setw(3) << now_ms.count();
    log_time = logtime.str();
  }

  return file_path.str();
}

/**
/* @brief  			디렉토리 생성 함수
/* @param  			std::string& path : 디렉토리명 포함 경로
/* @return 			생성 여부
/* @note        1. 생성된 디렉토리에는 모든 권한을 다 준다.
/*              2. boost lib를 이용하여 경로포함 파일명을 입력하면 중간에 없는 Directory를
/*                 생성 해주는 방법으로 변경 하였음
*/
bool Logger::create_directory(std::string& file_path)
{
  // if (mkdir(path.c_str(), 0777) == -1)
  // {
  //   std::cerr << "Error: " << strerror(errno) << std::endl;
  //   return false;
  // }
  // return true;

  boost::filesystem::path dir(file_path);
  if(!boost::filesystem::exists(dir.parent_path()))
  {
    if(boost::filesystem::create_directories(dir.parent_path()))
    {
      chmod(dir.parent_path().c_str(), 0777);  // 모든 권한 부여
      std::cout << "Directory created: " << dir.parent_path() << std::endl;
      return true;
    }
    else
    {
      return false;
    }
  }

  return true;
}

// /**
// /* @brief  			해당 디렉토리가 존재하는지 판단하고 flag에 따라 생성하는
// 함수
// /* @param  			std::string& path : 디렉토리명 포함 경로
// /* @param       bool create_falg  : 디렉토리가 존재하지 않을 경우 생성 할 것인지 플래그
// /* @return 			bool              : 디렉토리 존재 여부
// */

// bool Logger::is_directory_exist(std::string& path, bool create_flag)
// {
//   struct stat info;
//   if(stat(path.c_str(), &info) != 0)      // 경로에 접근 할 수 없거나 오류 발생
//   {
//     if(create_flag)
//       return create_directory(path);
//     return false;
//   }
//   else if(info.st_mode & S_IFDIR)         // 디렉토리 존재
//   {
//     return true;
//   }
//   else                                    // 동일한 파일명은 있으나 디렉토리는 없음
//   {
//     if(create_flag)
//       return create_directory(path);
//     return false;
//   }
//   return false;
// }
