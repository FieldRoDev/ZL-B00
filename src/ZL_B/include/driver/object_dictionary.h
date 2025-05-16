#pragma once

#include <string>
#include <unordered_map>

enum COMMAND_WORD
{
  SINGLE_DATA = 0x2F,
  DOUBLE_DATA = 0x2B,
  QUAD_DATA = 0x23,
  READ_DATA = 0x40
};

namespace CANOPEN_OD 
{
    // Controlword
    constexpr int CONTROL_WORD_INDEX = 0x6040;
    namespace CONTROL_WORD_VALUE 
    {
        constexpr int STOP                        = 0x06;
        constexpr int START                       = 0x0F;
        constexpr int RESET                       = 0x86;
        constexpr int QUICK_STOP                  = 0x0B;
        constexpr int ABSOLUTE_POSITION_RUN_SET1  = 0x2F;
        constexpr int ABSOLUTE_POSITION_RUN_SET2  = 0x3F;
        constexpr int INCREMENT_POSITION_RUN_SET1 = 0x4F;
        constexpr int INCREMENT_POSITION_RUN_SET2 = 0x5F;
        constexpr int HOMING_SET1                 = 0x0F;
        constexpr int HOMING_SET2                 = 0x1F;
    }

    // Operation Mode 인덱스
    constexpr int OPMODE_INDEX = 0x6060;
    namespace OPMODE_VALUE 
    {
        constexpr int POSITION = 1;
        constexpr int VELOCITY = 3;
        constexpr int TORQUE   = 4;
        constexpr int HOME     = 6;
    }

    constexpr int STATUS_WORD_INDEX = 0x6041; // statusword

    constexpr int QUICK_STOP_INDEX = 0x605A; // 비상 정지, 안전 관련 상황 발생시시
    namespace QUICK_STOP_VALUE
    {
        constexpr int STOP_WITHOUT_CONTROL           = 0;
        constexpr int STOP_WITH_RAMP                 = 1; // 선형적인 감속을 이용한 정지
        constexpr int STOP_WITH_QUICK_DECEL_THEN_OFF = 2; // 감속 없이 즉각적인 정지, 전원 차단
        constexpr int STOP_WITH_PROFILE              = 5; // 선형, 비선형적인 감속을 이용한 정지
        constexpr int STOP_WITH_QUICK_DECEL_ACTIVE   = 6; // 감속 없이 즉각적인 정지, 전원 미차단
        constexpr int USE_MOTOR_WINDING_BRAKE        = 18; // 모터 권선에 전류를 흘려(자기장 생성) 정지
    }  // namespace QUICK_STOP_VALUE

    constexpr int SHUTDOWN_STOP_INDEX = 0x605B; // 시스템 종료, 모터의 안전한 비활성화화
    namespace SHUTDOWN_STOP_VALUE
    {
        constexpr int STOP_WITHOUT_CONTROL   = 0;
        constexpr int STOP_WITH_RAMP         = 1;
        constexpr int STOP_WITH_QUICK_DECEL  = 2;
        constexpr int USE_MOTOR_WIDING_BRAKE = 18;
    }  // namespace SHUTDOWN_STOP_VALUE

    constexpr int DISABLE_STOP_INDEX = 0X605C; // 추가 동작 없이 에너지 절약 및 안전 유지지
    namespace DISABLE_STOP_VALUE
    {
        constexpr int STOP_WITHOUT_CONTROL   = 0;
        constexpr int STOP_WITH_RAMP         = 1;
        constexpr int STOP_WITH_QUICK_DECEL  = 2;
        constexpr int USE_MOTOR_WIDING_BRAKE = 18;
    }  // namespace DISABLE_STOP_VALUE

    constexpr int PAUSE_STOP_INDEX = 0x605D; // 작업 중 일시 정지 후 빠른 재가동이 필요한 경우
    namespace PAUSE_STOP_VALUE
    {
        constexpr int STOP_WITH_RAMP        = 1;
        constexpr int STOP_WITH_QUICK_DECEL = 2;
    }  // namespace PAUSE_STOP_VALUE

    constexpr int FAULT_STOP_INDEX = 0x605E; // 시스템 보호 및 에러로부터 안전 유지
    namespace FAULT_STOP_VALUE
    {
        constexpr int STOP_WITHOUT_CONTROL   = 0;
        constexpr int STOP_WITH_RAMP         = 1;
        constexpr int STOP_WITH_QUICK_DECEL  = 2;
        constexpr int USE_MOTOR_WIDING_BRAKE = 18;
    }  // namespace FAULT_STOP_VALUE

    // Homing mode setting
    constexpr int HOMING_METHOD_INDEX = 0x6098;
    namespace HOMING_VALUE
    {
        constexpr int NEGATIVE = 0x11;
        constexpr int POSITIVE = 0x12;
    }

    // Digital I/O setting
    constexpr int DIN_SETTING_INDEX   = 0x2010; // 0: off, 1: on, bit0~7: din1~8 (default: 0xFF)
    namespace DIN_SETTING_SUB_INDEX
    {
        constexpr int DIN_POLARITY      = 0x01;
        constexpr int DIN_SIMULATE      = 0x02;
        constexpr int DIN1_FUNCTION     = 0x03;
        constexpr int DIN2_FUNCTION     = 0x04;
        constexpr int DIN3_FUNCTION     = 0x05;
        constexpr int DIN4_FUNCTION     = 0x06;
        constexpr int DIN_REAL          = 0x0A;
        constexpr int DOUT_POLARITY     = 0x0D;
        constexpr int DOUT_SIMULATE     = 0x0E;
        constexpr int DOUT1_FUNCTION    = 0x0F;
        constexpr int DOUT2_FUNCTION    = 0x10;
        constexpr int DOUT_REAL         = 0x14;
        constexpr int ZERO_SPEED_WINDOW = 0x18;
        constexpr int LIMIT_FUNCTION    = 0x19;
    }
    namespace LIMIT_MODE_VALUE
    {
        constexpr int POSITIVE = 0x10;
        constexpr int NEGATIVE = 0x20;
        constexpr int NONE     = 0x00;
    }  // namespace LIMIT_MODE_VALUE

    // Velocity 인덱스
    constexpr int VELOCITY_DIRECTION_INDEX = 0x607E;
    const std::unordered_map<std::string, int> VELOCITY_DIRECTION_VALUES = {
        {"forward", 0},
        {"backward", 1}
    };

    constexpr int VELOCITY_COMMAND_INDEX  = 0x60FF; // target speed (Data type: int32_t)
    constexpr int VELOCITY_FEEDBACK_INDEX = 0x606C; // actual speed (Data type: int32_t)
    constexpr int MAX_VELOCITY_INDEX      = 0x6080; // max velocity limit (Data type: uint16_t)

    // Position 인덱스
    constexpr int POSITION_COMMAND_INDEX       = 0x607A; // target position (Data type: int32_t)
    constexpr int POSITION_SPEED_COMMAND_INDEX = 0x6081; // velocity (Data type: uint32_t)
    constexpr int POSITION_FEEDBACK_INDEX      = 0x6064; // actual position (Data type: int32_t)

    // Profile Acceleration, Deceleration 인덱스 (Data type : uint32_t)
    constexpr int PROFILE_ACCELERATION_INDEX = 0x6083; // default: 100rps/s
    constexpr int PROFILE_DECELERATION_INDEX = 0x6084; // default: 100rps/s
}