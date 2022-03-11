#include "AudioFile.h"
#include "./utilities.h"

/*
  Exercice :

  Complétez la boucle principale de remplissage du tableau af.samples[0] afin
  de générer un signal harmonique comportant 6 partiels dont les amplitudes sont
  définies par a(p) = 0.5 / p, avec p = 1 pour la fréquence fondamentale
*/

int main(int argc, char* argv[]) {
  float duration = 1;
  float sampleRate = 44100;
  float frequency = 440;
  int nbPartials = 6;

  if (argc > 1) {
    frequency = std::atof(*(argv + 1));
  }

  AudioFile<float> af;
  af.setNumChannels(1);
  af.setNumSamplesPerChannel(sampleRate * duration);

  std::vector<Oscillator> oscillators;

  for (int i = 0; i < nbPartials; i++) {
    oscillators.push_back(Oscillator(sampleRate));
  }

  for (int i = 0; i < af.getNumSamplesPerChannel(); i++) {
    // SOLUTION //////////////////////////////////////////

    float val = 0;

    for (int p = 1; p < nbPartials; p++) {
      val += oscillators[p - 1].getNextValue(frequency * p) / p;
    }
    
    af.samples[0][i] = 0.5 * val;

    //////////////////////////////////////////////////////
  }

  af.save("synthese-additive.wav", AudioFileFormat::Wave);

  return 0;
}