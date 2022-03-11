#include <cmath>
#include "interpolators.h"

//------------------------------------------------------------------------------
float getSinusoidValueAtIndex(int i, float sr, float f) {
  // SOLUTION ///////////////////////////////////////////

  float t = static_cast<float>(i) / sr;
  return sin(2 * M_PI * f * t);

  ///////////////////////////////////////////////////////
}

//------------------------------------------------------------------------------
float getNextPhaseValue(float phase, float sr, float f) {
  // SOLUTION ///////////////////////////////////////////

  // nbOfSamplesPerPeriod == sr / f
  // phaseIncrement == 1 / nbOfSamplesPerPeriod
  float nextPhase = phase + f / sr;

  if (nextPhase >= 1) {
    nextPhase -= floor(nextPhase); // keep phase between 0 and 1
  } else if (nextPhase < 0) { // this occurs when f < 0
    nextPhase += floor(fabs(phase) + 1);
  }

  return nextPhase;

  ///////////////////////////////////////////////////////
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
    // SOLUTION ///////////////////////////////////////////

    phase = getNextPhaseValue(phase, sr, frequency);
    return sin(2 * M_PI * phase);

    ///////////////////////////////////////////////////////
  }
};

//------------------------------------------------------------------------------
class Wavetable {
private:
  float sr;
  float phase;
  std::vector<float> table;

public:
  Wavetable(float sampleRate = 44100, int tableSize = 512) :
  sr(sampleRate),
  phase(0) {
    table.resize(tableSize);
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
