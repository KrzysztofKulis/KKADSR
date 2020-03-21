#include "pch/pch.h"

#include "Stage.h"

namespace KKADSR {
namespace Stage {

template <typename T>
Stage<T>::Stage(const T start_value, const T end_value,
                const StageTimespan& timespan, const Curves::LinearMode mode,
                const ClockResolution resolution)
    : curve_(start_value, end_value,
             std::chrono::duration_cast<ClockResolution>(timespan).count() /
                 resolution.count(),
             mode) {}

template <typename T>
T Stage<T>::Proceed() {
  return this->curve_.NextValue();
}

template <typename T>
inline bool Stage<T>::IsLastStep() const {
  return curve_.IsLastStep();
}

template <typename T>
void Stage<T>::Reset() {
  curve_.ResetStep();
}

template class Stage<float>;
template class Stage<double>;
template class Stage<int>;

}  // namespace Stage
}  // namespace KKADSR