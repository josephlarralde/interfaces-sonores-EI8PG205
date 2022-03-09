#include "AudioFile.h"
#include "./utilities.h"

/*
  Exercices :

  - Modifiez la fonction fillTable afin de générer une forme d'onde en dents de
    scie à bande limitée à 15 harmoniques, suivant la définition exposée dans le
    support de cours

  - Faites de même avec un forme d'onde en dents de scie
*/

// la fonction fillTable remplit le vecteur en argument
// avec une période de la forme d'onde souhaitée :

void fillTable(std::vector<float>& table) {
  for (int i = 0; i < table.size(); i++) {
    table[i] = sin(2 * M_PI * i / table.size());
  }
}

int main(int argc, char* argv[]) {
  float duration = 5;
  float sampleRate = 44100;
  float amplitude = 0.2;
  float frequency = 440;

  Wavetable osc(sampleRate);
  fillTable(osc.getTable());

  AudioFile<float> af;
  af.setNumChannels(1);
  af.setNumSamplesPerChannel(sampleRate * duration);

  for (int i = 0; i < af.getNumSamplesPerChannel(); i++) {
    af.samples[0][i] = amplitude * osc.getNextValue(frequency);
  }

  af.save("table-d-onde.wav", AudioFileFormat::Wave);
  return 0;
}