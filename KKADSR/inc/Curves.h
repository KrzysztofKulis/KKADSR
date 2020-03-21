#ifndef KKADSR_CURVES_H
#define KKADSR_CURVES_H

// declare usage of precompiled headers
#include "pch/pch.h"

#include <functional>
#include <map>
#include <string>
#include <vector>

#include "Common.h"

namespace KKADSR {
namespace Curves {

/**
 *  KKADSR::Curves enums
 */
enum class LinearMode { Rising = 0, Falling };

/*  Curve type index    */
const enum class CurveTypeIndex { Linear = 0, Logarythmic };

/**
 *  KKADSR::Curves types
 */

/*  Curve parameters    */
template <typename T>
using CurveParams_t = std::vector<std::pair<std::string, T>>;

/*  Curve type  */
template <typename T>
using CurveType_t =
    std::pair<CurveTypeIndex, std::function<void(CurveParams_t<T>)>>;

/*  Curve stepspan  */
using CurveStepspan = unsigned long long int;

/**
 *  KKADSR::Curves constants
 */

const std::map<CurveTypeIndex, std::string> kCurveTypes = {
    {std::make_pair(CurveTypeIndex::Linear, "LINEAR")},
    {std::make_pair(CurveTypeIndex::Logarythmic, "LOGARYTHMIC")}};

/**
 *  KKADR::Curves::Linear
 *
 *  Generates linear transition
 */
template <typename T>
class Linear {
 public:
  using StepType = std::size_t;
  // TODO: [MINOR] Implement constructor taking CurveParams_t (a list of params)
  Linear(const CurveParams_t<T>& params);

  Linear(const T start_value, const T end_value, const CurveStepspan& stepspan,
         const Curves::LinearMode mode);

  /**
   *  KKADR::Curves::Linear::Initialize
   *
   *  Initialize start and end value of the curve, its timespan and monotonicity
   */
  void Initialize(const T start_value, const T end_value,
                  const CurveStepspan& stepspan, const Curves::LinearMode mode);

  T NextValue();

  bool IsLastStep() const;

  void ResetStep();

 private:
  T start_value_ = {};
  T end_value_ = {};
  CurveStepspan stepspan_ = {};
  LinearMode mode_ = {};
  T current_value_ = {};
  T value_delta_ = {};
  StepType step_ = {};
  bool is_last_step_ = {};
};

// TODO: [MINOR] Implement Logarythmic Curve
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