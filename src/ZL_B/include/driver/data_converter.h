#include <vector>
#include <cstdint>
#include <cfloat>
#include <stdexcept>
#include <cmath>

#define RESOLUTION 65536
#define FACTOR 1875.0
#define SCALE_FACTOR 512
#define RATIO_MOTOR 35
#define RATIO_STEER 5.5

inline int32_t rpm_to_internal_velocity(int32_t rpm)
{
  return static_cast<int32_t>((static_cast<int64_t>(rpm) * SCALE_FACTOR * RESOLUTION) / FACTOR);
}

inline double position_to_radian(const int32_t position)
{
  return static_cast<double>(position) * (2 * M_PI) / (RESOLUTION * RATIO_MOTOR * RATIO_STEER);
}

inline double position_to_degree(const int32_t position)
{
  return static_cast<double>(position) * 360.0 / (RESOLUTION * RATIO_MOTOR * RATIO_STEER);
}

inline int32_t radian_to_position(const double radian)
{
  return static_cast<int32_t>(radian * (RESOLUTION * RATIO_MOTOR * RATIO_STEER) / (2 * M_PI)); 
}

inline int32_t degree_to_position(const double degree)
{
  return static_cast<int32_t>(degree * (RESOLUTION * RATIO_MOTOR * RATIO_STEER) / 360);
}

inline int32_t linear_velocity_to_rpm(const double vel)
{
  return static_cast<int32_t>(vel * 60 * 19 / (M_PI * 0.25));
}

inline double rpm_to_linear_velocity(const int32_t rpm)
{
  return static_cast<double>(rpm * (M_PI * 0.25) / (60 * 19));
}