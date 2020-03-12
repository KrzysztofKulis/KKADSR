#include "pch.h"
//#include "libstdaudio-master/include/audio_backend/__wasapi_backend.h"

// int main() { return 0; }

#ifdef _WIN32
#define _USE_MATH_DEFINES
#endif

#include <math.h>
#include <array>
#include <thread>
#include "libstdaudio-master/include/audio.h"

//#include "IADSR.h"

int main() {
  //using namespace std::experimental;

  //auto device = get_default_audio_output_device();
  //if (!device) return 1;

  //float frequency_hz = 124.0f;
  //float delta = 2.0f * frequency_hz * float(M_PI / device->get_sample_rate());
  //float phase = 0;

  ////KKADSR::ADSR()

  //device->connect([=](audio_device&,
  //                    audio_device_io<float> & io) mutable noexcept {
  //  if (!io.output_buffer.has_value()) return;

  //  auto& out = *io.output_buffer;

  //  for (int frame = 0; frame < out.size_frames(); ++frame) {
  //    float next_sample = std::sin(phase);
  //    phase = std::fmod(phase + delta, 2.0f * static_cast<float>(M_PI));

  //    // implement example of adsr

  //    for (int channel = 0; channel < out.size_channels(); ++channel)
  //      out(frame, channel) = 0.2f * next_sample;
  //  }
  //});

  //device->start();
  //std::this_thread::sleep_for(std::chrono::seconds(5));
    return 0;
}