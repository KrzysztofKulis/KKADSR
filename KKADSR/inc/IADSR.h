#ifndef KKADSR_IADSR_H
#define KKADSR_IADSR_H

#include "pch.h"

#include <chrono>

#include "Curves.h"

namespace KKADSR {

using CallbackFunction = std::function<void()>;
using CurveFunction = std::function<void()>;

template <typename T>
class Stage {
 public:
  void set_type(const std::string& type);
  std::string type() const;

 private:
  void SetCurve(const CurveFunction&& curve);

  CallbackFunction* callback_ = {};
  std::string type = {};
};

template <typename gain>
class ADSR {
 public:
  using stage_num = std::size_t;
  using stage_idx = stage_num;
  using stage_len = std::chrono::microseconds;
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
  void SetStageParam(ADSR::Curves::CurveParams_t params);

 protected:
};
}  // namespace KKADSR

#endif