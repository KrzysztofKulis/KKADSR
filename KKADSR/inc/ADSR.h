#ifndef KKADSR_ADSR_H
#define KKADSR_ADSR_H

#include "pch/pch.h"

#include <atomic>
#include <chrono>
#include <limits>
#include <memory>
#include <mutex>
#include <thread>

#include "Common.h"
#include "Curves.h"
#include "Stage.h"

namespace KKADSR {
namespace ADSR {
using CurveFunction = std::function<void()>;
using stage_num = std::size_t;
using stage_idx = stage_num;
using stage_len = Common::timespan;
using stage_fun = Common::CurveFunction;

template <typename T>
class ADSR {
 public:
  using stage_amp = T;

  /*    Max stage index */
  static constexpr const stage_idx max_stage_idx =
      std::numeric_limits<stage_idx>::max();
  ADSR();
  ~ADSR(){};

  /**
   *    Get output amplitude
   */
  T GetOutput();

  /**
   *    Set a callback function used for timing all of the stages of the ADSR
   *    generator
   */
  void SetClockCallback(const std::function<void()>& f);

  /**
   *    Create stage sequence to a given stage index with given parameters
   */
  void CreateStage(const stage_idx idx, const stage_len len,
                   const stage_amp min_amp, const stage_amp max_amp,
                   const Curves::LinearMode mode);

  /**
   *    Initialize stage sequence to a given stage index with given parameters
   */
  void InitStage(const stage_idx idx, const stage_len len,
                 const stage_amp max_amp);

  /**
   *    Set stage function
   */
  void SetStageSequence(const int num);

  bool IsOn();

  void SetStageParam(Curves::CurveParams_t<T> params);

  static void ClockFun();

 protected:
  std::vector<std::unique_ptr<Stage::Stage<T>>> stages_ = {};
  stage_idx stage_idx_ = {};
  
  static inline Common::CallbackFunction clock_fun_ = {};
  static inline Common::timespan clock_resolution_ = {};
  static inline std::unique_ptr<std::thread> clock_thread_ = {};
  static inline std::atomic_bool step_ready_ = {};
  static inline std::mutex step_ready_mtx_ = {};
  T result_ = {};
};
}  // namespace ADSR
}  // namespace KKADSR

#endif  // KKADSR_ADSR_H