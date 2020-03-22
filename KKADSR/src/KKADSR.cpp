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

void Sleep(char key) {
  while (GetKeyState(key) & 0x8000) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}

int main() {
  using namespace KKADSR::ADSR;
  using namespace KKADSR::Curves;
  using template_type = double;

  // Create ADSR object
  KKADSR::ADSR::ADSR<template_type> adsr;

  // Create simple linear stages
  adsr.CreateStage(0, stage_len(10), 0.0, 1.0, LinearMode::Rising);
  adsr.CreateStage(1, stage_len(1000), 1.0, 0.5, LinearMode::Falling);
  adsr.CreateStage(2, stage_len(1000), 0.5, 0.5, LinearMode::Rising);
  adsr.CreateStage(3, stage_len(1000), 0.5, 0.0, LinearMode::Falling);

  using namespace std::experimental;
  auto device = get_default_audio_output_device();
  if (!device) return 1;

  float frequency_hz = 124.0f;
  auto rate = device->get_sample_rate();
  float delta = 2.0f * frequency_hz * float(M_PI / rate);
  float phase = 0;
  bool key = false;

  device->connect([ =, &adsr, &key, &rate, &frequency_hz, &phase, &delta](
      audio_device&, audio_device_io<float> & io) mutable noexcept {
    if (!io.output_buffer.has_value()) return;

    auto& out = *io.output_buffer;

    // update frequency
    if (key) {
      delta = 2.0f * frequency_hz * float(M_PI / rate);
      phase = 0;
      key = false;
    }

    for (int frame = 0; frame < out.size_frames(); ++frame) {
      float next_sample = std::sin(phase);
      phase = std::fmod(phase + delta, 2.0f * static_cast<float>(M_PI));

      for (int channel = 0; channel < out.size_channels(); ++channel) {
        auto f = 0.4f * next_sample;
        auto g = adsr.GetOutput();
        out(frame, channel) = f * g;
      }
    }
  });

  device->start();

  while (true) {
    if (GetKeyState('A') & 0x8000) {
      adsr.Trigger();
      key = true;
      frequency_hz = 130.813f;
      Sleep('A');
    } else if (GetKeyState('S') & 0x8000) {
      adsr.Trigger();
      key = true;
      frequency_hz = 146.832f;
      Sleep('S');
    } else if (GetKeyState('D') & 0x8000) {
      adsr.Trigger();
      key = true;
      frequency_hz = 164.813f;
      Sleep('D');
    } else if (GetKeyState('F') & 0x8000) {
      adsr.Trigger();
      key = true;
      frequency_hz = 174.614f;
      Sleep('F');
    } else if (GetKeyState('G') & 0x8000) {
      adsr.Trigger();
      key = true;
      frequency_hz = 195.997f;
      Sleep('G');
    } else if (GetKeyState('H') & 0x8000) {
      adsr.Trigger();
      key = true;
      frequency_hz = 220.000f;
      Sleep('H');
    } else if (GetKeyState('J') & 0x8000) {
      adsr.Trigger();
      key = true;
      frequency_hz = 246.941f;
      Sleep('J');
    } else if (GetKeyState('K') & 0x8000) {
      adsr.Trigger();
      key = true;
      frequency_hz = 261.625f;
      Sleep('K');
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  return 0;
}