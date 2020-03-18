#include "pch/pch.h"

#ifdef _WIN32
#define _USE_MATH_DEFINES
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
  KKADSR::ADSR::ADSR<template_type> adsr;
  adsr.CreateStage(0, stage_len(500), 0.0, 1.0, LinearMode::Rising);
  adsr.CreateStage(1, stage_len(250), 1.0, 0.5, LinearMode::Falling);
  adsr.CreateStage(2, stage_len(2000), 0.5, 0.5, LinearMode::Rising);
  adsr.CreateStage(3, stage_len(500), 0.5, 0.0, LinearMode::Falling);

  do {
  std::cout << adsr.GetOutput() << std::endl;
  } while (adsr.IsOn());

  //using namespace std::experimental;
  //auto device = get_default_audio_output_device();
  //if (!device) return 1;

  //float frequency_hz = 124.0f;
  //float delta = 2.0f * frequency_hz * float(M_PI / device->get_sample_rate());
  //float phase = 0;

  //device->connect([=, &adsr](audio_device&,
  //                    audio_device_io<float> & io) mutable noexcept {
  //  if (!io.output_buffer.has_value()) return;

  //  auto& out = *io.output_buffer;

  //  for (int frame = 0; frame < out.size_frames(); ++frame) {
  //    float next_sample = std::sin(phase);
  //    phase = std::fmod(phase + delta, 2.0f * static_cast<float>(M_PI));

  //    for (int channel = 0; channel < out.size_channels(); ++channel)
  //    {
  //      auto f = 0.2f * next_sample;
  //      auto g = adsr.GetOutput();
  //      //std::cout << f << ' ' << g << '\n';
  //      out(frame, channel) = f;
  //    }
  //  }
  //});

  //device->start();
  //std::this_thread::sleep_for(std::chrono::seconds(5));
  return 0;
}