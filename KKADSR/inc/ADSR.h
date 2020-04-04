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
using stage_len = Common::timespan_m;
using stage_fun = Common::CurveFunction;

template <typename T>
class ADSR {
 public:
  using stage_amp = T;

  /*    Max stage index */
  static constexpr const stage_idx max_stage_idx =
      std::numeric_limits<stage_idx>::max();
  ADSR();
  ADSR& operator=(const ADSR& other) = delete;
  ADSR& operator=(ADSR&& other) noexcept = delete;
  ADSR (const ADSR& other) = delete;
  ADSR (ADSR&& other) noexcept = delete;
  ~ADSR() = default;

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

  bool Trigger();

  void SetStageParam(Curves::CurveParams_t<T> params);

  static void ClockFun();

 protected:
  std::vector<std::unique_ptr<Stage::Stage<T>>> stages_ = {};
  stage_idx stage_idx_ = {};

  static inline Common::CallbackFunction clock_fun_ = {};
  static inline Common::timespan_u clock_resolution_ = {};
  static inline std::unique_ptr<std::thread> clock_thread_ = {};
  static inline std::atomic_bool enable_get_output_ = {};
  static inline std::atomic_bool enable_clock_ = {};
  static inline std::mutex enable_get_output_mtx_ = {};
  static inline std::mutex enable_clock_mtx_ = {};
  T result_ = {};
  bool is_on_ = {};
};
}  // namespace ADSR
}  // namespace KKADSR

#endif  // KKADSR_ADSR_H