#include "AudioFile.h"
#include "ADSR.h"
#include "./utilities.h"

/*
  Exercice :

  En utilisant la formule de modulation de fréquence avec conservation du timbre
  exposée dans le support de cours, générez un signal harmonique de fréquence
  440 Hz comportant seulement des harmoniques impaires.
*/

int main(int argc, char* argv[]) {
  std::string basename = "synthese-fm";
  float duration = 5;
  float sampleRate = 44100;
  float amplitude = 1;
  float fc = 440;
  float mr = 1;
  float mi = 1;

  if (argc > 1) {
    fc = std::atof(*(argv + 1));

    if (argc > 2) {
      basename = std::string(*(argv + 2));
    }
  }
  AudioFile<float> af;
  af.setNumChannels(1);
  af.setNumSamplesPerChannel(sampleRate * duration);

  Oscillator carrier(sampleRate);
  Oscillator modulator(sampleRate);

  float fm = fc * mr;

  for (int i = 0; i < af.getNumSamplesPerChannel(); i++) {
    // TODO ...
  }

  af.save(basename + ".wav", AudioFileFormat::Wave);

  return 0;
}