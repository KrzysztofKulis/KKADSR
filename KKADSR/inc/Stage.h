#ifndef KKADSR_STAGE_H
#define KKADSR_STAGE_H

#include "pch/pch.h"

#include <chrono>

#include "Common.h"
#include "Curves.h"

namespace KKADSR {
namespace Stage {

/**
 *  KKADSR::Stage types
 */

/*  Stage timespan  */
using StageTimespan = Common::timespan_m;

/*  Clock resolution */
using ClockResolution = Common::timespan_u;

/**
 *  KKADSR::Stage::Stage
 *
 *  Keeps single stage parameters
 */

template <typename T>
class Stage {
 public:
  Stage(const T start_value, const T end_value, const StageTimespan& timespan,
        const Curves::LinearMode mode, const ClockResolution resolution);
  T Proceed();
  bool IsLastStep() const;
  void Reset();
  bool IsOn() const;
  void Start();

 private:
  Curves::Linear<T> curve_;
  bool is_on_ = {};
};

}  // namespace Stage
}  // namespace KKADSR

#endif  // KKADSR_STAGE_H
