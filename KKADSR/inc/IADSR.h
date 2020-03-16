#ifndef KKADSR_IADSR_H
#define KKADSR_IADSR_H

#include "pch/pch.h"

#include <chrono>

#include "Curves.h"

namespace KKADSR {
namespace ADSR {
using CurveFunction = std::function<void()>;
using stage_num = std::size_t;
using stage_idx = stage_num;

template <typename gain>
class ADSR {
 public:
  using stage_amp = gain;

  ADSR(const std::function<void()>&&){};
  ~ADSR(){};

  /**
   *    Get output amplitude based on input amplitude
   */
  gain GetOutput(gain input){};

  /**
   *    Set a callback function used for timing all of the stages of the ADSR
   *    generator
   */
  void SetClockCallback(const std::function<void()>& f);

  /**
   *    Initialize stage sequence to a given stage index with given parameters
   */
  void InitStage(const stage_idx idx, const stage_len len,
                 const stage_amp max_amp);

  /**
   *    Set stage function
   */
  void SetStageSequence(const int num);
  void SetStageParam(Curves::CurveParams_t<gain> params);

 protected:
};
}  // namespace ADSR
}  // namespace KKADSR

#endif