#include "pch/pch.h"

#include "ADSR.h"

namespace KKADSR {
namespace ADSR {

template <typename T>
void ADSR<T>::ClockFun() {
  while (true) {
    while (!step_ready_.load()) {
    }
    std::this_thread::sleep_for(clock_resolution_);
    {
      std::scoped_lock<std::mutex> lock(step_ready_mtx_);
      step_ready_.store(true);
    }
    while (step_ready_.load()) {
    }
  }
}

template <typename T>
ADSR<T>::ADSR() {
  clock_resolution_ = Stage::ClockResolution(200);
  clock_fun_ = ClockFun;
  clock_thread_ = std::make_unique<std::thread>(&ClockFun);
  clock_thread_->detach();
  {
    std::scoped_lock<std::mutex> lock(step_ready_mtx_);
    step_ready_.store(true);
  }
}

template <typename T>
T ADSR<T>::GetOutput() {
  if (step_ready_.load()) {
    result_ = stages_.at(stage_idx_)->Proceed();
    if (stages_.at(stage_idx_)->IsLastStep()) {
      stages_.at(stage_idx_)->Reset();
      ++stage_idx_;
      if (stage_idx_ == stages_.size()) {
        stage_idx_ = {};
      }
    }
    {
      std::scoped_lock<std::mutex> lock(step_ready_mtx_);
      step_ready_.store(true);
    }
  }
  return result_;
}

template <typename T>
void ADSR<T>::SetClockCallback(const std::function<void()>& f){};

template <typename T>
void ADSR<T>::InitStage(const stage_idx idx, const stage_len len,
                        const stage_amp max_amp) {}

template <typename T>
void ADSR<T>::CreateStage(const stage_idx idx, const stage_len len,
                          const stage_amp min_amp, const stage_amp max_amp,
                          const Curves::LinearMode mode) {
  stages_.push_back(std::make_unique<Stage::Stage<T>>(min_amp, max_amp, len,
                                                      mode, clock_resolution_));
}

template <typename T>
void ADSR<T>::SetStageSequence(const int num) {}

template <typename T>
bool ADSR<T>::IsOn() {
  return !(stage_idx_ == stages_.size() ||
           stages_.at(stage_idx_)->IsLastStep());
}

template <typename T>
bool ADSR<T>::Trigger() {
  if (!IsOn()) {
    return false;
  }

  stage_idx_ = {};
  return true;
}

template <typename T>
void ADSR<T>::SetStageParam(Curves::CurveParams_t<T> params) {}

// explicit template instatiation
template class ADSR<float>;
template class ADSR<double>;
template class ADSR<int>;

}  // namespace ADSR
}  // namespace KKADSR
