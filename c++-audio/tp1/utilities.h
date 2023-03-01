#include <cmath>
#include "interpolators.h"

//------------------------------------------------------------------------------
float getSinusoidValueAtIndex(int i, float sr, float f) {
  // TODO ///////////////////////////////////////////////

  // ...
  
  return 0;

  ///////////////////////////////////////////////////////
}

//------------------------------------------------------------------------------
float getNextPhaseValue(float phase, float sr, float f) {
  // TODO ///////////////////////////////////////////////

  // ...

  return 0;

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
    // TODO ///////////////////////////////////////////////

    // ...

    return 0;

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
