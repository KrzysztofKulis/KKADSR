#include "pch/pch.h"

#ifdef _WIN32
#define _USE_MATH_DEFINES
#endif

#ifndef DEBUG_PRINT
#define NDEBUG_PRINT
#endif

#include <math.h>
#include <array>
#include <functional>
#include <thread>
#include "libstdaudio-master/include/audio.h"

#include "ADSR.h"
#include "Common.h"

int main() {
  using namespace KKADSR::ADSR;
  using namespace KKADSR::Curves;
  using template_type = double;

  // Create ADSR object
  KKADSR::ADSR::ADSR<template_type> adsr;

  // Create simple linear stages
  adsr.CreateStage(0, stage_len(5), 0.0, 1.0, LinearMode::Rising);
  adsr.CreateStage(1, stage_len(25), 1.0, 0.5, LinearMode::Falling);
  adsr.CreateStage(2, stage_len(200), 0.5, 0.5, LinearMode::Rising);
  adsr.CreateStage(3, stage_len(25), 0.5, 0.0, LinearMode::Falling);

  // Get output
  do {
    auto output = adsr.GetOutput();
#ifdef DEBUG_PRINT
    std::cout << output << std::endl;
#endif
  } while (adsr.IsOn());

  using namespace std::experimental;
  auto device = get_default_audio_output_device();
  if (!device) return 1;

  float frequency_hz = 124.0f;
  float delta = 2.0f * frequency_hz * float(M_PI / device->get_sample_rate());
  float phase = 0;

  device->connect([ =, &adsr ](audio_device&,
                               audio_device_io<float> & io) mutable noexcept {
    if (!io.output_buffer.has_value()) return;

    auto& out = *io.output_buffer;

    for (int frame = 0; frame < out.size_frames(); ++frame) {
      float next_sample = std::sin(phase);
      phase = std::fmod(phase + delta, 2.0f * static_cast<float>(M_PI));

      for (int channel = 0; channel < out.size_channels(); ++channel) {
        auto f = 0.2f * next_sample;
        auto g = adsr.GetOutput();
        // std::cout << f << ' ' << g << '\n';
        out(frame, channel) = f;
      }
    }
  });

  device->start();
  while (true) {
    if (GetKeyState('s') & 0x8000) {
      if (!adsr.IsOn()) {
        adsr.Trigger();
      }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  return 0;
}