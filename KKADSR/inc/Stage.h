#ifndef KKADSR_STAGE_H
#define KKADSR_STAGE_H

// declare usage of precompiled headers
#ifdef KK_USE_PCH
#include "pch.h"
#else
#include <chrono>
#endif

namespace KKADSR {
namespace Stage {

/**
 *  KKADSR::Stage namespace types
 */

/*  Stage timespan  */
using stage_len = std::chrono::microseconds;

}  // namespace Stage
}  // namespace KKADSR

#endif  // KKADSR_STAGE_H
