#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

// Safe 큐 클래스 정의
template <typename T>
class SafeQueue
{
private:
  std::queue<T>           _queue;  // 실제 데이터를 저장할 큐
  mutable std::mutex      _mutex;  // 동기화를 위한 뮤텍스
  std::condition_variable _cond;   // 조건 변수 (대기 및 통지에 사용)

public:
  // 큐에 데이터를 추가하는 메서드
  void push(const T& value)
  {
    std::lock_guard<std::mutex> lock(_mutex);  // 뮤텍스 잠금
    _queue.push(std::move(value));             // 큐에 데이터 추가
    _cond.notify_one();                        // 대기 중인 스레드에 통지
  }

  // 큐에서 데이터를 꺼내는 메서드
  bool pop(T& value)
  {
    std::unique_lock<std::mutex> lock(_mutex);  // 뮤텍스 잠금 (unique_lock 사용)
    // _cond.wait(lock,
    //            [this] { return !_queue.empty(); });  // 큐가 비어있지 않을 때까지 대기
    if(_queue.empty())
    {
      return false;  // 큐가 비어있으면 false 반환
    }
    value = std::move(_queue.front());  // 첫 번째 요소를 value에 이동
    _queue.pop();                       // 첫 번째 요소 제거
    return true;
  }

  // 큐가 비어있는지 확인하는 메서드
  bool empty() const
  {
    std::lock_guard<std::mutex> lock(_mutex);  // 뮤텍스 잠금
    return _queue.empty();                     // 큐의 empty 상태 반환
  }
};