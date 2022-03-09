#include "AudioFile.h"
#include "./utilities.h"

/*
  Exercice :

  Afin de pallier le problème de l'exercice précédent (erreurs d'arrondi des
  valeurs de temps), complétez la fonction getNextPhaseValue dans le fichier
  utilities.h pour obtenir le même résultat, en vous inspirant de la définition
  incrémentale d'un signal sinusoidal exposée dans le support de cours.
*/

//------------------------------------------------------------------------------

int main(int argc, char* argv[]) {
  float duration = 20;
  float sampleRate = 44100;
  float amplitude = 0.2;
  float frequency = 440;
  float phase = 0;

  if (argc > 1) {
    frequency = std::atof(*(argv + 1));
  }

  AudioFile<float> af;
  af.setNumChannels(1);
  af.setNumSamplesPerChannel(sampleRate * duration);

  for (int i = 0; i < af.getNumSamplesPerChannel(); i++) {
    af.samples[0][i] = 0.2 * sin(2 * M_PI * phase);
    phase = amplitude * getNextPhaseValue(phase, sampleRate, frequency);
  }

  af.save("sinusoide-phase.wav", AudioFileFormat::Wave);

  return 0;
}