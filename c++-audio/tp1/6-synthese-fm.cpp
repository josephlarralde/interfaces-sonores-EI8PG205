#include "AudioFile.h"
#include "./utilities.h"

/*
  Exercice :

  En utilisant la formule de modulation de fréquence avec conservation du timbre
  exposée dans le support de cours, générez un signal harmonique de fréquence
  440 Hz comportant seulement des harmoniques impaires.
*/

int main(int argc, char* argv[]) {
  float duration = 5;
  float sampleRate = 44100;
  float amplitude = 1;

  float fc = 440;     // carrier frequency
  float mr = 2;       // modulation ratio
  float fm = fc * mr; // modulation frequency
  float mi = 1;       // modulation index

  AudioFile<float> af;
  af.setNumChannels(1);
  af.setNumSamplesPerChannel(sampleRate * duration);

  Oscillator carrier(sampleRate);
  Oscillator modulator(sampleRate);

  for (int i = 0; i < af.getNumSamplesPerChannel(); i++) {
    // TODO //////////////////////////////////////////////

    // ...
    
    // af.samples[0][i] = ???

    //////////////////////////////////////////////////////
  }

  af.save("synthese-fm.wav", AudioFileFormat::Wave);

  return 0;
}