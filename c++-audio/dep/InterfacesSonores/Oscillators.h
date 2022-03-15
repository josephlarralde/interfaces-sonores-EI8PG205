#pragma once

#include <vector>
#include "oscillator-utils.h"
#include "interpolators.h"

//------------------------------------------------------------------------------
class OscillatorBase {
private:
  float sampleRate;

protected:
  float phase;

public:
  OscillatorBase(float sr = 44100) : sampleRate(sr), phase(0) {}
  virtual ~OscillatorBase() {}

  void setSampleRate(float newSampleRate) {
    sampleRate = newSampleRate;
  }

  virtual float update(float frequency) = 0;

protected:
  void updatePhase(float frequency) {
    phase = getNextPhaseValue(phase, sampleRate, frequency);
  }
};

//------------------------------------------------------------------------------
class SineOscillator : public OscillatorBase {
public:
  SineOscillator(float sr = 44100) : OscillatorBase(sr) {}
  ~SineOscillator() {}

  float update(float frequency) {
    updatePhase(frequency);
    return sin(2 * M_PI * phase);
  }
};

//------------------------------------------------------------------------------
class WaveTableOscillator : public OscillatorBase {
private:
  std::vector<float> table;

public:
  WaveTableOscillator(float sr = 44100, unsigned int tableSize = 512) :
  OscillatorBase(sr) {
    table.resize(tableSize);
    setWaveShape(WaveShape::Sine);
  }

  ~WaveTableOscillator() {}

  void setWaveShape(WaveShape shape, int harmonics = 15) {
    fillWaveTable(&(table[0]), table.size(), shape, harmonics);
  }

  float update(float frequency) {
    updatePhase(frequency);

    float findex = phase * table.size();
    int index = floor(findex);
    float frac = findex - index;
    return interpolateCubic(&(table[0]), table.size(), index, frac);    
  }
};
