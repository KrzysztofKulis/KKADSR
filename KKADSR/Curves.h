#pragma once

#include "pch.h"

namespace ADSR {
namespace Curves {
enum class CurveTypeIndex { Linear = 0, Logarythmic };

template <typename T>
using CurveParams_t = std::vector<std::pair<std::string, T>>;

template <typename T>
using CurveType_t =
    std::pair<CurveTypeIndex, std::function<void(CurveParams_t<T>)>>;

template <typename T>
T Linear(CurveParams_t<T> params);

template <typename T>
T Logarythmic(CurveParams_t<T> params);

std::map<std::string, CurveType_t<double>> CurveMap = {
    {"LINEAR",
     {CurveTypeIndex::Linear,
      std::bind(Linear<double>, std::placeholders::_1)}},
    {"LOGARYTHMIC",
     {CurveTypeIndex::Logarythmic,
      std::bind(Logarythmic<double>, std::placeholders::_1)}}};

}  // namespace Curves
}  // namespace ADSR