#ifndef KKADSR_CURVES_H
#define KKADSR_CURVES_H

// declare usage of precompiled headers
#ifdef KK_USE_PCH
#include "pch.h"
#else
#include <functional>
#include <map>
#include <string>
#include <vector>
#endif

#include "Stage.h"

namespace KKADSR {
namespace Curves {

/**
 *  KKADSR::Curves namespace types
 */

/*  Curve type index    */
const enum class CurveTypeIndex { Linear = 0, Logarythmic };

/*  Curve parameters    */
template <typename T>
using CurveParams_t = std::vector<std::pair<std::string, T>>;

/*  Curve type  */
template <typename T>
using CurveType_t =
    std::pair<CurveTypeIndex, std::function<void(CurveParams_t<T>)>>;

const std::map<CurveTypeIndex, std::string> kCurveTypes = {
    {std::make_pair(CurveTypeIndex::Linear, "LINEAR")},
    {std::make_pair(CurveTypeIndex::Logarythmic, "LOGARYTHMIC")}};

/**
 *  KKADSR::Curves enums
 */
enum class LinearMode { Rising = 0, Falling };

/**
 *  KKADR::Curves::Linear
 *
 *  Generates linear transition
 */
template <typename T>
class Linear {
  using StepType = std::size_t;

 public:
  // TODO: [MINOR] Implement constructor taking CurveParams_t (a list of params)
  Linear(CurveParams_t<T> params);

  /**
   *  KKADR::Curves::Linear::Initialize
   *
   *  Initialize start and end value of the curve, its length and monotonicity
   */
  void Initialize(const T start_value, const T end_value,
                  const KKADSR::Stage::stage_len& stage_len,
                  const Curves::LinearMode mode);

  T NextValue();

 private:
  T start_value_ = {};
  T end_value_ = {};
  KKADSR::Stage::stage_len stage_len_ = {};
  LinearMode mode_ = {};
  T current_value_ = {};
  T value_delta_ = {};
  StepType step_ = {};
};

// template <typename T>
// T Logarythmic(CurveParams_t<T> params);
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

#endif  // KKADSR_CURVES_H