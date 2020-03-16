#include "pch/pch.h"

#include "Stage.h"

namespace KKADSR {
namespace Stage {

template <typename T>
Stage<T>::Stage(const T start_value, const T end_value,
                const StageTimespan& timespan, const Curves::LinearMode mode)
    : curve_(start_value, end_value, timespan.count(), mode) {}

template <typename T>
T Stage<T>::Proceed() {
  return this->curve_.NextValue();
}

template class Stage<float>;
template class Stage<double>;
template class Stage<int>;

}  // namespace Stage
}  // namespace KKADSR