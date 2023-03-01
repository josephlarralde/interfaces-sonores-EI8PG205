#include "AudioFile.h"
#include "./utilities.h"

/*
  Exercices :

  - Modifiez la fonction fillTable afin de générer une forme d'onde en dents de
    scie à bande limitée comportant 15 harmoniques, suivant la définition
    exposée dans le support de cours

  - Ajoutez la possibilité de générer une forme d'onde carrée

  - Ajoutez la possibilité de générer une forme d'onde triangle
*/

// la fonction fillTable remplit le vecteur en argument
// avec une période de la forme d'onde souhaitée :

// SOLUTION ////////////////////////////////////////////////////////////////////

enum WaveShape
{
  Sinusoid = 0,
  SawTooth,
  Square,
  Triangle
};

void fillTable(std::vector<float>& table, WaveShape shape, int nbHarmonics = 15)
{
  float phase = 0.f;
  float phaseInc = 1.f / table.size();

  switch (shape) {
    //--------------------------------------------------------------------------
    case WaveShape::Sinusoid:
    {
      for (int i = 0; i < table.size(); i++) {
        table[i] = sin(2 * M_PI * phase);
        phase += phaseInc;
      }
    }
    break;

    // TODO ////////////////////////////////////////////////////////////////////

    //--------------------------------------------------------------------------
    case WaveShape::SawTooth:
    {
      // ...
    }
    break;

    //--------------------------------------------------------------------------
    case WaveShape::Square:
    {
      // ...
    }
    break;

    //--------------------------------------------------------------------------
    case WaveShape::Triangle:
    {
      // ...
    }
    break;

    ////////////////////////////////////////////////////////////////////////////

    //--------------------------------------------------------------------------
    default:
    break;
  }
}

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[]) {
  float duration = 5;
  float sampleRate = 44100;
  float amplitude = 0.2;
  float frequency = 440;

  if (argc > 1) {
    frequency = std::atof(*(argv + 1));
  }

  Wavetable osc(sampleRate);
  fillTable(osc.getTable(), WaveShape::SawTooth);

  AudioFile<float> af;
  af.setNumChannels(1);
  af.setNumSamplesPerChannel(sampleRate * duration);

  for (int i = 0; i < af.getNumSamplesPerChannel(); i++) {
    af.samples[0][i] = amplitude * osc.getNextValue(frequency);
  }

  af.save("table-d-onde.wav", AudioFileFormat::Wave);
  return 0;
}