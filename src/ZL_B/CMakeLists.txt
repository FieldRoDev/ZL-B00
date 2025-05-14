# CMake Program의 최소 버전
cmake_minimum_required(VERSION 3.0.0)

project(ZL_B00 VERSION 0.1.0 LANGUAGES CXX)

# C++11 표준 사용
set(NODE_NAME "ZL_B")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(yaml-cpp REQUIRED)
find_package(catkin REQUIRED COMPONENTS
  roscpp
  can_msgs
)

catkin_package(
  CATKIN_DEPENDS roscpp can_msgs
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${PROJECT_SOURCE_DIR}/include/.global
  ${PROJECT_SOURCE_DIR}/include/canopen
  ${PROJECT_SOURCE_DIR}/include/driver
)

add_executable(main
  src/main.cpp
  src/driver/ZL_B.cpp
  src/driver/ZL_B_traction.cpp
  src/driver/ZL_B_steer.cpp
  src/canopen/canopen.cpp
  src/.global/thread_action_info.cpp
  src/.global/logger.cpp
)

target_link_libraries(main
  ${catkin_LIBRARIES}
  yaml-cpp
)
