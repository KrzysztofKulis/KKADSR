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

/*  Stage timespan  */
using timespan = std::chrono::microseconds;

/*  Callback function   */
using CallbackFunction = std::function<void()>;

/*  Curve function   */
using CurveFunction = std::function<void()>;

}  // namespace Common
}  // namespace KKADSR

#endif  // KKADSR_COMMON_H
