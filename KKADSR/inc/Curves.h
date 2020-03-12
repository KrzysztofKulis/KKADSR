#pragma once

#include "pch.h"
#include "Stage.h"

namespace KKADSR {
namespace Curves {

/**
 *  KKADSR::Curves namespace types
 */
const enum class CurveTypeIndex { Linear = 0, Logarythmic };

const std::map<CurveTypeIndex, std::string> CurveTypes = {
    {std::make_pair(CurveTypeIndex::Linear, "LINEAR")},
    {std::make_pair(CurveTypeIndex::Logarythmic, "LOGARYTHMIC")}};

template <typename T>
using CurveParams_t = std::vector<std::pair<std::string, T>>;

template <typename T>
using CurveType_t =
    std::pair<CurveTypeIndex, std::function<void(CurveParams_t<T>)>>;

enum class LinearMode { Rising = 0, Falling };

template <typename T>
class Linear {
  using StepType = std::size_t;

  Linear(CurveParams_t<T> params);

  T current_value_ = {};
  T min_value_ = {};
  T max_value_ = {};
  T value_delta_ = {};
  LinearMode mode_ = {};
  KKADSR::Stage::stage_len stage_len_ = {};
  StepType step_ = {};

  void Initialize(const T max_value, const T min_value,
                  const KKADSR::Stage::stage_len& stage_len,
                  const Curves::LinearMode mode);

  // inline T ExecuteStep() { current_value = }
};

template <typename T>
T Logarythmic(CurveParams_t<T> params);

// std::map<std::string, CurveType_t<double>> CurveMap = {
//    {"LINEAR",
//     {CurveTypeIndex::Linear,
//      std::bind(Linear<double>, std::placeholders::_1)}},
//    {"LOGARYTHMIC",
//     {CurveTypeIndex::Logarythmic,
//      std::bind(Logarythmic<double>, std::placeholders::_1)}}};
//
}  // namespace Curves
}  // namespace KKADSR