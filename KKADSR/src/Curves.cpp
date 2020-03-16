#include "pch/pch.h"

#include "Curves.h"

namespace KKADSR {
namespace Curves {

template <typename T>
Linear<T>::Linear(const CurveParams_t<T>& params){};

template <typename T>
Linear<T>::Linear(const T start_value, const T end_value,
                  const CurveStepspan& stepspan,
                  const Curves::LinearMode mode) {
  Initialize(start_value, end_value, stepspan, mode);
};

template <typename T>
void Linear<T>::Initialize(const T start_value, const T end_value,
                           const CurveStepspan& stepspan,
                           const Curves::LinearMode mode) {
  start_value_ = start_value;
  end_value_ = end_value;
  stepspan_ = stepspan;
  mode_ = mode;
  current_value_ = start_value_;
  value_delta_ = static_cast<T>(stepspan_) / (end_value - start_value);
  step_ = {};
}

template <typename T>
inline T Linear<T>::NextValue() {
  T next_value = value_delta_ * static_cast<T>(step_) + start_value_;
  ++step_;
  return next_value;
}

// explicit template instatiation
template class Linear<float>;
template class Linear<double>;
template class Linear<int>;

// TODO: [MAJOR] Implement setter methods for params

}  // namespace Curves
}  // namespace KKADSR