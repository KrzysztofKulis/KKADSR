#include "pch.h"
#include "Curves.h"

namespace KKADSR {
namespace Curves {

template <typename T>
inline void Linear<T>::Initialize(const T max_value, const T min_value,
                                  const KKADSR::Stage::stage_len& stage_len,
                                  const Curves::LinearMode mode) {
  max_value_ = max_value;
  min_value_ = min_value;
  stage_len_ = stage_len;
  mode_ = mode;
  step_ = {};
  mode_ == Curves::LinearMode::Rising ? current_value_ = {}
                                      : current_value_ = max_value;
  switch (mode_) {
    case LinearMode::Rising:
      value_delta_ =
          static_cast<T>(stage_len_.count()) / (max_value - min_value);
      break;
    case LinearMode::Falling:
      value_delta_ =
          static_cast<T>(stage_len_.count()) / (min_value - max_value);
      break;
    default:
      break;
  }
}

}  // namespace Curves
}  // namespace KKADSR