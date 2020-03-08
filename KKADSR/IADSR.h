#pragma once

#include "pch.h"

#include "Curves.h"

template <typename T>
class IADSR {
 public:
  IADSR(){};
  virtual ~IADSR(){};

  T GetOutput(){};

  virtual void SetStageFunction(const std::string type = "LINEAR");
  virtual void SetStageParam(ADSR::Curves::CurveParams_t params);
  virtual void SetStagesSequence(const int num);

 protected:
};