#include "Curves.h"

namespace KKADSR {
namespace Curves {

template <typename T>
void Linear<T>::Initialize(const T start_value, const T end_value,
                           const KKADSR::Stage::stage_len& stage_len,
                           const Curves::LinearMode mode) {
  start_value_ = start_value;
  end_value_ = end_value;
  stage_len_ = stage_len;
  mode_ = mode;
  current_value_ = start_value_;
  value_delta_ = static_cast<T>(stage_len_.count()) / (end_value - start_value);
  step_ = {};
}

template <typename T>
inline T Linear<T>::NextValue() {
  T next_value = value_delta_ * static_cast<T>(step_);
  ++step_;
  return next_value;
}

// TODO: [NEXT] Implement setter methods for params

}  // namespace Curves
}  // namespace KKADSR