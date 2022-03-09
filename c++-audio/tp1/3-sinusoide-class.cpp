#include "AudioFile.h"
#include "./utilities.h"

/*
  Exercice :

  Complétez la classe Oscillator dans le fichier utilities.h afin d'obtenir le
  même résultat qu'à l'exercice précédent.
*/

//------------------------------------------------------------------------------

int main(int argc, char* argv[]) {
  float duration = 20;
  float sampleRate = 44100;
  float amplitude = 0.2;
  float frequency = 440;

  if (argc > 1) {
    frequency = std::atof(*(argv + 1));
  }

  AudioFile<float> af;
  af.setNumChannels(1);
  af.setNumSamplesPerChannel(sampleRate * duration);

  Oscillator osc(sampleRate);

  for (int i = 0; i < af.getNumSamplesPerChannel(); i++) {
    af.samples[0][i] = amplitude * osc.getNextValue(frequency);
  }

  af.save("sinusoide-class.wav", AudioFileFormat::Wave);

  return 0;
}