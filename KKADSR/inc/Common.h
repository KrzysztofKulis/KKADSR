#ifndef KKASDR_COMMON_H
#define KKASDR_COMMON_H

#include "pch/pch.h"

#include <chrono>

#include "Common.h"

namespace KKADSR {
namespace Common {

/**
 *  KKADSR::Common types
 */

/*  Timespan in microseconds */
using timespan_u = std::chrono::microseconds;

/*  Timespan in milliseconds */
using timespan_m = std::chrono::milliseconds;

/*  Callback function   */
using CallbackFunction = std::function<void()>;

/*  Curve function   */
using CurveFunction = std::function<void()>;

/*  Variadic function   */
template <typename... Args>
using VariadicFunction = std::function<void(Args...)>;

}  // namespace Common
}  // namespace KKADSR

#endif  // KKADSR_COMMON_H
