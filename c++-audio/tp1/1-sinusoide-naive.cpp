#include "AudioFile.h"
#include "./utilities.h"

/*
  Exercice :

  - Afin de générer dans un fichier mono un signal sinusoïdal de fréquence fixe
    f(t) = 440 Hz et d'amplitude fixe a(t) = 0.2 d'une durée de 1 seconde,
    complétez la fonction getSinusoidValueAtIndex dans le fichier utilities.h

  - Écoutez le résultat.

  - Modifiez la variable duration pour générer un fichier de 20 secondes.
  
  - Écoutez à nouveau le résultat. Qu'entendez-vous ?
*/

//------------------------------------------------------------------------------

int main(int argc, char* argv[]) {
  float duration = 20;      // seconds
  float sampleRate = 44100; // Hz
  float amplitude = 0.2;
  float frequency = 440;    // Hz

  if (argc > 1) {
    frequency = std::atof(*(argv + 1));
  }

  AudioFile<float> af;
  af.setNumChannels(1);
  af.setNumSamplesPerChannel(sampleRate * duration);

  for (int i = 0; i < af.getNumSamplesPerChannel(); i++) {
    af.samples[0][i] = amplitude * getSinusoidValueAtIndex(i, sampleRate, frequency);
  }

  af.save("sinusoide-naive.wav", AudioFileFormat::Wave);

  return 0;
}