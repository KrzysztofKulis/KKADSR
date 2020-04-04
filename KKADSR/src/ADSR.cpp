#include "pch/pch.h"

#include <iostream>
#include <numeric>
#include "ADSR.h"

namespace KKADSR {
namespace ADSR {

template <typename T>
void ADSR<T>::ClockFun() {
  while (true) {
    // wait for clock trigger
    while (!enable_clock_.load()) {
    }
    // clear flag
    {
      std::scoped_lock<std::mutex> lock(enable_clock_mtx_);
      enable_clock_.store(false);
    }
    std::this_thread::sleep_for(clock_resolution_);
    // signal that the next value may be calculated
    {
      std::scoped_lock<std::mutex> lock(enable_get_output_mtx_);
      enable_get_output_.store(true);
    }
  }
}

template <typename T>
ADSR<T>::ADSR() {
  clock_resolution_ = Stage::ClockResolution(200);
  clock_fun_ = ClockFun;
  {
    std::scoped_lock<std::mutex> lock(enable_get_output_mtx_);
    enable_get_output_.store(true);
  }
  {
    std::scoped_lock<std::mutex> lock(enable_clock_mtx_);
    enable_clock_.store(false);
  }
  clock_thread_ = std::make_unique<std::thread>(&ClockFun);
  clock_thread_->detach();
}

template <typename T>
T ADSR<T>::GetOutput() {
  if (!IsOn()) {
    return {};
  }

  // return if clock still counting
  if (!enable_get_output_.load()) {
    return result_;
  }

  // clear flag
  {
    std::scoped_lock<std::mutex> lock(enable_get_output_mtx_);
    enable_get_output_.store(false);
  }

  static std::chrono::high_resolution_clock::time_point start = {};

  static std::vector<long long> timer;
  timer.reserve(200000);

  timer.push_back(std::chrono::duration_cast<std::chrono::microseconds>(
                      std::chrono::high_resolution_clock::now() - start)
                      .count());

  start = std::chrono::high_resolution_clock::now();

  result_ = stages_.at(stage_idx_)->Proceed();

  if (timer.size() == 100) {
    static size_t mean = 0;
    static auto avg =
        std::accumulate(timer.begin() + 5, timer.end(), 0LL) / timer.size();
   // std::cout << "Average time: " << avg << "us." << std::endl;
    timer.clear();
  }

  if (stages_.at(stage_idx_)->IsLastStep()) {
    stages_.at(stage_idx_)->Reset();
    ++stage_idx_;
    if (stage_idx_ == stages_.size()) {
      stage_idx_ = {};
      is_on_ = false;
    }
  }

  // start clock
  {
    std::scoped_lock<std::mutex> lock(enable_clock_mtx_);
    enable_clock_.store(true);
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
  return is_on_;
}

template <typename T>
bool ADSR<T>::Trigger() {
  if (IsOn()) {
    return false;
  }

  stages_.at(stage_idx_)->Reset();
  stage_idx_ = {};
  is_on_ = true;
  //{
  //  std::scoped_lock<std::mutex> lock(enable_get_output_mtx_);
  //  enable_get_output_.store(true);
  //}
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
