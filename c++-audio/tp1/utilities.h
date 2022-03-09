#include <cmath>
#include "interpolators.h"

//------------------------------------------------------------------------------
float getSinusoidValueAtIndex(int i, float sr, float f) {
  // TODO ...
}

//------------------------------------------------------------------------------
float getNextPhaseValue(float phase, float sr, float f) {
  // TODO ...
}

//------------------------------------------------------------------------------
class Oscillator {
private:
  float sr;
  float phase;

public:
  Oscillator(float sampleRate = 44100) :
  sr(sampleRate),
  phase(0) {}

  ~Oscillator() {}

  float getNextValue(float frequency) {
    // TODO ...
  }
};

//------------------------------------------------------------------------------
class Wavetable {
private:
  float sr;
  float phase;
  std::vector<float> table;

public:
  Wavetable(float sampleRate = 44100) :
  sr(sampleRate),
  phase(0) {
    table.resize(512);
  }

  ~Wavetable() {}

  std::vector<float>& getTable() {
    return table;
  }

  float getNextValue(float frequency) {
    phase = getNextPhaseValue(phase, sr, frequency);
    float findex = phase * table.size();
    int index = floor(findex);
    float frac = findex - index;
    return interpolateCubic(&(table[0]), table.size(), index, frac);
  }
};