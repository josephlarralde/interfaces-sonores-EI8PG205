#include "AudioFile.h"
#include "./utilities.h"

/*
  Exercice :

  Générez un signal stéréo créant des battements binauraux de fréquence perçue
  440 Hz et de fréquence de battements 5 Hz.
*/

int main(int argc, char* argv[]) {
  float duration = 10;
  float sampleRate = 44100;
  float amplitude = 0.2;
  float frequency = 440;
  float beating = 5;

  AudioFile<float> af;
  af.setNumChannels(2);
  af.setNumSamplesPerChannel(sampleRate * duration);

  Oscillator osc1(sampleRate);
  Oscillator osc2(sampleRate);

  // SOLUTION ////////////////////////////////////////////

  // on divise la fréquence de battements par 2 pour correspondre
  // au phénomène perçu plutôt qu'à la réalité mathématique (cf. cours 1) :

  beating *= 0.5;

  float fl = frequency + beating;
  float fr = frequency - beating;

  for (int i = 0; i < af.getNumSamplesPerChannel(); i++) {
    af.samples[0][i] = amplitude * osc1.getNextValue(fl);
    af.samples[1][i] = amplitude * osc2.getNextValue(fr);
  }

  ////////////////////////////////////////////////////////

  af.save("battements-binauraux.wav", AudioFileFormat::Wave);

  return 0;
}